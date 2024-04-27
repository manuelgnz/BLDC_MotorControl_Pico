/**
 * @file board.h
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

#ifndef BOARD_H
#define BOARD_H

/* -------------------------------- Includes -------------------------------- */

/* -------------------------- Constants and macros -------------------------- */

#define PWM1_A      (0U)
#define PWM1_B      (1U)
#define PWM2_A      (2U)
#define PWM2_B      (3U)
#define PWM3_A      (4U)
#define PWM3_B      (5U)
#define PWM_DAC_1   (6U)
#define PWM_DAC_2   (7U)
#define UART_TX_PIN (12U)
#define UART_RX_PIN (13U)

/** Test GPIO. */
#define TEST0_GPIO      (21U)

/** Board built-in LED gpio. */
#define BOARD_LED_GPIO  (25U)



/* ---------------------------------- Types --------------------------------- */

/* ------------------------------- Public data ------------------------------ */

/* ------------------------- Public code prototypes ------------------------- */

/**
 * @brief Inits all the board's GPIOs.
 */
void gpioInit(void);

#endif // BOARD_H

/* ------------------------------- End of file ------------------------------ */
