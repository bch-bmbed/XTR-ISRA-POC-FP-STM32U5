#ifndef NB_BIOMETRICS_LIBRARY_H
#define NB_BIOMETRICS_LIBRARY_H

#include <NBTypes.h>
#include <NBErrors.h>
#include <NBBiometricsTypes.h>
#include <NBBiometricsTemplate.h>
#include <NBBiometricsContext.h>

#ifdef NB_CPP
extern "C"
{
#endif

/*
  Summary:
   Function to version of current loaded library.
  Parameters:
   psVersion :  [out] result, library version
  Returns:
   If the function succeeds, the return value is NB_OK. If the
   function fails, one of the error codes is returned (<link Error codes>).
*/
NBResult NB_API NBBiometricsLibraryGetVersion(NBVersion * psVersion);

#ifdef NB_CPP
}
#endif

#endif // !NB_BIOMETRICS_LIBRARY_H
