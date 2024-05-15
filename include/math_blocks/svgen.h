/* =================================================================================
File name:       SVGEN.H  
===================================================================================*/


#ifndef __SVGEN_H__
#define __SVGEN_H__

#include <stdint.h>

typedef struct 	{ float  Ualpha; 			// Input: reference alpha-axis phase voltage
				  float  Ubeta;			// Input: reference beta-axis phase voltage
				  float  Ta;				// Output: reference phase-a switching function
				  float  Tb;				// Output: reference phase-b switching function
				  float  Tc;				// Output: reference phase-c switching function
				  float  tmp1;			// Variable: temp variable
				  float  tmp2;			// Variable: temp variable
				  float  tmp3;			// Variable: temp variable
				  uint16_t VecSector;		// Space vector sector
				} SVGEN;
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				

/*-----------------------------------------------------------------------------
Default initalizer for the SVGEN object.
-----------------------------------------------------------------------------*/                     
#define SVGEN_DEFAULTS { 0,0,0,0,0 }                       

/*------------------------------------------------------------------------------
	Space Vector  Generator (SVGEN) Macro Definition
------------------------------------------------------------------------------*/

#ifdef TEST
				static void SVGENDQ_MACRO(SVGEN * v);
#endif


static inline void SVGENDQ_MACRO(SVGEN * v)
{
    v->tmp1 = v->Ubeta;
    v->tmp2 = (v->Ubeta) * 0.5 + 0.866 * v->Ualpha;
    v->tmp3 = v->tmp2 - v->tmp1;

    v->VecSector = 3;
    v->VecSector = (v->tmp2 > 0) ? (v->VecSector - 1) : v->VecSector;
    v->VecSector = (v->tmp3 > 0) ? (v->VecSector - 1) : v->VecSector;
    v->VecSector = (v->tmp1 < 0) ? (7 - v->VecSector) : v->VecSector;

    if (v->VecSector == 1 || v->VecSector == 4)
    {
        v->Ta = v->tmp2;
        v->Tb = v->tmp1 - v->tmp3;
        v->Tc = -v->tmp2;
    }
    else if (v->VecSector == 2 || v->VecSector == 5)
    {
        v->Ta = v->tmp3 + v->tmp2;
        v->Tb = v->tmp1;
        v->Tc = -v->tmp1;
    }
    else
    {
        v->Ta = v->tmp3;
        v->Tb = -v->tmp3;
        v->Tc = -(v->tmp1 + v->tmp2);
    }

}

//#define SVGENDQ_MACRO(v)														\
//	v.tmp1= v.Ubeta;															\
//	v.tmp2= (v.Ubeta)*0.5 + 0.866 * v.Ualpha;					                \
//    v.tmp3= v.tmp2 - v.tmp1;													\
//																				\
//	v.VecSector=3;																\
//	v.VecSector=(v.tmp2> 0)?( v.VecSector-1):v.VecSector;						\
//	v.VecSector=(v.tmp3> 0)?( v.VecSector-1):v.VecSector;						\
//	v.VecSector=(v.tmp1< 0)?(7-v.VecSector) :v.VecSector;						\
//																				\
//	if     (v.VecSector==1 || v.VecSector==4)                                   \
//      {     v.Ta= v.tmp2; 														\
//      		v.Tb= v.tmp1-v.tmp3; 												\
//      		v.Tc=-v.tmp2;														\
//      }								    										\
//   																				\
//    else if(v.VecSector==2 || v.VecSector==5)                                   \
//      {     v.Ta= v.tmp3+v.tmp2; 												\
//      		v.Tb= v.tmp1; 														\
//      		v.Tc=-v.tmp1;														\
//      }																	   		\
//   																				\
//    else                                                                        \
//      {     v.Ta= v.tmp3; 														\
//      		v.Tb=-v.tmp3; 														\
//      		v.Tc=-(v.tmp1+v.tmp2);												\
//      }																	   		\
//																				\

#endif // __SVGEN_H__
