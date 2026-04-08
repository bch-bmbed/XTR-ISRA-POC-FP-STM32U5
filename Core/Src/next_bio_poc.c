/*
 * next_bio_poc.c
 *
 *  Created on: 8 avr. 2026
 *      Author: benjamin.chalant
 */

#include "next_bio_port.h"
#include <stdio.h>
#include "logger_xtr.h"

static HNBDevice hDevice = NULL;

NBResult NEXT_TestFirmwareVersion(void)
{
    NBDeviceIO io;
    NBVersion version;
    NBResult res;

    log_printf(LOG_DBG, "AWAKE before reset=%d\r\n", NEXT_AwakeRead());

    NEXT_Deselect();

    NEXT_ResetHigh();
    HAL_Delay(20);

    NEXT_ResetLow();
    HAL_Delay(20);
    NEXT_ResetHigh();

    HAL_Delay(500);

    log_printf(LOG_DBG, "AWAKE after reset=%d\r\n", NEXT_AwakeRead());

    res = NBDevicesInitializeA(NULL, NULL, NULL, 0);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBDevicesInitializeA failed %d\r\n", res);
        return res;
    }

    NEXT_GetDeviceIO(&io);

    res = NBDeviceConnectToSpiRaw(
            &io,
            0,
            &hDevice);

    if (NBFailed(res))
    {
    	log_printf(LOG_DBG, "Connect failed %d\r\n",res);
        return res;
    }

    res =
        NBDeviceGetFirmwareVersion(
            hDevice,
            &version);

    if (NBFailed(res))
    {
    	log_printf(LOG_DBG, "FW read failed %d\r\n",res);
        return res;
    }

    log_printf(LOG_DBG, "FW: %d.%d.%d.%d\r\n",
        version.iMajor,
        version.iMinor,
        version.iBuild,
        version.iRevision);

    NBDeviceDestroy(hDevice);

    return NB_OK;
}
