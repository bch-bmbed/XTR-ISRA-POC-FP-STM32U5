#include "next_bio_poc.h"
#include "logger_xtr.h"
#include <string.h>
#include "stdlib.h"

NBResult NEXT_TestFirmwareVersion(void)
{
    NBResult res;
    NBVersion version;
    HNBDevice hDevice;

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        return NB_ERROR_INVALID_OPERATION;
    }

    memset(&version, 0, sizeof(version));

    res = NBDeviceGetFirmwareVersion(hDevice, &version);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBDeviceGetFirmwareVersion failed %d\r\n", (int)res);
        return res;
    }

    log_printf(LOG_DBG, "FW: %d.%d.%d.%d\r\n",
               version.iMajor,
               version.iMinor,
               version.iBuild,
               version.iRevision);

    return NB_OK;
}

NBResult NEXT_TestSupportedScanFormats(void)
{
    NBResult res;
    HNBDevice hDevice;
    NBDeviceScanFormat formats[16];
    NBUInt count;
    NBUInt i;

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        return NB_ERROR_INVALID_OPERATION;
    }

    memset(formats, 0, sizeof(formats));
    count = 0U;

    res = NBDeviceGetSupportedScanFormats(
        hDevice,
        formats,
        (NBUInt)(sizeof(formats) / sizeof(formats[0])),
        &count);

    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBDeviceGetSupportedScanFormats failed %d\r\n", (int)res);
        return res;
    }

    log_printf(LOG_DBG, "Supported scan formats count=%u\r\n", (unsigned int)count);

    for (i = 0U; i < count; i++)
    {
        log_printf(LOG_DBG,
                   "fmt[%u] = %u\r\n",
                   (unsigned int)i,
                   (unsigned int)formats[i]);
    }

    return NB_OK;
}

NBResult NEXT_TestScanFormatInfo(void)
{
    NBResult res;
    HNBDevice hDevice;
    NBDeviceScanFormat formats[16];
    NBDeviceScanFormatInfo info;
    NBUInt count;
    NBUInt i;

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        return NB_ERROR_INVALID_OPERATION;
    }

    memset(formats, 0, sizeof(formats));
    count = 0U;

    res = NBDeviceGetSupportedScanFormats(
        hDevice,
        formats,
        (NBUInt)(sizeof(formats) / sizeof(formats[0])),
        &count);

    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBDeviceGetSupportedScanFormats failed %d\r\n", (int)res);
        return res;
    }

    log_printf(LOG_DBG, "Supported scan formats count=%u\r\n", (unsigned int)count);

    for (i = 0U; i < count; i++)
    {
        memset(&info, 0, sizeof(info));

        res = NBDeviceGetScanFormatInfo(hDevice, formats[i], &info);
        if (NBFailed(res))
        {
            log_printf(LOG_DBG,
                       "NBDeviceGetScanFormatInfo(fmt=%u) failed %d\r\n",
                       (unsigned int)formats[i],
                       (int)res);
            continue;
        }

        log_printf(LOG_DBG,
                   "fmt[%u]=%u width=%u height=%u hDpi=%u vDpi=%u bytes=%lu\r\n",
                   (unsigned int)i,
                   (unsigned int)formats[i],
                   (unsigned int)info.uiWidth,
                   (unsigned int)info.uiHeight,
                   (unsigned int)info.uiHorizontalResolution,
                   (unsigned int)info.uiVerticalResolution,
                   (unsigned long)(info.uiWidth * info.uiHeight));
    }

    return NB_OK;
}

NBResult NEXT_TestCalibration(void)
{
    NBResult res;
    HNBDevice hDevice;
    static NBByte calibrationBuffer[NBDEVICE_FAP20_CALIBRATION_BUFFER_SIZE];
    NBSizeType calibrationSize = sizeof(calibrationBuffer);
    NBDeviceCalibrationDataAddress calibrationAddress;

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        return NB_ERROR_INVALID_OPERATION;
    }

    memset(calibrationBuffer, 0, sizeof(calibrationBuffer));

    log_printf(LOG_DBG, "Calibration start\r\n");
    log_printf(LOG_DBG, "Sensor must be clean and empty\r\n");

    res = NBDeviceGenerateCalibrationDataInplace(
        hDevice,
        calibrationBuffer,
        &calibrationSize);

    if (NBFailed(res))
    {
        log_printf(LOG_DBG,
                   "NBDeviceGenerateCalibrationDataInplace failed %d\r\n",
                   (int)res);
        return res;
    }

    log_printf(LOG_DBG,
               "Calibration generated inplace, size=%lu\r\n",
               (unsigned long)calibrationSize);

    calibrationAddress.pCalibrationData = calibrationBuffer;
    calibrationAddress.stCalibrationDataSize = calibrationSize;

    res = NBDeviceSetBlobParameter(
        hDevice,
        NB_DEVICE_BLOB_PARAMETER_CALIBRATION_DATA_ADDRESS,
        (const NBByte *)&calibrationAddress,
        sizeof(calibrationAddress));

    if (NBFailed(res))
    {
        log_printf(LOG_DBG,
                   "NBDeviceSetBlobParameter(CALIBRATION_DATA_ADDRESS) failed %d\r\n",
                   (int)res);
        return res;
    }

    log_printf(LOG_DBG, "Calibration applied\r\n");

    res = NEXT_Calibration_SaveToFlash(calibrationBuffer, (uint32_t)calibrationSize);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG,
                   "NEXT_Calibration_SaveToFlash failed %d\r\n",
                   (int)res);
        return res;
    }

    log_printf(LOG_DBG, "Calibration saved to flash\r\n");

    return NB_OK;
}

NBResult NEXT_TestCaptureImage(void)
{
    NBResult res;
    HNBDevice hDevice;
    NBDeviceScanFormatInfo info;
    NBDeviceScanStatus status;
    NBByte *pImage = NULL;
    const NBDeviceScanFormat scanFormat = (NBDeviceScanFormat)10;
    NBSizeType imageSize;
    NBUInt32 sum = 0;
    NBSizeType i;

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        return NB_ERROR_INVALID_OPERATION;
    }

    memset(&info, 0, sizeof(info));
    status = 0;

    res = NBDeviceGetScanFormatInfo(hDevice, scanFormat, &info);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBDeviceGetScanFormatInfo failed %d\r\n", (int)res);
        return res;
    }

    imageSize = (NBSizeType)info.uiWidth * (NBSizeType)info.uiHeight;

    log_printf(LOG_DBG,
               "Capture fmt=%u width=%u height=%u hDpi=%u vDpi=%u size=%lu\r\n",
               (unsigned int)scanFormat,
               (unsigned int)info.uiWidth,
               (unsigned int)info.uiHeight,
               (unsigned int)info.uiHorizontalResolution,
               (unsigned int)info.uiVerticalResolution,
               (unsigned long)imageSize);

    pImage = (NBByte *)malloc(imageSize);
    if (pImage == NULL)
    {
        log_printf(LOG_DBG, "malloc failed for image buffer\r\n");
        return NB_ERROR_OUT_OF_MEMORY;
    }

    memset(pImage, 0, imageSize);

    res = NBDeviceScan(
        hDevice,
        scanFormat,
        pImage,
        imageSize,
        NB_DEVICE_SCAN_SKIP_FINGER_DETECTION_FLAG,
        &status);

    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBDeviceScan failed %d status=%d\r\n", (int)res, (int)status);
        free(pImage);
        return res;
    }

    for (i = 0; i < imageSize; i++)
    {
        sum += pImage[i];
    }

    log_printf(LOG_DBG,
               "Scan OK status=%d mean=%lu first8=%u,%u,%u,%u,%u,%u,%u,%u\r\n",
               (int)status,
               (unsigned long)(sum / imageSize),
               (unsigned int)pImage[0],
               (unsigned int)pImage[1],
               (unsigned int)pImage[2],
               (unsigned int)pImage[3],
               (unsigned int)pImage[4],
               (unsigned int)pImage[5],
               (unsigned int)pImage[6],
               (unsigned int)pImage[7]);

    /* Optionnel : dump brut sur UART en hex est trop lourd.
       Mieux : sauvegarde plus tard en BMP/PGM côté host. */

    free(pImage);
    return NB_OK;
}

NBResult NEXT_TestCaptureImageToPgm(void)
{
    NBResult res;
    HNBDevice hDevice;
    NBDeviceScanFormatInfo info;
    NBDeviceScanStatus status;
    NBByte *pImage = NULL;
    const NBDeviceScanFormat scanFormat = (NBDeviceScanFormat)10;
    NBSizeType imageSize;
    NBSizeType i;

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        return NB_ERROR_INVALID_OPERATION;
    }

    memset(&info, 0, sizeof(info));
    status = 0;

    res = NBDeviceGetScanFormatInfo(hDevice, scanFormat, &info);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBDeviceGetScanFormatInfo failed %d\r\n", (int)res);
        return res;
    }

    imageSize = info.uiWidth * info.uiHeight;

    pImage = (NBByte *)malloc(imageSize);
    if (pImage == NULL)
    {
        return NB_ERROR_OUT_OF_MEMORY;
    }

    log_printf(LOG_DBG, "Place finger in 3 seconds...\r\n");
    HAL_Delay(3000);

    res = NBDeviceScan(
        hDevice,
        scanFormat,
        pImage,
        imageSize,
        0,
        &status);

    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "Scan failed %d\r\n", (int)res);
        free(pImage);
        return res;
    }

    log_printf(LOG_DBG, "PGM BEGIN\r\n");

    /* Header PGM ASCII */
    log_printf(LOG_DBG, "P2\r\n");
    log_printf(LOG_DBG, "%u %u\r\n", info.uiWidth, info.uiHeight);
    log_printf(LOG_DBG, "255\r\n");

    for (i = 0; i < imageSize; i++)
    {
        log_printf(LOG_DBG, "%u ", pImage[i]);

        if ((i % info.uiWidth) == 0)
        {
            log_printf(LOG_DBG, "\r\n");
        }
    }

    log_printf(LOG_DBG, "\r\nPGM END\r\n");

    free(pImage);
    return NB_OK;
}
