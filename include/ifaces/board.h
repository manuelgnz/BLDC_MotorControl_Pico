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

#define PWM1_A_GPIO           (0U)
#define PWM1_B_GPIO           (1U)
#define PWM2_A_GPIO           (2U)
#define PWM2_B_GPIO           (3U)
#define PWM3_A_GPIO           (4U)
#define PWM3_B_GPIO           (5U)
#define PWM_DAC_1_GPIO        (6U)
#define PWM_DAC_2_GPIO        (7U)
#define UART_TX_GPIO          (12U)
#define UART_RX_GPIO          (13U)
#define PHASE_A_CURRENT_GPIO  (26U)
#define PHASE_B_CURRENT_GPIO  (27U)

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
