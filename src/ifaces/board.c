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
#include "hardware/adc.h"

/* -------------------------- Constants and macros -------------------------- */

/* ---------------------------------- Types --------------------------------- */

/* ------------------------------- Public data ------------------------------ */

/* ------------------------------ Private data ------------------------------ */

/* ------------------------- Private code prototypes ------------------------ */

/* ------------------------------- Public code ------------------------------ */

void gpioInit(void)
{

    // LED
    gpio_set_function(BOARD_LED_GPIO, GPIO_FUNC_SIO);
    gpio_set_dir(BOARD_LED_GPIO, GPIO_OUT);
    
    // TEST GPIOs
    gpio_set_function(TEST0_GPIO, GPIO_FUNC_SIO);
    gpio_set_dir(TEST0_GPIO, GPIO_OUT);

    // PWM
    gpio_set_function(PWM1_A_GPIO, GPIO_FUNC_PWM);
    gpio_set_function(PWM1_B_GPIO, GPIO_FUNC_PWM);
    gpio_set_function(PWM2_A_GPIO, GPIO_FUNC_PWM);
    gpio_set_function(PWM2_B_GPIO, GPIO_FUNC_PWM);
    gpio_set_function(PWM3_A_GPIO, GPIO_FUNC_PWM);
    gpio_set_function(PWM3_B_GPIO, GPIO_FUNC_PWM);
    gpio_set_function(PWM_DAC_1_GPIO, GPIO_FUNC_PWM);
    gpio_set_function(PWM_DAC_2_GPIO, GPIO_FUNC_PWM);

    // UART
    gpio_set_function(UART_TX_GPIO, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_GPIO, GPIO_FUNC_UART);

    // ADC
    adc_gpio_init(PHASE_A_CURRENT_GPIO);
    adc_gpio_init(PHASE_B_CURRENT_GPIO);
}

/* ------------------------------ Private code ------------------------------ */

/* ------------------------------- End of file ------------------------------ */
