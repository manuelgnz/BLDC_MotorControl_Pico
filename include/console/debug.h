/**
 * @file debug.h
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

#ifndef DEBUG_H
#define DEBUG_H

/* -------------------------------- Includes -------------------------------- */

/* -------------------------- Constants and macros -------------------------- */

/** UART interface. */
#define UART_ID   uart0

/** UART baudrate. */
#define BAUD_RATE 115200

/** UART communication data bits. */
#define DATA_BITS 8

/** UART communication stop bits. */
#define STOP_BITS 1

/** UART communication parity. */
#define PARITY    UART_PARITY_NONE

/* ---------------------------------- Types --------------------------------- */

/* ------------------------------- Public data ------------------------------ */

/* ------------------------- Public code prototypes ------------------------- */

/**
 * @brief UART RX interrupt routine.
*/
void uartRxIsr(void);

#endif // DEBUG_H

/* ------------------------------- End of file ------------------------------ */
