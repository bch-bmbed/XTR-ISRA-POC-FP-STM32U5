/*
 * next_id3.c
 *
 *  Created on: 10 avr. 2026
 *      Author: benjamin.chalant
 */

#include "next_id3.h"

#include "logger_xtr.h"
#include "next_bio_device.h"

#include "NBDevice.h"
#include "NBErrors.h"

#include <string.h>
#include <stdlib.h>

#define NEXT_ID3_IMAGE_WIDTH   300U
#define NEXT_ID3_IMAGE_HEIGHT  400U
#define NEXT_ID3_IMAGE_SIZE    (NEXT_ID3_IMAGE_WIDTH * NEXT_ID3_IMAGE_HEIGHT)

#define NEXT_ID3_MODE          FingerExtractMode_SmallSensor370DPI
#define NEXT_ID3_MODE_NAME     "SmallSensor370DPI"
#define NEXT_ID3_DPI           370U

static void NEXT_ID3_InvertImage(uint8_t *pImage, uint32_t size)
{
    uint32_t i;
    for (i = 0; i < size; i++)
    {
        pImage[i] = (uint8_t)(255U - pImage[i]);
    }
}

typedef struct
{
    id3FingerExtractMode mode;
    const char *name;
} NEXT_ID3_ModeEntry;

static unsigned short NEXT_ID3_ModeToDpi(id3FingerExtractMode mode)
{
    switch (mode)
    {
    case FingerExtractMode_LowSpeed370DPI:
    case FingerExtractMode_HighSpeed370DPI:
    case FingerExtractMode_SmallSensor370DPI:
        return 370;

    case FingerExtractMode_LowSpeed:
    case FingerExtractMode_HighSpeed:
    case FingerExtractMode_SmallSensor:
    default:
        return 500;
    }
}

int NEXT_ID3_SmokeTest(void)
{
    int result;
    int templateObjSize;
    ID3FINGER_TEMPLATE hTemplate = NULL;
    uint8_t *pTemplateBuffer = NULL;

    log_printf(LOG_DBG, "ID3 smoke test start\r\n");

    templateObjSize = sizeOf_ID3FINGER_TEMPLATE();
    log_printf(LOG_DBG, "ID3 template object size=%d\r\n", templateObjSize);

    if (templateObjSize <= 0)
    {
        log_printf(LOG_DBG, "Invalid ID3 template size\r\n");
        return -1;
    }

    pTemplateBuffer = (uint8_t *)malloc((size_t)templateObjSize);
    if (pTemplateBuffer == NULL)
    {
        log_printf(LOG_DBG, "ID3 template malloc failed\r\n");
        return -2;
    }

    memset(pTemplateBuffer, 0, (size_t)templateObjSize);

    result = id3FingerTemplate_Initialize(&hTemplate, pTemplateBuffer, templateObjSize);
    log_printf(LOG_DBG, "id3FingerTemplate_Initialize -> %d\r\n", result);

    if (result == ID3_SUCCESS)
    {
        log_printf(LOG_DBG, "ID3 smoke test OK\r\n");
    }

    free(pTemplateBuffer);
    return result;
}

int NEXT_ID3_ExtractFromNextCapture(void)
{
    NBResult nbRes;
    HNBDevice hDevice;
    NBDeviceScanFormatInfo info;
    NBDeviceScanStatus scanStatus = 0;

    uint8_t *pImage = NULL;
    uint8_t *pTemplateBuffer = NULL;
    uint8_t *pExtractBuffer = NULL;

    ID3FINGER_TEMPLATE hTemplate = NULL;
    ID3FINGER_EXTRACT hExtract = NULL;

    int id3Res;
    int templateObjSize;
    int extractObjSize;
    unsigned char imageQuality = 0;

    uint32_t i;
    uint32_t sum = 0;
    uint8_t minv = 255;
    uint8_t maxv = 0;

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        log_printf(LOG_DBG, "NEXT_DeviceGetHandle returned NULL\r\n");
        return -100;
    }

    memset(&info, 0, sizeof(info));
    nbRes = NBDeviceGetScanFormatInfo(hDevice, (NBDeviceScanFormat)10, &info);
    if (NBFailed(nbRes))
    {
        log_printf(LOG_DBG, "NBDeviceGetScanFormatInfo(fmt=10) failed %d\r\n", (int)nbRes);
        return (int)nbRes;
    }

    log_printf(LOG_DBG,
               "ID3 capture fmt=10 width=%u height=%u hDpi=%u vDpi=%u bytes=%lu\r\n",
               (unsigned int)info.uiWidth,
               (unsigned int)info.uiHeight,
               (unsigned int)info.uiHorizontalResolution,
               (unsigned int)info.uiVerticalResolution,
               (unsigned long)(info.uiWidth * info.uiHeight));

    if ((info.uiWidth != NEXT_ID3_IMAGE_WIDTH) || (info.uiHeight != NEXT_ID3_IMAGE_HEIGHT))
    {
        log_printf(LOG_DBG, "Unexpected image geometry for ID3 path\r\n");
        return -101;
    }

    pImage = (uint8_t *)malloc(NEXT_ID3_IMAGE_SIZE);
    if (pImage == NULL)
    {
        log_printf(LOG_DBG, "Image malloc failed\r\n");
        return -102;
    }

    memset(pImage, 0, NEXT_ID3_IMAGE_SIZE);

    log_printf(LOG_DBG, "Place finger for ID3 extraction in 5 seconds...\r\n");
    HAL_Delay(5000);

    nbRes = NBDeviceScan(
        hDevice,
        (NBDeviceScanFormat)10,
        pImage,
        NEXT_ID3_IMAGE_SIZE,
        NB_DEVICE_SCAN_SKIP_FINGER_DETECTION_FLAG,
        &scanStatus);

    log_printf(LOG_DBG, "NBDeviceScan -> %d status=%d\r\n", (int)nbRes, (int)scanStatus);
    if (NBFailed(nbRes))
    {
        free(pImage);
        return (int)nbRes;
    }

    for (i = 0; i < NEXT_ID3_IMAGE_SIZE; i++)
    {
        uint8_t v = pImage[i];
        sum += v;
        if (v < minv) minv = v;
        if (v > maxv) maxv = v;
    }

    log_printf(LOG_DBG,
               "Image stats: min=%u max=%u mean=%lu first8=%u,%u,%u,%u,%u,%u,%u,%u\r\n",
               (unsigned int)minv,
               (unsigned int)maxv,
               (unsigned long)(sum / NEXT_ID3_IMAGE_SIZE),
               pImage[0], pImage[1], pImage[2], pImage[3],
               pImage[4], pImage[5], pImage[6], pImage[7]);

    templateObjSize = sizeOf_ID3FINGER_TEMPLATE();
    extractObjSize = sizeOf_ID3FINGER_EXTRACT((int)NEXT_ID3_IMAGE_WIDTH, (int)NEXT_ID3_IMAGE_HEIGHT);

    log_printf(LOG_DBG,
               "ID3 object sizes: template=%d extract=%d\r\n",
               templateObjSize,
               extractObjSize);

    if ((templateObjSize <= 0) || (extractObjSize <= 0))
    {
        free(pImage);
        return -103;
    }

    pTemplateBuffer = (uint8_t *)malloc((size_t)templateObjSize);
    pExtractBuffer = (uint8_t *)malloc((size_t)extractObjSize);

    if ((pTemplateBuffer == NULL) || (pExtractBuffer == NULL))
    {
        log_printf(LOG_DBG, "ID3 object malloc failed\r\n");
        free(pImage);
        free(pTemplateBuffer);
        free(pExtractBuffer);
        return -104;
    }

    memset(pTemplateBuffer, 0, (size_t)templateObjSize);
    memset(pExtractBuffer, 0, (size_t)extractObjSize);

    id3Res = id3FingerTemplate_Initialize(&hTemplate, pTemplateBuffer, templateObjSize);
    log_printf(LOG_DBG, "id3FingerTemplate_Initialize -> %d\r\n", id3Res);
    if (id3Res != ID3_SUCCESS)
    {
        free(pImage);
        free(pTemplateBuffer);
        free(pExtractBuffer);
        return id3Res;
    }

    id3Res = id3FingerExtract_Initialize(
        &hExtract,
        (int)NEXT_ID3_IMAGE_WIDTH,
        (int)NEXT_ID3_IMAGE_HEIGHT,
        pExtractBuffer,
        extractObjSize);
    log_printf(LOG_DBG, "id3FingerExtract_Initialize -> %d\r\n", id3Res);
    if (id3Res != ID3_SUCCESS)
    {
        free(pImage);
        free(pTemplateBuffer);
        free(pExtractBuffer);
        return id3Res;
    }

    log_printf(LOG_DBG, "Trying %s dpi=%u\r\n",
               NEXT_ID3_MODE_NAME,
               (unsigned int)NEXT_ID3_DPI);

    id3Res = id3FingerExtract_CreateTemplate(
        hExtract,
        pImage,
        hTemplate,
        NEXT_ID3_MODE,
        NEXT_ID3_DPI);

    log_printf(LOG_DBG, "CreateTemplate(%s) -> %d\r\n",
               NEXT_ID3_MODE_NAME,
               id3Res);

    if (id3Res != ID3_SUCCESS)
    {
        free(pImage);
        free(pTemplateBuffer);
        free(pExtractBuffer);
        return id3Res;
    }

    id3Res = id3FingerTemplate_GetImageQuality(hTemplate, &imageQuality);
    log_printf(LOG_DBG,
               "id3FingerTemplate_GetImageQuality -> %d quality=%u\r\n",
               id3Res,
               (unsigned int)imageQuality);

    log_printf(LOG_DBG, "ID3 extract from Next capture OK\r\n");

    free(pImage);
    free(pTemplateBuffer);
    free(pExtractBuffer);

    return ID3_SUCCESS;
}

