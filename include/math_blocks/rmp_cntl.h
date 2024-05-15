/* =================================================================================
File name:        RMP_CNTL.H  
===================================================================================*/
#ifndef __RMP_CNTL_H__
#define __RMP_CNTL_H__

#include <math.h>

typedef struct { float      TargetValue; 	// Input: Target input (pu)
				 uint32_t     RampDelayMax;	// Parameter: Maximum delay rate (Q0) - independently with global Q
		 	 	 float      RampLowLimit;	// Parameter: Minimum limit (pu)
				 float      RampHighLimit;	// Parameter: Maximum limit (pu)
				 uint32_t     RampDelayCount; // Variable: Incremental delay (Q0) - independently with global Q
				 float      SetpointValue;	// Output: Target output (pu)
				 uint32_t     EqualFlag;		// Output: Flag output (Q0) - independently with global Q
				 float	    Tmp;			// Variable: Temp variable
		  	   } RMPCNTL;	            


/*-----------------------------------------------------------------------------
Default initalizer for the RMPCNTL object.
-----------------------------------------------------------------------------*/                     
#define RMPCNTL_DEFAULTS {  0,      \
                            5,      \
                           -1,      \
                            1,      \
                            0,      \
                          	0,      \
                          	0,      \
                          	0,      \
                   		  }

/*------------------------------------------------------------------------------
 	RAMP Controller Macro Definition
------------------------------------------------------------------------------*/

#ifdef TEST
		  	 static void RC_MACRO(RMPCNTL * v);
#endif

static inline void RC_MACRO(RMPCNTL * v)
{
    v->Tmp = v->TargetValue - v->SetpointValue;
    /* 0.0000305 is resolution of Q15 */
    if (fabs(v->Tmp) >= 0.0000305) {
        v->RampDelayCount++;
        if (v->RampDelayCount >= v->RampDelayMax) {
            if (v->TargetValue >= v->SetpointValue)
                v->SetpointValue += 0.0000305;
            else
                v->SetpointValue -= 0.0000305;

            if (v->SetpointValue > v->RampHighLimit)
                v->SetpointValue = v->RampHighLimit;
            if (v->SetpointValue < v->RampLowLimit)
                v->SetpointValue = v->RampLowLimit;

            v->RampDelayCount = 0;
        }
    } else {
        v->EqualFlag = 0x7FFFFFFF;
    }

}

//#define RC_MACRO(v)																	\
//	v.Tmp = v.TargetValue - v.SetpointValue;										\
///*  0.0000305 is resolution of Q15 */												\
//if (fabs(v.Tmp) >= 0.0000305)				    							        \
//{																					\
//	v.RampDelayCount++	;															\
//		if (v.RampDelayCount >= v.RampDelayMax)										\
//		{																			\
//			if (v.TargetValue >= v.SetpointValue)									\
//				v.SetpointValue += 0.0000305;									    \
//			else																	\
//				v.SetpointValue -= 0.0000305;									    \
//																					\
//			if(v.SetpointValue > v.RampHighLimit)                                   \
//			    v.SetpointValue = v.RampHighLimit;                                  \
//			if(v.SetpointValue < v.RampLowLimit)                                    \
//			    v.SetpointValue = v.RampLowLimit;                                   \
//			                                                                        \
//			v.RampDelayCount = 0;													\
//																					\
//		}																			\
//}																					\
//else v.EqualFlag = 0x7FFFFFFF;

#endif // __RMP_CNTL_H__
