/**
 * @file template.h
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

#ifndef SYSTIME_H
#define SYSTIME_H

/* -------------------------------- Includes -------------------------------- */

#include <pico/stdlib.h>

/* -------------------------- Constants and macros -------------------------- */

/** Size of the time counters array. */
#define TIME_COUNTERS_SIZE   10U                    

/* ---------------------------------- Types --------------------------------- */

/** @brief Delay timer struct. */
typedef struct
{
    uint64_t previousTime;
    uint64_t currentTime;
    uint64_t interval;
} delay_t;

/* ------------------------------- Public data ------------------------------ */

/* ------------------------- Public code prototypes ------------------------- */

/**
 * 
*/
delay_t * delayInit(delay_t * delay, uint64_t time);

/**
 * 
*/
uint16_t delayElapsedTime(delay_t * delay);

/**
 * 
*/
void delayEnd(delay_t * delay);

#endif // SYSTIME_H

/* ------------------------------- End of file ------------------------------ */
