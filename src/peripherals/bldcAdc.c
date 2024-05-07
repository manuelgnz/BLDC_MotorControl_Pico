/**
 * @file bldcAdc.c
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

/* -------------------------------- Includes -------------------------------- */

#include <bldcAdc.h>
#include <board.h>

/* -------------------------- Constants and macros -------------------------- */

/* ---------------------------------- Types --------------------------------- */


/* ------------------------------- Public data ------------------------------ */

uint16_t adc26 = 0U;

uint16_t adc27 = 0U;

/* ------------------------------ Private data ------------------------------ */


/* ------------------------- Private code prototypes ------------------------ */


/* ------------------------------- Public code ------------------------------ */

void adcSwTrigger(void)
{
    hw_set_bits(&adc_hw->cs, ADC_CS_START_ONCE_BITS);
}

void adcIsr(void)
{
    static uint8_t nextAdc = 0U;
    
    if (nextAdc == 0U)
    {
        adc26 = adc_fifo_get();
        adc_select_input(PHASE_B_CURRENT_GPIO - 26U);
    }
    else
    {
        adc27 = adc_fifo_get();
        adc_select_input(PHASE_A_CURRENT_GPIO - 26U);
    }

    nextAdc ^= 1U;    

    gpio_xor_mask(1 << TEST0_GPIO);
}

/* ------------------------------ Private code ------------------------------ */


/* ------------------------------- End of file ------------------------------ */
