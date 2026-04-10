/*
 * next_bio_flash.h
 *
 *  Created on: 9 avr. 2026
 *      Author: benjamin.chalant
 */

#ifndef NEXT_BIO_FLASH_H
#define NEXT_BIO_FLASH_H

#include "main.h"
#include "NBDevice.h"
#include "NBErrors.h"

#define NEXT_CALIB_FLASH_ADDR         ((uint32_t)0x081E0000UL)
#define NEXT_CALIB_FLASH_SIZE         ((uint32_t)0x00020000UL) /* 128 KB */
#define NEXT_CALIB_MAGIC              ((uint32_t)0x4E42434CUL) /* "NBCL" */
#define NEXT_CALIB_VERSION            ((uint32_t)1UL)

typedef struct
{
    uint32_t magic;
    uint32_t version;
    uint32_t data_size;
    uint32_t crc32;
} NEXT_CalibHeader_t;

NBResult NEXT_Calibration_SaveToFlash(const uint8_t *pData, uint32_t size);
NBResult NEXT_Calibration_LoadFromFlash(const uint8_t **ppData, uint32_t *pSize);
NBResult NEXT_Calibration_EraseFlash(void);

#endif
