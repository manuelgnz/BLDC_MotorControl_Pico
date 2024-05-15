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
#include <stdio.h>
#include <stdbool.h>
#include <debug.h>
#include <board.h>
#include <system.h>
#include <foc.h>
#include <sysTime.h>
#include <string.h>
#include <trace.h>
#include <utils.h>
#include <bldcAdc.h>

/* ------------------------- Private code prototypes ------------------------ */

static void refreshCurrentScreen(void);
static void setActiveScreenRefresh(screenRefresh_t refresh);
static screenRefresh_t getActiveScreenRefresh(void);
static int16_t isTheCurrentScreenValid(void);
static void executeCmd(unsigned char *msg, uint16_t len);
static void enableHalfBridge(void);
static void disableHalfBridge(void);
static void setSpeed(void);
static void goSetpoint(void);
static void setFocLevel(void);
static void enableDisableFocInterrupt(void);
static void startStopFoc(void);
static void setPwmValues(void);
static void setPwmDacSelection(void);
static void screen1(void);
static void screen2(void);
static void screen3(void);
static void screen4(void);

/* ------------------------------ Private data ------------------------------ */

static delay_t debugRefreshDelay;         // Delay structure to refresh the screen

static struct commandBuffer command =
{
    .buffer[0] = 0,
    .index = 0
};

static pwmDacSelection_t pwmDacSelection = SET_POINT;

static uint16_t activeScreenId = DEFAULT_ACTIVE_SCREEN;

static struct screen screens[MAX_SCREENS_NUMBER] =
{
    {
    .id = 1,
    .title = "Screen 1",
    .refresh = REFRESH,
    .routine = &screen1
    },
    {
    .id = 2,
    .title = "Screen 2",
    .refresh = REFRESH,
    .routine = &screen2
    },
    {
    .id = 3,
    .title = "Screen 3",
    .refresh = REFRESH,
    .routine = &screen3
    },
    {
    .id = 4,
    .title = "Screen 4",
    .refresh = REFRESH,
    .routine = &screen4
    },
};

static struct action actions [MAX_ACTIONS_NUMBER] =
{
    {
    .key = 'v',
    .simple = 0,
    .screen = 1,
    .routine = &setSpeed,
    //.description = "Motor Speed [-10.0 : +10.0]"
    },
    {
    .key = 'g',
    .simple = 0,
    .screen = 1,
    .routine = &goSetpoint,
    //.description = "Set point: Go to given position"
    },
    {
    .key = 'e',
    .simple = 1,
    .screen = 0,
    .routine = &enableHalfBridge,
    //.description = "Enable bridge driver and FOC algorithm"
    },
    {
    .key = 'd',
    .simple = 1,
    .screen = 0,
    .routine = &disableHalfBridge,
    //.description = "Disable bridge driver and FOC algorithm"
    },
    {
    .key = 'f',
    .simple = 1,
    .screen = 1,
    .routine = &enableDisableFocInterrupt,
    //.description = "Enable/Disable FOC ISR function"
    },
    {
    .key = 'w',
    .simple = 1,
    .screen = 1,
    .routine = &startStopFoc,
    //.description = "Enable/Disable FOC algorithm"
    },
    {
    .key = 'j',
    .simple = 0,
    .screen = 2,
    .routine = &setPwmValues,
    //.description = "Set PWM values (FOC ISR must be disable)"
    },
    {
    .key = 'u',
    .simple = 0,
    .screen = 1,
    .routine = &setPwmDacSelection,
    //.description = "Select output of the PWM test point"
    },
    {
    .key = 'l',
    .simple = 0,
    .screen = 1,
    .routine = &setFocLevel,
    //.description = "Set FOC level"
    }
};

/* ------------------------------- Public data ------------------------------ */

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

void debugInit(void)
{
    delayInit(&debugRefreshDelay, DEBUG_REFRESH_TIME);
}

void debugInfo(halSciHandler_t * const sci)
{
    // DAC PWM actualization
    // pwmDacRefresh();

	// Check if a key was pressed
    while(uart_is_readable(sci->regs))
    {
        unsigned char c;
        c = uart_getc(sci->regs);

        // Once refresh of the current selected screen if refresh is off
        // Force the refresh of the screen when a key is pressed
        if ((getActiveScreenRefresh() != REFRESH) && (getActiveScreen()->id != 6))
        {
            setActiveScreenRefresh(REFRESH_ONCE);
        }

        delayEnd(&debugRefreshDelay);

        // Screen selection
        if (command.index == 0 && c>='0'&& c<='9')
        {
            setScreen(c-'0');
        }
        else
        {
            char simpleCmdExecuted = 0;

            if (command.index == 0)
            {
                // Simple command execution
                for (uint16_t i = 0U; i < MAX_ACTIONS_NUMBER; i++)
                {
                    if (((actions[i].screen == 0) || (actions[i].screen == getActiveScreen()->id)) && (actions[i].simple))
                    {
                        if ((c == actions[i].key) || (c == (actions[i].key - 0x20)))
                        {
                            actions[i].routine();
                            simpleCmdExecuted = 1;
                        }
                    }
                }
            }

            if(!simpleCmdExecuted)
            {
                // Command execution
                switch(c)
                {
                    case 27:
                        command.index = 0;
                        break;
                    case 13:
                        executeCmd(command.buffer, command.index);
                        break;
                    case 'r':
                    case 'R':
                        if(getActiveScreen()->refresh == REFRESH) getActiveScreen()->refresh = REFRESH_ONCE;
                        else getActiveScreen()->refresh = REFRESH;
                        break;
                    default:
                        command.buffer[command.index] = c;
                        if ((command.index + 1U) < MAX_DEBUG_COMMAND_LENGTH)
                        {
                            command.index++;
                        }
                        else
                        {
                            command.index = 0U;
                        }
                       break;
                }
            }
        }
    }

    sciSendFlush(sci, false);

    // Refresh screen info if refresh time is elapsed
    if(delayElapsedTime(&debugRefreshDelay))
    {
        refreshCurrentScreen();
    }
}

void pwmDacRefresh(void)
{
    // if(pwmDacSelection == RGEN_POSITION)
    // {
    //     if((float)system.foc->rg1.Angle >= 0.0)
    //     {
    //         pwmDacSet(&epwm4_handler, (float)system.foc->rg1.Angle);
    //     }
    //     else
    //     {
    //         pwmDacSet(&epwm4_handler, (float)system.foc->rg1.Angle + 1.0);
    //     }
    // }
    // else if (pwmDacSelection == ROT_RSLV_ELECTRICAL_POSITION)
    // {
    //     pwmDacSet(&epwm4_handler, system.foc->rotElecTheta);
    // }
    // else if (pwmDacSelection == ROT_RSLV_MECHANICAL_POSITION)
    // {
    //     pwmDacSet(&epwm4_handler, system.foc->rotMechTheta);
    // }
    // else if (pwmDacSelection == RVDT_POSITION)
    // {
    //     pwmDacSet(&epwm4_handler, (float)system.rvdt->volts / 3.0);
    // }
    // else if (pwmDacSelection == SET_POINT)
    // {
    //     pwmDacSet(&epwm4_handler, system.control.tactileCue.shaker.wave.value / (2*system.control.tactileCue.shaker.wave.amplitude) + 0.5);
    // }
    // else
    // {
    //     /* do nothing */
    // }
}

void setScreen(uint16_t screenId)
{
    if (screenId <= MAX_SCREENS_NUMBER)
    {
        activeScreenId = screenId;

        if (activeScreenId != 0U)
        {
            if (screens[activeScreenId-1U].refresh != REFRESH)
            {
                screens[activeScreenId-1U].refresh = REFRESH_ONCE;
            }
        }
    }
}

struct screen* getActiveScreen(void)
{
    return (&screens[activeScreenId-1]);
}

/* ------------------------------ Private code ------------------------------ */

static void executeCmd(unsigned char *msg, uint16_t len)
{
    // If no command return
    if(len != 0U)
    {
        // Once refresh of the current selected screen if refresh is off
        if ((getActiveScreenRefresh() != REFRESH) && (getActiveScreen()->id != 6U))
        {
            setActiveScreenRefresh(REFRESH_ONCE);
        }

        // Command execution
        for (uint16_t i = 0U; i < MAX_ACTIONS_NUMBER; i++)
        {
            if (((actions[i].screen == 0) || (actions[i].screen == getActiveScreen()->id)) && !actions[i].simple)
            {
                if ((msg[0] == actions[i].key) || (msg[0] == (actions[i].key - 0x20)))
                {
                    actions[i].routine();
                }
            }
        }

        // Initializes command buffer index
        command.index = 0;
    }
    else
    {
        /* do nothing */
    }
}

static int16_t isTheCurrentScreenValid(void)
{
    return (activeScreenId && activeScreenId <= MAX_SCREENS_NUMBER);
}

static screenRefresh_t getActiveScreenRefresh(void)
{
    screenRefresh_t ret = REFRESH_NONE;

    if(isTheCurrentScreenValid())
    {
        ret = screens[activeScreenId-1].refresh;
    }
    else
    {
        /* do nothing */
    }

    return (ret);
}

static void setActiveScreenRefresh(screenRefresh_t refresh)
{
    if (isTheCurrentScreenValid())
    {
        screens[activeScreenId-1].refresh = refresh;
    }
    else
    {
        /* do nothing */
    }
}

// Not enough stack memory -> .stack : > RAMD1
static void refreshCurrentScreen(void)
{
    char str[100];

    command.buffer[command.index] = 0;     // Set \0 termination to use as string

    // Refresh screen if '_activeScreenId' is valid and the 'refresh' flag of the corresponding screen is set
    if (isTheCurrentScreenValid())
    {
        if (getActiveScreenRefresh())
        {
            TRACE_REFRESH();
            if (getActiveScreenRefresh() == REFRESH)
            {
                sprintf(str, "SCREEN %u: '%s' \t RecBuff[%u]: %s \t REFRESH \n", activeScreenId,  getActiveScreen()->title, command.index, command.buffer);
            }
            else
            {
                sprintf(str, "SCREEN %u: '%s' \t RecBuff[%u]: %s \t NO REFRESH \n", activeScreenId,  getActiveScreen()->title, command.index, command.buffer);
            }

            TRACE_STRING_SIMPLE(str);

            // Call screen routine
            getActiveScreen()->routine();

            // Refresh only once time if REFRESH is not selected
            if (getActiveScreenRefresh() != REFRESH)
            {
                setActiveScreenRefresh(REFRESH_NONE);
            }
        }
    }
}

// ######################################################################################################
//                                              ACTIONS
// ######################################################################################################

static void enableHalfBridge(void)
{

}

static void disableHalfBridge(void)
{

}

static void setSpeed(void)
{
    char str[100], aux[20];

    float speed = strToFloat(&command.buffer[1], command.index-1);

    if(command.index > 1)
    {
        bldcSystem.foc->speedRef = (float)speed/10;
    }

    sprintf(str, "Speed: %s", floatToStr(bldcSystem.foc->speedRef, aux));
    TRACE_STRING_SIMPLE(str);
}

static void goSetpoint(void) {
    char str[100], aux[20];

    float setpoint = strToFloat(&command.buffer[1], command.index-1);
    sprintf(str, "Set Point: %s", floatToStr(setpoint, aux));
    //int16_t setpoint = strToInt(&_command.buffer[1], _command.index-1);
    //sprintf(str, "Set Point: %d", setpoint);
    TRACE_STRING_SIMPLE(str);
    bldcSystem.setPoint = setpoint;
}

static void enableDisableFocInterrupt(void) {
    char str[100];

    bldcSystem.foc->enable = !bldcSystem.foc->enable;

    sprintf(str, "foc_enable: %u", bldcSystem.foc->enable);
    TRACE_STRING_SIMPLE(str);
}

static void startStopFoc(void) {
    char str[100];

    bldcSystem.foc->lsw = !bldcSystem.foc->lsw;

    sprintf(str, "lsw: %u", bldcSystem.foc->lsw);
    TRACE_STRING_SIMPLE(str);
}

static void setPwmValues(void)
{

}

static void setFocLevel(void)
{
    char str[100];

    int16_t level = strToInt(&command.buffer[1], command.index-1);

    if(command.index == 1) {
        level = bldcSystem.foc->level;
    }

    switch(level) {
    case MANUAL_PWM:
        sprintf(str, "Level: 0 - Manual PWM");
        break;
    case OPEN_LOOP:
        sprintf(str, "Level: 1 - Open Loop");
        break;
    case CLOSE_LOOP:
        sprintf(str, "Level: 2 - Close Loop");
        break;
    case SPEED_LOOP:
        sprintf(str, "Level: 3 - Speed Loop");
        break;
    case POSITION_LOOP_FOLLOW_UP:
    default:
        sprintf(str, "Level: 4 - Position Loop Follow Up");
        break;
    }

    TRACE_STRING_SIMPLE(str);
    bldcSystem.foc->level = level;
}

static void setPwmDacSelection(void) {
    char str[100];
    char strSelect[40] = "";

    int16_t select = strToInt(&command.buffer[1], command.index-1);

    if(command.index == 1) {
        select = pwmDacSelection;
    }

    switch(select) {
    case RGEN_POSITION:
        strcpy(strSelect, "Ramp Gen. Position");
        pwmDacSelection = RGEN_POSITION;
        break;
    case ROT_RSLV_ELECTRICAL_POSITION:
    default:
        strcpy(strSelect, "Rotor Electrical Position");
        pwmDacSelection = ROT_RSLV_ELECTRICAL_POSITION;
        break;
    case ROT_RSLV_MECHANICAL_POSITION:
        pwmDacSelection = ROT_RSLV_MECHANICAL_POSITION;
        strcpy(strSelect, "Rotor Mechanical Position");
        break;
    case RVDT_POSITION:
        strcpy(strSelect, "RVDT Position");
        pwmDacSelection = RVDT_POSITION;
        break;
    case SET_POINT:
        strcpy(strSelect, "Set Point");
        pwmDacSelection = SET_POINT;
        break;
    }

    sprintf(str, "PWM DAC Out(%d): %s", select, strSelect);
    TRACE_STRING_SIMPLE(str);
}

// ######################################################################################################
//                                              SCREENS
// ######################################################################################################
static void screen1(void)
{
    char s[120U];

    uint64_t ticks = time_us_64();
    sprintf(s, "Ticks: %llu | ADC(26): %hu | ADC(27): %hu \r\n", ticks, adc26, adc27);

    TRACE_STRING_SIMPLE(s);
}

static void screen2(void)
{
    TRACE_STRING_SIMPLE("PANTALLA 2");
}

static void screen3(void)
{
    TRACE_STRING_SIMPLE("PANTALLA 3");
}

static void screen4(void)
{
    TRACE_STRING_SIMPLE("PANTALLA 4");
}

/* ------------------------------- End of file ------------------------------ */
