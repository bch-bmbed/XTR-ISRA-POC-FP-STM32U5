#ifndef NB_BIOMETRICS_CONTEXT_H
#define NB_BIOMETRICS_CONTEXT_H

#include <NBBiometricsTypes.h>
#include <NBBiometricsTemplate.h>

#ifdef NB_CPP
extern "C"
{
#endif

/* Skip the finger not remove status when doing scan (in scenarios when sensor is awaken from sleep after finger is put on sensor area (in SPI)) */
#define NB_BIOMETRICS_SCAN_SKIP_FINGER_NOT_REMOVED_STATUS_FLAG      0x08
/* Use snapshot scan function (capture single image from sensor) to get image for extractor */
#define NB_BIOMETRICS_SCAN_USE_SNAPSHOT_FLAG                        0x10
/* Use this flag to allow for minutia inversion in FM220 generated ISO verification/identification */
#define NB_BIOMETRICS_VERIFY_CANDIDATE_FM220_FLAG                   0x20
/* Use this flag to skip template stitching for custom scan*/
#define NB_BIOMETRICS_SKIP_TEMPLATE_STITCHING_FLAG                  0x40

/*
  Summary:
   Create biometric context and obtain context handle.
  Parameters:
   hDevice :    [in] handle to device
   uiFlags :    [in] bitmask specifying flags, which modify
                slightly behavior of the function
   phContext :  [out] handle to biometric context
  Remarks:
   Biometric context handle is allocated on heap and returned
   after successful execution of the function.
   
   Each obtained biometric context needs to be destroyed using
   NBBiometricsContextDestroy function.
   
   Handle to device is required. During context creation license
   stored in device will be verified and, in case license is not
   valid, NB_ERROR_FAILED will be returned.
   
   Device is required to be connected during whole lifetime of
   NBBiometricsContext (until NBBiometricsContextDestroy is
   called), in case device is disconnected, dependent
   NBBiometricsContext should be destroyed.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextCreate(const HNBDevice hDevice, NBUInt uiFlags, HNBBiometricsContext * phContext);
/*
  Summary:
   Create biometric context using specified license and obtain
   context handle.
  Parameters:
   hDevice :        [in] handle to device
   pLicense :       [in] biometric context license
   stLicenseSize :  [in] biometric context license size
   uiFlags :        [in] bitmask specifying flags, which modify
                    slightly behavior of the function
   phContext :      [out] handle to biometric context
  Remarks:
   Biometric context handle is allocated on heap and returned
   after successful execution of the function.
   
   Each obtained biometric context needs to be destroyed using
   NBBiometricsContextDestroy function.
   
   Handle to device is required. Device is required to be
   connected during whole lifetime of NBBiometricsContext (until
   NBBiometricsContextDestroy is called), in case device is
   disconnected, dependent NBBiometricsContext should be
   destroyed.
   
   During context creation specified license will be verified
   and, in case license is not valid, NB_ERROR_FAILED will be
   returned.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextCreateWithLicense(const HNBDevice hDevice, const NBVoid * pLicense, NBSizeType stLicenseSize, NBUInt uiFlags, HNBBiometricsContext * phContext);
#ifdef NB_BIOMETRICS_LITE
    /*
      Summary:
       Create biometric context in specified memory buffer and
       obtain context handle.
      Parameters:
       hDevice :       [in] handle to device
       pBuffer :       [in/out] memory buffer, where biometric
                       context handle will be allocated in
       stBufferSize :  [in] memory buffer size
       uiFlags :       [in] bitmask specifying flags, which modify
                       slightly behavior of the function
       pstSize :       [out] minimal memory size required for buffer
       phContext :     [out] handle to biometric context
      Remarks:
       Biometric context handle is allocated in specified memory
       buffer and returned after successful execution of the
       function.
       
       pBuffer must exist until device handle is not destroyed
       (using NBBiometricsContextDestroy function).
       
       Each obtained biometric context needs to be destroyed using
       NBBiometricsContextDestroy function.
       
       Handle to device is required. During context creation license
       stored in device will be verified and, in case license is not
       valid, NB_ERROR_FAILED will be returned.
       
       Device is required to be connected during whole lifetime of
       NBBiometricsContext (until NBBiometricsContextDestroy is
       called), in case device is disconnected, dependent
       NBBiometricsContext should be destroyed.
      Returns:
       If the function succeeds, the return value is NB_OK. If the
       function fails, one of the error codes is returned (<link Error codes>).
    */
    NBResult NB_API NBBiometricsContextCreateInMemory(const HNBDevice hDevice, NBByte * pBuffer, NBSizeType stBufferSize, NBUInt uiFlags, NBSizeType * pstSize, HNBBiometricsContext * phContext);
    /*
      Summary:
       Create biometric context in specified memory buffer using
       specified license and obtain context handle.
      Parameters:
       hDevice :        [in] handle to device
       pLicense :       [in] biometric context license
       stLicenseSize :  [in] biometric context license size
       pBuffer :        [in/out] memory buffer, where biometric
                        context handle will be allocated in
       stBufferSize :   [in] memory buffer size
       uiFlags :        [in] bitmask specifying flags, which modify
                        slightly behavior of the function
       pstSize :        [out] minimal memory size required for buffer
       phContext :      [out] handle to biometric context
      Remarks:
       Biometric context handle is allocated in specified memory
       buffer and returned after successful execution of the
       function.
       
       pBuffer must exist until device handle is not destroyed
       (using NBBiometricsContextDestroy function).
       
       Each obtained biometric context needs to be destroyed using
       NBBiometricsContextDestroy function.
       
       Handle to device is required. Device is required to be
       connected during whole lifetime of NBBiometricsContext (until
       NBBiometricsContextDestroy is called), in case device is
       disconnected, dependent NBBiometricsContext should be
       destroyed.
       
       During context creation specified license will be verified
       and, in case license is not valid, NB_ERROR_FAILED will be
       returned.
      Returns:
       If the function succeeds, the return value is NB_OK. If the
       function fails, one of the error codes is returned (<link Error codes>).
    */
    NBResult NB_API NBBiometricsContextCreateWithLicenseInMemory(const HNBDevice hDevice, const NBVoid * pLicense, NBSizeType stLicenseSize, NBByte * pBuffer, NBSizeType stBufferSize, NBUInt uiFlags, NBSizeType * pstSize, HNBBiometricsContext * phContext);
#endif
/*
  Summary:
   Destroys biometrics context obtained using
   NBBiometricsContextCreate,
   NBBiometricsContextCreateWithLicense,
   NBBiometricsContextCreateInMemory or
   NBBiometricsContextCreateWithLicenseInMemory functions and
   frees all resources obtained by biometrics handle.
  Parameters:
   hContext :  [in] handle to biometric context
  Remarks:
   After handle is destroyed, it is caller's responsibility to
   set the biometrics context handle to NULL. Calling
   NBBiometricsContext functions with destroyed handle can give
   unpredictable results.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextDestroy(HNBBiometricsContext hContext);

/*
  Summary:
   Set value for specified parameter.
  Parameters:
   hContext :     [in] handle to biometric context
   uiParameter :  [in] id of parameter
   iValue :       [in] value for specified parameter
  Remarks:
   Parameter value is applied only for specified biometric
   context (biometric context handle).
   
   Currently no public parameters are supported.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextSetParameter(const HNBBiometricsContext hContext, NBUInt uiParameter, NBInt iValue);
/*
  Summary:
   Get value of specified parameter.
  Parameters:
   hContext :     [in] handle to biometric context
   uiParameter :  [in] id of parameter
   piValue :      [out] result, value for specified parameter
  Remarks:
   Currently no public parameters are supported.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextGetParameter(const HNBBiometricsContext hContext, NBUInt uiParameter, NBInt * piValue);

/*
  Summary:
   Get info of fingerprint recognition algorithm that is being
   used.
  Parameters:
   hContext :         [in] handle to biometric context
   psAlgorithmInfo :  [out] result, filled structure with
                      algorithm info
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextGetAlgorithmInfo(const HNBBiometricsContext hContext, NBBiometricsAlgorithmInfo * psAlgorithmInfo);
/*
  Summary:
   Get max template size for specified template type.
  Parameters:
   hContext :       [in] handle to biometric context
   eTemplateType :  [in] template type
   pstSize :        [out] result, max template size
  Remarks:
   NB_ERROR_NOT_SUPPORTED will be returned if specified template
   type is not supported for specified biometric context.
   
   Returned max template size should be used to allocate memory
   needed to call NBBiometricsContextLoadTemplateFromMemory and
   NBBiometricsContextSaveTemplateToMemory.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextGetMaxTemplateSize(const HNBBiometricsContext hContext, NBBiometricsTemplateType eTemplateType, NBSizeType * pstSize);
/*
  Summary:
   Convert specified security level to security level value.
  Parameters:
   hContext :        [in] handle to biometric context
   eSecurityLevel :  [in] desired security level
   piValue :         [out] result, security level value
  Remarks:
   Returned security level value should be used when calling
   verification and identification functions.
   
   Security level value sets the threshold for matching
   fingerprint templates. The higher eSecurityLevel is, the more
   secure system becomes, however it also reduces the
   convenience for authorized users as they sometimes will need
   to go through several identification/verification operations
   to authenticate. eSecurityLevel needs to be carefully
   selected to suit both security and system users needs.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextGetSecurityLevel(const HNBBiometricsContext hContext, NBBiometricsSecurityLevel eSecurityLevel, NBInt * piValue);
/*
  Summary:
   Check whether specified template type is
   supported.
  Parameters:
   hContext :       [in] handle to biometric context
   eTemplateType :  [in] template type to check
   pbValue :        [out] result, whether template type is
                    supported
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextIsTemplateTypeSupported(const HNBBiometricsContext hContext, NBBiometricsTemplateType eTemplateType, NBBool * pbValue);

/*
  Summary:
   Get list of supported template types by specified biometric context.
  Parameters:
   hContext :               [in] handle to biometric context
   areTemplateTypes :       [in/out] pre\-allocated array of
                                NBBiometricsTemplateType
   uiTemplateTypesLength :  [in] pre\-allocated array length
   puiCount :               [out] actual count of supported device
                                scan formats
  Remarks:
   Function requires caller to allocate areTemplateTypes.
   NBBiometricsContextGetSupportedTemplateTypes only fills 
   information into pre-allocated array.
   NBBiometricsContextGetSupportedTemplateTypes accepts areTemplateTypes = NULL
   and uiTemplateTypesLength = 0 in order for caller to find out
   how many template types are supported and then pre-allocate array
   before passing for second time to
   NBBiometricsContextGetSupportedTemplateTypes.
   
   NB_ERROR_INSUFFICIENT_BUFFER error will be returned if the
   specified buffer is not sufficient to store function result.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextGetSupportedTemplateTypes(const HNBBiometricsContext hContext, NBBiometricsTemplateType * areTemplateTypes, NBUInt uiTemplateTypesLength, NBUInt * puiCount);

/*
  Summary:
   Retrieve extended information about template type.
  Parameters:
   hContext :       [in] handle to biometric context
   eTemplateType :  [in] template type to retrieve information
                    for
   pbValue :        [out] result, extended template type
                    information
  Remarks:
   If specified template type is not supported,
   NB_ERROR_NOT_SUPPORTED is returned (to check whether device
   format is supported,
   NBBiometricsContextIsTemplateTypeSupported function can be
   used).
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextGetTemplateTypeInfo(const HNBBiometricsContext hContext, NBBiometricsTemplateType eTemplateType, NBBiometricsTemplateTypeInfo * psTemplateTypeInfo);

/*
  Summary:
   Load template (using desired template type) from
   specified memory buffer.
  Parameters:
   hContext :        [in] handle to biometric context
   eTemplateType :   [in] type of template to load
   pBuffer :         [in] memory buffer from where to load
                     template from
   stBufferSize :    [in] size of memory buffer
   uiFlags :         [in] bitmask specifying flags, which modify
                     slightly behavior of the function
   pTemplate :       [in/out] pre\-allocated template buffer
                     where to store loaded template
   stTemplateSize :  [in] size of pre\-allocated template buffer
   pstSize :         [out] result, actual size of pre\-allocated
                     template buffer used
  Remarks:
   NB_ERROR_NOT_SUPPORTED will be returned if specified template
   type is not supported for specified biometric context.
   
   pTemplate is required and stTemplateSize must be no less then
   max template size returned by
   NBBiometricsContextGetMaxTemplateSize function.
   
   pTemplate can be resized to returned actual size after the
   template loading was completed.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextLoadTemplateFromMemory(const HNBBiometricsContext hContext, 
    NBBiometricsTemplateType eTemplateType, const NBByte * pBuffer, NBSizeType stBufferSize, NBUInt uiFlags,
    NBVoid * pTemplate, NBSizeType stTemplateSize, NBSizeType * pstSize);
/*
  Summary:
   Save template to specified memory buffer.
  Parameters:
   hContext :        [in] handle to biometric context
   pTemplate :       [in] template to save
   stTemplateSize :  [in] size of template to save
   uiFlags :         [in] bitmask specifying flags, which modify
                     slightly behavior of the function
   pBuffer :         [in/out] pre\-allocated buffer where to save
                     template
   stBufferSize :    [in] pre\-allocated buffer size
   pstSize :         [out] result, actual buffer size used
  Remarks:
   pBuffer is required and stBufferSize must be no less then max
   template size returned by
   NBBiometricsContextGetMaxTemplateSize function.
   
   pBuffer can be resized to returned actual size after template
   saving was completed.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextSaveTemplateToMemory(const HNBBiometricsContext hContext, 
    const NBVoid * pTemplate, NBSizeType stTemplateSize, NBUInt uiFlags,
    NBByte * pBuffer, NBSizeType stBufferSize, NBSizeType * pstSize);
/*
  Summary:
   Convert template to specified destination template type.
  Parameters:
   hContext :                   [in] handle to biometric context
   pSourceTemplate :            [in] template to convert
   stSourceTemplateSize :       [in] size of template to convert
   eDestinationTemplateType :   [in] destination template type
   uiFlags :                    [in] bitmask specifying flags,
                                which modify slightly behavior of
                                the function
   pDestinationTemplate :       [in/out] pre\-allocated template
   stDestinationTemplateSize :  [in] pre\-allocated template size
   pstSize :                    [out] result, actual template
                                size used
  Remarks:
   pDestinationTemplate is required and
   stDestinationTemplateSize must be no less then max template
   size returned by NBBiometricsContextGetMaxTemplateSize
   function.
   
   pDestinationTemplate can be resized to returned actual size
   after template conversion was completed.
   
   pDestinationTemplate template type should be different from
   pSourceTemplate template type.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextConvertTemplate(const HNBBiometricsContext hContext, const NBVoid * pSourceTemplate, NBSizeType stSourceTemplateSize,
    NBBiometricsTemplateType eDestinationTemplateType, NBUInt uiFlags, NBVoid * pDestinationTemplate, NBSizeType stDestinationTemplateSize, NBSizeType * pstSize);

/*
  Summary:
   Create enroll template from one or more live finger image.
  Parameters:
   hContext :         [in] handle to biometric context
   eTemplateType :    [in] template type to extract
   eFingerPosition :  [in] finger position to be used during
                      extraction
   psParams :         [in] scan parameters (scan format, timeout,
                      preview event ...)
   uiFlags :          [in] bitmask specifying flags, which modify
                      slightly behavior of the function
   pTemplate :        [in/out] pre\-allocated buffer where to
                      save template
   stTemplateSize :   [in] pre\-allocated buffer size
   peStatus :         [out] result, operation status
   pstSize :          [out] result, actual pre\-allocated buffer
                      size used
  Remarks:
   By default, enroll function expects user to provide 3
   fingerprint images for the same finger that user wants to
   enroll. First fingerprint image is taken as template and all
   subsequent images are compared to the first one (to ensure
   that wrong finger is not provided). If user fails to provide
   second fingerprint (that would match with first fingerprint
   image) for 5 times, function fails with peStatus set to
   NBBiometricsStatusBadQuality. Same logic applies for third
   fingerprint image.
   
   NB_ERROR_NOT_SUPPORTED will be returned if specified template
   type is not supported for specified biometric context.
   
   pTemplate is required and stTemplateSize must be no less then
   max template size returned by
   NBBiometricsContextGetMaxTemplateSize function.
   
   Function does one or more extended fingerprint scan
   internally and waits for a valid finger to be placed on the
   sensor to start extraction.
   NB_BIOMETRICS_SCAN_USE_SNAPSHOT_FLAG can be used to change
   this behaviour.
   
   On successful extraction, peStatus will be equal to
   NBBiometricsStatusOk.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextCreateEnrollTemplateFromScan(const HNBBiometricsContext hContext, NBBiometricsTemplateType eTemplateType, NBBiometricsFingerPosition eFingerPosition, const NBBiometricsScanParams * psParams, NBUInt uiFlags,
    NBVoid * pTemplate, NBSizeType stTemplateSize, NBBiometricsStatus * peStatus, NBSizeType * pstSize);

/*
  Summary:
   Extract finger template from live finger image.
  Parameters:
   hContext :         [in] handle to biometric context
   eTemplateType :    [in] template type to extract
   eFingerPosition :  [in] finger position to be used during
                      extraction
   psParams :         [in] scan parameters (scan format, timeout,
                      preview event ...)
   uiFlags :          [in] bitmask specifying flags, which modify
                      slightly behavior of the function
   pTemplate :        [in/out] pre\-allocated buffer where to
                      save template
   stTemplateSize :   [in] pre\-allocated buffer size
   peStatus :         [out] result, operation status
   pstSize :          [out] result, actual pre\-allocated buffer
                      size used
  Remarks:
   NB_ERROR_NOT_SUPPORTED will be returned if specified template
   type is not supported for specified biometric context.
   
   pTemplate is required and stTemplateSize must be no less then
   max template size returned by
   NBBiometricsContextGetMaxTemplateSize function.
   
   Function does extended fingerprint scan internally and waits
   for a valid finger to be placed on the sensor to start
   extraction. NB_BIOMETRICS_SCAN_USE_SNAPSHOT_FLAG can be used
   to change this behaviour.
   
   On successful extraction, peStatus will be equal to
   NBBiometricsStatusOk.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextExtractFromScan(const HNBBiometricsContext hContext,
    NBBiometricsTemplateType eTemplateType, NBBiometricsFingerPosition eFingerPosition, const NBBiometricsScanParams * psParams, NBUInt uiFlags,
    NBVoid * pTemplate, NBSizeType stTemplateSize, NBBiometricsStatus * peStatus, NBSizeType * pstSize);

/*
  Summary:
   Extract finger template from live finger image.
  Parameters:
   hContext :         [in] handle to biometric context
   eTemplateType :    [in] template type to extract
   eFingerPosition :  [in] finger position to be used during
					  extraction
   psParams :         [in] scan parameters (scan format, timeout,
					  preview event ...)
   uiFlags :          [in] bitmask specifying flags, which modify
					  slightly behavior of the function
   pFmrTemplate :     [in/out] pre\-allocated buffer where to
					  save FMR template
   stFmrTemplateSize :[in] pre\-allocated buffer size for FMR Template
   uiCount :          [in] Compression value will be changed based on finger count
   peStatus :         [out] result, operation status
   pstSize :          [out] result, actual pre\-allocated buffer
   pFirTemplate :     [out] pre\-allocated buffer where to
					  save FIR template
   pstFirSize :[out] will get the buffer size for FIR Template
  Remarks:
   NB_ERROR_NOT_SUPPORTED will be returned if specified template
   type is not supported for specified biometric context.

   pFmrTemplate is required and stFmrTemplateSize must be no less then
   max template size returned by
   NBBiometricsContextGetMaxTemplateSize function.

   pFirTemplate is required and pstFirSize is the size
   of the pFirTemplate.

   Function does extended fingerprint scan internally and waits
   for a valid finger to be placed on the sensor to start
   extraction. NB_BIOMETRICS_SCAN_USE_SNAPSHOT_FLAG can be used
   to change this behaviour.

   On successful extraction, peStatus will be equal to
   NBBiometricsStatusOk.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextExtractFromScanWithBuffer(const HNBBiometricsContext hContext,
	NBBiometricsTemplateType eTemplateType, NBBiometricsFingerPosition eFingerPosition, const NBBiometricsScanParams * psParams, NBUInt uiFlags,
	NBVoid * pFmrTemplate, NBSizeType stFmrTemplateSize, NBUInt uiCount, NBBiometricsStatus * peStatus, NBSizeType * pstSize, NBVoid * pFirTemplate, NBSizeType * pstFirSize);

/*
  Summary:
   Verify live finger image with extracted/loaded finger
   template.
  Parameters:
   hContext :             [in] handle to biometric context
   eTemplateType :        [in] template type to be used during
                          extraction
   eFingerPosition :      [in] finger position to be used during
                          extraction
   psParams :             [in] scan parameters (scan format,
                          timeout, preview event ...)
   pTemplate :            [in] template to verify against
   stTemplateSize :       [in] size of template
   iSecurityLevelValue :  [in] security level value to be used as
                          threshold
   uiFlags :              [in] bitmask specifying flags, which
                          modify slightly behavior of the
                          function
   peStatus :             [out] result, operation status
   psResult :             [out] result, verify result
  Remarks:
   pTemplate should be either extracted
   (NBBiometricsContextExtractFromScan) or loaded
   (NBBiometricsContextLoadTemplateFromMemory).
   
   iSecurityLevelValue should be used to set verification
   threshold according to system security level requirements.
   
   Function does extended fingerprint scan internally and waits
   for a valid finger to be placed on the sensor to start
   extraction.
   
   On successful verification, peStatus will be equal to
   NBBiometricsStatusOk, if template is not verified
   NBBiometricsStatusMatchNotFound will be returned.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextVerifyFromScan(const HNBBiometricsContext hContext,
    NBBiometricsTemplateType eTemplateType, NBBiometricsFingerPosition eFingerPosition, const NBBiometricsScanParams * psParams, const NBVoid * pTemplate, NBSizeType stTemplateSize, NBInt iSecurityLevelValue, NBUInt uiFlags,
    NBBiometricsStatus * peStatus, NBBiometricsVerifyResultDetails * psResult);
/*
  Summary:
   Verify two extracted/loaded finger templates.
  Parameters:
   hContext :             [in] handle to biometric context
   pTemplate :            [in] first template
   stTemplateSize :       [in] first template size
   pOtherTemplate :       [in] second template
   stOtherTemplateSize :  [in] second template size
   iSecurityLevelValue :  [in] security level value to be used as
                          threshold
   uiFlags :              [in] bitmask specifying flags, which
                          modify slightly behavior of the
                          function
   peStatus :             [out] result, operation status
   psResult :             [out] result, verify result
  Remarks:
   pTemplate and pOtherTemplate should be either extracted
   (NBBiometricsContextExtractFromScan) or loaded
   (NBBiometricsContextLoadTemplateFromMemory).
   
   iSecurityLevelValue should be used to set verification
   threshold according to system security level requirements.
   
   On successful verification, peStatus will be equal to
   NBBiometricsStatusOk, if template is not verified
   NBBiometricsStatusMatchNotFound will be returned.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextVerifyFromTemplate(const HNBBiometricsContext hContext, 
    const NBVoid * pTemplate, NBSizeType stTemplateSize, const NBVoid * pOtherTemplate, NBSizeType stOtherTemplateSize, NBInt iSecurityLevelValue, NBUInt uiFlags,
    NBBiometricsStatus * peStatus, NBBiometricsVerifyResultDetails * psResult);

/*
  Summary:
   Identify live finger image in specified list of
   extracted/loaded finger templates.
  Parameters:
   hContext :             [in] handle to biometric context
   eTemplateType :        [in] template type to be used during extraction
   eFingerPosition :      [in] finger position to be used during
                          extraction
   psParams :             [in] scan parameters (scan format,
                          timeout, preview event ...)
   psIterator :           [in] template list iterator
   iSecurityLevelValue :  [in] security level value to be used as
                          threshold
   uiFlags :              [in] bitmask specifying flags, which
                          modify slightly behavior of the
                          function
   peStatus :             [out] result, operation status
   psResult :             [out] result, identify result
  Remarks:
   iSecurityLevelValue should be used to set identification
   threshold according to system security level requirements.
   
   psIterator needs to be implemented (either pGetTemplates or
   (pHasNextTemplate and pNextTemplate) functions must be set
   for iterator to work).
   
   Function does extended fingerprint scan internally and waits
   for a valid finger to be placed on the sensor to start
   extraction.
   
   On successful identification, peStatus will be equal to
   NBBiometricsStatusOk and psResult contains details about
   which template from set that was used in iteration was
   identified, if template is not identified
   NBBiometricsStatusMatchNotFound will be returned.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextIdentifyFromScan(const HNBBiometricsContext hContext,
    NBBiometricsTemplateType eTemplateType, NBBiometricsFingerPosition eFingerPosition, const NBBiometricsScanParams * psParams, const NBBiometricsTemplateIterator * psIterator, NBInt iSecurityLevelValue, NBUInt uiFlags,
    NBBiometricsStatus * peStatus, NBBiometricsIdentifyResultDetails * psResult);
/*
  Summary:
   Identify extracted/loaded template in specified set of
   extracted/loaded finger templates.
  Parameters:
   hContext :             [in] handle to biometric context
   pTemplate :            [in] template to identify
   stTemplateSize :       [in] template to identify size
   psIterator :           [in] template list iterator
   iSecurityLevelValue :  [in] security level value to be used as
                          threshold
   uiFlags :              [in] bitmask specifying flags, which
                          modify slightly behavior of the
                          function
   peStatus :             [out] result, operation status
   psResult :             [out] result, identify result
  Remarks:
   pTemplate should be either extracted
   (NBBiometricsContextExtractFromScan) or loaded
   (NBBiometricsContextLoadTemplateFromMemory).
   
   iSecurityLevelValue should be used to set identification
   threshold according to system security level requirements.
   
   psIterator needs to be implemented (either pGetTemplates or
   (pHasNextTemplate and pNextTemplate) functions must be set
   for iterator to work).
   
   On successful identification, peStatus will be equal to
   NBBiometricsStatusOk and psResult contains details about
   which template from set that was used in iteration was
   identified, if template is not identified
   NBBiometricsStatusMatchNotFound will be returned.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextIdentifyFromTemplate(const HNBBiometricsContext hContext,
    const NBVoid * pTemplate, NBSizeType stTemplateSize, const NBBiometricsTemplateIterator * psIterator, NBInt iSecurityLevelValue, NBUInt uiFlags,
    NBBiometricsStatus * peStatus, NBBiometricsIdentifyResultDetails * psResult);

/*
  Summary:
   Get whether biometric operation (extraction, verification,
   identification) is running.
  Parameters:
   hContext :  [in] handle to biometric context
   pbValue :   [out] result, whether biometric operation is in
               progress
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextIsOperationRunning(const HNBBiometricsContext hContext, NBBool * pbValue);
/*
  Summary:
   Cancel on-going biometric (extraction, verification,
   identification) operation.
  Parameters:
   hContext :  [in] handle to biometric context
  Remarks:
   If no biometric operation is in progress, function will
   succeed and won't return any error.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsContextCancelOperation(const HNBBiometricsContext hContext);

#ifdef NB_CPP
}
#endif

#endif // !NB_BIOMETRICS_CONTEXT_H
