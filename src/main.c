/**
 * @file main.c
 * @brief Main source file where the init and tasks take place.
 * 
 * @version aa
 * @date 25 Apr 2024
 * @author manuelgnzmunoz@gmail.com
 */

/* -------------------------------- Includes -------------------------------- */

#include <pico/stdlib.h>
#include <stdio.h>
#include <hardware/pwm.h>
#include <hardware/adc.h>
#include <system.h>
#include <debug.h>
#include <sysTime.h>
#include <board.h>
#include <bldcAdc.h>

/* -------------------------- Constants and macros -------------------------- */

/* ------------------------------ Private data ------------------------------ */

/* ------------------------------- Public code ------------------------------ */

int main(void)
{
    systemInit();

    debugInit();

    setPwmDutyCycle(bldcSystem.pwmSlices.pwm1Slice, 0.1f);
    setPwmDutyCycle(bldcSystem.pwmSlices.pwm2Slice, 0.5f);
    setPwmDutyCycle(bldcSystem.pwmSlices.pwm3Slice, 0.5f);
    setPwmDutyCycle(bldcSystem.pwmSlices.pwmDac1Slice, 0.5f);
    setPwmDutyCycle(bldcSystem.pwmSlices.pwmDac2Slice, 0.5f);

    delay_t delayCycle1;
    delay_t delayCycle2;
    delayInit(&delayCycle1, 1000);   // 1 ms
    delayInit(&delayCycle2, 1000000); // 1 s
    
    //Infinite loop
    while(1)
    {
        if (delayElapsedTime(&delayCycle1))
        {
            /* do nothing */
        }

        if (delayElapsedTime(&delayCycle2))
        {
            uint64_t ticks = time_us_64();

            #ifdef ADC_BLOCKING
            adc_select_input(PHASE_A_CURRENT_GPIO - 26U);
            adc26 = adc_read();
            adc_select_input(PHASE_B_CURRENT_GPIO - 26U);
            adc27 = adc_read();
            #else
            adcSwTrigger();    
            #endif
            // Toggle LED
            gpio_xor_mask(1 << BOARD_LED_GPIO);
        }

        debugInfo(&sciHandler);
    }    
}

/* ------------------------------- End of file ------------------------------ */
