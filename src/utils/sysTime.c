/**
 * @file template.c
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

/* -------------------------------- Includes -------------------------------- */

#include <sysTime.h>

/* -------------------------- Constants and macros -------------------------- */


/* ---------------------------------- Types --------------------------------- */

/* ------------------------------- Public data ------------------------------ */


/* ------------------------------ Private data ------------------------------ */


/* ------------------------- Private code prototypes ------------------------ */


/* ------------------------------- Public code ------------------------------ */

delay_t * delayInit(delay_t * delay, uint64_t time)
{
    delay->currentTime = time_us_64();
    delay->previousTime = delay->currentTime;
    delay->interval = time;
    return delay;
}

uint16_t delayElapsedTime(delay_t * delay)
{
    uint16_t hasDelayElapsed = 0;

    delay->currentTime = time_us_64();
    if ((delay->currentTime - delay->previousTime) >= (delay->interval))
    {
        // Bug fixing: Actualize the previous time with the current time in order to not accumulate
        // true conditions when delayElapsedTime function is not called.
        delay->previousTime = delay->currentTime;
        // Increments the previous time with the interval time to have always the same interval
        // even if this function is called some time after the interval time have achieved
        //delay->previousTime += delay->interval;
        hasDelayElapsed = 1;
    }

    return (hasDelayElapsed);
}

void delayEnd(delay_t * delay)
{
    delay->previousTime = time_us_64() - delay->interval;
}

/* ------------------------------ Private code ------------------------------ */


/* ------------------------------- End of file ------------------------------ */
