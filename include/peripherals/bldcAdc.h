/**
 * @file bldcAdc.h
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

#ifndef BLDCADC_H
#define BLDCADC_H

/* -------------------------------- Includes -------------------------------- */

#include <hardware/adc.h>

/* -------------------------- Constants and macros -------------------------- */

/* ---------------------------------- Types --------------------------------- */

/* ------------------------------- Public data ------------------------------ */

extern uint16_t adc26;

extern uint16_t adc27;

/* ------------------------- Public code prototypes ------------------------- */

/**
 * @brief Trigger ADC reading by SW in a non blocking way.
 */
void adcSwTrigger(void);

/**
 * @brief ADC ISR.
 */
void adcIsr(void);

#endif // BLDCADC_H

/* ------------------------------- End of file ------------------------------ */
