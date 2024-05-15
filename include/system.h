/**
 * @file template.h
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

#ifndef SYSTEM_H
#define SYSTEM_H

/* -------------------------------- Includes -------------------------------- */

#include <stdint.h>
#include <foc.h>
#include <trace.h>

/* -------------------------- Constants and macros -------------------------- */

/** Timer alarm number. */
#define ALARM_NUM 0

//---------------------------------------------------------------------------------------
//                  |  ROTOR POSITION   |   CURRENTS FEEDBACK   |   POSITION FEEDBACK   |
//---------------------------------------------------------------------------------------
// OPEN_LOOP        |                   |                       |                       |
// CLOSE_LOOP       |         X         |           X           |                       |
// SPEED_LOOP       |         X         |           X           |           X           |
// POSITION_LOOP    |         X         |           X           |           X           |
//---------------------------------------------------------------------------------------

/** PWM Output manually managed. */
#define MANUAL_PWM                  0

/** Rotor position estimation (RG_MACRO) and no currents feedback. */
#define OPEN_LOOP                   1

/** Rotor position read by resolver driver and no currents feedback. */   
#define CLOSE_LOOP                  2

/** Rotor position read by resolver driver and currents feedback. */
#define SPEED_LOOP                  3

/** Rotor position read by resolver driver, currents feedback and RVDT position feedback, manual set point. */
#define POSITION_LOOP_FOLLOW_UP     4

/** Rotor position read by resolver driver, currents feedback and RVDT position feedback, set point given by load cell. */
#define POSITION_LOOP_FORCE_CONTROL 5

/* ---------------------------------- Types --------------------------------- */

typedef struct
{
    uint8_t pwm1Slice;
    uint8_t pwm2Slice;
    uint8_t pwm3Slice;
    uint8_t pwmDac1Slice;
    uint8_t pwmDac2Slice;
} pwmSlices_t;

typedef struct
{
    float setPoint;
    pwmSlices_t pwmSlices;
    foc_t * foc;
} bldcSystem_t;

/* ------------------------------- Public data ------------------------------ */

/** Global system variable containing handlers and data. */
extern bldcSystem_t bldcSystem;

/* ------------------------- Public code prototypes ------------------------- */

/**
 * @brief System init.
 */
void systemInit(void);

/**
 * @brief System init.
 * 
 * @param[in] slice Selected slice to change duty cycle.
 * @param[in] dutyCycle Selected duty cycle.
 */
void setPwmDutyCycle(uint8_t slice, float dutyCycle);

#endif // SYSTEM_H

/* ------------------------------- End of file ------------------------------ */
