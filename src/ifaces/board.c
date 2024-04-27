/**
 * @file template.c
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

/* -------------------------------- Includes -------------------------------- */

#include <board.h>
#include <pico/stdlib.h>

/* -------------------------- Constants and macros -------------------------- */

/* ---------------------------------- Types --------------------------------- */

/* ------------------------------- Public data ------------------------------ */

/* ------------------------------ Private data ------------------------------ */

/* ------------------------- Private code prototypes ------------------------ */

/* ------------------------------- Public code ------------------------------ */

void gpioInit(void)
{
    // LED
    gpio_set_dir(25, GPIO_IN);
    gpio_put(25, 0);
    gpio_set_function(25, GPIO_FUNC_SIO);
    gpio_set_dir(25, GPIO_OUT);

    // PWM
    gpio_set_function(PWM1_A, GPIO_FUNC_PWM);
    gpio_set_function(PWM1_B, GPIO_FUNC_PWM);
    gpio_set_function(PWM2_A, GPIO_FUNC_PWM);
    gpio_set_function(PWM2_B, GPIO_FUNC_PWM);
    gpio_set_function(PWM3_A, GPIO_FUNC_PWM);
    gpio_set_function(PWM3_B, GPIO_FUNC_PWM);
    gpio_set_function(PWM_DAC_1, GPIO_FUNC_PWM);
    gpio_set_function(PWM_DAC_2, GPIO_FUNC_PWM);
}

/* ------------------------------ Private code ------------------------------ */

/* ------------------------------- End of file ------------------------------ */
