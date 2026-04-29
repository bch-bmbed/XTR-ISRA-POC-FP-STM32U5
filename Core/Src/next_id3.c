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

#include "id3FingerMatch.h"

#define NEXT_ID3_IMAGE_WIDTH   300U
#define NEXT_ID3_IMAGE_HEIGHT  400U
#define NEXT_ID3_IMAGE_SIZE    (NEXT_ID3_IMAGE_WIDTH * NEXT_ID3_IMAGE_HEIGHT)

#define NEXT_ID3_SCAN_FORMAT   ((NBDeviceScanFormat)10)
#define NEXT_ID3_MODE          FingerExtractMode_SmallSensor370DPI
#define NEXT_ID3_MODE_NAME     "SmallSensor370DPI"
#define NEXT_ID3_DPI           370U

#define NEXT_ID3_FD_REMOVED_THRESHOLD  20U
#define NEXT_ID3_FD_PRESENT_THRESHOLD  70U
#define NEXT_ID3_FD_STABLE_MS          300U
#define NEXT_ID3_FD_TIMEOUT_MS         10000U
#define NEXT_ID3_FD_POLL_MS            50U

static NBResult NEXT_ID3_GetFingerDetect(HNBDevice hDevice, uint32_t *pValue)
{
    return NBDeviceGetFingerDetectValue(
        hDevice,
        NB_DEVICE_DEFAULT_FINGER_DETECT_TYPE,
        pValue);

    HAL_Delay(300);
}

static int NEXT_ID3_WaitFingerRemoved(HNBDevice hDevice, uint32_t timeoutMs)
{
    uint32_t start = HAL_GetTick();

    while ((HAL_GetTick() - start) < timeoutMs)
    {
        uint32_t fd = 0;
        NBResult res = NEXT_ID3_GetFingerDetect(hDevice, &fd);

        if (NBSucceeded(res))
        {
            log_printf(LOG_DBG, "FD removed wait value=%lu\r\n", (unsigned long)fd);

            if (fd <= NEXT_ID3_FD_REMOVED_THRESHOLD)
            {
                return 0;
            }
        }

        HAL_Delay(NEXT_ID3_FD_POLL_MS);
    }

    return -1;
}

static int NEXT_ID3_WaitFingerStable(HNBDevice hDevice,
                                     uint32_t threshold,
                                     uint32_t stableMs,
                                     uint32_t timeoutMs)
{
    uint32_t start = HAL_GetTick();
    uint32_t stableStart = 0;

    while ((HAL_GetTick() - start) < timeoutMs)
    {
        uint32_t fd = 0;
        NBResult res = NEXT_ID3_GetFingerDetect(hDevice, &fd);

        if (NBSucceeded(res))
        {
            log_printf(LOG_DBG, "FD stable wait value=%lu\r\n", (unsigned long)fd);

            if (fd >= threshold)
            {
                if (stableStart == 0)
                {
                    stableStart = HAL_GetTick();
                }

                if ((HAL_GetTick() - stableStart) >= stableMs)
                {
                    return 0;
                }
            }
            else
            {
                stableStart = 0;
            }
        }

        HAL_Delay(NEXT_ID3_FD_POLL_MS);
    }

    return -1;
}

//static void NEXT_ID3_InvertImage(uint8_t *pImage, uint32_t size)
//{
//    uint32_t i;
//    for (i = 0; i < size; i++)
//    {
//        pImage[i] = (uint8_t)(255U - pImage[i]);
//    }
//}
//
//typedef struct
//{
//    id3FingerExtractMode mode;
//    const char *name;
//} NEXT_ID3_ModeEntry;
//
//static unsigned short NEXT_ID3_ModeToDpi(id3FingerExtractMode mode)
//{
//    switch (mode)
//    {
//    case FingerExtractMode_LowSpeed370DPI:
//    case FingerExtractMode_HighSpeed370DPI:
//    case FingerExtractMode_SmallSensor370DPI:
//        return 370;
//
//    case FingerExtractMode_LowSpeed:
//    case FingerExtractMode_HighSpeed:
//    case FingerExtractMode_SmallSensor:
//    default:
//        return 500;
//    }
//}
typedef struct
{
    id3FingerExtractMode mode;
    uint16_t dpi;
    const char *name;
} NEXT_ID3_ModeBench;

static const NEXT_ID3_ModeBench kId3Modes[] =
{
    { FingerExtractMode_SmallSensor370DPI, 370, "SmallSensor370DPI" },
    { FingerExtractMode_LowSpeed370DPI,    370, "LowSpeed370DPI"    },
    { FingerExtractMode_HighSpeed370DPI,   370, "HighSpeed370DPI"   },
    { FingerExtractMode_SmallSensor,       500, "SmallSensor500DPI" },
    { FingerExtractMode_LowSpeed,          500, "LowSpeed500DPI"    },
    { FingerExtractMode_HighSpeed,         500, "HighSpeed500DPI"   },
};

typedef enum
{
    NEXT_ID3_VARIANT_NORMAL = 0,
    NEXT_ID3_VARIANT_INVERTED,
    NEXT_ID3_VARIANT_STRETCH,
    NEXT_ID3_VARIANT_MIRROR_X,
    NEXT_ID3_VARIANT_MIRROR_Y,
} NEXT_ID3_ImageVariant;

typedef struct
{
    NEXT_ID3_ImageVariant variant;
    const char *name;
} NEXT_ID3_VariantEntry;

static const NEXT_ID3_VariantEntry kVariants[] =
{
    { NEXT_ID3_VARIANT_NORMAL,   "normal"   },
    { NEXT_ID3_VARIANT_INVERTED, "inverted" },
    { NEXT_ID3_VARIANT_STRETCH,  "stretch"  },
    { NEXT_ID3_VARIANT_MIRROR_X, "mirrorX"  },
    { NEXT_ID3_VARIANT_MIRROR_Y, "mirrorY"  },
};

typedef struct
{
    uint32_t scanFlags;
    uint32_t steadyDelayMs;
    const char *name;
} NEXT_ID3_CaptureSetting;

static const NEXT_ID3_CaptureSetting kCaptureSettings[] =
{
    { NB_DEVICE_SCAN_SKIP_FINGER_DETECTION_FLAG,  500, "skip_fd_500ms"  },
    { NB_DEVICE_SCAN_SKIP_FINGER_DETECTION_FLAG, 1500, "skip_fd_1500ms" },
    { NB_DEVICE_SCAN_SKIP_FINGER_DETECTION_FLAG, 2500, "skip_fd_2500ms" },
    { 0U,                                        500, "normal_500ms"   },
    { 0U,                                       1500, "normal_1500ms"  },
    { 0U,                                       2500, "normal_2500ms"  },
};

typedef struct
{
    int useScanEx;
    uint32_t flags;
    const char *name;
} NEXT_ID3_ScanSetting;

static const NEXT_ID3_ScanSetting kScanSettings[] =
{
    { 0, 0U, "Scan_normal" },
    { 0, NB_DEVICE_SCAN_SKIP_FINGER_NOT_REMOVED_STATUS_FLAG, "Scan_skipNotRemoved" },
    { 1, 0U, "ScanEx_normal" },
    { 1, NB_DEVICE_SCAN_SKIP_FINGER_NOT_REMOVED_STATUS_FLAG, "ScanEx_skipNotRemoved" },
};

static void NEXT_ID3_PrepareVariant(const uint8_t *src,
                                    uint8_t *dst,
                                    uint32_t width,
                                    uint32_t height,
                                    NEXT_ID3_ImageVariant variant)
{
    uint32_t x, y;
    uint8_t minv = 255;
    uint8_t maxv = 0;

    memcpy(dst, src, width * height);

    switch (variant)
    {
    case NEXT_ID3_VARIANT_INVERTED:
        for (uint32_t i = 0; i < width * height; i++)
        {
            dst[i] = (uint8_t)(255U - dst[i]);
        }
        break;

    case NEXT_ID3_VARIANT_STRETCH:
        for (uint32_t i = 0; i < width * height; i++)
        {
            if (dst[i] < minv) minv = dst[i];
            if (dst[i] > maxv) maxv = dst[i];
        }

        if (maxv > minv)
        {
            for (uint32_t i = 0; i < width * height; i++)
            {
                dst[i] = (uint8_t)(((uint32_t)(dst[i] - minv) * 255U) / (uint32_t)(maxv - minv));
            }
        }
        break;

    case NEXT_ID3_VARIANT_MIRROR_X:
        for (y = 0; y < height; y++)
        {
            for (x = 0; x < width; x++)
            {
                dst[y * width + x] = src[y * width + (width - 1U - x)];
            }
        }
        break;

    case NEXT_ID3_VARIANT_MIRROR_Y:
        for (y = 0; y < height; y++)
        {
            memcpy(&dst[y * width],
                   &src[(height - 1U - y) * width],
                   width);
        }
        break;

    case NEXT_ID3_VARIANT_NORMAL:
    default:
        break;
    }
}

static int NEXT_ID3_EvaluateImageBestQuality(const uint8_t *pImage,
                                             int *pBestQuality,
                                             const char **pBestVariant)
{
    uint8_t *pVariantImage = NULL;
    uint8_t *pTemplateBuffer = NULL;
    uint8_t *pExtractBuffer = NULL;

    int templateObjSize;
    int extractObjSize;
    int bestQuality = -1;
    const char *bestVariant = "none";

    const NEXT_ID3_VariantEntry variants[] =
    {
        { NEXT_ID3_VARIANT_NORMAL,  "normal"  },
        { NEXT_ID3_VARIANT_STRETCH, "stretch" },
    };

    if ((pImage == NULL) || (pBestQuality == NULL) || (pBestVariant == NULL))
    {
        return ID3_E_INVALID_PARAMETER;
    }

    templateObjSize = sizeOf_ID3FINGER_TEMPLATE();
    extractObjSize = sizeOf_ID3FINGER_EXTRACT((int)NEXT_ID3_IMAGE_WIDTH,
                                              (int)NEXT_ID3_IMAGE_HEIGHT);

    if ((templateObjSize <= 0) || (extractObjSize <= 0))
    {
        return -103;
    }

    pVariantImage = malloc(NEXT_ID3_IMAGE_SIZE);
    pTemplateBuffer = malloc((size_t)templateObjSize);
    pExtractBuffer = malloc((size_t)extractObjSize);

    if ((pVariantImage == NULL) || (pTemplateBuffer == NULL) || (pExtractBuffer == NULL))
    {
        free(pVariantImage);
        free(pTemplateBuffer);
        free(pExtractBuffer);
        return -104;
    }

    for (uint32_t v = 0; v < sizeof(variants) / sizeof(variants[0]); v++)
    {
        ID3FINGER_TEMPLATE hTemplate = NULL;
        ID3FINGER_EXTRACT hExtract = NULL;
        unsigned char quality = 0;
        int res;
        int qRes;

        NEXT_ID3_PrepareVariant(
            pImage,
            pVariantImage,
            NEXT_ID3_IMAGE_WIDTH,
            NEXT_ID3_IMAGE_HEIGHT,
            variants[v].variant);

        memset(pTemplateBuffer, 0, (size_t)templateObjSize);
        memset(pExtractBuffer, 0, (size_t)extractObjSize);

        res = id3FingerTemplate_Initialize(&hTemplate,
                                           pTemplateBuffer,
                                           templateObjSize);
        if (res != ID3_SUCCESS)
        {
            continue;
        }

        res = id3FingerExtract_Initialize(&hExtract,
                                          (int)NEXT_ID3_IMAGE_WIDTH,
                                          (int)NEXT_ID3_IMAGE_HEIGHT,
                                          pExtractBuffer,
                                          extractObjSize);
        if (res != ID3_SUCCESS)
        {
            continue;
        }

        res = id3FingerExtract_CreateTemplate(
            hExtract,
            pVariantImage,
            hTemplate,
            FingerExtractMode_SmallSensor370DPI,
            370U);

        if (res != ID3_SUCCESS)
        {
            continue;
        }

        qRes = id3FingerTemplate_GetImageQuality(hTemplate, &quality);
        if ((qRes == ID3_SUCCESS) && ((int)quality > bestQuality))
        {
            bestQuality = (int)quality;
            bestVariant = variants[v].name;
        }
    }

    free(pVariantImage);
    free(pTemplateBuffer);
    free(pExtractBuffer);

    *pBestQuality = bestQuality;
    *pBestVariant = bestVariant;

    return ID3_SUCCESS;
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

static int NEXT_ID3_CaptureTemplate(uint8_t *pTemplateBuffer,
                                    int templateObjSize,
                                    int *pQuality)
{
    NBResult nbRes;
    HNBDevice hDevice;
    NBDeviceScanFormatInfo info;
    NBDeviceScanStatus scanStatus = 0;

    uint8_t *pImage = NULL;
    uint8_t *pExtractBuffer = NULL;

    ID3FINGER_TEMPLATE hTemplate = NULL;
    ID3FINGER_EXTRACT hExtract = NULL;

    int id3Res;
    int extractObjSize;
    unsigned char imageQuality = 0;

    uint32_t i;
    uint32_t sum = 0;
    uint8_t minv = 255;
    uint8_t maxv = 0;

    if ((pTemplateBuffer == NULL) || (templateObjSize <= 0) || (pQuality == NULL))
    {
        return ID3_E_INVALID_PARAMETER;
    }

    *pQuality = 0;

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        log_printf(LOG_DBG, "NEXT_DeviceGetHandle returned NULL\r\n");
        return -100;
    }

    memset(&info, 0, sizeof(info));
    nbRes = NBDeviceGetScanFormatInfo(hDevice, NEXT_ID3_SCAN_FORMAT, &info);
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
        NEXT_ID3_SCAN_FORMAT,
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

    extractObjSize = sizeOf_ID3FINGER_EXTRACT((int)NEXT_ID3_IMAGE_WIDTH, (int)NEXT_ID3_IMAGE_HEIGHT);

    log_printf(LOG_DBG,
               "ID3 object sizes: template=%d extract=%d\r\n",
               templateObjSize,
               extractObjSize);

    if (extractObjSize <= 0)
    {
        free(pImage);
        return -103;
    }

    pExtractBuffer = (uint8_t *)malloc((size_t)extractObjSize);
    if (pExtractBuffer == NULL)
    {
        log_printf(LOG_DBG, "ID3 extract malloc failed\r\n");
        free(pImage);
        return -104;
    }

    memset(pTemplateBuffer, 0, (size_t)templateObjSize);
    memset(pExtractBuffer, 0, (size_t)extractObjSize);

    id3Res = id3FingerTemplate_Initialize(&hTemplate, pTemplateBuffer, templateObjSize);
    log_printf(LOG_DBG, "id3FingerTemplate_Initialize -> %d\r\n", id3Res);
    if (id3Res != ID3_SUCCESS)
    {
        free(pImage);
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
        free(pExtractBuffer);
        return id3Res;
    }

    id3Res = id3FingerTemplate_GetImageQuality(hTemplate, &imageQuality);
    log_printf(LOG_DBG,
               "id3FingerTemplate_GetImageQuality -> %d quality=%u\r\n",
               id3Res,
               (unsigned int)imageQuality);

    if (id3Res == ID3_SUCCESS)
    {
        *pQuality = (int)imageQuality;
    }

    free(pImage);
    free(pExtractBuffer);

    return id3Res;
}

int NEXT_ID3_TestTwoTemplates(void)
{
    int res;
    int templateObjSize;
    int quality1 = 0;
    int quality2 = 0;

    uint8_t *pTemplate1 = NULL;
    uint8_t *pTemplate2 = NULL;

    templateObjSize = sizeOf_ID3FINGER_TEMPLATE();
    log_printf(LOG_DBG, "ID3 template object size=%d\r\n", templateObjSize);

    if (templateObjSize <= 0)
    {
        return -1;
    }

    pTemplate1 = (uint8_t *)malloc((size_t)templateObjSize);
    pTemplate2 = (uint8_t *)malloc((size_t)templateObjSize);

    if ((pTemplate1 == NULL) || (pTemplate2 == NULL))
    {
        log_printf(LOG_DBG, "Template malloc failed\r\n");
        free(pTemplate1);
        free(pTemplate2);
        return -2;
    }

    log_printf(LOG_DBG, "=== ID3 TEMPLATE 1 ===\r\n");
    res = NEXT_ID3_CaptureTemplate(pTemplate1, templateObjSize, &quality1);
    if (res != ID3_SUCCESS)
    {
        log_printf(LOG_DBG, "Template 1 extraction failed %d\r\n", res);
        free(pTemplate1);
        free(pTemplate2);
        return res;
    }

    log_printf(LOG_DBG, "Template 1 OK quality=%d\r\n", quality1);

    log_printf(LOG_DBG, "Remove finger, then prepare same finger for template 2\r\n");
    HAL_Delay(3000);

    log_printf(LOG_DBG, "=== ID3 TEMPLATE 2 ===\r\n");
    res = NEXT_ID3_CaptureTemplate(pTemplate2, templateObjSize, &quality2);
    if (res != ID3_SUCCESS)
    {
        log_printf(LOG_DBG, "Template 2 extraction failed %d\r\n", res);
        free(pTemplate1);
        free(pTemplate2);
        return res;
    }

    log_printf(LOG_DBG, "Template 2 OK quality=%d\r\n", quality2);
    log_printf(LOG_DBG, "ID3 two-template capture OK\r\n");

    free(pTemplate1);
    free(pTemplate2);

    return ID3_SUCCESS;
}

int NEXT_ID3_BenchmarkImageVariants(void)
{
    NBResult nbRes;
    HNBDevice hDevice;
    NBDeviceScanFormatInfo info;
    NBDeviceScanStatus scanStatus = 0;

    uint8_t *pImage = NULL;
    uint8_t *pVariantImage = NULL;
    uint8_t *pTemplateBuffer = NULL;
    uint8_t *pExtractBuffer = NULL;

    int templateObjSize;
    int extractObjSize;

    int bestQuality = -1;
    const char *bestModeName = "none";
    const char *bestVariantName = "none";

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        log_printf(LOG_DBG, "NEXT_DeviceGetHandle returned NULL\r\n");
        return -100;
    }

    memset(&info, 0, sizeof(info));
    nbRes = NBDeviceGetScanFormatInfo(hDevice, NEXT_ID3_SCAN_FORMAT, &info);
    if (NBFailed(nbRes))
    {
        log_printf(LOG_DBG, "NBDeviceGetScanFormatInfo(fmt=10) failed %d\r\n", (int)nbRes);
        return (int)nbRes;
    }

    log_printf(LOG_DBG,
               "ID3 variant bench fmt=10 width=%u height=%u hDpi=%u vDpi=%u bytes=%lu\r\n",
               (unsigned int)info.uiWidth,
               (unsigned int)info.uiHeight,
               (unsigned int)info.uiHorizontalResolution,
               (unsigned int)info.uiVerticalResolution,
               (unsigned long)(info.uiWidth * info.uiHeight));

    pImage = malloc(NEXT_ID3_IMAGE_SIZE);
    pVariantImage = malloc(NEXT_ID3_IMAGE_SIZE);

    if ((pImage == NULL) || (pVariantImage == NULL))
    {
        log_printf(LOG_DBG, "Image malloc failed\r\n");
        free(pImage);
        free(pVariantImage);
        return -102;
    }

    log_printf(LOG_DBG, "Place finger for ID3 variant bench in 5 seconds...\r\n");
    HAL_Delay(5000);

    nbRes = NBDeviceScan(
        hDevice,
        NEXT_ID3_SCAN_FORMAT,
        pImage,
        NEXT_ID3_IMAGE_SIZE,
        NB_DEVICE_SCAN_SKIP_FINGER_DETECTION_FLAG,
        &scanStatus);

    log_printf(LOG_DBG, "NBDeviceScan -> %d status=%d\r\n", (int)nbRes, (int)scanStatus);

    if (NBFailed(nbRes))
    {
        free(pImage);
        free(pVariantImage);
        return (int)nbRes;
    }

    templateObjSize = sizeOf_ID3FINGER_TEMPLATE();
    extractObjSize = sizeOf_ID3FINGER_EXTRACT((int)NEXT_ID3_IMAGE_WIDTH,
                                              (int)NEXT_ID3_IMAGE_HEIGHT);

    pTemplateBuffer = malloc((size_t)templateObjSize);
    pExtractBuffer = malloc((size_t)extractObjSize);

    if ((pTemplateBuffer == NULL) || (pExtractBuffer == NULL))
    {
        log_printf(LOG_DBG, "ID3 malloc failed\r\n");
        free(pImage);
        free(pVariantImage);
        free(pTemplateBuffer);
        free(pExtractBuffer);
        return -104;
    }

    for (uint32_t v = 0; v < sizeof(kVariants) / sizeof(kVariants[0]); v++)
    {
        NEXT_ID3_PrepareVariant(
            pImage,
            pVariantImage,
            NEXT_ID3_IMAGE_WIDTH,
            NEXT_ID3_IMAGE_HEIGHT,
            kVariants[v].variant);

        for (uint32_t m = 0; m < sizeof(kId3Modes) / sizeof(kId3Modes[0]); m++)
        {
            ID3FINGER_TEMPLATE hTemplate = NULL;
            ID3FINGER_EXTRACT hExtract = NULL;
            unsigned char quality = 0;
            int res;
            int qRes;

            memset(pTemplateBuffer, 0, (size_t)templateObjSize);
            memset(pExtractBuffer, 0, (size_t)extractObjSize);

            res = id3FingerTemplate_Initialize(&hTemplate,
                                               pTemplateBuffer,
                                               templateObjSize);
            if (res != ID3_SUCCESS)
            {
                log_printf(LOG_DBG, "VAR %-9s MODE %-20s templateInit=%d\r\n",
                           kVariants[v].name,
                           kId3Modes[m].name,
                           res);
                continue;
            }

            res = id3FingerExtract_Initialize(&hExtract,
                                              (int)NEXT_ID3_IMAGE_WIDTH,
                                              (int)NEXT_ID3_IMAGE_HEIGHT,
                                              pExtractBuffer,
                                              extractObjSize);
            if (res != ID3_SUCCESS)
            {
                log_printf(LOG_DBG, "VAR %-9s MODE %-20s extractInit=%d\r\n",
                           kVariants[v].name,
                           kId3Modes[m].name,
                           res);
                continue;
            }

            res = id3FingerExtract_CreateTemplate(
                hExtract,
                pVariantImage,
                hTemplate,
                kId3Modes[m].mode,
                kId3Modes[m].dpi);

            qRes = ID3_E_INVALID_HANDLE;
            if (res == ID3_SUCCESS)
            {
                qRes = id3FingerTemplate_GetImageQuality(hTemplate, &quality);
            }

            log_printf(LOG_DBG,
                       "VAR %-9s MODE %-20s dpi=%u extract=%d qRes=%d quality=%u\r\n",
                       kVariants[v].name,
                       kId3Modes[m].name,
                       (unsigned int)kId3Modes[m].dpi,
                       res,
                       qRes,
                       (unsigned int)quality);

            if ((res == ID3_SUCCESS) &&
                (qRes == ID3_SUCCESS) &&
                ((int)quality > bestQuality))
            {
                bestQuality = (int)quality;
                bestModeName = kId3Modes[m].name;
                bestVariantName = kVariants[v].name;
            }
        }
    }

    log_printf(LOG_DBG,
               "ID3 VARIANT BENCH BEST variant=%s mode=%s quality=%d\r\n",
               bestVariantName,
               bestModeName,
               bestQuality);

    free(pImage);
    free(pVariantImage);
    free(pTemplateBuffer);
    free(pExtractBuffer);

    return ID3_SUCCESS;
}

int NEXT_ID3_BenchmarkCaptureSettings(void)
{
    NBResult nbRes;
    HNBDevice hDevice;
    NBDeviceScanFormatInfo info;
    NBDeviceScanStatus scanStatus = 0;

    uint8_t *pImage = NULL;

    int globalBestQuality = -1;
    const char *globalBestSetting = "none";
    const char *globalBestVariant = "none";

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        log_printf(LOG_DBG, "NEXT_DeviceGetHandle returned NULL\r\n");
        return -100;
    }

    memset(&info, 0, sizeof(info));
    nbRes = NBDeviceGetScanFormatInfo(hDevice, NEXT_ID3_SCAN_FORMAT, &info);
    if (NBFailed(nbRes))
    {
        log_printf(LOG_DBG, "NBDeviceGetScanFormatInfo(fmt=10) failed %d\r\n", (int)nbRes);
        return (int)nbRes;
    }

    log_printf(LOG_DBG,
               "ID3 capture settings bench fmt=10 width=%u height=%u hDpi=%u vDpi=%u bytes=%lu\r\n",
               (unsigned int)info.uiWidth,
               (unsigned int)info.uiHeight,
               (unsigned int)info.uiHorizontalResolution,
               (unsigned int)info.uiVerticalResolution,
               (unsigned long)(info.uiWidth * info.uiHeight));

    pImage = malloc(NEXT_ID3_IMAGE_SIZE);
    if (pImage == NULL)
    {
        log_printf(LOG_DBG, "Image malloc failed\r\n");
        return -102;
    }

    for (uint32_t s = 0; s < sizeof(kCaptureSettings) / sizeof(kCaptureSettings[0]); s++)
    {
        int bestQuality = -1;
        const char *bestVariant = "none";

        uint32_t sum = 0;
        uint8_t minv = 255;
        uint8_t maxv = 0;

        memset(pImage, 0, NEXT_ID3_IMAGE_SIZE);

        log_printf(LOG_DBG, "CAP %-16s place finger in 3 seconds...\r\n",
                   kCaptureSettings[s].name);
        HAL_Delay(3000);

        log_printf(LOG_DBG, "CAP %-16s keep steady %lu ms...\r\n",
                   kCaptureSettings[s].name,
                   (unsigned long)kCaptureSettings[s].steadyDelayMs);
        HAL_Delay(kCaptureSettings[s].steadyDelayMs);

        nbRes = NBDeviceScan(
            hDevice,
            NEXT_ID3_SCAN_FORMAT,
            pImage,
            NEXT_ID3_IMAGE_SIZE,
            kCaptureSettings[s].scanFlags,
            &scanStatus);

        if (NBFailed(nbRes))
        {
            log_printf(LOG_DBG,
                       "CAP %-16s scan=%d status=%d\r\n",
                       kCaptureSettings[s].name,
                       (int)nbRes,
                       (int)scanStatus);
            continue;
        }

        for (uint32_t i = 0; i < NEXT_ID3_IMAGE_SIZE; i++)
        {
            uint8_t v = pImage[i];
            sum += v;
            if (v < minv) minv = v;
            if (v > maxv) maxv = v;
        }

        NEXT_ID3_EvaluateImageBestQuality(pImage, &bestQuality, &bestVariant);

        log_printf(LOG_DBG,
                   "CAP %-16s scan=%d status=%d min=%u max=%u mean=%lu bestVariant=%s quality=%d\r\n",
                   kCaptureSettings[s].name,
                   (int)nbRes,
                   (int)scanStatus,
                   (unsigned int)minv,
                   (unsigned int)maxv,
                   (unsigned long)(sum / NEXT_ID3_IMAGE_SIZE),
                   bestVariant,
                   bestQuality);

        if (bestQuality > globalBestQuality)
        {
            globalBestQuality = bestQuality;
            globalBestSetting = kCaptureSettings[s].name;
            globalBestVariant = bestVariant;
        }

        log_printf(LOG_DBG, "Remove finger before next setting\r\n");
        HAL_Delay(2500);
    }

    log_printf(LOG_DBG,
               "ID3 CAPTURE BENCH BEST setting=%s variant=%s quality=%d\r\n",
               globalBestSetting,
               globalBestVariant,
               globalBestQuality);

    free(pImage);

    return ID3_SUCCESS;
}

int NEXT_ID3_BenchmarkScanEx(void)
{
    NBResult nbRes;
    HNBDevice hDevice;
    NBDeviceScanFormatInfo info;
    NBDeviceScanStatus scanStatus = 0;

    uint8_t *pImage = NULL;

    int bestQualityGlobal = -1;
    const char *bestSettingGlobal = "none";
    const char *bestVariantGlobal = "none";

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        log_printf(LOG_DBG, "Device handle NULL\r\n");
        return -1;
    }

    memset(&info, 0, sizeof(info));
    nbRes = NBDeviceGetScanFormatInfo(hDevice, NEXT_ID3_SCAN_FORMAT, &info);
    if (NBFailed(nbRes))
    {
        log_printf(LOG_DBG, "GetScanFormatInfo failed %d\r\n", (int)nbRes);
        return (int)nbRes;
    }

    log_printf(LOG_DBG,
        "ScanEx bench fmt=%u w=%u h=%u bytes=%lu\r\n",
        (unsigned int)NEXT_ID3_SCAN_FORMAT,
        (unsigned int)info.uiWidth,
        (unsigned int)info.uiHeight,
        (unsigned long)(info.uiWidth * info.uiHeight));

    pImage = malloc(NEXT_ID3_IMAGE_SIZE);
    if (!pImage)
        return -2;

    for (uint32_t s = 0; s < sizeof(kScanSettings)/sizeof(kScanSettings[0]); s++)
    {
        int bestQuality = -1;
        const char *bestVariant = "none";

        uint32_t sum = 0;
        uint8_t minv = 255;
        uint8_t maxv = 0;

        memset(pImage, 0, NEXT_ID3_IMAGE_SIZE);

        log_printf(LOG_DBG, "TEST %-20s place finger...\r\n", kScanSettings[s].name);
        HAL_Delay(3000);

        if (kScanSettings[s].useScanEx)
        {
        	nbRes = NBDeviceScanEx(
        	    hDevice,
        	    NEXT_ID3_SCAN_FORMAT,
        	    5000,                 // timeout ms
        	    NULL,                 // preview callback
        	    NULL,                 // user param
        	    pImage,
        	    NEXT_ID3_IMAGE_SIZE,
        	    kScanSettings[s].flags,
        	    &scanStatus);
        }
        else
        {
            HAL_Delay(500); // steady time

            nbRes = NBDeviceScan(
                hDevice,
                NEXT_ID3_SCAN_FORMAT,
                pImage,
                NEXT_ID3_IMAGE_SIZE,
                kScanSettings[s].flags,
                &scanStatus);
        }

        if (NBFailed(nbRes))
        {
            log_printf(LOG_DBG,
                "TEST %-20s scan FAILED %d\r\n",
                kScanSettings[s].name,
                (int)nbRes);
            continue;
        }

        // stats image
        for (uint32_t i = 0; i < NEXT_ID3_IMAGE_SIZE; i++)
        {
            uint8_t v = pImage[i];
            sum += v;
            if (v < minv) minv = v;
            if (v > maxv) maxv = v;
        }

        // qualité ID3 (normal + stretch)
        NEXT_ID3_EvaluateImageBestQuality(pImage, &bestQuality, &bestVariant);

        log_printf(LOG_DBG,
            "TEST %-20s status=%d min=%u max=%u mean=%lu variant=%s quality=%d\r\n",
            kScanSettings[s].name,
            (int)scanStatus,
            (unsigned int)minv,
            (unsigned int)maxv,
            (unsigned long)(sum / NEXT_ID3_IMAGE_SIZE),
            bestVariant,
            bestQuality);

        if (bestQuality > bestQualityGlobal)
        {
            bestQualityGlobal = bestQuality;
            bestSettingGlobal = kScanSettings[s].name;
            bestVariantGlobal = bestVariant;
        }

        log_printf(LOG_DBG, "Remove finger\r\n");
        HAL_Delay(2500);
    }

    log_printf(LOG_DBG,
        "BEST SCAN setting=%s variant=%s quality=%d\r\n",
        bestSettingGlobal,
        bestVariantGlobal,
        bestQualityGlobal);

    free(pImage);
    return 0;
}

int NEXT_ID3_BenchmarkFingerDetectCapture(void)
{
    NBResult nbRes;
    HNBDevice hDevice;
    NBDeviceScanFormatInfo info;
    NBDeviceScanStatus scanStatus = 0;

    uint8_t *pImage = NULL;

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        log_printf(LOG_DBG, "Device handle NULL\r\n");
        return -1;
    }

    memset(&info, 0, sizeof(info));
    nbRes = NBDeviceGetScanFormatInfo(hDevice, NEXT_ID3_SCAN_FORMAT, &info);
    if (NBFailed(nbRes))
    {
        log_printf(LOG_DBG, "GetScanFormatInfo failed %d\r\n", (int)nbRes);
        return (int)nbRes;
    }

    log_printf(LOG_DBG,
               "FD capture bench fmt=10 w=%u h=%u bytes=%lu\r\n",
               (unsigned int)info.uiWidth,
               (unsigned int)info.uiHeight,
               (unsigned long)(info.uiWidth * info.uiHeight));

    pImage = malloc(NEXT_ID3_IMAGE_SIZE);
    if (pImage == NULL)
    {
        return -2;
    }

    for (uint32_t attempt = 1; attempt <= 5; attempt++)
    {
        int bestQuality = -1;
        const char *bestVariant = "none";

        uint32_t sum = 0;
        uint8_t minv = 255;
        uint8_t maxv = 0;

        memset(pImage, 0, NEXT_ID3_IMAGE_SIZE);

        log_printf(LOG_DBG, "ATTEMPT %lu remove finger...\r\n", (unsigned long)attempt);
        if (NEXT_ID3_WaitFingerRemoved(hDevice, NEXT_ID3_FD_TIMEOUT_MS) != 0)
        {
            log_printf(LOG_DBG, "ATTEMPT %lu wait removed timeout\r\n", (unsigned long)attempt);
            continue;
        }

        log_printf(LOG_DBG, "ATTEMPT %lu place finger stable...\r\n", (unsigned long)attempt);
        if (NEXT_ID3_WaitFingerStable(hDevice,
                                      NEXT_ID3_FD_PRESENT_THRESHOLD,
                                      NEXT_ID3_FD_STABLE_MS,
                                      NEXT_ID3_FD_TIMEOUT_MS) != 0)
        {
            log_printf(LOG_DBG, "ATTEMPT %lu wait stable timeout\r\n", (unsigned long)attempt);
            continue;
        }

        nbRes = NBDeviceScan(
            hDevice,
            NEXT_ID3_SCAN_FORMAT,
            pImage,
            NEXT_ID3_IMAGE_SIZE,
            0U,
            &scanStatus);

        if (NBFailed(nbRes))
        {
            log_printf(LOG_DBG,
                       "ATTEMPT %lu scan failed %d status=%d\r\n",
                       (unsigned long)attempt,
                       (int)nbRes,
                       (int)scanStatus);
            continue;
        }

        for (uint32_t i = 0; i < NEXT_ID3_IMAGE_SIZE; i++)
        {
            uint8_t v = pImage[i];
            sum += v;
            if (v < minv) minv = v;
            if (v > maxv) maxv = v;
        }

        NEXT_ID3_EvaluateImageBestQuality(pImage, &bestQuality, &bestVariant);

        log_printf(LOG_DBG,
                   "ATTEMPT %lu scan=%d status=%d min=%u max=%u mean=%lu variant=%s quality=%d\r\n",
                   (unsigned long)attempt,
                   (int)nbRes,
                   (int)scanStatus,
                   (unsigned int)minv,
                   (unsigned int)maxv,
                   (unsigned long)(sum / NEXT_ID3_IMAGE_SIZE),
                   bestVariant,
                   bestQuality);
    }

    free(pImage);

    return 0;
}

