//******************************************************************************
// Copyright (c) 2020, XtreamWave
//******************************************************************************
//! @file         util.h
//! @author       XtreamWave
//! @brief        Smartcard library
//! @details      This module implements misc utility functions.
//! @warning      None
//******************************************************************************

#ifndef INC_UTIL_H_
#define INC_UTIL_H_

#define CRC16_CCITT_FALSE   0
#define CRC16_MCRF4XX       1
#define CRC16_MODBUS        2

unsigned long get_time_ms(void);
char nibble2char(unsigned char n);
int is_hex_digit(char c);
unsigned char char2nibble(char c);
int convert_asc_to_bin(char* asc, unsigned char* bin);
char* convert_bin_to_asc(unsigned char* bin, int len);

unsigned short compute_crc16(unsigned char* data, int len, int algo);
//unsigned short compute_crc16_hw(void* hcrc, unsigned char* data, int len);

#endif // INC_UTIL_H_
