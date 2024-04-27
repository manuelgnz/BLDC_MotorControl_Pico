/**
 * @file debug.c
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

/* -------------------------------- Includes -------------------------------- */

#include <pico/stdlib.h>
#include <board.h>
#include <debug.h>

/* -------------------------- Constants and macros -------------------------- */

/* ---------------------------------- Types --------------------------------- */

/* ------------------------------- Public data ------------------------------ */

/* ------------------------------ Private data ------------------------------ */

/* ------------------------- Private code prototypes ------------------------ */

/* ------------------------------- Public code ------------------------------ */

// RX interrupt handler
void uartRxIsr(void)
{
    while (uart_is_readable(UART_ID))
    {
        uint8_t ch = uart_getc(UART_ID);
        // Can we send it back?
        if (uart_is_writable(UART_ID))
        {
            uart_putc(UART_ID, ch);
        }
    }
}

/* ------------------------------ Private code ------------------------------ */

/* ------------------------------- End of file ------------------------------ */
