#ifndef NB_BIOMETRICS_TEMPLATE_H
#define NB_BIOMETRICS_TEMPLATE_H

#include <NBBiometricsTypes.h>

#ifdef NB_CPP
extern "C"
{
#endif

/*
  Summary:
   Get finger position specified in template.
  Parameters:
   pTemplate :       [in] pointer to template buffer
   stTemplateSize :  [in] template buffer size
   pePosition :      [out] result, finger position
  Remarks:
   Function is valid only for templates loaded using
   NBBiometricsContextLoadTemplateFromMemory,
   NBBiometricsContextExtractFromScan or
   NBBiometricsContextConvertTemplate.
   
   NB_ERROR_FORMAT will be returned if specified template is
   invalid or not loaded.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsTemplateGetPosition(const NBVoid * pTemplate, NBSizeType stTemplateSize, NBBiometricsFingerPosition * pePosition);
/*
  Summary:
   Get template type specified in template.
  Parameters:
   pTemplate :       [in] pointer to template buffer
   stTemplateSize :  [in] template buffer size
   peType :          [out] result, template type
  Remarks:
   Function is valid only for templates loaded using
   NBBiometricsContextLoadTemplateFromMemory,
   NBBiometricsContextExtractFromScan or
   NBBiometricsContextConvertTemplate.
   
   NB_ERROR_FORMAT will be returned if specified template is
   invalid or not loaded.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsTemplateGetType(const NBVoid * pTemplate, NBSizeType stTemplateSize, NBBiometricsTemplateType * peType);
/*
  Summary:
   Get actual template size.
  Parameters:
   pTemplate :       [in] pointer to template buffer
   stTemplateSize :  [in] template buffer size
   pstSize :         [out] result, actual template size
  Remarks:
   Function is valid only for templates loaded using
   NBBiometricsContextLoadTemplateFromMemory,
   NBBiometricsContextExtractFromScan or
   NBBiometricsContextConvertTemplate.
   
   NB_ERROR_FORMAT will be returned if specified template is
   invalid or not loaded.
   
   If template buffer size (stTemplateSize) is bigger than
   returned actual template size (pstSize) - it can be reduced
   to the returned actual template size.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsTemplateGetSize(const NBVoid * pTemplate, NBSizeType stTemplateSize, NBSizeType * pstSize);
/*
  Summary:
   Get template quality.
  Parameters:
   pTemplate :       [in] pointer to template buffer
   stTemplateSize :  [in] template buffer size
   piValue :         [out] result, template quality
  Remarks:
   Function is valid only for templates loaded using
   NBBiometricsContextLoadTemplateFromMemory,
   NBBiometricsContextExtractFromScan or
   NBBiometricsContextConvertTemplate.
   
   NB_ERROR_FORMAT will be returned if specified template is
   invalid or not loaded.
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsTemplateGetQuality(const NBVoid * pTemplate, NBSizeType stTemplateSize, NBInt * piValue);

#ifdef NB_CPP
}
#endif

#endif // !NB_BIOMETRICS_TEMPLATE_H
