#include "next_bio_device.h"
#include "logger_xtr.h"

static HNBDevice g_hDevice = NULL;
static NBBool g_nbInitialized = NBFalse;

static NBResult NEXT_DeviceOpen(HNBDevice *phDevice)
{
    NBResult res;
    NBDeviceIO io;

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

    res = NEXT_GetDeviceIO(&io);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NEXT_GetDeviceIO failed %d\r\n", (int)res);
        return res;
    }

    res = NBDeviceConnectToSpiRaw(&io, 0U, phDevice);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBDeviceConnectToSpiRaw failed %d\r\n", (int)res);
        return res;
    }

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
