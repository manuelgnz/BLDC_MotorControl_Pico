/**
 * @file foc.c
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

/* -------------------------------- Includes -------------------------------- */

#include <foc.h>
#include <hardware/timer.h>
#include <system.h>
#include <pico/stdlib.h>

/* -------------------------- Constants and macros -------------------------- */

/* ---------------------------------- Types --------------------------------- */


/* ------------------------------- Public data ------------------------------ */


/* ------------------------------ Private data ------------------------------ */


/* ------------------------- Private code prototypes ------------------------ */


/* ------------------------------- Public code ------------------------------ */

void foc(void)
{
    // Clear the alarm irq
    hw_clear_bits(&timer_hw->intr, 1u << ALARM_NUM);
    // Reset the alarm register
    timer_hw->alarm[ALARM_NUM] = timer_hw->timerawl + FOC_PERIOD ;
}

/* ------------------------------ Private code ------------------------------ */


/* ------------------------------- End of file ------------------------------ */
