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
#include <system.h>
#include <debug.h>
#include <sysTime.h>
#include <board.h>

/* -------------------------- Constants and macros -------------------------- */

/* ------------------------------ Private data ------------------------------ */

/* ------------------------------- Public code ------------------------------ */

int main(void)
{
    systemInit();

    setPwmDutyCycle(bldcSystem.pwmSlices.pwm1Slice, 0.8f);
    setPwmDutyCycle(bldcSystem.pwmSlices.pwm2Slice, 0.5f);
    setPwmDutyCycle(bldcSystem.pwmSlices.pwm3Slice, 0.5f);
    setPwmDutyCycle(bldcSystem.pwmSlices.pwmDac1Slice, 0.5f);
    setPwmDutyCycle(bldcSystem.pwmSlices.pwmDac2Slice, 0.5f);

    delay_t delayCycle1;
    delay_t delayCycle2;
    delayInit(&delayCycle1, 1000);   // 1 ms
    delayInit(&delayCycle2, 500000); // 0.5 s
    
    //Infinite loop
    while(1)
    {
        if (delayElapsedTime(&delayCycle1))
        {
            gpio_xor_mask(1 << TEST0_GPIO);
        }

        if (delayElapsedTime(&delayCycle2))
        {
            uint64_t ticks = time_us_64();

            char s[20U];
            sprintf(s, "Ticks: %llu \r\n", ticks);
            // Send out a string, with CR/LF conversions
            uart_puts(UART_ID, s);

            // Toggle LED
            gpio_xor_mask(1 << BOARD_LED_GPIO);
        }
    }    
}

/* ------------------------------- End of file ------------------------------ */
