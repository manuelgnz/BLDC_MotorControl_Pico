/**
 * @file template.c
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

/* -------------------------------- Includes -------------------------------- */

#include <system.h>
#include <board.h>
#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <hardware/pll.h>
#include <hardware/timer.h>
#include <hardware/clocks.h>
#include <hardware/structs/pll.h>
#include <hardware/structs/clocks.h>
#include <foc.h>
#include <debug.h>

/* -------------------------- Constants and macros -------------------------- */

/** Motor phases PWM frequency in kHz. */
#define MOTOR_PWM_FREQUENCY     10U  // 10 kHz

/** PWM DAC frequency in kHz. */
#define DAC_PWM_FREQUENCY       60  // 60 kHz (150 in HURJET)

/* ---------------------------------- Types --------------------------------- */


/* ------------------------------- Public data ------------------------------ */

/** Global system variable containing handlers and data. */
bldcSystem_t bldcSystem;

/* ------------------------------ Private data ------------------------------ */


/* ------------------------- Private code prototypes ------------------------ */

/**
 * @brief UART peripheral init.
 */
static void uartInit(void);

/**
 * @brief PWM peripheral init.
 */
static void pwmInit(void);

/**
 * @brief Timer peripheral init.
 */
static void timerInit(void);

/* ------------------------------- Public code ------------------------------ */

void systemInit(void)
{
    gpioInit();
    uartInit();
    pwmInit();
    timerInit();
}

void setPwmDutyCycle(uint8_t slice, float dutyCycle)
{
    uint16_t wrap = pwm_hw->slice[slice].top;
    uint16_t counterCompare = wrap * dutyCycle;
    pwm_set_chan_level(slice, 0U, counterCompare);
    pwm_set_chan_level(slice, 1U, counterCompare);
}

/* ------------------------------ Private code ------------------------------ */

static void uartInit(void)
{
    // Set up our UART with a basic baud rate.
    uart_init(UART_ID, BAUD_RATE);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, false);

    // Set our data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Set up a RX interrupt. Select correct interrupt for the UART we are using
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    // Set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, uartRxIsr);
    irq_set_enabled(UART_IRQ, true);

    // Enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, true, false);
}

static void pwmInit(void)
{
    bldcSystem.pwmSlices.pwm1Slice = pwm_gpio_to_slice_num(PWM1_A);
    bldcSystem.pwmSlices.pwm2Slice = pwm_gpio_to_slice_num(PWM2_A);
    bldcSystem.pwmSlices.pwm3Slice = pwm_gpio_to_slice_num(PWM3_A);
    bldcSystem.pwmSlices.pwmDac1Slice = pwm_gpio_to_slice_num(PWM_DAC_1);
    bldcSystem.pwmSlices.pwmDac2Slice = pwm_gpio_to_slice_num(PWM_DAC_2);

    pwm_config config =
    {
        .csr = 0,
        .div = 0,
        .top = 0
    };

    // uint32_t clkSysFreq = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS); TODO
    uint32_t clkSysFreq = 125000;

    // PWM Motor Phases
    uint32_t pwmWrapValue = ((clkSysFreq / (uint32_t)MOTOR_PWM_FREQUENCY) / (uint32_t)2U);

    pwm_config_set_phase_correct(&config, true);                // Up-down mode
    pwm_config_set_clkdiv_int(&config, 1U);                     // Div 1
    pwm_config_set_clkdiv_mode(&config, PWM_DIV_FREE_RUNNING);  // Free-running
    pwm_config_set_output_polarity(&config, false, true);       // Invert B output
    pwm_config_set_wrap(&config, (uint16_t)pwmWrapValue);       // Max value

    // Load the configuration into our PWM slice, and set it running.
    pwm_init(bldcSystem.pwmSlices.pwm1Slice, &config, true);
    pwm_init(bldcSystem.pwmSlices.pwm2Slice, &config, true);
    pwm_init(bldcSystem.pwmSlices.pwm3Slice, &config, true);


    // DAC 1 & 2
    pwmWrapValue = (clkSysFreq / (uint32_t)DAC_PWM_FREQUENCY);

    pwm_config_set_phase_correct(&config, false);               // Up mode
    pwm_config_set_clkdiv_int(&config, 1U);                     // Div 1
    pwm_config_set_clkdiv_mode(&config, PWM_DIV_FREE_RUNNING);  // Free-running
    pwm_config_set_output_polarity(&config, false, true);       // Invert B output
    pwm_config_set_wrap(&config, (uint16_t)pwmWrapValue);       // Max value

    pwm_init(bldcSystem.pwmSlices.pwmDac1Slice, &config, true);
    pwm_init(bldcSystem.pwmSlices.pwmDac2Slice, &config, true);
}

static void timerInit(void)
{
    // Enable the interrupt for the alarm (we're using Alarm 0)
    hw_set_bits(&timer_hw->inte, 1u << ALARM_NUM) ;
    // Associate an interrupt handler with the ALARM_IRQ
    irq_set_exclusive_handler(TIMER_IRQ_0, foc) ;
    // Enable the alarm interrupt
    irq_set_enabled(TIMER_IRQ_0, true) ;
    // Write the lower 32 bits of the target time to the alarm register, arming it.
    timer_hw->alarm[ALARM_NUM] = timer_hw->timerawl + FOC_PERIOD;
}

/* ------------------------------- End of file ------------------------------ */
