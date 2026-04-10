/*
 * next_bio_biometrics.c
 *
 *  Created on: 10 avr. 2026
 *      Author: benjamin.chalant
 */

#include "next_bio_biometrics.h"
#include "next_bio_device.h"
#include "logger_xtr.h"
#include <string.h>
#include <stdlib.h>

static HNBBiometricsContext g_hBioContext = NULL;

NBResult NEXT_BiometricsInit(void)
{
    NBResult res;
    HNBDevice hDevice;

    if (g_hBioContext != NULL)
    {
        return NB_OK;
    }

    hDevice = NEXT_DeviceGetHandle();
    if (hDevice == NULL)
    {
        return NB_ERROR_INVALID_OPERATION;
    }

    res = NBBiometricsContextCreate(hDevice, 0U, &g_hBioContext);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBBiometricsContextCreate failed %d\r\n", (int)res);
        return res;
    }

    log_printf(LOG_DBG, "NBBiometricsContextCreate OK\r\n");
    return NB_OK;
}

void NEXT_BiometricsDeinit(void)
{
    if (g_hBioContext != NULL)
    {
        NBBiometricsContextDestroy(g_hBioContext);
        g_hBioContext = NULL;
    }
}

HNBBiometricsContext NEXT_BiometricsGetContext(void)
{
    return g_hBioContext;
}
