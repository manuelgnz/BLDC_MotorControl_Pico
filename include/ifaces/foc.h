/**
 * @file foc.h
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

#ifndef FOC_H
#define FOC_H

/* -------------------------------- Includes -------------------------------- */

// Include header for the PARK object
#include <math_blocks/park.h>
// Include header for the IPARK object
#include <math_blocks/ipark.h>
// Include header for the CLARKE object
#include <math_blocks/clarke.h>
// Include header for the speed object
#include <math_blocks/speed_fr.h>
 // Include header for the SVGENDQ object
#include <math_blocks/svgen.h>
// Include header for the RAMPGEN object
#include <math_blocks/rampgen.h>
// Include header for the RMPCNTL object
#include <math_blocks/rmp_cntl.h>
// Include header for the PI object
#include <math_blocks/pi.h>
// Include header for the PID object
#include <math_blocks/pid_grando.h>

/* -------------------------- Constants and macros -------------------------- */

/** FOC frequency. */
#define FOC_FREQUENCY   20

/** FOC period in us. */
#define FOC_PERIOD      ((1.0f/((float)FOC_FREQUENCY))*1000.0f)

/* ---------------------------------- Types --------------------------------- */

//------------------------------------------
// FOC structures declaration
//------------------------------------------
typedef struct {
    // Flag activated when FOC ISR is attended
    uint16_t isrFlag;
    // FOC enable switch
    uint16_t enable;
    // Logic switch
    uint16_t lsw;
    // Working Level: 0-Open Loop   1-Speed Loop    2-PositionLoop
    uint16_t level;
    // Foc Interrupt ticker for debugging purposes
    uint32_t IsrTicker;
    // Init Theta
    float initTheta;
    // Raw Theta
    float rawTheta;
    // Rotor Electrical angle
    float rotElecTheta;
    // Actuator Mechanical angle
    float rotMechTheta;
    // Speed Reference
    float speedRef;
    //  Id reference (pu)
    float idRef;
    //  Iq reference (pu)
    float iqRef;
    //
    SPEED_MEAS_QEP speed1;
    //  Instance a Space Vector PWM modulator
    SVGEN svgen1;
    //  Instance Clarke Transform
    CLARKE clarke1;
    //  Instance Park Transform
    PARK park1;
    //  Instance Reverse Park Transform
    IPARK ipark1;
    //
    PID_CONTROLLER pid_spd;
    //
    PI_CONTROLLER pi_id;
    //
    PI_CONTROLLER pi_iq;
    //  Instance a ramp controller to smoothly ramp the frequency
    RMPCNTL rc1;
    //  Instance a ramp generator to simulate an Angle
    RAMPGEN rg1;
} foc_t;

/* ------------------------------- Public data ------------------------------ */

/* ------------------------- Public code prototypes ------------------------- */

/**
 * @brief FOC.
 */
void foc(void);

#endif // FOC_H

/* ------------------------------- End of file ------------------------------ */
