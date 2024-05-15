/* =================================================================================
File name:       PI.H 
===================================================================================*/


#ifndef __PI_H__
#define __PI_H__

typedef struct {  float  Ref;   			// Input: reference set-point
				  float  Fbk;   			// Input: feedback
				  float  Out;   			// Output: controller output
				  float  Kp;				// Parameter: proportional loop gain
				  float  Ki;			    // Parameter: integral gain
				  float  Umax;			// Parameter: upper saturation limit
				  float  Umin;			// Parameter: lower saturation limit
				  float  up;				// Data: proportional term
				  float  ui;				// Data: integral term
				  float  v1;				// Data: pre-saturated controller output
				  float  i1;				// Data: integrator storage: ui(k-1)
				  float  w1;				// Data: saturation record: [u(k-1) - v(k-1)]
				} PI_CONTROLLER;


/*-----------------------------------------------------------------------------
Default initalisation values for the PI_GRANDO objects
-----------------------------------------------------------------------------*/                     

#define PI_CONTROLLER_DEFAULTS {	\
						   0, 		\
                           0, 		\
						   0, 		\
                           (1.0),	\
                           (0.0),	\
                           (1.0),	\
                           (-1.0), 	\
                           (0.0),	\
                           (0.0), 	\
                           (0.0),	\
                           (0.0),	\
                           (1.0) 	\
              			  }

/*------------------------------------------------------------------------------
	PI_GRANDO Macro Definition
------------------------------------------------------------------------------*/

#ifdef TEST
				static void PI_MACRO(PI_CONTROLLER * v);
#endif

static inline void PI_MACRO(PI_CONTROLLER * v)
{
    /* proportional term */
    v->up = v->Kp * (v->Ref - v->Fbk);

    /* integral term */
    v->ui = (v->Out == v->v1) ? (v->Ki * v->up + v->i1) : v->i1;
    v->i1 = v->ui;

    /* control output */
    v->v1 = v->up + v->ui;
    /*v->Out = _IQsat(v->v1, v->Umax, v->Umin); */
    v->Out = v->v1;
    if (v->Out > v->Umax)
        v->Out = v->Umax;
    if (v->Out < v->Umin)
        v->Out = v->Umin;
    //v->w1 = (v->Out == v->v1) ? _IQ(1.0) : _IQ(0.0);
}

//#define PI_MACRO(v)												\
//																\
//	/* proportional term */ 									\
//	v.up = v.Kp * (v.Ref - v.Fbk);						        \
//																\
//	/* integral term */ 										\
//	v.ui = (v.Out == v.v1)?(v.Ki * v.up+ v.i1) : v.i1;	        \
//	v.i1 = v.ui;												\
//																\
//	/* control output */ 										\
//	v.v1 = v.up + v.ui;											\
//	/*v.Out= _IQsat(v.v1, v.Umax, v.Umin);	*/					\
//	v.Out = v.v1;                                               \
//	if(v.Out > v.Umax)                                          \
//	    v.Out = v.Umax;                                         \
//	if(v.Out < v.Umin)                                          \
//		v.Out = v.Umin;                                         \
//	//v.w1 = (v.Out == v.v1) ? _IQ(1.0) : _IQ(0.0);				\

// ***********************************************************************************
//   This macro works with angles as inputs, hence error is rolled within -pi to +pi
// ***********************************************************************************
#define PI_POS_MACRO(v)                                         \
    /* proportional term */                                     \
    v.up = v.Ref - v.Fbk;                                       \
    v.up = v.Kp * v.up;                                         \
/*  if (v.up >= _IQ(0.5))
      v.up -= _IQ(1.0);
    else if (v.up <= _IQ(-0.5))
      v.up += _IQ(1.0); */                                      \
                                                                \
    /* integral term */                                         \
    v.ui = (v.Out == v.v1)?(v.Ki * v.up+ v.i1) : v.i1;          \
    v.i1 = v.ui;                                                \
                                                                \
    /* control output */                                        \
    /*if(v.w1)  */                                              \
    /*v.v1 = v.up;  */                                          \
    /*else  */                                                  \
    v.v1 = v.up + v.ui;                                         \
                                                                \
    v.Out = v.v1;                                               \
    if(v.Out > v.Umax)                                          \
        v.Out = v.Umax;                                         \
    if(v.Out < v.Umin)                                          \
        v.Out = v.Umin;                                         \
    //v.w1 = (v.Out == v.v1) ? _IQ(1.0) : _IQ(0.0);             \


#endif // __PI_H__

