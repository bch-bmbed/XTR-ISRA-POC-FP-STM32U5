//******************************************************************************
// Copyright (c) 2020, XtreamWave
//******************************************************************************
//! @file         logger.c
//! @author       XtreamWave
//! @brief        Smartcard library
//! @details      This module implements logger functions.
//! @warning      None
//******************************************************************************

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "logger_xtr.h"
#include "util.h"

#define LOG_UART_TIMEOUT 100

UART_HandleTypeDef *log_huart;
int log_level;
int log_state;
static char log_buffer[LOG_BUFFER_SIZE];

//******************************************************************************
//! @brief     This function initializes the log module.
//!
//! @param[in] huart the UART handler
//!
//! @warning   None
//******************************************************************************
void log_init(void* huart)
{
    log_huart = (UART_HandleTypeDef*)huart;
    log_level = LOG_INF;
    log_state = 1;
}

//******************************************************************************
//! @brief     This function transmits data to the log UART.
//!
//! @param[in] data the data buffer to transmit
//! @param[in] data_len the data length
//!
//! @warning   None
//******************************************************************************
void log_transmit(uint8_t *data, uint16_t data_len)
{
    HAL_UART_Transmit(log_huart, data, data_len, LOG_UART_TIMEOUT);
}

//******************************************************************************
//! @brief     This function sets the current log level.
//!
//! @param[in] level the log level (one of the LOG_XXX constant)
//!
//! @warning   None
//******************************************************************************
void log_set_level(int level)
{
    log_level = level;
}

//******************************************************************************
//! @brief     This function gets the current log level.
//!
//! @warning   Current log level
//******************************************************************************
int log_get_level(void)
{
    return log_level;
}

//******************************************************************************
//! @brief     This function checks the current log level.
//!
//! @param[in] level the log level (one of the LOG_XXX constant)
//!
//! @return 1 if log level is valid, 0 otherwise
//!
//! @warning   None
//******************************************************************************
int log_check_level(int level)
{
    return ((log_state) &&  (level <= log_level));
}

//******************************************************************************
//! @brief     This function logs a string.
//!
//! @param[in] level the log level (one of the LOG_XXX constant)
//! @param[in] format... the string in printf format
//!
//! @warning   None
//******************************************************************************
void log_printf(int level, const char* format, ...)
{
    if (log_check_level(level)) {
        va_list argptr;
        va_start(argptr, format);
        vsnprintf(log_buffer, LOG_BUFFER_SIZE, format, argptr);
        va_end(argptr);
        log_transmit((uint8_t*)log_buffer, strlen(log_buffer));
    }
}

//******************************************************************************
//! @brief     This function logs a buffer in hexa and ascii (multiple lines).
//!
//! @param[in] level the log level (one of the LOG_XXX constant)
//! @param[in] data the buffer
//! @param[in] length the buffer length
//! @param[in] flag 1 to dump HEX+ASCII, 0 to dump only HEX
//!
//! @warning   None
//******************************************************************************
void log_dump_hex_array(int level, unsigned char *data, int length, int flag)
{
    char line[67];
    int n, i, j, l;
    unsigned char c;

    if (log_check_level(level)) {
        if (length == 0) return;
        n = ((length - 1) / 16) + 1;
        for (i = 0; i < n; i++)
        {
            l = 16;
            if (i == (n - 1)) l = ((length - 1) % 16) + 1; // last line may be shorter
            memset(line, ' ', sizeof(line));
            for (j = 0; j < 16; j++)
            {
                if (j < l) {
                    c = *data++;
                    line[3*j  ] = nibble2char(c >> 4);
                    line[3*j+1] = nibble2char(c & 15);
                    if ((c >= 0x20) && (c <= 0x7F))
                        line[50+j] = c;
                    else
                        line[50+j] = '.';
                }
            }
            if (flag) line[66] = 0; else line[47] = 0;
            log_printf(level, "%s\r\n", line);
        }
    }
}

//******************************************************************************
//! @brief     This function logs a buffer in hexa (single line).
//!
//! @param[in] level the log level (one of the LOG_XXX constant)
//! @param[in] header the log header string
//! @param[in] buf the buffer
//! @param[in] len the buffer length
//!
//! @warning   None
//******************************************************************************
void log_dump_hex(int level, char* header, unsigned char* buf, int len)
{
    if (log_check_level(level)) {
        log_printf(level, "%s", header);
        for (int i = 0; i < len; i++) log_printf(level, " %02X", buf[i]);
        log_printf(level, "\r\n");
    }
}

//******************************************************************************
//! @brief     This function disables logging.
//!
//! @warning   None
//******************************************************************************
void log_disable(void)
{
    log_state = 0;
}

//******************************************************************************
//! @brief     This function enables logging.
//!
//! @warning   None
//******************************************************************************
void log_enable(void)
{
    log_state = 1;
}
