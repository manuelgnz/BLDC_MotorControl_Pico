/* =================================================================================
File name:        SPEED_FR.H  
===================================================================================*/


#ifndef __SPEED_FR_H__
#define __SPEED_FR_H__

#include <stdint.h>

typedef struct {
       float ElecTheta;  		// Input: Electrical angle (pu)
       uint32_t DirectionQep; // Variable: Direction of rotation (Q0) - independently with global Q
       float OldElecTheta;   	// History: Electrical angle at previous step (pu)
       float Speed;       	// Output: Speed in per-unit  (pu)
       float BaseRpm;      // Parameter: Base speed in rpm (Q0) - independently with global Q
       float K1;         	// Parameter: Constant for differentiator (Q21) - independently with global Q
       float K2;         		// Parameter: Constant for low-pass filter (pu)
       float K3;         		// Parameter: Constant for low-pass filter (pu)
       int32_t SpeedRpm;      // Output : Speed in rpm  (Q0) - independently with global Q
       float Tmp;				//Variable: Temp variable
       } SPEED_MEAS_QEP;   	// Data type created

/*-----------------------------------------------------------------------------
Default initalizer for the SPEED_MEAS_QEP object.
-----------------------------------------------------------------------------*/                     
#define SPEED_MEAS_QEP_DEFAULTS   { 0, \
                                    1, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
                               	  }	

/*------------------------------------------------------------------------------
 SPEED_FR Macro Definition
------------------------------------------------------------------------------*/

#ifdef TEST
       static void SPEED_FR_MACRO(SPEED_MEAS_QEP * v);
#endif

static inline void SPEED_FR_MACRO(SPEED_MEAS_QEP * v)
{
    /* Differentiator */
    /* Synchronous speed computation */
    v->Tmp = v->ElecTheta - v->OldElecTheta;
    if (v->Tmp < -0.5)
        v->Tmp = v->Tmp + 1.0;
    else if (v->Tmp > 0.5)
        v->Tmp = v->Tmp - 1.0;
    v->Tmp = v->K1 * v->Tmp;

    /* Low-pass filter */
    /* Q21 = GLOBAL_Q*Q21 + GLOBAL_Q*Q21 */
    v->Tmp = v->K2 * v->Speed + v->K3 * v->Tmp;

    /* Saturate the output */
    /*v->Tmp=_IQsat(v->Tmp,_IQ21(1),_IQ21(-1));    */
    if(v->Tmp > 1) v->Tmp = 1;
    if(v->Tmp < -1) v->Tmp = -1;
    v->Speed = v->Tmp;

    /* Update the electrical angle */
    v->OldElecTheta = v->ElecTheta;

    /* Change motor speed from pu value to rpm value (GLOBAL_Q -> Q0) */
    /* Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q */
    v->SpeedRpm = v->BaseRpm * v->Speed;

}

//#define SPEED_FR_MACRO(v)											\
///* Differentiator*/													\
///* Synchronous speed computation   */								\
//   v.Tmp = v.ElecTheta - v.OldElecTheta;		                    \
//   if (v.Tmp < -0.5)			                                        \
//     v.Tmp = v.Tmp + 1.0;                                           \
//   else if (v.Tmp > 0.5)			                                \
//     v.Tmp = v.Tmp - 1.0;                                           \
//   v.Tmp = v.K1 * v.Tmp;		                                    \
///* Low-pass filter*/												\
///* Q21 = GLOBAL_Q*Q21 + GLOBAL_Q*Q21*/								\
//   	v.Tmp = v.K2 * v.Speed + v.K3 * v.Tmp;		                    \
///* Saturate the output */											\
//	/*v.Tmp=_IQsat(v.Tmp,_IQ21(1),_IQ21(-1));	*/				    \
//    if(v.Tmp > 1) v.Tmp = 1;                                        \
//    if(v.Tmp < -1) v.Tmp = -1;                                      \
//	v.Speed = v.Tmp;										        \
///* Update the electrical angle */									\
//    v.OldElecTheta = v.ElecTheta;									\
///* Change motor speed from pu value to rpm value (GLOBAL_Q -> Q0)*/	\
///* Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q*/					\
//    v.SpeedRpm = v.BaseRpm * v.Speed;

#endif // __SPEED_FR_H__
