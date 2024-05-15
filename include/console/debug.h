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

#include <stdint.h>
#include <trace.h>

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

#define DEBUG_REFRESH_TIME 1000000      // Debug refresh time for the screen when refresh is active

#define DEFAULT_ACTIVE_SCREEN 0         // Default screen selected

#define MAX_SCREENS_NUMBER 6            // Max number of screens

#define MAX_ACTIONS_NUMBER 30U

#define MAX_DEBUG_COMMAND_LENGTH 20U

#define LOG_SCREEN_ID   6U

#define RECIVE_BUFFER_SIZE 16           // Serial Receive Buffer Size

#define DEBUG_INFO_BUFFER_SIZE 100U

#define MAX_DEBUG_COMMAND_LENGTH 20U

/* ---------------------------------- Types --------------------------------- */

/** @brief  */
typedef struct commandBuffer
{
    unsigned char buffer[MAX_DEBUG_COMMAND_LENGTH];      // Buffer to save the received commands from the console
    uint16_t index;                             // Buffer index which is incremented when a new char is received from the console
} commandBuffer_t;

/** @brief  */
typedef struct action
{
    unsigned char key;                   // Initial key for the action
    char simple;                // Flag indicating if only one key is needed for the action
    char screen;                // Screen where the action is active. If null the action is active for every screens
    void (*routine)(void);      // Action routine executed when key pressed
} action_t;

/** @brief  */
typedef enum
{
    REFRESH_NONE = 0,  /**< REFRESH_NONE */
    REFRESH_ONCE = 1,  /**< REFRESH_ONCE */
    REFRESH = 2        /**< REFRESH */
} screenRefresh_t;

/** @brief  */
typedef enum
{
    RGEN_POSITION = 0,                 // RGEN_POSITION
    ROT_RSLV_ELECTRICAL_POSITION = 1,  // ROT_RSLV_ELECTRICAL_POSITION
    ROT_RSLV_MECHANICAL_POSITION = 2,  // ROT_RSLV_MECHANICAL_POSITION
    RVDT_POSITION = 3,                 // RVDT_POSITION
    SET_POINT = 4                      // SET_POINT
} pwmDacSelection_t;

/** @brief  */
typedef struct screen
{
    uint16_t id;                // screen Id
    char title[60];             // Screen title
    screenRefresh_t refresh;    // Flag indicating if the screen must to auto refresh
    void (*routine)(void);      // Screen routine that sends the information
} screen_t;

/** @brief  */
typedef struct debugInfo
{
    float currentA;
    float currentB;
    uint16_t rotPosition;
    uint16_t actPosition;
    float aux;
} debugInfo_t;

/** @brief  */
typedef struct debugHandler
{
    uint16_t flag;                          // Flag to activate info debug save into the buffer
    uint16_t timeCount;                     // Variable to count the time elapsed
    uint16_t timePeriod;                    // Time to save a debug info point
    uint16_t index;                         // Index to the buffer to save info
    struct debugInfo *debugInfo;            // Pointer to debug info buffer
} debugHandler_t;

/* ------------------------------- Public data ------------------------------ */

/* ------------------------- Public code prototypes ------------------------- */

/**
 * @brief
 *
 */
void debugInit(void);

/**
 * @brief
 *
 * @param sci
 */
void debugInfo(halSciHandler_t * const sci);

/**
 * @brief
 *
 */
void pwmDacRefresh(void);

/**
 * @brief
 *
 * @param screenId
 */
void setScreen(uint16_t screenId);

/**
 * @brief
 *
 * @return
 */
struct screen* getActiveScreen(void);

/**
 * @brief UART RX interrupt routine.
*/
void uartRxIsr(void);

#endif // DEBUG_H

/* ------------------------------- End of file ------------------------------ */
