#include "next_bio_poc.h"
#include "logger_xtr.h"
#include <string.h>

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

