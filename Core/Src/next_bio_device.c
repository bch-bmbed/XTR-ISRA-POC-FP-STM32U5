#include "next_bio_device.h"
#include "logger_xtr.h"
#include <string.h>

static HNBDevice g_hDevice = NULL;
static NBDeviceIO g_sDeviceIO;
static NBBool g_nbInitialized = NBFalse;

static NBResult NEXT_DeviceOpen(HNBDevice *phDevice)
{
    NBResult res;

    if (phDevice == NULL)
    {
        return NB_ERROR_ARGUMENT_NULL;
    }

    *phDevice = NULL;

    NEXT_Deselect();

    log_printf(LOG_DBG, "AWAKE before reset=%d\r\n", (int)NEXT_AwakeRead());

    NEXT_ResetHigh();
    HAL_Delay(20);
    NEXT_ResetLow();
    HAL_Delay(20);
    NEXT_ResetHigh();
    HAL_Delay(500);

    log_printf(LOG_DBG, "AWAKE after reset=%d\r\n", (int)NEXT_AwakeRead());

    memset(&g_sDeviceIO, 0, sizeof(g_sDeviceIO));

    log_printf(LOG_DBG, "Before NEXT_GetDeviceIO\r\n");
    res = NEXT_GetDeviceIO(&g_sDeviceIO);
    log_printf(LOG_DBG, "After NEXT_GetDeviceIO: %d\r\n", (int)res);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NEXT_GetDeviceIO failed %d\r\n", (int)res);
        return res;
    }

    log_printf(LOG_DBG, "About to connect raw...\r\n");
    res = NBDeviceConnectToSpiRaw(&g_sDeviceIO, 0U, phDevice);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBDeviceConnectToSpiRaw failed %d\r\n", (int)res);
        return res;
    }

    log_printf(LOG_DBG, "Raw connect OK\r\n");
    return NB_OK;
}

NBResult NEXT_DeviceInit(void)
{
    NBResult res;

    if (g_nbInitialized == NBTrue)
    {
        return NB_OK;
    }

    res = NBDevicesInitializeA(NULL, NULL, NULL, 0);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBDevicesInitializeA failed %d\r\n", (int)res);
        return res;
    }

    g_nbInitialized = NBTrue;

    res = NEXT_DeviceOpen(&g_hDevice);
    if (NBFailed(res))
    {
        NBDevicesTerminate();
        g_nbInitialized = NBFalse;
        return res;
    }

    log_printf(LOG_DBG, "NEXT_DeviceInit OK\r\n");
    return NB_OK;
}

void NEXT_DeviceDeinit(void)
{
    if (g_hDevice != NULL)
    {
        NBDeviceDestroy(g_hDevice);
        g_hDevice = NULL;
    }

    if (g_nbInitialized == NBTrue)
    {
        NBDevicesTerminate();
        g_nbInitialized = NBFalse;
    }
}

HNBDevice NEXT_DeviceGetHandle(void)
{
    return g_hDevice;
}

NBBool NEXT_DeviceIsReady(void)
{
    return (g_hDevice != NULL) ? NBTrue : NBFalse;
}

NBResult NEXT_ApplyCalibrationFromFlash(void)
{
    NBResult res;
    HNBDevice hDevice;
    const uint8_t *pData = NULL;
    uint32_t size = 0;
    NBDeviceCalibrationDataAddress addr;

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        return NB_ERROR_INVALID_OPERATION;
    }

    res = NEXT_Calibration_LoadFromFlash(&pData, &size);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "No valid calibration in flash\r\n");
        return res;
    }

    addr.pCalibrationData = (NBByte *)pData;
    addr.stCalibrationDataSize = size;

    res = NBDeviceSetBlobParameter(
        hDevice,
        NB_DEVICE_BLOB_PARAMETER_CALIBRATION_DATA_ADDRESS,
        (const NBByte *)&addr,
        sizeof(addr));

    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "Apply calibration from flash failed %d\r\n", (int)res);
        return res;
    }

    log_printf(LOG_DBG, "Calibration loaded from flash, size=%lu\r\n", (unsigned long)size);
    return NB_OK;
}
