//******************************************************************************
// Copyright (c) 2020, XtreamWave
//******************************************************************************
//! @file         logger.h
//! @author       XtreamWave
//! @brief        Smartcard library
//! @details      This module implements logger functions.
//! @warning      None
//******************************************************************************

#ifndef INC_LOGGER_H_
#define INC_LOGGER_H_

#define LOG_ALW   0 // always
#define LOG_ERR   0 // error
#define LOG_INF   1 // info
#define LOG_VER   2 // verbose
#define LOG_DBG   3 // debug

// LOG buffer
#define LOG_BUFFER_SIZE 512

void log_init(void* huart);
void log_set_level(int level);
int log_get_level(void);
int log_check_level(int level);
void log_printf(int level, const char* format, ...);
void log_dump_hex_array(int level, unsigned char *data, int length, int flag);
void log_dump_hex(int level, char* header, unsigned char* buf, int len);
void log_disable(void);
void log_enable(void);

#endif // INC_LOGGER_H_
