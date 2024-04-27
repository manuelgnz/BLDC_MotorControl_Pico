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

/* -------------------------- Constants and macros -------------------------- */

/** Timer alarm number. */
#define ALARM_NUM 0

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
    pwmSlices_t pwmSlices;
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
