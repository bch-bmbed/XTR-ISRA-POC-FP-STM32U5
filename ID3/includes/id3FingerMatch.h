//!doc
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2011 - id3 Semiconductors
//
// $Revision: 2849 $
// $Date: 2016-07-06 14:12:17 +0200 (mer. 06 juil. 2016) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerMatch_h
#define _id3FingerMatch_h

#ifndef ID3FINGER_API
	#define ID3FINGER_API extern
#endif

#include "id3FingerTemplate.h"
#include "id3FingerTemplateRecord.h"
#include "id3FingerMatchStructs.h"
#include "id3FingerMatchEnums.h"		

#ifdef __cplusplus
extern "C" {
#endif

// Handle to a FingerMatch object
typedef void* ID3FINGER_MATCH;

//--------------------------------------------------------------------------------------------------
// Returns the size of the buffer required to create a fingerprint matcher.
//	
// Returns
//		The size (in octets).
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int sizeOf_ID3FINGER_MATCH();

//---------------------------------------------------------------------------
// Initializes a fingerprint matcher.
//
// Parameters
//		phMatcher:
//			[out] Receives a handle to the fingerprint matcher.
//
//		buffer:
//			[in] A handle to the memory reserved for the fingerprint matcher.
//
//		bufferSize:
//			[in] The size of the memory reserved for the fingerprint matcher.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		The size of the memory has to be higher or equal the value given by sizeOf_ID3FINGER_MATCH() function.
//---------------------------------------------------------------------------
ID3FINGER_API int id3FingerMatch_Initialize(ID3FINGER_MATCH* phMatcher,unsigned char* buffer,int bufferSize);

//--------------------------------------------------------------------------------------------------
// Gets the verification's acceptance threshold.
//
// Parameters
//		hMatcher:
//			[in] A handle to a fingerprint matcher.
//
//		param:
//			[out] Receives the threshold. See id3FingerMatchThreshold for details.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerMatch_GetThreshold(ID3FINGER_MATCH hMatcher,int* param);

//--------------------------------------------------------------------------------------------------
// Sets the verification's acceptance threshold.
//
// Parameters
//		hMatcher:
//			[in] A handle to a fingerprint matcher.
//
//		param:
//			[in] The desired threshold. See id3FingerMatchThreshold for a list of possible values.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerMatch_SetThreshold(ID3FINGER_MATCH hMatcher,int param);

//--------------------------------------------------------------------------------------------------
// Compares two fingerprint templates.
//
// Parameters
//		hMatcher:
//			[in] A handle to a fingerprint matcher.
//
//		reference:
//			[in] A handle to a reference fingerprint template.
//
//		probe:
//			[in] A handle to a probe fingerprint template.
//
//		hMatchDetails:
//			[out] Receives the comparison result. See id3FingerMatchResult for details.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerMatch_CompareTemplates(ID3FINGER_MATCH hMatcher, ID3FINGER_TEMPLATE reference, ID3FINGER_TEMPLATE probe, id3FingerMatchResult* hMatchResult);

//--------------------------------------------------------------------------------------------------
// Compares a fingerprint template to a fingerprint template record.
//
// Parameters
//		hMatcher:
//			[in] A handle to a fingerprint matcher.
//
//		reference:
//			[in] A handle to a reference fingerprint template record.
//
//		probe:
//			[in] A handle to a probe fingerprint template.
//
//		hMatchDetails:
//			[out] Receives the comparison result. See id3FingerMatchResult for details.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerMatch_Compare(ID3FINGER_MATCH hMatcher, ID3FINGER_TRECORD reference, ID3FINGER_TEMPLATE probe, id3FingerMatchResult* hMatchResult);

//--------------------------------------------------------------------------------------------------
// Compares two fingerprint template records.
//
// Parameters
//		hMatcher:
//			[in] A handle to a fingerprint matcher.
//
//		reference:
//			[in] A handle to a reference fingerprint template record.
//
//		probe:
//			[in] A handle to the probe fingerprint template record.
//
//		hMatchResult:
//			[out] Receives the comparison result. See id3FingerMatchResult for details.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerMatch_CompareRecords(ID3FINGER_MATCH hMatcher, ID3FINGER_TRECORD reference, ID3FINGER_TRECORD probe, id3FingerMatchResult* hMatchResult);

//--------------------------------------------------------------------------------------------------
// Gets detailed information about the last comparison.
//
// Parameters
//		hMatcher:
//			[in] A handle to a fingerprint matcher.
//
//		position:
//			[in] The fingerprint position. See id3FingerPosition for details.
//
//		hMatchResult:
//			[out] Receives the comparison information.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerMatch_GetComparisonDetails(ID3FINGER_MATCH hMatcher, unsigned char position, id3FingerMatchResult* hMatchResult);

//--------------------------------------------------------------------------------------------------
// Returns the CBEFF ID of the implemented minutiae matching algorithm.
//	
// Returns
//		The CBEFF ID.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API unsigned int id3FingerMatch_CBEFFID();

#ifdef __cplusplus
}
#endif


#endif
