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

NBResult NEXT_ExtractTemplate(NEXT_TemplateBuffer *pOut)
{
    NBResult res;
    HNBBiometricsContext hContext;
    NBBiometricsTemplateType templateType = NBBiometricsTemplateTypeIso;
    NBBiometricsFingerPosition fingerPosition = NBBiometricsFingerPositionRightThumb;
    NBBiometricsScanParams scanParams;
    NBBiometricsStatus bioStatus = NBBiometricsStatusNone;
    NBSizeType maxTemplateSize = 0;
    NBInt quality = 0;
    NBUInt uiFlags = NB_BIOMETRICS_SCAN_USE_SNAPSHOT_FLAG |
                     NB_BIOMETRICS_SCAN_SKIP_FINGER_NOT_REMOVED_STATUS_FLAG;

    if (pOut == NULL)
    {
        return NB_ERROR_ARGUMENT_NULL;
    }

    memset(pOut, 0, sizeof(*pOut));

    hContext = NEXT_BiometricsGetContext();
    if (hContext == NULL)
    {
        return NB_ERROR_INVALID_OPERATION;
    }

    memset(&scanParams, 0, sizeof(scanParams));
    scanParams.eScanFormat = (NBDeviceScanFormat)10;
    scanParams.iTimeout = 10000;
    scanParams.pPreviewProc = NULL;
    scanParams.pParam = NULL;

    res = NBBiometricsContextGetMaxTemplateSize(
        hContext,
        templateType,
        &maxTemplateSize);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBBiometricsContextGetMaxTemplateSize failed %d\r\n", (int)res);
        return res;
    }

    if (maxTemplateSize > NEXT_MAX_TEMPLATE_SIZE)
    {
        log_printf(LOG_DBG, "Template buffer too small: need=%lu\r\n", (unsigned long)maxTemplateSize);
        return NB_ERROR_ARGUMENT_OUT_OF_RANGE;
    }

    log_printf(LOG_DBG, "Place finger now and keep it steady...\r\n");
    HAL_Delay(3000);

    res = NBBiometricsContextExtractFromScan(
        hContext,
        templateType,
        fingerPosition,
        &scanParams,
        uiFlags,
        pOut->data,
        NEXT_MAX_TEMPLATE_SIZE,
        &bioStatus,
        &pOut->size);

    log_printf(LOG_DBG,
               "Extract result=%d bioStatus=%d templateSize=%lu\r\n",
               (int)res,
               (int)bioStatus,
               (unsigned long)pOut->size);

    if (NBFailed(res) || pOut->size == 0U)
    {
        return res;
    }

    res = NBBiometricsTemplateGetQuality(pOut->data, pOut->size, &quality);
    if (NBFailed(res))
    {
        log_printf(LOG_DBG, "NBBiometricsTemplateGetQuality failed %d\r\n", (int)res);
        return res;
    }

    pOut->quality = quality;
    pOut->valid = NBTrue;

    log_printf(LOG_DBG, "Template quality=%d\r\n", (int)pOut->quality);

    return NB_OK;
}

NBResult NEXT_TestVerifyTwoScans(void)
{
    NBResult res;
    HNBBiometricsContext hContext;
    NEXT_TemplateBuffer t1;
    NEXT_TemplateBuffer t2;
    NBBiometricsStatus bioStatus = NBBiometricsStatusNone;
    NBBiometricsVerifyResultDetails verifyResult;
    NBInt securityLevel = 3; /* point de départ raisonnable pour POC */
    NBUInt uiFlags = 0U;

    memset(&verifyResult, 0, sizeof(verifyResult));

    hContext = NEXT_BiometricsGetContext();
    if (hContext == NULL)
    {
        return NB_ERROR_INVALID_OPERATION;
    }

    log_printf(LOG_DBG, "=== TEMPLATE 1 ===\r\n");
    res = NEXT_ExtractTemplate(&t1);
    if (NBFailed(res) || (t1.valid != NBTrue))
    {
        log_printf(LOG_DBG, "Template 1 extraction failed %d\r\n", (int)res);
        return res;
    }

    log_printf(LOG_DBG, "=== TEMPLATE 2 ===\r\n");
    res = NEXT_ExtractTemplate(&t2);
    if (NBFailed(res) || (t2.valid != NBTrue))
    {
        log_printf(LOG_DBG, "Template 2 extraction failed %d\r\n", (int)res);
        return res;
    }

    res = NBBiometricsContextVerifyFromTemplate(
        hContext,
        t1.data,
        t1.size,
        t2.data,
        t2.size,
        securityLevel,
        uiFlags,
        &bioStatus,
        &verifyResult);

    log_printf(LOG_DBG,
               "Verify result=%d bioStatus=%d score=%d\r\n",
               (int)res,
               (int)bioStatus,
               (int)verifyResult.iScore);

    return res;
}
