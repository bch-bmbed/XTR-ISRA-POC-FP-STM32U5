//!doc
//--------------------------------------------------------------------------------------------------
// Copyright (c) - id3 Technologies
//
// $Revision: 2487 $
// $Date: 2016-02-03 16:22:10 +0100 (mer. 03 févr. 2016) $
//--------------------------------------------------------------------------------------------------
#ifndef _id3LicenseTokenARM9_h
#define _id3LicenseTokenARM9_h

#include "id3Errors.h"
#include "id3Types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ID3_E_GETRANDOM_FAILED      -20
#define ID3_E_ATHENTICATION_FAILED  -21

/// <summary>
/// Genarate random bytes in random array
/// random array must be initialized with at least 24 bytes allocated
/// </summary>
/// <returns>
///	- ID3_SUCCESS if the function succeeds.
/// - ID3_E_GETRANDOM_FAILED if the function failed
/// - See <xref target="Error Codes"/> for the list of possible error codes.
/// </returns>
ID3API int ID3CALL id3License_GetRandom(unsigned char * random);


/// <summary>
/// Verify the cryptogram authenticity
/// </summary>
/// <returns>
///	- ID3_SUCCESS if the function succeeds.
/// - ID3_E_ATHENTICATION_FAILED if the authentication failed
/// - ID3_E_INVALID_HANDLE if the id3License_GetRandom has not be called before
/// - See <xref target="Error Codes"/> for the list of possible error codes.
/// </returns>
ID3API int ID3CALL id3License_Authenticate(unsigned char * cryptogram);


#ifdef __cplusplus
}
#endif

#endif
