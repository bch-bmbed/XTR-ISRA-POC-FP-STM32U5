#ifndef NB_DEVICE_H
#define NB_DEVICE_H

#include <NBDevicesTypes.h>

#ifdef NB_CPP
extern "C"
{
#endif

#define DEBUG_SAVE_BMP 0
#define DEBUG_INDUCE_DEADLINES 0

/* Default finger detect type */
#define NB_DEVICE_DEFAULT_FINGER_DETECT_TYPE                    NBDeviceFingerDetectTypeEnhanced
/* Default finger detection threshold (above threshold, image is considered to have a fingerprint present) */
#define NB_DEVICE_DEFAULT_FINGER_DETECT_THRESHOLD               40
/* Infinite threshold is used in extended capture and means that the operation will either
   succeed or continue until canceled.                      */
#define NB_DEVICE_SCAN_TIMEOUT_INFINITE                         -1

/* Skip the finger not remove status when doing scan (in scenarios when sensor is awaken from sleep after finger is put on sensor area (in SPI)) */
#define NB_DEVICE_SCAN_SKIP_FINGER_NOT_REMOVED_STATUS_FLAG       0x08

/*Do not do any finger detections during scan, just return the image*/
#define NB_DEVICE_SCAN_SKIP_FINGER_DETECTION_FLAG                0x10

/*
  Do not do GPIO initialization (and deinitialization) when
  connecting to device module through SPI                  
*/
#define NB_DEVICE_CONNECT_TO_SPI_SKIP_GPIO_INIT_FLAG             0x02

/*
  Customized finger detection threshold. NB_DEVICE_PARAMETER_ENHANCED_FINGER_DETECT_THRESHOLD can be used as threshold, defining
  that any score above specified threshold can be considered as meaning that there is finger present on device surface.
*/
#define NB_DEVICE_PARAMETER_ENHANCED_FINGER_DETECT_THRESHOLD    103

/*
  Enable / disable anti-latent protection.
*/
#define NB_DEVICE_PARAMETER_SUBTRACT_BACKGROUND                 105
/*
  Supported only by NB-2023-S-UID, NB-2023-U-UID, NB-3023-U-UID, NB-65200-U and NB-65210-S.
  Enable / disable anti-spoof protection.
*/
#define NB_DEVICE_PARAMETER_ANTISPOOF_ENABLED                   108
/*
  Threshold for spoof assessment - if the image score is bigger than this value then is a live scan.
  Available values: 0 (spoof) - 1000 (live)). Set the value to -1 to reset to default.
*/
#define NB_DEVICE_PARAMETER_ANTISPOOF_THRESHOLD                 109
/*
    Interface for user to specify requested output image type.
*/
#define NB_DEVICE_PARAMETER_IMAGE_TYPE                          110

/*
    Enhanced fingerprint image preview in all the states of FAP20 devices.
*/
#define NB_DEVICE_PARAMETER_IMAGE_PREVIEW_ENABLED               410

/*
  Set / get device compensation data
*/
#define NB_DEVICE_BLOB_PARAMETER_CALIBRATION_DATA               201

/*
  Set the Customer defined key (CDK), this parameter writes the passed key to the physical device
*/
#define NB_DEVICE_BLOB_PARAMETER_SET_CDK                        202

/*
  Set / get device compensation data address (pointer and size stored in the NBDeviceCalibrationDataAddress structure)
*/
#define NB_DEVICE_BLOB_PARAMETER_CALIBRATION_DATA_ADDRESS       204

/*
  Enable the macro to read the calibratioln data from calibratioln file(serialnum_calblob.bin) insted of reading
  from 65200U module  
*/
//#define NBDEVICE_65200_GENERATE_CALIBRATION_DATA

#ifdef NBDEVICE_65200_GENERATE_CALIBRATION_DATA
/*
  Get the Calibration data from NB-65200U module
*/
#define NB_DEVICE_BLOB_PARAMETER_CALIBRATION_GET                205
#endif

/*
  Enable/disable MIMS C2 parameter adjustment.
*/
#define NB_DEVICE_IMAGE_ADJUST_C2_ENABLE                        650
/*
  Set the customized value for MIMS C2 parameter.
*/
#define NB_DEVICE_IMAGE_C2_BLACK_MIMS_PARAM                     651

/*
  Enable/disable MIMS S1 parameter adjustment.
*/
#define NB_DEVICE_IMAGE_ADJUST_S1_ENABLE                        652
/*
  Set the customized value for MIMS S1 parameter.
*/
#define NB_DEVICE_IMAGE_S1_MIMS_PARAM                           653

/*
  65200 CDK identifier
*/
#define NBDEVICE_65200_CDK_IDENTIFIER "Application Lock"
/*
  65100 authentication 1 identifier
*/
#define NBDEVICE_65100_AUTH1_ID "AUTH1"
/*
  65100 authentication 2 identifier
*/
#define NBDEVICE_65100_AUTH2_ID "AUTH2"

/*
  Size of the calibration data for NB-65200 and NB-65210 (width * height)
*/
#define NBDEVICE_FAP20_CALIBRATION_DATA_SIZE 120000
/*
  Size of the calibration header for NB-65210
*/
#define NBDEVICE_FAP20_CALIBRATION_HEADER_SIZE 110
/*
  Size of the calibration check sum for NB-65210
*/
#define NBDEVICE_FAP20_CALIBRATION_CHECKSUM_SIZE 36
/*
  Size of the calibration data for NB-65200 and NB-65210 plus the calibration header
*/
#define NBDEVICE_FAP20_CALIBRATION_SIZE (NBDEVICE_FAP20_CALIBRATION_DATA_SIZE + NBDEVICE_FAP20_CALIBRATION_HEADER_SIZE + NBDEVICE_FAP20_CALIBRATION_CHECKSUM_SIZE)
/*
  Size of the buffer necessary to calibrate NB-65210-S
*/
#define NBDEVICE_FAP20_CALIBRATION_BUFFER_SIZE (NBDEVICE_FAP20_CALIBRATION_SIZE + NBDEVICE_FAP20_CALIBRATION_DATA_SIZE / 2)
/*
  Max value of the compression ratio for WSQ type
*/
#define NBDEVICE_MAX_WSQ_COMPRESSION_RATIO_VALUE 6.5f
/*
  Configured value of the compression ratio for single WSQ fingerprint
*/
#define NBDEVICE_CFG_WSQ_COMPRESSION_RATIO_VALUE_SINGLE 1.0f
/*
  Configured value of the compression ratio for double WSQ fingerprint
*/
#define NBDEVICE_CFG_WSQ_COMPRESSION_RATIO_VALUE_DUAL 0.8f
/*
  Configured value for single fingerprint count
*/
#define NB_BIOMETRICS_CONTEXT_FINGER_COUNT 1

/*
 * Device manipulation
 */

 
/*
 * Connecting and destroying connection to the device
 */
 
/*
  Summary:
   Connect to a device using specified device descriptor
   (NBDeviceInfoA) obtained from either by calling
   NBDevicesGetDevicesA or through NBDevicesDeviceChangedProcA
   callback.
  Parameters:
   psDeviceInfo :  [in] device descriptor
   uiFlags :       [in] bitmask specifying flags, which modify
                   slightly behavior of the function
   phDevice :      [out] handle to device
  Remarks:
   Device handle is allocated on heap and returned after
   successful execution of the function.
   
   Each obtained device handle needs to be destroyed using
   NBDeviceDestroy function.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceConnectA(const NBDeviceInfoA * psDeviceInfo, NBUInt uiFlags, HNBDevice * phDevice);

/*
  Summary:
   Connect to a device using specified serial port.
  Parameters:
   iPort :           [in] port number
   uiFlags :         [in] bitmask specifying flags, which modify
                     slightly behavior of the function
   phDevice :        [out] handle to device
  Remarks:
   Device handle is allocated on heap and returned after
   successful execution of the function.

   Each obtained device handle needs to be destroyed using
   NBDeviceDestroy function.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceConnectToUart(NBInt iPort, NBUInt uiFlags, HNBDevice * phDevice);

/*
  Summary:
   It returns the firmware upgrade status for 65100T from RDS.
  Parameters:
   pbIsDevFWUpgradeInitialized : [out] returns the status of firmware update progress.
  Remarks:
   0-Firmware upgrade not started or finished.
   1-Firmware upgrade is in-progress. So, the user needs to wait before it complete.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDevice65100TIsFWUpgradeInitialized(NBBool * pbIsDevFWUpgradeInitialized);

/*
  Summary:
   Connect to a device using custom interface.
  Parameters:
   psCommInterface : [in] communication interface 
   caSettings :      [in] connection string (MAC address for Bluetooth)
   uiFlags :         [in] bitmask specifying flags, which modify
                     slightly behavior of the function
   phDevice :        [out] handle to device
  Remarks:
   Device handle is allocated on heap and returned after
   successful execution of the function.

   Each obtained device handle needs to be destroyed using
   NBDeviceDestroy function.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceConnectToCustom(NBDeviceCommInterface *psCommInterface, NBAChar* caSettings, NBUInt uiFlags, HNBDevice * phDevice);

/*
  Summary:
   Connect to a device using specified SPI name, awake and reset
   pin number.
  Parameters:
   szSpi :      [in] name of SPI device
   iAwakePin :  [in] awake pin number
   iResetPin :  [in] reset pin number
   uiFlags :    [in] bitmask specifying flags, which modify
                slightly behavior of the function
   phDevice :   [out] handle to device
  Remarks:
   Device handle is allocated on heap and returned after
   successful execution of the function.
   
   Each obtained device handle needs to be destroyed using
   NBDeviceDestroy function.
   
   If SPI is not supported on current platform,
   NB_ERROR_NOT_SUPPORTED error will be returned.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceConnectToSpiA(const NBAChar * szSpi, NBInt iAwakePin, NBInt iResetPin, NBUInt uiFlags, HNBDevice * phDevice);
/*
  Summary:
   Connect to a device using specified SPI name, awake, reset,
   and chip select pin number.
  Parameters:
   szSpi :           [in] name of SPI device
   iAwakePin :       [in] awake pin number
   iResetPin :       [in] reset pin number
   iChipSelectPin :  [in] chip select pin number (\-1 is allowed,
                     meaning not specified)
   uiFlags :         [in] bitmask specifying flags, which modify
                     slightly behavior of the function
   phDevice :        [out] handle to device
  Remarks:
   Device handle is allocated on heap and returned after
   successful execution of the function.
   
   Each obtained device handle needs to be destroyed using
   NBDeviceDestroy function.
   
   If SPI is not supported on current platform,
   NB_ERROR_NOT_SUPPORTED error will be returned.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceConnectToSpiExA(const NBAChar * szSpi, NBInt iAwakePin, NBInt iResetPin, NBInt iChipSelectPin, NBUInt uiFlags, HNBDevice * phDevice);

/*
  Summary:
   Connect to a device using specified SPI name, awake, reset,
   and chip select pin number.
  Parameters:
   psIOParams : [in] pointer to the structure which holds
                all function arguments.
                structure members:
                szSpiName   :  [in] name of SPI device
                szSysfsPath :  [in] SYSFS path
                iAwakePin   :  [in] awake pin number
                iResetPin   :  [in] reset pin number
                uiFlags     :  [in] bitmask specifying flags, which modify
                                    slightly behavior of the function
                phDevice    :  [out] handle to device
  Remarks:
   Device handle is allocated on heap and returned after
   successful execution of the function.
   
   Each obtained device handle needs to be destroyed using
   NBDeviceDestroy function.
   
   If SPI is not supported on current platform,
   NB_ERROR_NOT_SUPPORTED error will be returned.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceConnectToSpiEnhA(NBDeviceIOParams * psIOParams);

#ifdef NB_DEVICES_LITE
    /*
      Summary:
       Connect to a device using specified platform/board
       abstraction structure.
      Parameters:
       psDeviceIO :  [in] platform abstraction structure (BSP), will
                     be copied internally
       uiFlags :     [in] bitmask specifying flags, which modify
                     slightly behavior of the function
       phDevice :    [out] handle to device
      Remarks:
       Device handle is allocated on heap and is returned after
       successful execution of the function.
       
       Each obtained device handle needs to be destroyed using
       NBDeviceDestroy function.
       
       If SPI is not supported on current platform,
       NB_ERROR_NOT_SUPPORTED error will be returned.
      Returns:
       If the function succeeds, the return value is NB_OK. If the
       function fails, one of the error codes is returned (<link Error codes>).
    */
    NBResult NB_API NBDeviceConnectToSpiRaw(const NBDeviceIO * psDeviceIO, NBUInt uiFlags, HNBDevice * phDevice);
    /*
      Summary:
       Connect to a device using specified platform/board
       abstraction structure, created handle will be allocated in
       specified memory buffer.
      Parameters:
       psDeviceIO :    [in] platform abstraction structure (BSP),
                       will be copied internally
       pBuffer :       [in/out] memory buffer, where device handle
                       will be allocated in
       stBufferSize :  [in] size of the memory buffer
       uiFlags :       [in] bitmask specifying flags, which modify
                       slightly behavior of the function
       pstSize :       [out] minimal memory size required for buffer
       phDevice :      [out] handle to device
      Remarks:
       Device handle is allocated in specified memory buffer and
       returned after successful execution of the function.
       
       pBuffer must exist until device handle is not destroyed
       (using NBDeviceDestroy).
       
       Each obtained device handle needs to be destroyed using
       NBDeviceDestroy function.
       
       If SPI is not supported on current platform,
       NB_ERROR_NOT_SUPPORTED error will be returned.
      Returns:
       If the function succeeds, the return value is NB_OK. If the
       function fails, one of the error codes is returned (<link Error codes>).
    */
    NBResult NB_API NBDeviceConnectToSpiRawInMemory(const NBDeviceIO * psDeviceIO, NBByte * pBuffer, NBSizeType stBufferSize, NBUInt uiFlags, NBSizeType * pstSize, HNBDevice * phDevice);
    /*
      Summary:
       CRC32 function provided for NBDeviceIO CRC callback when application
       does not have a hardware based CRC function to use.
      Parameters:
       pContext :      UNUSED
       pu8Message :    [in] message buffer to perform CRC over
       stMessageLen :  [in] length of message buffer in bytes
       pu32Crc :       [out] CRC32 of message
      Remarks:
       None
      Returns:
       If the function succeeds, the return value is NB_OK. If the
       function fails, one of the error codes is returned (<link Error codes>).
    */
    NBResult NB_API NBDeviceCrc32A(void * pContext, const NBByte *pu8Message, NBSizeType stMessageLen, NBUInt32* pu32Crc);

    /*
      Summary:
       Link in and activate Obfuscation Security (NB-65210-S only)
      Parameters:
       hDevice :         [in] handle to device
      Remarks:
       None
      Returns:
       If the function succeeds, the return value is NB_OK. If the
       function fails, one of the error codes is returned (<link Error codes>).
    */
    NBResult NB_API NBDeviceEnableObfSecurity(const HNBDevice hDevice);

    /*
      Summary:
       Returns whether the module supports obfuscation
      Parameters:
       hDevice :         [in] handle to device
       pbIsSupported:    [out] NBTrue if supported, NBFalse otherwise

      Remarks:
       None
      Returns:
       If the function succeeds, the return value is NB_OK. If the
       function fails, one of the error codes is returned (<link Error codes>).
    */
    NBResult NB_API NBDeviceIsObfSupported(const HNBDevice hDevice, NBBool * pbIsSupported);
    
    /*
      Summary:
        Performs 15 times of quarter partial scan, then analyze the PIV image quality on the final full captured image.
      Parameters:
        hDevice :         [in] handle to device
        pPIVImage :       [in/out] pre\-allocated buffer to store the PIV image when only test failed.
                          pPIVImage can be NULL if no PIV image is requested. 
        peQualifyStatus : [out] result, information specifying status of
                          PIV image test. If the peQualifyStatus is NBTrue then the sensore qualified 
                          in the PIV test with given PIV settings else it is not qualified.
      Returns:
        If the function succeeds, the return value is NB_OK. If the
        function fails, one of 'the error codes is returned (<link Error codes>).
    */
    NBResult NB_API NBDevicePIVimageTest(const HNBDevice hDevice, NBByte * pPIVImage, NBByte * peQualifyStatus);
    
#if (NB_DEVICES_LITE_FEATURE_BLACKLINE_UNIFORMITY_SNR_TEST)
    /*
      Summary:
        TEST BUILD ONLY. This is for a configurable value used when getting a black image for uniformity test. Not intended for normal use case. If this is not called by the application,
        a default value will be used.
      Parameters:
        hDevice :         [in] handle to device
        u8Value1 :        [in] first adjustment value to set to (byte; valid value: 0-255)
        fValue2 :         [in] second adjustment value to set to (float; valid value: > 0)
      Returns:
        If the function succeeds, the return value is NB_OK. If the
        function fails, one of the error codes is returned (<link Error codes>).
    */
    NBResult NB_API NBDeviceSetAdjustmentValue(const HNBDevice hDevice, const NBByte u8Value1, const NBFloat fValue2);
#endif
#endif

/*
  Summary:
   Destroys device handle obtained using NBDeviceConnectA,
   NBDeviceConnectToSpiA, NBDeviceConnectToSpiExA,
   NBDeviceConnectToSpiRaw or NBDeviceConnectToSpiRawInMemory
   functions and frees all resources obtained by device handle.
  Parameters:
   hDevice :  [in] handle to device
  Remarks:
   After handle is destroyed, it is caller's responsibility to
   set the device handle to NULL. Calling NBDevice functions
   with a destroyed handle can give unpredictable results.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceDestroy(HNBDevice hDevice);

/*
  Summary:
   Securely open a session with the device, the device might 
   be unusable before the session is opened.
  Parameters:
   hDevice :       [in] device handle
   pKeyId :        [in] session key identifier
   stKeyIdSize :   [in] session key identifier size
   pKey :          [in] session key
   stKeySize :     [in] session key size
  Remarks:
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceOpenSession(const HNBDevice hDevice, const NBByte *pKeyId, NBSizeType stKeyIdSize, const NBByte *pKey, NBSizeType stKeySize);

/*
  Summary:
   Close secure connection.
  Parameters:
   hDevice :       [in] device handle
  Remarks:
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceCloseSession(const HNBDevice hDevice);

/*
  Summary:
   Determine is a session is open and active.
  Parameters:
   hDevice :        [in] device handle
   bIsSessionOpen : [out] value indicating if a session is open
  Remarks:
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceIsSessionOpen(const HNBDevice hDevice, NBBool *pbIsSessionOpen);

/*
  Summary:
   Get the device LowLevelInterfaceType.
  Parameters:
   hDevice :              [in] device handle
   NBDeviceLowLevelInterfaceType : [out] LowLevelInterfaceType
  Remarks:
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetLowLevelInterfaceType(const HNBDevice hDevice, NBDeviceLowLevelInterfaceType *pInterfaceType);
/*
  Summary:
   Get the device capabilities.
  Parameters:
   hDevice :              [in] device handle
   ppsDeviceCapabilites : [out] device capabilities
  Remarks:
   The psDeviceCapabilites is allocated by the function and must be released using NBDeviceFree.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetCapabilities(const HNBDevice hDevice, NBDeviceCapabilities **ppsDeviceCapabilites);

/*
  Summary:
   Set custom scan parameters in the device context for later custom scans.
  Parameters:
   hDevice :                [in] device handle
   uiHorizontalOrigin :     [in] horizontal coordinate of the scan (uiHorizontalOrigin + uiWidth <= 300)
   uiVerticalOrigin :       [in] vertical coordinate of the scan (multiple of 8, uiVerticalOrigin + uiHeight <= 400)
   uiWidth :                [in] width (uiWidth is multiple of 2, uiWidth > 16, uiHorizontalOrigin + uiWidth <= 300)
   uiHeight :               [in] height (uiHeight is multiple of 8, uiHeight > 16, uiVerticalOrigin + uiHeight <= 400)
   uiHorizontalResolution : [in] device capabilities
   uiVerticalResolution :   [in] device capabilities
  Remarks:
   The function has to be called again to set different parameters.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceSetCustomScanFormat(const HNBDevice hDevice, NBUInt uiHorizontalOrigin, NBUInt uiVerticalOrigin, NBUInt uiWidth, NBUInt uiHeight, NBUInt uiHorizontalResolution, NBUInt uiVerticalResolution);

/*
 * Getting device state, resetting connection and parameters
 */
 
 /*
     Summary:
      Get current device state.
     Parameters:
      hDevice :        [in] handle to device
      peDeviceState :  [out] result, current device state
     Remarks:
      If returned device state is NBDeviceStateNotConnected -
      device is disconnected and removed from the system. In this
      case caller needs to destroy handle to device using
      NBDeviceDestroy.
      
      If returned device state is NBDeviceStateNotAwake - device is
      in sleep mode and can be awaken by using NBDeviceReset
      function.
     Returns:
      If the function succeeds, the return value is NB_OK. If the
      function fails, one of the error codes is returned (<link Error codes>).
 */
NBResult NB_API NBDeviceGetState(const HNBDevice hDevice, NBDeviceState * peDeviceState);

/*
  Summary:
   Soft resets connected device, awakes device if it is in
   NBDeviceStateNotAwake state (i.e. low power mode, see
   NBDeviceEnterStopMode).
  Parameters:
   hDevice :  [in] Handle to device
  Remarks:
   Current device state can be obtained using NBDeviceGetState
   method.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceReset(const HNBDevice hDevice);

/*
 *Getting device type, description, supported scan formats
 */
 
/*
    Summary:
     Get device type.
    Parameters:
     hDevice :       [in] handle to device
     peDeviceType :  [out] result, device type
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetType(const HNBDevice hDevice, NBDeviceType * peDeviceType);

/*
    Summary:
     Get device connection type.
    Parameters:
     hDevice :       [in] handle to device
     peDeviceType :  [out] result, device connection type
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetConnectionType(const HNBDevice hDevice, NBDeviceConnectionType * peConnectionType);

/*
    Summary:
     Get version of firmware present in the device.
    Parameters:
     hDevice :    [in] handle to device
     psVersion :  [out] result, firmware version
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetFirmwareVersion(const HNBDevice hDevice, NBVersion * psVersion);

/*
    Summary:
     Get device id.
    Parameters:
     hDevice :         [in] handle to device
     szValue :         [in/out] pre\-allocated buffer to store
                       device id
     uiValueLength :   [in] pre\-allocated buffer length
     puiValueLength :  [out] actual length of device id (not
                       including null\-terminator)
    Remarks:
     Before calling NBDeviceGetIdA to get device id, actual length
     of device id needs to be determined. To do that,
     NBDeviceGetIdA needs to be called with szValue set to NULL
     and uiValueLength set to 0. This way, puiValueLength will
     return actual length of device id (without the trailing
     null-termination symbol). Afterwards, caller allocates
     puiValueLength + 1 size of buffer and calls NBDeviceGetIdA
     with specifying pre-allocated buffer and its size,
     NBDevicesGetIdA will fill device id into specified buffer.
     
     NB_ERROR_INSUFFICIENT_BUFFER error will be returned if the
     specified buffer is not sufficient to store function result.
     
     NB_DEVICE_STRING_MAX_LENGTH can be used to pre-allocate
     buffer (on heap or stack), thus removing initial call to
     NBDeviceGetIdA.
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetIdA(const HNBDevice hDevice, NBAChar * szValue, NBUInt uiValueLength, NBUInt * puiValueLength);

/*
    Summary:
     Get device manufacturer.
    Parameters:
     hDevice :         [in] handle to device
     szValue :         [in/out] pre\-allocated buffer to store
                       device manufacturer
     uiValueLength :   [in] pre\-allocated buffer length
     puiValueLength :  [out] actual length of device manufacturer
                       (not including null\-terminator)
    Remarks:
     Before calling NBDeviceGetManufacturerA to get device
     manufacturer, actual length of device manufacturer needs to
     be determined. To do that, NBDeviceGetManufacturerA needs to
     be called with szValue set to NULL and uiValueLength set to
     \0. This way, puiValueLength will return actual length of
     device manufacturer (without the trailing null-termination
     symbol). Afterwards, caller allocates puiValueLength + 1 size
     of buffer and calls NBDeviceGetManufacturerA with specifying
     pre-allocated buffer and its size, NBDeviceGetManufacturerA
     will fill device manufacturer into specified buffer.
     
     NB_ERROR_INSUFFICIENT_BUFFER error will be returned if the
     specified buffer is not sufficient to store function result.
     
     NB_DEVICE_STRING_MAX_LENGTH can be used to pre-allocate
     buffer (on heap or stack), thus removing initial call to
     NBDeviceGetManufacturerA.
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetManufacturerA(const HNBDevice hDevice, NBAChar * szValue, NBUInt uiValueLength, NBUInt * puiValueLength);

/*
  Summary:
   Get device model.
  Parameters:
   hDevice :         [in] handle to device
   szValue :         [in/out] pre\-allocated buffer to store
                     device model
   uiValueLength :   [in] pre\-allocated buffer length
   puiValueLength :  [out] actual length of device model (not
                     including null\-terminator)
  Remarks:
   Before calling NBDeviceGetModelA to get device model, actual
   length of device model needs to be determined. To do that,
   NBDeviceGetModelA needs to be called with szValue set to NULL
   and uiValueLength set to 0. This way, puiValueLength will
   return actual length of device model (without the trailing
   null-termination symbol). Afterwards, caller allocates
   puiValueLength + 1 size of buffer and calls NBDeviceGetModelA
   with specifying pre-allocated buffer and its size,
   NBDeviceGetModelA will fill device model into specified
   buffer.
   
   NB_ERROR_INSUFFICIENT_BUFFER error will be returned if the
   specified buffer is not sufficient to store function result.
   
   NB_DEVICE_STRING_MAX_LENGTH can be used to pre-allocate
   buffer (on heap or stack), thus removing initial call to
   NBDeviceGetModelA.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetModelA(const HNBDevice hDevice, NBAChar * szValue, NBUInt uiValueLength, NBUInt * puiValueLength);

/*
  Summary:
   Get serial number for connected device.
  Parameters:
   hDevice :         [in] handle to device
   szValue :         [in/out] pre\-allocated buffer to store
                     device serial number
   uiValueLength :   [in] pre\-allocated buffer length
   puiValueLength :  [out] actual length of device serial number
                     (not including null\-terminator)
  Remarks:
   Before calling NBDeviceGetSerialNumberA to get device serial
   number, actual length of device serial number needs to be
   determined. To do that, NBDeviceGetSerialNumberA needs to be
   called with szValue set to NULL and uiValueLength set to 0.
   This way, puiValueLength will return actual length of device
   serial number (without the trailing null-termination symbol).
   Afterwards, caller allocates puiValueLength + 1 size of
   buffer and calls NBDeviceGetSerialNumberA with specifying
   pre-allocated buffer and its size, NBDeviceGetSerialNumberA
   will fill device serial number into specified buffer.
   
   NB_ERROR_INSUFFICIENT_BUFFER error will be returned if the
   specified buffer is not sufficient to store function result.
   
   NB_DEVICE_STRING_MAX_LENGTH can be used to pre-allocate
   buffer (on heap or stack), thus removing initial call to
   NBDeviceGetSerialNumberA.

	 Note: 
	 
	 In the case where the whole fingerprint reader unit has a
	 serial number, the output value of szValue will be the serial 
	 number of the entire reader unit. To get the serial number of
	 only the internal module - use NBDeviceGetSerialModuleNumberA.

	 In the case it is only the internal reader module, the output 
	 value of szValue will be the serial number of the module itself

  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetSerialNumberA(const HNBDevice hDevice, NBAChar * szValue, NBUInt uiValueLength, NBUInt * puiValueLength);

//here
/*
	Summary:
	 Get serial number for connected fingerprint module.
	Parameters:
	 hDevice :         [in] handle to device
	 szValue :         [in/out] pre\-allocated buffer to store
										 device serial number
	 uiValueLength :   [in] pre\-allocated buffer length
	 puiValueLength :  [out] actual length of device serial number
										 (not including null\-terminator)
	Remarks:
	 Before calling NBDeviceGetSerialNumberA to get device serial
	 number, actual length of device serial number needs to be
	 determined. To do that, NBDeviceGetSerialNumberA needs to be
	 called with szValue set to NULL and uiValueLength set to 0.
	 This way, puiValueLength will return actual length of device
	 serial number (without the trailing null-termination symbol).
	 Afterwards, caller allocates puiValueLength + 1 size of
	 buffer and calls NBDeviceGetSerialNumberA with specifying
	 pre-allocated buffer and its size, NBDeviceGetSerialNumberA
	 will fill device serial number into specified buffer.

	 NB_ERROR_INSUFFICIENT_BUFFER error will be returned if the
	 specified buffer is not sufficient to store function result.

	 NB_DEVICE_STRING_MAX_LENGTH can be used to pre-allocate
	 buffer (on heap or stack), thus removing initial call to
	 NBDeviceGetSerialNumberA.

	 Note:

	 This method outputs the serial number of only the fingerprint 
	 module.

	Returns:
	 If the function succeeds, the return value is NB_OK. If the
	 function fails, one of the error codes is returned (<link Error codes>).
*/

NBResult NB_API NBDeviceGetModuleSerialNumberA(const HNBDevice hDevice, NBAChar * szValue, NBUInt uiValueLength, NBUInt * puiValueLength);

/*
  Summary:
   Get product name for connected device.
  Parameters:
   hDevice :         [in] handle to device
   szValue :         [in/out] pre\-allocated buffer to store
                     device product name
   uiValueLength :   [in] pre\-allocated buffer length
   puiValueLength :  [out] actual length of device product name
                     (not including null\-terminator)
  Remarks:
   Before calling NBDeviceGetProductA to get device product
   name, actual length of device product name needs to be
   determined. To do that, NBDeviceGetProductA needs to be
   called with szValue set to NULL and uiValueLength set to 0.
   This way, puiValueLength will return actual length of device
   product name (without the trailing null-termination symbol).
   Afterwards, caller allocates puiValueLength + 1 size of
   buffer and calls NBDeviceGetProductA with specifying
   pre-allocated buffer and its size, NBDeviceGetProductA will
   fill device product name into specified buffer.
   
   NB_ERROR_INSUFFICIENT_BUFFER error will be returned if the
   specified buffer is not sufficient to store function result.
   
   NB_DEVICE_STRING_MAX_LENGTH can be used to pre-allocate
   buffer (on heap or stack), thus removing initial call to
   NBDeviceGetProductA.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetProductA(const HNBDevice hDevice, NBAChar * szValue, NBUInt uiValueLength, NBUInt * puiValueLength);

/*
    Summary:
     Check if specified scan format is supported by device.
    Parameters:
     hDevice :        [in] handle to device
     eScanFormat :    [in] desired device scan format
     pbIsSupported :  [out] result, whether specified desired device
                      scan format is supported
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceIsScanFormatSupported(const HNBDevice hDevice, NBDeviceScanFormat eScanFormat, NBBool * pbIsSupported);

/*
    Summary:
     Get list of supported scan formats by specified device.
    Parameters:
     hDevice :              [in] handle to device
     areScanFormats :       [in/out] pre\-allocated array of
                            NBDeviceScanFormat
     uiScanFormatsLength :  [in] pre\-allocated array length
     puiCount :             [out] actual count of supported device
                            scan formats
    Remarks:
     Function requires caller to allocate areScanFormats.
     NBDeviceGetSupportedScanFormats only fills descriptor
     information into pre-allocated array.
     NBDeviceGetSupportedScanFormats accepts areScanFormats = NULL
     and uiScanFormatsLength = 0 in order for caller to find out
     how many scan formats are available and then pre-allocate array
     before passing for second time to
     NBDeviceGetSupportedScanFormats.
     
     NB_ERROR_INSUFFICIENT_BUFFER error will be returned if the
     specified buffer is not sufficient to store function result.
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetSupportedScanFormats(const HNBDevice hDevice, NBDeviceScanFormat * areScanFormats, NBUInt uiScanFormatsLength, NBUInt * puiCount);
/*
    Summary:
     Retrieve extended information about scan format.
    Parameters:
     hDevice :           [in] handle to device
     eScanFormat :       [in] desired scan format
     psScanFormatInfo :  [out] result, extended information about
                         specified scan format
    Remarks:
     If specified desired scan format is not supported,
     NB_ERROR_NOT_SUPPORTED is returned (to check whether device
     format is supported, NBDeviceIsScanFormatSupported function
     can be used).
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetScanFormatInfo(const HNBDevice hDevice, NBDeviceScanFormat eScanFormat, NBDeviceScanFormatInfo * psScanFormatInfo);

/*
 * Getting/Setting device parameters
 */

/*
    Summary:
     Set value for specified parameter.
    Parameters:
     hDevice :      [in] handle to device
     uiParameter :  [in] id of parameter
     iValue :       [in] value for specified parameter
    Remarks:
     Parameter value is applied only for specified device (device handle).
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceSetParameter(const HNBDevice hDevice, NBUInt uiParameter, NBInt iValue);
/*
    Summary:
     Set value for specified MIMS parameter.
    Parameters:
     hDevice :      [in] handle to device
     uiParameter :  [in] id of parameter
     fValue :       [in] value for specified MIMS parameter
    Remarks:
     Parameter value is applied only for specified device (device handle).
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceSetMIMSParameter(const HNBDevice hDevice, NBUInt uiParameter, const NBFloat fValue);

/*
    Summary:
     Get value of specified MIMS parameter.
    Parameters:
     hDevice :      [in] handle to device
     uiParameter :  [in] id of parameter
     pfValue :      [out] result, value for specified MIMS parameter
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetMIMSParameter(const HNBDevice hDevice, NBUInt uiParameter, NBFloat * pfValue);

/*
    Summary:
     Get value of specified parameter.
    Parameters:
     hDevice :      [in] handle to device
     uiParameter :  [in] id of parameter
     piValue :      [out] result, value for specified parameter
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetParameter(const HNBDevice hDevice, NBUInt uiParameter, NBInt * piValue);

/*
    Summary:
     Set value for specified blob parameter.
    Parameters:
     hDevice :      [in] handle to device
     uiParameter :  [in] id of parameter
     pBlob :       [in] parameter data
     stBlobSize :   [in] size of the parameter data
    Remarks:
     Parameter value is applied only for specified device (device handle).
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceSetBlobParameter(const HNBDevice hDevice, NBUInt uiParameter, const NBByte *pBlob, NBSizeType stBlobSize);

#ifndef NB_DEVICES_LITE
/*
    Summary:
     Get value of specified parameter.
    Parameters:
     hDevice :      [in] handle to device
     uiParameter :  [in] id of parameter
     ppBlob :      [out] result, data of the parameter
     pstBlobSize :  [out] result, value for specified parameter
    Remarks:
     The parameter data (ppiBlob) is allocated by the function and must be released using NBDeviceFree.
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGetBlobParameter(const HNBDevice hDevice, NBUInt uiParameter, NBByte **ppBlob, NBSizeType *pstBlobSize);
#endif

/*
 * Getting hardware fingerprint detect value, image acquisition
 */
 
/*
  Summary:
   Retrieve value representing whether there is finger present
   on the surface of the device.
  Parameters:
   hDevice :      [in] handle to device
   eDetectType :  [in] finger detection type
   piValue :      [out] result, value representing
                  score/probability that finger is present on
                  surface of the device (range\: 0\-255)
  Remarks:
   NB_DEVICE_DEFAULT_FINGER_DETECT_TYPE can be used to select
   default finger detect type to be used to detect whether
   finger is present on device surface.
   
   NB_DEVICE_DEFAULT_FINGER_DETECT_THRESHOLD can be used as
   threshold, defining that any score above specified threshold
   can be considered as meaning that there is finger present on
   device surface.

   Most of the devices automatically calibrate the finger present
   functionality when there is no finger on the device. This means
   that in the rare case when the user keeps his finger on the
   device the whole time since the last power-up or reset, the
   finger present functionality may not be calibrated yet and the
   returned piValue may be inaccurate. This will correct itself
   automatically when the user lifts his finger.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/ 
NBResult NB_API NBDeviceGetFingerDetectValue(const HNBDevice hDevice, NBDeviceFingerDetectType eDetectType, NBInt * piValue);
/*
  Summary:
   Scan snapshot from device scanning surface.
  Parameters:
   hDevice :       [in] handle to device
   eScanFormat :   [in] desired device scan format
   pBuffer :       [in/out] pre\-allocated buffer to store result
                   image
   stBufferSize :  [in] pre\-allocated buffer size
   uiFlags :       [in] bitmask specifying flags, which modify
                   slightly behavior of the function
   peStatus :      [out] result, additional information
                   specifying status of scan procedure
  Remarks:
   NB_ERROR_NOT_SUPPORTED error will be returned if specified
   desired scan format is not supported.
   
   pBuffer needs to be pre-allocated by function caller and its
   size should be equals or higher than (width x height) of
   desired scan format.
   
   peStatus returns status describing scanned snapshot, however
   it provides only additional feedback and pBuffer will still
   contain image captured even if peStatus status is not
   NBDeviceScanStatusOk.

   This function does not perform liveness detection or any
   image quality evaluation.
   
   NB_DEVICE_SCAN_SKIP_FINGER_DETECTION_FLAG flag,
   passed as uiFlags parameter (LITE only), disables the check of
   presence of fingerprint entirely (function will just scan).

  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceScan(const HNBDevice hDevice, NBDeviceScanFormat eScanFormat, NBByte * pBuffer, NBSizeType stBufferSize, NBUInt uiFlags, NBDeviceScanStatus * peStatus);
/*
  Summary:
   Extended scanning, blocks until best possible fingerprint
   image is captured or operation is timeout/canceled.
  Parameters:
   hDevice :       [in] handle to device
   eScanFormat :   [in] desired device scan format
   iTimeout :      [in] timeout in milliseconds
   pPreviewProc :  [in] callback to be called when new preview
                   image is captured (optional)
   pParam :        [in] pass\-through parameter to be passed to
                   pPreviewProc on new preview event (optional)
   pBuffer :       [in/out] pre\-allocated buffer to store result
                   image
   stBufferSize :  [in] pre\-allocated buffer size
   uiFlags :       [in] bitmask specifying flags, which modify
                   slightly behavior of the function
   peStatus :      [out] result, information specifying status of
                   scan procedure
  Remarks:
   Function blocks execution and does scanning until image of
   satisfactory parameters is acquired, or set timeout expires,
   or scanning is canceled.
   
   NB_DEVICE_SCAN_TIMEOUT_INFINITE can be used to indicate
   infinite scan timeout.
   
   NB_ERROR_NOT_SUPPORTED error will be returned if specified
   desired scan format is not supported.
   
   If uiTimeout is set to 0, NBDeviceScanEx returns after first
   image scan.
   
   pBuffer needs to be pre-allocated by function caller and its
   size should be equals or higher than (width x height) of
   desired scan format.
   
   peStatus returns status describing function execution.
   pBuffer will still contain last image captured (if it was
   captured) even if peStatus status is not
   NBDeviceScanStatusOk.
   
   pPreviewProc and pParam can be NULL if no preview is
   requested.
   
   Preview enables previewing the image and possibility to
   override specified status (e.g. accept images with lower
   quality, or requiring even higher image quality).
   
   NB_DEVICE_FLAG_SCAN_SKIP_FINGER_NOT_REMOVED_STATUS flag,
   passed as uiFlags parameter, disables the check of presence
   of the fingerprint during scan initialization (resulting in
   NBDeviceScanStatusNotRemoved status) and can often be used
   after the device is awaken from sleep on finger detect (after
   NBDeviceEnterStopMode with SPI NBDevice).

   NB_DEVICE_SCAN_SKIP_FINGER_DETECTION_FLAG flag,
   passed as uiFlags parameter (LITE only), disables the check of
   presence of fingerprint entirely (function will just scan).

  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceScanEx(const HNBDevice hDevice, NBDeviceScanFormat eScanFormat, NBInt iTimeout, NBDeviceScanPreviewProc pPreviewProc, void * pParam, NBByte * pBuffer, NBSizeType stBufferSize, NBUInt uiFlags, NBDeviceScanStatus * peStatus);

/*
  Summary:
   Extended scanning, blocks until best possible fingerprint
   image is captured or operation is timeout/canceled.
  Parameters:
   hDevice :          [in] handle to device
   iTimeout :         [in] timeout in milliseconds
   pPreviewProc :     [in] callback to be called when new preview
                      image is captured (optional)
   pParam :           [in] pass\-through parameter to be passed to
                      pPreviewProc on new preview event (optional)
   ppBuffer :         [out] buffer containing the extracted template allocated by the function
   pstBufferSize :    [out] size of the buffer allocated by this function
   puiMinutiaeCount : [out] number of minutiae
   puiQualityScore :  [out] quality score of the extracted template
   peStatus :         [out] result, information specifying status of
                      scan procedure
  Remarks:
   Function blocks execution and scans until a satisfactory template is extracted, 
   or set timeout expires, or scanning is canceled.

   NB_DEVICE_SCAN_TIMEOUT_INFINITE can be used to indicate
   infinite scan timeout.

   pBuffer is allocated by the function and must be released 
   using the NBDeviceFree function.

   peStatus returns status describing function execution.

   pPreviewProc and pParam can be NULL if no preview is
   requested.

   Preview enables previewing the image and possibility to
   override specified status (e.g. accept images with lower
   quality, or requiring even higher image quality).
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceCaptureAndExtract(const HNBDevice hDevice, NBInt iTimeout, NBDeviceScanPreviewProc pPreviewProc, void * pParam, NBByte **ppBuffer, NBSizeType *pstBufferSize, NBUInt * puiMinutiaeCount, NBUInt * puiQualityScore, NBDeviceScanStatus * peStatus);

/*
  Summary:
   Provides the captured image buffer and extratced template from the
   captured image.
  Parameters:
   hDevice :               [in] handle to device
   iTimeout :              [in] timeout in milliseconds
   pPreviewProc :          [in] callback to be called when new preview
                           image is captured (optional)
   pParam :                [in] pass\-through parameter to be passed to
                           pPreviewProc on new preview event (optional)
   pImageBuffer :          [out] buffer containing the extracted template allocated by the function
   stImageBufferSize :     [out] size of the buffer allocated by this function
   ppTemplateBuffer :      [out] template buffer extracted from the scanned image
   pstTemplateBufferSize:  [out] size of the extracted template buffer
   puiMinutiaeCount :      [out] number of minutiae
   puiQualityScore :       [out] quality score of the extracted template
   peStatus :              [out] result, information specifying status of
                           scan procedure
  Remarks:
   Function blocks execution and scans until a satisfactory template is extracted,
   or set timeout expires, or scanning is canceled.

   NB_DEVICE_SCAN_TIMEOUT_INFINITE can be used to indicate
   infinite scan timeout.

   pImageBuffer is allocated by the function and must be released
   using the NBDeviceFree function.

   peStatus returns status describing function execution.

   pPreviewProc and pParam can be NULL if no preview is
   requested.

   Preview enables previewing the image and possibility to
   override specified status (e.g. accept images with lower
   quality, or requiring even higher image quality).
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceCaptureAndExtractData(const HNBDevice hDevice, NBInt iTimeout, NBDeviceScanPreviewProc pPreviewProc, void * pParam, NBByte * pImageBuffer, NBSizeType stImageBufferSize, NBByte **ppTemplateBuffer, NBSizeType *pstTemplateBufferSize, NBUInt * puiMinutiaeCount, NBUInt * puiQualityScore, NBDeviceScanStatus * peStatus);

/*
  Summary:
   Check if there is scan in progress.
  Parameters:
   hDevice :  [in] handle to device
   pbValue :  [out] result, whether scan is in
              progress
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceIsScanRunning(const HNBDevice hDevice, NBBool * pbValue);
/*
    Summary:
     Cancel on-going extended scan operation.
    Parameters:
     hDevice :  [in] handle to device
    Remarks:
     If no scan operation is in progress,
     NBDeviceCancelScan function will succeed and won't return any
     error.
    Returns:
     If the function succeeds, the return value is NB_OK. If the
     function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceCancelScan(const HNBDevice hDevice);

/*
  Summary:
   Method puts device/module in a low power state.
  Parameters:
   hDevice :                 [in] handle to device
   eStopMode :               [in] type of low power state mode to
                             enter
   uiFingerDetectionCount :  [in] finger detections to perform
                             before leaving the low power mode
                             (only to be used with
                             NBDeviceStopModeCountedFingerDetection)
  Remarks:
   Method halts device internal clocks putting the device to a
   low power state. Stop modes allow to change the behaviour of
   the device during low power state. If a finger is detected,
   device status pin is set and the module leaves sleep mode.
   Without a finger on the sensor, the application can do
   NBDeviceReset to leave the low power mode.
   
   Method is valid only for SPI devices, NB_ERROR_NOT_SUPPORTED
   error will be returned if the specified device is not SPI
   device.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceEnterStopMode(const HNBDevice hDevice, NBDeviceStopMode eStopMode, NBUInt uiFingerDetectionCount);

/*
  Summary:
   Method sets device/module LED.
  Parameters:
   hDevice :    [in] handle to device
   eLedState :  [in] type of LED pattern to set
  Remarks:
   Method is valid only for USB devices, NB_ERROR_NOT_SUPPORTED
   error will be returned if the specified device is not USB
   device or USB device does not support setting LED pattern.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceSetLedState(const HNBDevice hDevice, NBDeviceLedState eLedState);

/*
  Summary:
   Convert raw image data to other formats, like the ISO Finger Image Record (FIR) format.
   The image data can be stored raw or compressed using JPEG 2000. The converted image is stored in a buffer
   allocated by this function. The buffer must be released using the NBDeviceFree function.
  Parameters:
   pImage :            [in] image data
   uiWidth :           [in] width of the input image
   uiHeight :          [in] height of the input image
   uiDataDpi :         [in] dots per inch of the input image
   eFormat :           [in] output format
   fCompressionRatio : [in] compression ratio, value of 1 indicates lossless compression, 
                            only used with JPEG 2000 encoding
   eFingerPosition :   [in] finger present in the converted scan
   uiFlags :           [in] flags
   ppOutData :         [out] output buffer allocated by the function
   pstOutSize :        [out] size of the output data
  Remarks:
   The output data is allocated by this function and it must be 
   released by the NBDeviceFree function.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceConvertImage(const NBByte *pImage, NBUInt16 uiWidth, NBUInt16 uiHeight, NBUInt16 uiDataDpi, NBDeviceEncodeFormat eFormat,
    NBFloat fCompressionRatio, NBDeviceFingerPosition eFingerPosition, NBUInt uiFlags, NBByte **ppOutData, NBSizeType *pstOutSize);

/*
  Summary:
   Release a buffer allocated by NBDevices.
  Parameters:
   pData : [in] the buffer to release
*/
NBResult NB_API NBDeviceFree(NBByte *pData);

/*
  Summary:
   Produce calibration data for the currently attached device.
   The device must be absolutely clean.
  Parameters:
   hDevice :                [in] handle to device
   ppCalibrationData :      [out] calibration data
   pstCalibrationDataSize : [out] calibration data size
  Remarks:
   The process is very time consuming and may take several minutes.
   
   The output data is allocated by this function and it must be 
   released by the NBDeviceFree function.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGenerateCalibrationData(const HNBDevice hDevice, NBByte **ppCalibrationData, NBSizeType *pstCalibrationDataSize);

/*
  Summary:
   Produce calibration data for the currently attached device.
   The device must be absolutely clean.
  Parameters:
   hDevice :                [in] handle to device
   pCalibrationData :       [in] calibration data
   pstCalibrationDataSize : [in/out] calibration data size
  Remarks:
   The process is very time consuming and may take several minutes.

   If the function is called with ppCalibrationData == NULL then the 
   pstCalibrationDataSize will contain the ppCalibrationData size 
   necessary to perform the calibration.

   The output data is allocated by the caller based on the value 
   assigned to pstCalibrationDataSize when the function is called with 
   ppCalibrationData == NULL.

   When a valid ppCalibrationData is passed the function sets 
   pstCalibrationDataSize to the actual size of the calibration data
   in ppCalibrationData. The buffer can then be reallocated with just the 
   size pstCalibrationDataSize.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceGenerateCalibrationDataInplace(const HNBDevice hDevice, NBByte *pCalibrationData, NBSizeType *pstCalibrationDataSize);

/*
  Summary:
    Return the image quality score for the provided image. The exact range of the score values depends on the selected image quality algorithm.
  Parameters:
    pImage :          [ in] image data
    uiWidth :         [ in] width of the input image
    uiHeight :        [ in] height of the input image
    uiDataDpi :       [ in] dots per inch of the input image
    eQuality :        [ in] image quality algorithm
    piQualityScore : [ out] image quality score
  Returns:
    If the function succeeds, the return value is NB_OK. If the
    function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceImageQuality(const NBByte *pImage, NBUInt16 uiWidth, NBUInt16 uiHeight, NBUInt16 uiDataDpi, NBDeviceImageQualityAlgorithm eQuality, NBInt *piQualityScore);

/*
  Summary:
    Returns the background image(BG) with scan status.
  Parameters:
    hDevice :         [in] handle to device
    eScanFormat :     [in] desired device scan format
    pParam :          [in] pass-through parameter to be passed to
                           pPreviewProc on new preview event (optional)
    pBuffer :         [in/out] pre-allocated buffer to store result
                           image
    stBufferSize :    [in] pre-allocated buffer size
    peStatus :        [out] result, information specifying status of
                      scan procedure. If the peStatus is NBDeviceScanStatusNotRemoved
                      user has to call the API without keeping the finger on sensor.
  Returns:
    If the function succeeds, the return value is NB_OK. If the
    function fails, one of 'the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBDeviceScanBGImage(const HNBDevice hDevice, NBDeviceScanFormat eScanFormat, void * pParam, NBByte * pBuffer, NBSizeType stBufferSize, NBDeviceScanStatus * peStatus);

#ifdef NB_CPP
}
#endif

#endif // !NB_DEVICE_H
