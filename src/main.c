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
#include <hardware/pwm.h>
#include <system.h>

/* -------------------------- Constants and macros -------------------------- */

/* ------------------------------- Public code ------------------------------ */

int main(void)
{
    systemInit();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    setPwmDutyCycle(bldcSystem.pwmSlices.pwm1Slice, 0.5f);
    setPwmDutyCycle(bldcSystem.pwmSlices.pwm2Slice, 0.5f);
    setPwmDutyCycle(bldcSystem.pwmSlices.pwm3Slice, 0.5f);
    setPwmDutyCycle(bldcSystem.pwmSlices.pwmDac1Slice, 0.5f);
    setPwmDutyCycle(bldcSystem.pwmSlices.pwmDac2Slice, 0.5f);
    
    //Infinite loop
    while(1)
    {
        gpio_put(25, 1);
        sleep_ms(500);
        gpio_put(25,0);
        sleep_ms(500);
    }    
}

/* ------------------------------- End of file ------------------------------ */
