/*
 * next_bio_scan.c
 *
 *  Created on: 8 avr. 2026
 *      Author: benjamin.chalant
 */
#include "next_bio_port.h"
#include "NBDevices.h"
#include <string.h>
#include "logger_xtr.h"

NBResult NEXT_TestSupportedScanFormats(void)
{
    NBResult res;
    NBDeviceIO io;
    HNBDevice hDevice = NULL;
    NBBool bLibInitialized = NBFalse;

    NBDeviceScanFormat formats[16];
    NBUInt count = 0;
    NBUInt i;

    res = NBDevicesInitializeA(NULL, NULL, NULL, 0);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBDevicesInitializeA failed %d\r\n", res);
        return res;
    }
    bLibInitialized = NBTrue;

    NEXT_Deselect();

    log_printf(LOG_DBG, "AWAKE before reset=%d\r\n", NEXT_AwakeRead());

    NEXT_ResetHigh();
    HAL_Delay(20);
    NEXT_ResetLow();
    HAL_Delay(20);
    NEXT_ResetHigh();
    HAL_Delay(500);

    log_printf(LOG_DBG, "AWAKE after reset=%d\r\n", NEXT_AwakeRead());

    res = NEXT_GetDeviceIO(&io);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NEXT_GetDeviceIO failed %d\r\n", res);
        goto finally;
    }

    res = NBDeviceConnectToSpiRaw(&io, 0U, &hDevice);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "Connect failed %d\r\n", res);
        goto finally;
    }

    memset(formats, 0, sizeof(formats));

    res = NBDeviceGetSupportedScanFormats(
        hDevice,
        formats,
        (NBUInt)(sizeof(formats) / sizeof(formats[0])),
        &count);

    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBDeviceGetSupportedScanFormats failed %d\r\n", res);
        goto finally;
    }

    log_printf(LOG_DBG, "Supported scan formats count=%u\r\n", (unsigned int)count);

    for (i = 0; i < count; i++)
    {
        log_printf(LOG_DBG,
                   "fmt[%u] = %u\r\n",
                   (unsigned int)i,
                   (unsigned int)formats[i]);
    }

finally:
    if (hDevice)
    {
        NBDeviceDestroy(hDevice);
        hDevice = NULL;
    }

    if (bLibInitialized)
    {
        NBDevicesTerminate();
    }

    return res;
}
