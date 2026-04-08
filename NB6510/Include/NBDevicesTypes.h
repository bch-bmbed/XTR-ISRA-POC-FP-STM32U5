#ifndef NB_DEVICES_TYPES_H
#define NB_DEVICES_TYPES_H

#include <NBTypes.h>
#include <NBErrors.h>

#ifdef NB_CPP
extern "C"
{
#endif

#ifdef NB_EMBEDDED
    #define NB_DEVICES_LITE
#endif

#ifdef NB_DEVICES_LITE
    //Enable the below flag for blackline uniformity test in 65210-S.
    //This flag enabled build will be used for SNR test to get black images using 65210-S. 
    //Also, Enable the API "NBDeviceSetAdjustmentValue" in NBDevicesLite.def
    #define NB_DEVICES_LITE_FEATURE_BLACKLINE_UNIFORMITY_SNR_TEST 0
#endif

/*
   Declaration of a NBDevice device handle
*/
typedef NBHandle HNBDevice;

/*
    Enumeration of device types
*/
typedef enum
{
    /* Unknown device type */
    NBDeviceTypeUnknown = 0,
    /* NB 1010 SPI device */
    NBDeviceTypeNB1010S = 100,
    /* NB 1020 SPI device */
    NBDeviceTypeNB1020S = 101,
    /* NB 2020 SPI device */
    NBDeviceTypeNB2020S = 102,
    /* NB 2021 SPI device */
    NBDeviceTypeNB2021S = 103,
    /* NB 2022 SPI device */
    NBDeviceTypeNB2022S = 104,
    /* NB 2034 SPI device */
    NBDeviceTypeNB2034S = 105,
    /* NB 2023 SPI device */
    NBDeviceTypeNB2023S = 106,
    /* NB 2033 SPI device */
    NBDeviceTypeNB2033S = 107,
    /* NB 65210 SPI device */
    NBDeviceTypeNB65210S = 108,
    /* NB 1010 USB device */
    NBDeviceTypeNB1010U = 200,
    /* NB 1020 USB device */
    NBDeviceTypeNB1020U = 201,
    /* NB 2020 USB device */
    NBDeviceTypeNB2020U = 202,
    /* NB 2024 USB device */
    NBDeviceTypeNB2024U = 203,
    /* NB 3023 USB device */
    NBDeviceTypeNB3023U = 204,
    /* NB 2023 USB device */
    NBDeviceTypeNB2023U = 205,
    /* NB 2033 USB device */
    NBDeviceTypeNB2033U = 250,
    /* NB 65100 USB device */
    NBDeviceTypeNB65100U = 300,
    /* NB 65200 USB device */
    NBDeviceTypeNB65200U = 301,
    /* NB 65100 UART device */
    NBDeviceTypeNB65100UA = 302
} NBDeviceType;

/*
    Enumeration of device connection types
*/
typedef enum
{
    /* Unknown device connection type */
    NBDeviceConnectionTypeUnknown = 0,
    /* USB device connection type */
    NBDeviceConnectionTypeUsb = 1,
    /* SPI device connection type */
    NBDeviceConnectionTypeSpi = 2,
    /* UART device connection type */
    NBDeviceConnectionTypeUart = 3,
    /* Bluetooth device connection type */
    NBDeviceConnectionTypeBluetooth = 4
} NBDeviceConnectionType;

/*
    Enumeration of device states
*/
typedef enum
{
    /* Device is not connected (disconnected, NBDeviceDestroy is requested) */
    NBDeviceStateNotConnected = 0,
    /* Device is not awake (NBDeviceReset to wake device) */
    NBDeviceStateNotAwake = 1,
    /* Device is awake */
    NBDeviceStateAwake = 2
} NBDeviceState;

/*
    Enumeration of supported fingerprint detection types
*/
typedef enum
{
    /* Baseline */
    NBDeviceFingerDetectTypeBaseline = 0,
    /* Enhanced finger on */
    NBDeviceFingerDetectTypeEnhanced = 1,
    /* Quick (capacitive touch score) */
    NBDeviceFingerDetectTypeQuick = 2,
    /* Last wake (enhanced score following wake up) */
    NBDeviceFingerDetectTypeLastWake = 3
} NBDeviceFingerDetectType;

typedef enum
{
    NBDeviceLLinterfaceType_legacy = 0,
    NBDeviceLLinterfaceType_usb = 1,
    NBDeviceLLinterfaceType_nbuapi_65200 = 2,
    NBDeviceLLinterfaceType_nbuapi_65100 = 3,
    NBDeviceLLinterfaceType_spi= 4,
    NBDeviceLLinterfaceType_wbf = 5
} NBDeviceLowLevelInterfaceType;

/*
    Enumeration of supported scan formats
*/
typedef enum
{
    /* 12 mm x 17 mm format, width 180 pixels, height 256 pixels, 385 dpi */
    NBDeviceScanFormat12x17 = 0,
    /* 12 mm x 16 mm format, width 180 pixels, height 244 pixels, 385 dpi */
    NBDeviceScanFormat12x16 = 1,
    /* partial format, width 90 pixels, height 128 pixels, 385 dpi */
    NBDeviceScanFormatPartial = 2,
    /* 12 mm x 12 mm format, width 180 pixels, height 180 pixels, 385 dpi */
    NBDeviceScanFormat12x12 = 3,
    /* 12 mm x 17 mm format, width 234 pixels, height 332 pixels, upscaled to 500 dpi */
    NBDeviceScanFormat12x17_500 = 4,
    /* 12 mm x 16 mm format, width 234 pixels, height 317 pixels, upscaled to 500 dpi */
    NBDeviceScanFormat12x16_500 = 5,
    /* partial format, width 117 pixels, height 166 pixels, upscaled to 500 dpi */
    NBDeviceScanFormatPartial_500 = 6,
    /* 12 mm x 12 mm format, width 234 pixels, height 234 pixels, upscaled to 500 dpi */
    NBDeviceScanFormat12x12_500 = 7,
    /* quarter partial format, width 22 pixels, height 128 pixels, 385 dpi */
    NBDeviceScanFormatQuarterPartial = 8,
    /* quarter partial format, width 29 pixels, height 166 pixels, upscaled to 500 dpi */
    NBDeviceScanFormatQuarterPartial_500 = 9,
    /* 15 mm x 20 mm format, width 300 pixels, height 400 pixels, 500 dpi */
    NBDeviceScanFormat15x20_500 = 10,
    /* partial format, width 90 pixels, height 128 pixels, 500 dpi */
    NBDeviceScanFormatPartialNative_500 = 11,
    /* quarter partial format, width 22 pixels, height 128 pixels, 500 dpi */
    NBDeviceScanFormatQuarterPartialNative_500 = 12,
    /* Custom scan format */
    NBDeviceScanFormatCustom,
    /* Max enum value */
    NBDeviceScanFormatEnd
} NBDeviceScanFormat;

/*
  Enumeration of scan format types
*/
typedef enum
{
    /*
      Native (to device) scan format type
    */
    NBDeviceScanFormatTypeNative = 0,
    /*
      Upscaled (from native) scan format type
    */
    NBDeviceScanFormatTypeUpscaled = 1,
    /*
    Downscaled (from native) scan format type
    */
    NBDeviceScanFormatTypeDownscaled = 2,
    /*
      Optical equivalent scan format type
    */
    NBDeviceScanFormatTypeOpticalEquivalent = 3
} NBDeviceScanFormatType;

/*
  Structure holding extended information about scan format -
  scan format, scan format type, width, height, horizontal and
  vertical resolution                                         
*/
typedef struct
{
    /* Scan format */
    NBDeviceScanFormat eScanFormat;
    /* Scan format type */
    NBDeviceScanFormatType eScanFormatType;
    /* Left (pixels) */
    NBUInt uiLeft;
    /* Bottom (pixels) */
    NBUInt uiBottom;
    /* Width (pixels) */
    NBUInt uiWidth;
    /* Height (pixels) */
    NBUInt uiHeight;
    /* Horizontal resolution (dpi) */
    NBUInt uiHorizontalResolution;
    /* Vertical resolution (dpi) */
    NBUInt uiVerticalResolution;
    /* Format tag used in the device implemntation for NB-65100 */
    NBUInt8 uiFormatTag;
} NBDeviceScanFormatInfo;

/*
  Calibration data is managed by the user code and must be available 
  throught the entire lifetime of the affected device.
*/
typedef struct
{
    /* Address fo the actual calibration data */
    NBByte *pCalibrationData;
    /* Size of the calibration data */
    NBSizeType stCalibrationDataSize;
    /* The data is managed by the device and should be deallocated during destruction */
    NBBool bDeallocate;
} NBDeviceCalibrationDataAddress;

/*
    Enumeration of scan result statuses
*/
typedef enum
{
    /* Status is not set (None) */
    NBDeviceScanStatusNone = 0,
    /* Capture is successful */
    NBDeviceScanStatusOk = 1,
    /* Capture is canceled */
    NBDeviceScanStatusCanceled = 2,
    /* Timeout occurred */
    NBDeviceScanStatusTimeout = 3,
    /* No finger detected */
    NBDeviceScanStatusNoFinger = 4,
    /* Finger is present before scan start. This status can be suppressed by a flag NB_DEVICE_SCAN_SKIP_FINGER_NOT_REMOVED_STATUS_FLAG,
       but not in the case of a completely first scan in the session with background subtraction enabled. In this case at least one
       scan without fingerprint on sensor is mandatory to acquire a background image. */
    NBDeviceScanStatusNotRemoved = 5,
    /* Bad fingerprint quality */
    NBDeviceScanStatusBadQuality = 6,
    /* Bad fingerprint size */
    NBDeviceScanStatusBadSize = 7,
    /* The image contains a spoof */
    NBDeviceScanStatusSpoof = 8,

    NBDeviceScanStatusEmpty = 0x1000,
    NBDeviceScanStatusDone = 0x1001,
    NBDeviceScanStatusLiftFinger = 0x1002,
    NBDeviceScanStatusWaitForSensorInitialization = 0x1004,
    NBDeviceScanStatusPutFingerOnSensor = 0x1008,
    NBDeviceScanStatusKeepFingerOnSensor = 0x1010,
    NBDeviceScanStatusWaitForDataProcessing = 0x1020,
    NBDeviceScanStatusSpoofDetected = 0x1040
} NBDeviceScanStatus;

typedef enum 
{
    /* Device specific default image type */
    NBDeviceImageTypeDefault,
    /* Completely raw image produced by the device */
    NBDeviceImageTypeRaw,
    /* Raw image with compensation data */
    NBDeviceImageTypeCompensatedRaw,
    /* Legacy image */
    NBDeviceImageTypeLegacy,
    /* Enhanced image */
    NBDeviceImageTypeEnhanced
#if (NB_DEVICES_LITE_FEATURE_BLACKLINE_UNIFORMITY_SNR_TEST)
    /* Black uniform image: test only option */
    , NBDeviceImageTypeBlackUniform
#endif
} NBDeviceImageType;

typedef enum
{
    NBDeviceProcImageRotateFlipTypeRotateNone = 0,
    NBDeviceProcImageRotateFlipTypeRotate90 = 1,
    NBDeviceProcImageRotateFlipTypeRotate180 = 2,
    NBDeviceProcImageRotateFlipTypeRotate270 = 3,
    NBDeviceProcImageRotateFlipTypeFlipNone = 0,
    NBDeviceProcImageRotateFlipTypeFlipX = 4,
    NBDeviceProcImageRotateFlipTypeFlipY = 8,
    NBDeviceProcImageRotateFlipTypeFlipXY = NBDeviceProcImageRotateFlipTypeFlipX | NBDeviceProcImageRotateFlipTypeFlipY,
    NBDeviceProcImageRotateFlipTypeNone = NBDeviceProcImageRotateFlipTypeRotateNone | NBDeviceProcImageRotateFlipTypeFlipNone,
} NBDeviceProcImageRotateFlipType;

/* Maximum length for various strings used for
   device descriptions (e.g. device manufacturer or model)      */
#define NB_DEVICE_STRING_MAX_LENGTH 256

#define NB_DEVICE_BLUETOOTH_MAC_ADDRESS_SIZE 17

/*
    Device descriptor holding information about a device - device
    index, device ID, manufacturer, model, serial number, device
    type, firmware version                                       
*/           
typedef struct
{
    /* Internal device index */
    NBUInt uiDeviceIndex;
    /* Device id */
    NBAChar szId[NB_DEVICE_STRING_MAX_LENGTH];
    /* Device manufacturer */
    NBAChar szManufacturer[NB_DEVICE_STRING_MAX_LENGTH];
    /* Device model */
    NBAChar szModel[NB_DEVICE_STRING_MAX_LENGTH];
    /* Device serial number */
    NBAChar szSerialNumber[NB_DEVICE_STRING_MAX_LENGTH];
    /* Device type */
    NBDeviceType eType;
    /* Device firmware version */
    NBVersion sFirmwareVersion;
} NBDeviceInfoA;

/*
  Enumeration of stop modes that device could enter
*/
typedef enum
{
    /* Continuous finger detection */
    NBDeviceStopModeContinuousFingerDetection = 0,
    /* Hard stop (go directly to lowest power state) */
    NBDeviceStopModeHardStop = 1,
    /* Perform 1 .. n finger detections */
    NBDeviceStopModeCountedFingerDetection = 2
} NBDeviceStopMode;

/*
  Enumeration of LED states
*/
typedef enum
{
    /* LED off */
    NBDeviceLedStateOff = 0,
    /* LED flashes 0.3s ON, 0.3s OFF, and repeats */
    NBDeviceLedStateFingerOnRequested = 1,
    /* LED ON solid */
    NBDeviceLedStateInScan = 4,
    /* LED flashes Long ON, Short OFF, and repeats */
    NBDeviceLedStateCustom = 6
} NBDeviceLedState;



/*
  Enumeration of possible output formats for image conversion
*/
typedef enum
{
    /*
      Finger image record 010, according to ISO/IEC 19794-4:2005
    */
    NBDeviceIso010 = 0,
    /*
      Finger image record 010, with data encoded as JPEG 2000. Format is not supported in NBDevicesLite.
    */
    NBDeviceIso010Jpeg2000 = 1,
    /*
      Finger image record 010, with data encoded as JPEG 2000. Format is not supported in NBDevicesLite.
      Note: Although the data are JPEG 2000-encoded, the image data format field in the header is set
      to JPEG (3) instead of JPEG 2000 (4). This is necessary to get this FIR accepted by the
      Aadhaar (Indian government ID infrastructure). 
    */
    NBDeviceIso010Jpeg2000Aadhaar = 2,
    /*
      Finger image record 020, according to ISO/IEC 19794-4:2011
    */
    NBDeviceIso020 = 3,
    /*
      Finger image record 020, with data encoded as JPEG 2000. Format is not supported in NBDevicesLite.
    */
    NBDeviceIso020Jpeg2000 = 4,
    /*
    Finger image record 010, with data encoded as WSQ Format is not supported in NBDevicesLite.
    */
    NBDeviceIso010WSQ = 5,
    /*
    Finger image record 020, with data encoded as WSQ Format is not supported in NBDevicesLite.
    */
    NBDeviceIso020WSQ = 6,
    /*
        Finger image encoded as WSQ Format (not supported in NBDevicesLite).
    */
    NBDeviceWSQ = 7
} NBDeviceEncodeFormat;

/*
Enumeration of image quality algorithms
*/
typedef enum
{
    /*
        Unknown image quality algorithm
    */
    NBDeviceImageQualityAlgorithmUnknown = 0,
    /* 
        The original NFIQ
    */
    NBDeviceImageQualityAlgorithmNFIQ = 1
} NBDeviceImageQualityAlgorithm;

/*
  Enumeration of possible finger positions
*/
typedef enum
{
    /*
      Unknown finger position
    */
    NBDeviceFingerPositionUnknown = 0,
    /*
      Right thumb finger position
    */
    NBDeviceFingerPositionRightThumb = 1,
    /*
      Right index finger position
    */
    NBDeviceFingerPositionRightIndex = 2,
    /*
      Right middle finger position
    */
    NBDeviceFingerPositionRightMiddle = 3,
    /*
      Right ring finger position
    */
    NBDeviceFingerPositionRightRing = 4,
    /*
      Right little finger position
    */
    NBDeviceFingerPositionRightLittle = 5,
    /*
      Left thumb finger position
    */
    NBDeviceFingerPositionLeftThumb = 6,
    /*
      Left index finger position
    */
    NBDeviceFingerPositionLeftIndex = 7,
    /*
      Left middle finger position
    */
    NBDeviceFingerPositionLeftMiddle = 8,
    /*
      Left ring finger position
    */
    NBDeviceFingerPositionLeftRing = 9,
    /*
      Left little finger position
    */
    NBDeviceFingerPositionLeftLittle = 10,
} NBDeviceFingerPosition;

/* Additional information for scan preview */
typedef struct
{
    /* Finger detection value */
    NBInt iFingerDetectValue;
    NBInt iSpoofScore;
} NBDeviceScanPreviewDetails;

/*
  Summary:
   Callback function used in NBDeviceScanEx.
  Parameters:
   hDevice :             [in] handle to device
   peStatus :            [in/out] result, information specifying status of scan procedure
   psScanFormatInfo :    [in] result, extended information about specified scan format
   pBuffer :             [in] latest fingerprint image
   stBufferSize:         [in] pre\-allocated buffer size (size of the memory buffer)
   psDetails:            [in] struct containing only finger detection value
   pParam:               [in] pass\-through parameter to be passed to pPreviewProc on new preview event (optional)

  Remarks:
   Executed to display (preview) snapshots that don't meet the required quality.
   When the fingerprint of required quality is received, the callback is not executed anymore.

   Cancel functionality: when peStatus is set to value NBDeviceScanStatusCanceled, the NBDeviceScanEx function is interrupted.
*/

typedef NBResult(NB_CALLBACK NBDeviceScanPreviewProc)(const HNBDevice hDevice, NBDeviceScanStatus * peStatus, const NBDeviceScanFormatInfo * psScanFormatInfo, const NBByte * pBuffer, NBSizeType stBufferSize, const NBDeviceScanPreviewDetails * psDetails, void * pParam);
typedef NBResult(NB_CALLBACK NBDeviceDoCrc32)(void * pContext, const NBByte * pu8Message, NBSizeType stMessageLen, NBUInt32 * pu32Crc);

#ifdef NB_DEVICES_LITE

typedef NBResult(NB_CALLBACK NBDeviceGetRandomBytes)(void * pContext, NBByte * pu8Data, NBSizeType stDataLen);


/*
  Enumeration of allowed PIN values
*/
typedef enum
{
    /*
      UNKNOWN pin value
    */
    NBDevicePinValueUnknown = 0,
    /*
      LOW pin value
    */
    NBDevicePinValueLow = 1,
    /*
      HIGH pin value
    */
    NBDevicePinValueHigh = 2
} NBDevicePinValue;

typedef NBResult(NB_CALLBACK NBDeviceDestroyContextProc)(void * pContext);
typedef NBResult(NB_CALLBACK NBDeviceDelayMicrosecondsProc)(void * pContext, NBUInt32 ui32Value); // delay (sleep) in microseconds
typedef NBResult(NB_CALLBACK NBDeviceGetTimestampProc)(void * pContext, NBUInt32 * pu32Value); // return timestamp in milliseconds
typedef NBResult(NB_CALLBACK NBDeviceResetSetValueProc)(void * pContext, NBDevicePinValue eValue);
typedef NBResult(NB_CALLBACK NBDeviceAwakeGetValueProc)(void * pContext, NBDevicePinValue * peValue);
typedef NBResult(NB_CALLBACK NBDeviceSendReceiveDataProc)(void * pContext, NBUInt8 * pui8TxBuffer, NBUInt16 ui16TxLength, NBUInt8 * pui8RxBuffer, NBUInt16 ui16RxLength);
/*
  Structure holding communication abstraction primitives (BSP)
  that should be implemented by board                         
*/
typedef struct
{
    /*
      Specified whether HIGH awake pin value should be treated as
      connected device is awake (consult device specification for
      correct value)                                             
    */
    NBBool bIsAwakeHigh;

    /*
      User context that will be passed to all abstraction primitive
      functions (can be NULL)                                      
    */
    void * pContext;
    /*
      Function that should destroy(free) specified context (required if
      pContext is not NULL, otherwise optional)               
    */
    NBDeviceDestroyContextProc pDestroyContext;

    /*
      Function to delay (sleep) in milliseconds (required)
    */
    NBDeviceDelayMicrosecondsProc pDelayMicroseconds;
    /*
      Function to get current timestamp in milliseconds (required)
    */
    NBDeviceGetTimestampProc pGetTimestamp;
    /*
      Function to set reset pin value (required)
    */
    NBDeviceResetSetValueProc pResetSetValue;
    /*
      Function to get current awake pin value (required)
    */
    NBDeviceAwakeGetValueProc pAwakeGetValue;
    /*
      Function to send and receive data (required)
    */
    NBDeviceSendReceiveDataProc pSendReceiveData;
    /*
      Function to do a CRC32 (NB-65210-S only).  Can use NBDeviceDoCrc32 if necessary
     */
    NBDeviceDoCrc32             pDoCrc32;
    /*
     Function to get random bytes for various uses (NB-65210-S with non-plaintext only)
     */
    NBDeviceGetRandomBytes      pGetRandomBytes;
} NBDeviceIO;

#endif
 
/*
  Structure holding in/out parameters for SPI related APIs.                         
*/
typedef struct
{
    /* Name of SPI device */
    NBAChar szSpiName[128];

    /* SYSFS path for GPIO interface */	
    NBAChar szSysfsPath[128];

    /* SPI Clock speed in Hz */
    NBUInt uiSpiClk;

    /* Awake gpio pin number */
    NBInt iAwakePin;

    /* Reset gpio pin number */
    NBInt iResetPin;

    /* ChipSelect gpio pin number */
    NBInt iChipSelectPin;

    /* Handle to Device */
    HNBDevice * phDevice;

    /* bitmask specifying flags, which modify slightly behavior of the function */
    NBUInt uiFlags;

} NBDeviceIOParams;


#define NB_DEVICES_CAPABILITIES_VERSION 1


/*
  Enumeration of existing security models
*/
typedef enum
{
    /*
      Device does not support any security
    */
    NBDeviceSecurityModelNone = 0,
    /*
      Security model of 65100 (AUTH1 and AUTH2)
    */
    NBDeviceSecurityModel65100 = 1,
    /*
      Security model of 65200 (customer asigned key only version)
    */
    NBDeviceSecurityModel65200CakOnly = 2,
    /*
      Security model of 65200 (customer assigned key + customer defined key version)
    */
    NBDeviceSecurityModel65200CakCdk = 3,
} NBDeviceSecurityModel;

#ifdef NB_MSVC
#include <pshpack1.h>
#endif
typedef struct 
{
    /* Structure version */
    NBInt32 iVersion;
    /* Indicates if the antispoofing is supported */
    NBBool8 bSupportsAntispoofing;
    /* Indicates if the custom scan size and offset is supported */
    NBBool8 bSupportsCustomScan;
    /* Indicates if the final image upscaling to 500dpi is supported */
    NBBool8 bSupportsUpscaling;
    /* Indicates if the external compensation data is required */
    NBBool8 bRequiresExternalCalibrationData;
    /* Bitmap of all supported native image types */
    NBInt8 iSupportedNativeImageTypes;
    /* Bitmap of all supported user image types */
    NBInt8 iSupportedUserImageTypes;
    /* Security model enumeration */
    NBInt8 eSecurityModel;
    /* Indicates if the device supports template etraction */
    NBBool8 bSupportsExtractOnDevice;
    /* Bitmap of default image user type */
    NBInt8 iDefaultUserImageType;
    /* Reserved for later use */
    NBBool8 bReserved[63-13];
    /* Internal flags */
    NBUInt8 uiInternalFlags;
}
#ifdef NB_GCC
__attribute__((packed))
#endif
NBDeviceCapabilities;
#ifdef NB_MSVC
#include <poppack.h>
#endif



// ---- types ------------------------------

typedef int16_t NBDevice_CP_STATUS;
typedef void *NBDevice_LL_HANDLE;

typedef enum {
    // enumeration info type used in LL_ENUM_GET_DEV_INFO_HANDLER
    // must be equal to NBU_ENUM_INFO_xxx!
    NBDevice_LL_ENUM_INFO_FRIENDLY_NAME = 0,    // string
    NBDevice_LL_ENUM_INFO_UNIQUE_ID = 1,    // string
    NBDevice_LL_ENUM_INFO_USB_VID = 2,    // 32-bit number
    NBDevice_LL_ENUM_INFO_USB_PID = 3,    // 32-bit number
    NBDevice_LL_ENUM_INFO_COM_PORT_NUMBER = 4,    // 32-bit number

} NBDevice_LL_ENUM_INFO, *PNBDevice_LL_ENUM_INFO;

// ---- handlers ---------------------------

/**
    @brief Initializes the link layer driver.

    @details Called once before any other LL driver call. Can be empty
    if there is nothing to initialize.

    @return NBUERROR_OK or any appropriate error code.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_INITIALIZE_HANDLER)();

/**
    @brief Deinitialzes the link layer driver.

    @details It should revert all InitializeHandler actions and free
    all resources.

    @return NBUERROR_OK or any appropriate error code.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_TERMINATE_HANDLER)();

/**
    @brief Opens the device for communication and makes all necessary initialization.

    @details It should find the device according to given parameters, open it, configure
    and peform all necessary initialization. In EnumHandle is NULL, it can make complete
    enumeration internally and use DevParams and/or DevNumber to select proper device
    to open.

    @param DevParams all parameters necessary to find, open and configure device for
    communication. The format is "param1=value;param2=value;..." and both parameters
    and values are custom and dependent on the communication interface.

    @param EnumHandle optional (can be NULL) enumeration handle from successful
    EnumDevicesInitHandler() call. Used along with DevNumber to open the device selected
    by caller.

    @param DevNumber device number within opened enumeration. Used along with EnumHandle
    to open the device selected by the caller. It can be also used when EnumHandle is NULL
    to select the device within system etc.

    @retval non-NULL handle to be used for all communication with the opened device.
    @retval NULL if any error occured.
*/
typedef NBDevice_LL_HANDLE(*NBDevice_LL_OPEN_HANDLER)(const char *DevParams, NBDevice_LL_HANDLE EnumHandle, uint32_t DevNumber);

/**
    @brief Closes the opened device.

    @param Handle handle returned by OpenHandler() call.
*/
typedef void(*NBDevice_LL_CLOSE_HANDLER)(NBDevice_LL_HANDLE Handle);

/**
    @brief Closes and reopens the device.

    @details It should open the same device for which was Handle originally opened. The
    effect should be the same as CloseHandler() call followed by OpenHandler() call with
    original parameters.

    Used when there is a communication problem to restore connection to the default state.

    @param Handle handle returned by OpenHandler() call.

    @return NBUERROR_OK or any appropriate error code.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_REOPEN_HANDLER)(NBDevice_LL_HANDLE Handle);

/**
    @brief Sets the communication timeout.

    @details Communication timeout is used when waiting for the device in WaitForPacketStartHandler()
    and ReceiveByteHandler().

    @param Handle handle returned by OpenHandler() call.
    @param TimeoutMs timeout in milliseconds.

    @retval NBUERROR_OK or any appropriate error code.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_SET_TIMEOUT_HANDLER)(NBDevice_LL_HANDLE Handle, uint32_t TimeoutMs);

/**
    @brief Waits until device response packet start is detected or connection timeout expires.

    @details It should read data from the device until response packet start is detected.
    Any previous data should be ignored. If packet start can't be detected for given protocol,
    it returns once the first data byte is received.

    Shouldn't wait longer than communication timeout set by SetTimeoutHandler().

    @param Handle handle returned by OpenHandler() call.

    @retval NBUERROR_OK if packet start was detected.
    @retval NBUERROR_COMM_TIMEOUT if timeout expired.
    @retval NBUERROR_COMM_XXX for states where connection should be reopened.
    @retval any other appropriate error code.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_WAIT_FOR_PACKET_START_HANDLER)(NBDevice_LL_HANDLE Handle);

/**
    @brief Reads one received data byte.

    @details Waits until at least one received byte is available or connection timeout
    expires. Returns only real data, all link layer data changes as stuffing need
    to be handled internally.

    @param Handle handle returned by OpenHandler() call.
    @param Value pointer to a variable where received byte should be stored.

    @retval NBUERROR_OK if data byte was successfully read and returned.
    @retval NBUERROR_COMM_TIMEOUT if timeout expired.
    @retval NBUERROR_COMM_XXX for states where connection should be reopened.
    @retval any other appropriate error code.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_RECEIVE_BYTE_HANDLER)(NBDevice_LL_HANDLE Handle, uint8_t *Value);

/**
    @brief Informs LL driver about remaining size of currently receiving packet.

    @details Used as a hint which allows to optimize data read. It is called once
    transport layer knows the current packet size, usually after receiving the
    packet header. LL driver can read the rest of data at once which can have
    significant effect on trasfer speed.

    @note LL driver can allocate necessary buffer during this call but it shouldn't
    try to receive data. There is no way how to return a possible error so it would
    have to be propagated to next ReceiveByteHandler call.

    @note this hint is valid until next WaitForPacketStartHandler() call or an error
    returned from ReceiveByteHandler().

    @param Handle handle returned by OpenHandler() call.
    @param ReceiveDataSize the size of the data to be received.
*/
typedef void(*NBDevice_LL_SET_REMAINING_SIZE_HANDLER)(NBDevice_LL_HANDLE Handle, uint32_t ReceiveDataSize);

/**
    @brief Prepares/begins packet (command) transfer.

    @details it should discard any stale data from previous transfer(s) and initialize
    next transfer from the host to device. It should flush below driver buffers if
    available and possible. Then it should prepare and start new transfer for current
    communication protocol. For example, it can send STX byte at UART etc.

    @param Handle handle returned by OpenHandler() call.
    @param PacketSize size of the whole packet/command including all headers in bytes.
    The same value as LEN field in the command header plus command header size. It can be
    used as a hint for communication buffers allocation for example.

    @retval NBUERROR_OK on success.
    @retval NBUERROR_COMM_XXX for states where connection should be reopened.
    @retval any other appropriate error code.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_START_PACKET_SEND_HANDLER)(NBDevice_LL_HANDLE Handle, uint32_t PacketSize);

/**
    @brief Writes one byte of the sent packet.

    @details Data byte can be sent immediatelly or buffered depending on the used
    communication device and protocol. Stored data can be sent as link layer packets.

    Once LastByte is set, all buffered data should be sent. In this case function should wait
    until all data all really sent to the device.

    @param Handle handle returned by OpenHandler() call.
    @param Value byte to be sent.
    @param LastByte true if Value is the last byte of current packet/command. Otherwise false.

    @retval NBUERROR_OK on success.
    @retval NBUERROR_COMM_XXX for states where connection should be reopened.
    @retval any other appropriate error code.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_SEND_BYTE_HANDLER)(NBDevice_LL_HANDLE Handle, uint8_t Value, bool LastByte);

/**
    @brief Gets communication property. This handler is optional.

    @details Allows to get communication property as current UART speed, SPI frame size etc.
    Properties are communication interface specific.

    @param Handle handle returned by OpenHandler() call.
    @param PropertyType interface dependent property type.
    @param PropertyBuffer pointer to the buffer where property will be copied.
    @param BufferSize pointer to a variable which contains PropertyBufferSize on input
    and copied data size on output.

    @retval NBUERROR_OK if the property was copied to PropertyBuffer.
    @retval NBUERROR_UNEXPECTED_DATA_LENGTH if the BufferSize isn't big enough for the property.
    In this case BufferSize will contain the necessary property size on output.
    @retval NBUERROR_NOT_FOUND unknown PropertyType.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_GET_PROPERTY_HANDLER)(NBDevice_LL_HANDLE Handle, uint16_t PropertyType, void *PropertyBuffer, uint32_t *BufferSize);

/**
    @brief Sets communication property. This handler is optional.

    @details Allows to set communication property as UART speed, SPI frame size etc.
    Properties are communication interface specific. The property is set immediatelly
    so it should be done after device is requested the same and the command returns
    with OK status.

    @param Handle handle returned by OpenHandler() call.
    @param PropertyType interface dependent property type.
    @param PropertyBuffer pointer to property data.
    @param BufferSize property data size.

    @return NBUERROR_OK if the property is OK and was set. Any error means property wasn't set.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_SET_PROPERTY_HANDLER)(NBDevice_LL_HANDLE Handle, uint16_t PropertyType, void *PropertyBuffer, uint32_t BufferSize);

/**
    @brief Resets the device. This handler is optional.

    @details Resets the attached device.

    @param Handle handle returned by OpenHandler() call.

    @return NBUERROR_OK if the device was reset.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_RESET_HANDLER)(NBDevice_LL_HANDLE Handle);

/**
    @brief Initializes devices enumeration. Optional.

    @details Prepares everything necessary for enumeration based on Filter parameter. It is completely
    interface/system dependent. It can do nothing or make a complete enumeration.

    @note If enumeration doesn't make sense or can't be done, this handler can be NULL. In this case
    all other enumeration handlers should be also NULL.

    @param Filter filtering parameter, communication interface specific. "" is used for full list
    of devices. The format is "param1=value;param2=value;..." and both parameters and values are custom
    and dependent on the interface.

    @param EnumHandle pointer to a value to be set to enumeration handle on successful return. The handle
    is used to store enumeration data and is passed to other enumeration handlers.

    @retval NBUERROR_OK on success.
    @retval any other appropriate error code.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_ENUM_DEVICES_INIT_HANDLER)(const char *Filter, NBDevice_LL_HANDLE *EnumHandle);

/**
    @brief Frees all enumeration resources for given handle. Optional.

    @note Mandatory if EnumDevicesInitHandler is implemented.

    @param EnumHandle handle returned by successfull EnumDevicesInitHandler call.
*/
typedef void(*NBDevice_LL_ENUM_DEVICES_DONE_HANDLER)(NBDevice_LL_HANDLE EnumHandle);

/**
    @brief Returns number of the devices for given enumeration. Optional.

    @note Mandatory if EnumDevicesInitHandler is implemented.

    @param EnumHandle handle returned by successfull EnumDevicesInitHandler call.

    @return number of the devices found.
*/
typedef uint32_t(*NBDevice_LL_ENUM_GET_DEV_NUMBER_HANDLER)(NBDevice_LL_HANDLE EnumHandle);

/**
    @brief Provides information about one enumerated device. Optional.

    @details Provides user readable device name or description which allows to
    select the proper device for open.

    @note Mandatory if EnumDevicesInitHandler is implemented.

    @param EnumHandle handle returned by successfull EnumDevicesInitHandler call.
    @param DevNumber device number index within enumeration. Starts with 0.
    @param InfoType requested information type
    @param InfoBuffer pointer to a buffer for the requested info type.
    @param BufferSize pointer to variable which contains InfoType buffer size.on input
        and returned or expected number of bytes on output.

    @retval NBUERROR_OK on success.
    @retval NBUERROR_COMM_NO_DEVICE if the DevNumber is higher than number of enumerated devices.
    @retval NBUERROR_COMM_NOT_SUPPORTED if requested parameter isn't supported for this kind of device
    @retval NBUERROR_NOT_FOUND for unknown parameter
    @retval NBUERROR_UNEXPECTED_DATA_LENGTH if BufferSize is too small for requested info. In this case
        BufferSize contains expected buffer size on output.
    @retval any appropriate error code.
*/
typedef NBDevice_CP_STATUS(*NBDevice_LL_ENUM_GET_DEV_INFO_HANDLER)(NBDevice_LL_HANDLE EnumHandle, uint32_t DevNumber, NBDevice_LL_ENUM_INFO InfoType,
    void *InfoBuffer, uint32_t *BufferSize);

// ---- driver structure -------------------

// To be incremented after any interface change
#define LL_INTERFACE_VERSION            1

typedef struct {
    // link layer host driver
    NBDevice_LL_INITIALIZE_HANDLER               InitializeHandler;              // mandatory
    NBDevice_LL_TERMINATE_HANDLER                TerminateHandler;               // mandatory
    NBDevice_LL_OPEN_HANDLER                     OpenHandler;                    // mandatory
    NBDevice_LL_CLOSE_HANDLER                    CloseHandler;                   // mandatory
    NBDevice_LL_REOPEN_HANDLER                   ReopenHandler;                  // mandatory
    NBDevice_LL_SET_TIMEOUT_HANDLER              SetTimeoutHandler;              // mandatory
    NBDevice_LL_WAIT_FOR_PACKET_START_HANDLER    WaitForPacketStartHandler;      // mandatory
    NBDevice_LL_RECEIVE_BYTE_HANDLER             ReceiveByteHandler;             // mandatory
    NBDevice_LL_SET_REMAINING_SIZE_HANDLER       SetRemainingSizeHandler;        // optinal
    NBDevice_LL_START_PACKET_SEND_HANDLER        StartPacketSendHandler;         // mandatory
    NBDevice_LL_SEND_BYTE_HANDLER                SendByteHandler;                // mandatory
    NBDevice_LL_GET_PROPERTY_HANDLER             GetPropertyHandler;             // optional
    NBDevice_LL_SET_PROPERTY_HANDLER             SetPropertyHandler;             // optional
    NBDevice_LL_RESET_HANDLER                    ResetHandler;                   // optional
    NBDevice_LL_ENUM_DEVICES_INIT_HANDLER        EnumDevicesInitHandler;         // optional
    NBDevice_LL_ENUM_DEVICES_DONE_HANDLER        EnumDevicesDoneHandler;         // optional / mandatory if EnumDevicesInitHandler isn't NULL
    NBDevice_LL_ENUM_GET_DEV_NUMBER_HANDLER      EnumGetDevNumberHandler;        // optional / mandatory if EnumDevicesInitHandler isn't NULL
    NBDevice_LL_ENUM_GET_DEV_INFO_HANDLER        EnumGetDevInfoHandler;          // optional / mandatory if EnumDevicesInitHandler isn't NULL

} NBDevice_LL_DRV_HOST, *PNBDevice_LL_DRV_HOST;


typedef struct {
    uint32_t             InterfaceVersion;           // Must be equal to LL_INTERFACE_VERSION
    NBDevice_LL_DRV_HOST InterfaceFunctions;
} NBDeviceCommInterface;


#ifdef NB_CPP
}
#endif

#endif // !NB_DEVICES_TYPES_H
