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
        return NB_ERROR_INVALID_STATE;
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
        return NB_ERROR_INVALID_STATE;
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
