/* =================================================================================
File name:        RAMPGEN.H  
===================================================================================*/

#ifndef __RAMPGEN_H__
#define __RAMPGEN_H__

#include <stdint.h>

typedef struct { float  Freq; 		// Input: Ramp frequency (pu)
		 	     float  StepAngleMax;	// Parameter: Maximum step angle (pu)
	 	 	     float  Angle;		// Variable: Step angle (pu)
			     float  Gain;			// Input: Ramp gain (pu)
			     float  Out;  	 	// Output: Ramp signal (pu)
			     float  Offset;		// Input: Ramp offset (pu)
	  	  	   } RAMPGEN;	            

/*------------------------------------------------------------------------------
      Object Initializers
------------------------------------------------------------------------------*/                       
#define RAMPGEN_DEFAULTS {0,		\
						  0,		\
						  0,		\
						  1,	    \
						  0,		\
						  1, 	    \
                         }

/*------------------------------------------------------------------------------
	RAMP(Sawtooh) Generator Macro Definition
------------------------------------------------------------------------------*/                                               

#ifdef TEST
	  	  	static void RG_MACRO(RAMPGEN * v);
#endif


static inline void RG_MACRO(RAMPGEN * v)
{
    /* Compute the angle rate */
    v->Angle += v->StepAngleMax * v->Freq;

    /* Saturate the angle rate within (-1,1) */
    if (v->Angle > 1.0)
        v->Angle -= 1.0;
    else if (v->Angle < -1.0)
        v->Angle += 1.0;
    v->Out = v->Angle;

}

#endif // __RAMPGEN_H__
