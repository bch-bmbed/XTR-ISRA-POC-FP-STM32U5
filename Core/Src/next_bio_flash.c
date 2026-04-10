/*
 * next_bio_flash.c
 *
 *  Created on: 9 avr. 2026
 *      Author: benjamin.chalant
 */

#include "next_bio_flash.h"
#include <string.h>

#define NEXT_FLASH_PAGE_SIZE          ((uint32_t)0x2000UL) /* 8 KB */
#define NEXT_FLASH_PROG_SIZE          ((uint32_t)16UL)     /* quad-word */

static uint32_t NEXT_Crc32(const uint8_t *pData, uint32_t size)
{
    uint32_t crc = 0xFFFFFFFFU;
    uint32_t i, j;

    for (i = 0; i < size; i++)
    {
        crc ^= pData[i];
        for (j = 0; j < 8; j++)
        {
            uint32_t mask = -(crc & 1U);
            crc = (crc >> 1) ^ (0xEDB88320U & mask);
        }
    }

    return ~crc;
}

static uint32_t NEXT_FlashGetBank(uint32_t addr)
{
    return (addr < 0x08100000UL) ? FLASH_BANK_1 : FLASH_BANK_2;
}

NBResult NEXT_Calibration_EraseFlash(void)
{
    HAL_StatusTypeDef hal;
    FLASH_EraseInitTypeDef erase = {0};
    uint32_t page_error = 0;
    uint32_t first_page = (NEXT_CALIB_FLASH_ADDR - 0x08000000UL) / NEXT_FLASH_PAGE_SIZE;
    uint32_t nb_pages = NEXT_CALIB_FLASH_SIZE / NEXT_FLASH_PAGE_SIZE;

    HAL_FLASH_Unlock();

    erase.TypeErase = FLASH_TYPEERASE_PAGES;
    erase.Banks = NEXT_FlashGetBank(NEXT_CALIB_FLASH_ADDR);
    erase.Page = first_page % 256U;
    erase.NbPages = nb_pages;

    hal = HAL_FLASHEx_Erase(&erase, &page_error);

    HAL_FLASH_Lock();

    return (hal == HAL_OK) ? NB_OK : NB_ERROR_FAILED;
}

NBResult NEXT_Calibration_SaveToFlash(const uint8_t *pData, uint32_t size)
{
    HAL_StatusTypeDef hal;
    NEXT_CalibHeader_t hdr;
    uint32_t total_size;
    uint32_t addr;
    uint8_t quad[NEXT_FLASH_PROG_SIZE];
    uint32_t i, chunk;

    if ((pData == NULL) || (size == 0U))
    {
        return NB_ERROR_ARGUMENT_NULL;
    }

    total_size = sizeof(hdr) + size;
    if (total_size > NEXT_CALIB_FLASH_SIZE)
    {
        return NB_ERROR_ARGUMENT_OUT_OF_RANGE;
    }

    hdr.magic = NEXT_CALIB_MAGIC;
    hdr.version = NEXT_CALIB_VERSION;
    hdr.data_size = size;
    hdr.crc32 = NEXT_Crc32(pData, size);

    if (NEXT_Calibration_EraseFlash() != NB_OK)
    {
        return NB_ERROR_FAILED;
    }

    HAL_FLASH_Unlock();

    addr = NEXT_CALIB_FLASH_ADDR;

    /* header */
    memset(quad, 0xFF, sizeof(quad));
    memcpy(quad, &hdr, sizeof(hdr));
    hal = HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, addr, (uint32_t)quad);
    if (hal != HAL_OK)
    {
        HAL_FLASH_Lock();
        return NB_ERROR_FAILED;
    }
    addr += NEXT_FLASH_PROG_SIZE;

    /* data */
    for (i = 0; i < size; i += NEXT_FLASH_PROG_SIZE)
    {
        memset(quad, 0xFF, sizeof(quad));
        chunk = ((size - i) >= NEXT_FLASH_PROG_SIZE) ? NEXT_FLASH_PROG_SIZE : (size - i);
        memcpy(quad, &pData[i], chunk);

        hal = HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, addr, (uint32_t)quad);
        if (hal != HAL_OK)
        {
            HAL_FLASH_Lock();
            return NB_ERROR_FAILED;
        }

        addr += NEXT_FLASH_PROG_SIZE;
    }

    HAL_FLASH_Lock();
    return NB_OK;
}

NBResult NEXT_Calibration_LoadFromFlash(const uint8_t **ppData, uint32_t *pSize)
{
    const NEXT_CalibHeader_t *pHdr;
    const uint8_t *pBlob;
    uint32_t crc;

    if ((ppData == NULL) || (pSize == NULL))
    {
        return NB_ERROR_ARGUMENT_NULL;
    }

    pHdr = (const NEXT_CalibHeader_t *)NEXT_CALIB_FLASH_ADDR;

    if ((pHdr->magic != NEXT_CALIB_MAGIC) || (pHdr->version != NEXT_CALIB_VERSION))
    {
        return NB_ERROR_FAILED;
    }

    if ((pHdr->data_size == 0U) || ((sizeof(NEXT_CalibHeader_t) + pHdr->data_size) > NEXT_CALIB_FLASH_SIZE))
    {
        return NB_ERROR_FAILED;
    }

    pBlob = (const uint8_t *)(NEXT_CALIB_FLASH_ADDR + sizeof(NEXT_CalibHeader_t));
    crc = NEXT_Crc32(pBlob, pHdr->data_size);

    if (crc != pHdr->crc32)
    {
        return NB_ERROR_FAILED;
    }

    *ppData = pBlob;
    *pSize = pHdr->data_size;

    return NB_OK;
}
