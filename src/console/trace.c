/**
 * @file template.c
 * @brief Module description.
 * 
 * @version aa
 * @date 01 Jan 2001
 * @author manuelgnzmunoz@gmail.com
 */

/* -------------------------------- Includes -------------------------------- */

#include <trace.h>
#include <string.h>

/* -------------------------- Constants and macros -------------------------- */

/** Maximum number of characters to send in a single send (non blocking). */
#define SINGLE_SEND_MAX_CHARACTERS_NUM   16U

/* ------------------------------- Public data ------------------------------ */

/** SCI handler. */
halSciHandler_t sciHandler;

/** SCI RX buffer. */
unsigned char halSciRxBuffer[SCI_RX_BUFFER_LEN];

/** SCI TX buffer. */
unsigned char halSciTxBuffer[SCI_TX_BUFFER_LEN];

/* ------------------------------ Private data ------------------------------ */

/** SCI interface handler for tracing. */
static halSciHandler_t * traceHandler;

/* ------------------------------- Public code ------------------------------ */

void traceInit(halSciHandler_t * handler)
{
    traceHandler = handler;
}

void traceString(const char *str)
{
    size_t len = strlen(str);

    (void)sciAsyncSend(traceHandler, (const unsigned char *)str, len);
    (void)sciAsyncSend(traceHandler, "\r\n", 2);
}

void traceNewLine(size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        (void)sciAsyncSend(traceHandler, "\r\n", 2);
    }
}

void traceRefresh(void)
{
    // \033[: ESC [, control sequence introducer.
    // 2J: clear the entire screen.
    // H: move the cursor to row 1, column 1.
    // 0m: turn off the colors and style.
    // ?25l: hide the cursor.
    const char clearScreen[] = "\033" "[2J"
                               "\033" "[H"
                               "\033" "[0m"
                               "\033" "[?25l";
    size_t len = strlen(clearScreen);

    (void)sciAsyncSend(traceHandler, (const unsigned char *)clearScreen,
                          len);
}

void sciSendFlush(halSciHandler_t * handler, bool all)
{
    halSciBuffer_t * txBuffer = &handler->txBuffer;

    if (all)
    {
        uart_write_blocking(handler->regs, txBuffer->data, txBuffer->count);
        txBuffer->count = 0U;
    }
    else
    {
        if (txBuffer->count > 0UL)
        {
            uint16_t charactersToSend = 0U;

            if (txBuffer->count < SINGLE_SEND_MAX_CHARACTERS_NUM)
            {
                charactersToSend = txBuffer->count;
            }
            else
            {
                charactersToSend = SINGLE_SEND_MAX_CHARACTERS_NUM;
            }
            
            // Write the characters
            uart_write_blocking(handler->regs, &txBuffer->data[txBuffer->first], charactersToSend);
            txBuffer->first += charactersToSend;
            txBuffer->count -= charactersToSend;

            if (txBuffer->first >= txBuffer->dataLength)
            {
                txBuffer->first -= txBuffer->dataLength;
            }
        }
    }
}

bool sciAsyncSend(halSciHandler_t * handler, const unsigned char *data, size_t len)
{
    bool status;
    halSciBuffer_t *buffer = &handler->txBuffer;

    if ((len + buffer->count) <= buffer->dataLength)
    {
        for (size_t i = 0UL; i < len; i++)
        {
            buffer->data[buffer->last] = data[i];
            buffer->last++;
            buffer->count++;

            if (buffer->last >= buffer->dataLength)
            {
                buffer->last = 0UL;
            }
        }

        status = true;
    }
    else
    {
        status = false;
    }

    return status;
}

/* ------------------------------ Private code ------------------------------ */

/* ------------------------------- End of file ------------------------------ */
