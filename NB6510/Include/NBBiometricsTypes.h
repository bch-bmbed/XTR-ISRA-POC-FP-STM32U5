#ifndef NB_BIOMETRICS_TYPES_H
#define NB_BIOMETRICS_TYPES_H

#include <NBTypes.h>
#include <NBErrors.h>
#include <NBDevices.h>

#ifdef NB_CPP
extern "C"
{
#endif

#ifdef NB_EMBEDDED
    #define NB_BIOMETRICS_LITE
#endif

/*
   Declaration of a NBBiometricsContext device handle
*/
typedef NBHandle HNBBiometricsContext;

/*
  Enumeration of possible finger positions
*/
typedef enum
{
    /*
      Unknown finger position
    */
    NBBiometricsFingerPositionUnknown = 0,
    /*
      Right thumb finger position
    */
    NBBiometricsFingerPositionRightThumb = 1,
    /*
      Right index finger position
    */
    NBBiometricsFingerPositionRightIndex = 2,
    /*
      Right middle finger position
    */
    NBBiometricsFingerPositionRightMiddle = 3,
    /*
      Right ring finger position
    */
    NBBiometricsFingerPositionRightRing = 4,
    /*
      Right little finger position
    */
    NBBiometricsFingerPositionRightLittle = 5,
    /*
      Left thumb finger position
    */
    NBBiometricsFingerPositionLeftThumb = 6,
    /*
      Left index finger position
    */
    NBBiometricsFingerPositionLeftIndex = 7,
    /*
      Left middle finger position
    */
    NBBiometricsFingerPositionLeftMiddle = 8,
    /*
      Left ring finger position
    */
    NBBiometricsFingerPositionLeftRing = 9,
    /*
      Left little finger position
    */
    NBBiometricsFingerPositionLeftLittle = 10,
} NBBiometricsFingerPosition;

/*
  Enumeration of possible template types
*/
typedef enum
{
    /*
      Unknown template type
    */
    NBBiometricsTemplateTypeUnknown = 0,
    /*
      Proprietary algorithm vendor template format
    */
    NBBiometricsTemplateTypeProprietary = 1,
    /*
      ISO/IEC 19794-2 template format
    */
    NBBiometricsTemplateTypeIso = 2,
    /*
      ANSI/INCITS 378 template format
    */
    NBBiometricsTemplateTypeAnsi = 3,
    /*
      ISO/IEC 19794-2 Compact Card template format
    */
    NBBiometricsTemplateTypeIsoCompactCard = 4
} NBBiometricsTemplateType;

/*
  Structure holding information about specific template type
*/
typedef struct
{
    /*
      Template type that structure provides information for
                                                           
    */
    NBBiometricsTemplateType eTemplateType;
    /*
      Specifies whether extraction is supported for specified
      template type                                          
    */
    NBBool bIsExtractionSupported;
    /*
      Specifies whether verification is supported for specified
      template type                                            
    */
    NBBool bIsVerificationSupported;
    /*
      Specifies whether identification is supported for specified
      template type                                              
    */
    NBBool bIsIdentificationSupported;
    /*
      Specifies whether conversion to specified template type is
      supported                                                 
    */
    NBBool bIsConversionToSupported;
    /*
      Specifies whether conversion from specified template type is
      supported                                                   
    */
    NBBool bIsConversionFromSupported;
    /*
      Max template size for specified template type that the
      structure is for                                      
    */
    NBSizeType stMaxTemplateSize;
} NBBiometricsTemplateTypeInfo;

/*
  Enumeration of biometric operation result statuses
*/
typedef enum
{
    /*
      Status is not set (None)
    */
    NBBiometricsStatusNone = 0,
    /*
      Operations is successful
    */
    NBBiometricsStatusOk = 1,
    /*
      Timeout occurred
    */
    NBBiometricsStatusTimeout = 2,
    /*
      Operation is canceled
    */
    NBBiometricsStatusCanceled = 3,
    /*
      Operation did not complete, because of bad fingerprint
      quality                                               
    */
    NBBiometricsStatusBadQuality = 4,
    /*
      Operation did not complete, because of too few minutiae
    */
    NBBiometricsStatusTooFewMinutiae = 5,
    /*
      No match found (not verified, not identified)
    */
    NBBiometricsStatusMatchNotFound = 6,
    /*
      Latent detected
    */
    NBBiometricsStatusLatentDetected = 7,
    /*
      Need more samples (for enrollment or stitching)
     */
    NBBiometricsStatusNeedMoreSamples = 8,
    /*
      Spoof Detected
     */
    NBBiometricsStatusSpoofDetected = 9
} NBBiometricsStatus;

/*
  Structure holding information about fingerprint recognition
  algorithm and it's vendor used by the SDK                  
*/
typedef struct
{
    /*
      Algorithm id
    */
    NBUInt uiId;
    /*
      Algorithm version
    */
    NBVersion sVersion;
} NBBiometricsAlgorithmInfo;

typedef NBResult(NB_CALLBACK NBBiometricsScanPreviewProc)(const HNBBiometricsContext hContext, NBBiometricsStatus eBiometricsStatus, const HNBDevice hDevice, NBDeviceScanStatus * peStatus, const NBDeviceScanFormatInfo * psScanFormatInfo, const NBByte * pBuffer, NBSizeType stBufferSize, const NBDeviceScanPreviewDetails * psDetails, void * pParam);

/*
  Structure containing scan parameters to be used during
  fingerprint acquisition                               
*/
typedef struct
{
    /*
      Desired device scan format
    */
    NBDeviceScanFormat eScanFormat;
    /*
      Timeout in milliseconds (NB_DEVICE_SCAN_TIMEOUT_INFINITE can
      be used to specify infinite timeout)                        
    */
    NBInt iTimeout;
    /*
      Callback to be called when new preview image is captured
      (optional)                                              
    */
    NBBiometricsScanPreviewProc pPreviewProc;
    /*
      Pass-through parameter to be passed to pPreviewProc on new
      preview event (optional)                                  
    */
    void * pParam;
} NBBiometricsScanParams;

typedef NBResult (NB_CALLBACK NBBiometricsTemplateIteratorInitProc)(NBVoid * pContext);
typedef NBResult (NB_CALLBACK NBBiometricsTemplateIteratorTerminateProc)(NBVoid * pContext);
typedef NBResult (NB_CALLBACK NBBiometricsTemplateIteratorNextTemplateProc)(NBVoid * pContext, const NBVoid * * ppTemplateId, const NBVoid * * ppTemplate, NBSizeType * pstTemplateSize);
typedef NBResult (NB_CALLBACK NBBiometricsTemplateIteratorHasNextTemplateProc)(NBVoid * pContext, NBBool * pbValue);
typedef NBResult (NB_CALLBACK NBBiometricsTemplateIteratorGetTemplatesProc)(NBVoid * pContext, const NBVoid * const * * parpTemplateIds, const NBVoid * const * * parpTemplates, const NBSizeType ** parstTemplateSizes, NBUInt * puiTemplateCount);

/*
  Structure holding function pointers and implementing simple
  iterator used to go through gallery templates              
*/
typedef struct
{
    /*
      Context to be passed as pass-through to all iterator
      functions                                           
    */
    void * pContext;
    /*
      Iterator initialization (required)
    */
    NBBiometricsTemplateIteratorInitProc pInitProc;
    /*
      Iterator termination (required)
    */
    NBBiometricsTemplateIteratorTerminateProc pTerminateProc;
    /*
      \Returns next template (either pNextTemplate or pGetTemplates
      is required)                                                 
    */
    NBBiometricsTemplateIteratorNextTemplateProc pNextTemplateProc;
    /*
      \Returns whether iterator contains any more items (required
      when pNextProc is used)                                    
    */
    NBBiometricsTemplateIteratorHasNextTemplateProc pHasNextTemplateProc;
    /*
      \Returns array of templates (either pNextTemplate or
      pGetTemplates is required)                          
    */
    NBBiometricsTemplateIteratorGetTemplatesProc pGetTemplatesProc;
} NBBiometricsTemplateIterator;

/*
  Enumeration of supported security levels (used in
  verification/identification)                     
*/
typedef enum
{
    /*
      Lowest security level (~ 1 % false acceptance rate)
    */
    NBBiometricsSecurityLevelLowest = 0,
    /*
      Lower security level (~ 0.1-1 % false acceptance rate)
    */
    NBBiometricsSecurityLevelLower = 1,
    /*
      Low security level (~ 0.1 % false acceptance rate)
    */
    NBBiometricsSecurityLevelLow = 2,
    /*
      Below normal security level (~ 0.01-0.1 % false acceptance
      rate)                                                     
    */
    NBBiometricsSecurityLevelBelowNormal = 3,
    /*
      Normal security level (~ 0.01 % false acceptance rate)
    */
    NBBiometricsSecurityLevelNormal = 4,
    /*
      Above normal security level (~ 0.001-0.01 % false acceptance
      rate)                                                       
    */
    NBBiometricsSecurityLevelAboveNormal = 5,
    /*
      High security level (~ 0.001 % false acceptance rate)
    */
    NBBiometricsSecurityLevelHigh = 6,
    /*
      Higher security level (~ 0.0001-0.001 % false acceptance rate)
    */
    NBBiometricsSecurityLevelHigher = 7,
    /*
      Highest security level (~ 0.0001 % false acceptance rate)
    */
    NBBiometricsSecurityLevelHighest = 8
} NBBiometricsSecurityLevel;

/*
  Structure holding verification result information
*/
typedef struct
{
    /*
      Score of verified template
    */
    NBInt iScore;
} NBBiometricsVerifyResultDetails;

/*
  Structure holding identification result
*/
typedef struct
{
    /*
      Id of identified template
    */
    const NBVoid * pTemplateId;
    /*
      Index of identified template in specified template array (-1
      if pGetItemsProc is not set in NBBiometricsTemplateIterator)
    */
    NBInt iIndex;
    /*
      Score of identified template
    */
    NBInt iScore;
} NBBiometricsIdentifyResultDetails;

#ifdef NB_CPP
}
#endif

#endif // !NB_BIOMETRICS_TYPES_H
