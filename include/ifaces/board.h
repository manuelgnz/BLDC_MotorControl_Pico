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

/* ---------------------------------- Types --------------------------------- */

/* ------------------------------- Public data ------------------------------ */

/** Template public variable. */
extern int templateData1;

/* ------------------------- Public code prototypes ------------------------- */

/**
 * @brief Inits all the board's GPIOs.
 */
void gpioInit(void);

#endif // BOARD_H

/* ------------------------------- End of file ------------------------------ */
