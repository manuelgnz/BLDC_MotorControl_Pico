/**
 * @file trace.h
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

#ifndef TRACE_H
#define TRACE_H

/* -------------------------------- Includes -------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include <pico/stdlib.h>

/* -------------------------- Constants and macros -------------------------- */

/** Macro to print a string. */
#define TRACE_STRING_SIMPLE(X)     traceString(X)

/** Macro to refresh the debug screen. */
#define TRACE_REFRESH()            traceRefresh()

/** SCI RX buffer size in bytes. */
#define SCI_RX_BUFFER_LEN   30U

/** SCI TX buffer size in bytes. */
#define SCI_TX_BUFFER_LEN   1024U

/* ---------------------------------- Types --------------------------------- */

/** @brief SCI data buffer type. Used internally. */
typedef struct
{
    unsigned char *data;
    size_t dataLength;
    size_t first;
    size_t last;
    size_t count;
} halSciBuffer_t;

/** @brief Handler of the SCI interface. */
typedef struct
{
    uart_inst_t * regs;
    halSciBuffer_t txBuffer;
    volatile halSciBuffer_t rxBuffer;
} halSciHandler_t;

/* ------------------------------- Public data ------------------------------ */

/** SCI handler. */
extern halSciHandler_t sciHandler;

/** SCI RX buffer. */
extern uint8_t halSciRxBuffer[SCI_RX_BUFFER_LEN];

/** SCI TX buffer. */
extern uint8_t halSciTxBuffer[SCI_TX_BUFFER_LEN];

/* ------------------------- Public code prototypes ------------------------- */

/**
 * @brief Template public function.
 *
 * @retval 0 If condition 1.
 * @retval 1 If condition 2.
 */
void traceInit(halSciHandler_t * handler);

/**
 * @brief Template public function.
 *
 * @retval 0 If condition 1.
 * @retval 1 If condition 2.
 */
void traceString(const char *str);

/**
 * @brief Template public function.
 *
 * @retval 0 If condition 1.
 * @retval 1 If condition 2.
 */
void traceNewLine(size_t count);

/**
 * @brief Template public function.
 *
 * @retval 0 If condition 1.
 * @retval 1 If condition 2.
 */
void traceRefresh(void);

/**
 * @brief Template public function.
 *
 * @retval 0 If condition 1.
 * @retval 1 If condition 2.
 */
void sciSendFlush(halSciHandler_t * handler, bool all);

/**
 * @brief Template public function.
 *
 * @retval 0 If condition 1.
 * @retval 1 If condition 2.
 */
bool sciAsyncSend(halSciHandler_t * handler, const unsigned char *data, size_t len);

#endif // TRACE_H

/* ------------------------------- End of file ------------------------------ */
