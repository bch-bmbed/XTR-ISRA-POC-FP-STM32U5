//!doc
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2011 - id3 Semiconductors
//
// $Revision: 2798 $
// $Date: 2016-05-31 15:17:42 +0200 (mar. 31 mai 2016) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerEnroll_h
#define _id3FingerEnroll_h

#ifndef ID3FINGER_API
#define ID3FINGER_API extern
#endif

#include "id3FingerTemplate.h"
#include "id3FingerTemplateRecord.h"
#include "id3FingerEnrollEnums.h"

// Handle to a FingerExtract object
typedef void* ID3FINGER_ENROLL;

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------------------------------------
// Returns the size of the buffer required to create an enroller.
//
// Returns
//		The size (in octets).
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int sizeOf_ID3FINGER_ENROLL(void);

//---------------------------------------------------------------------------
// Initializes a fingerprint enroller.
//
// Parameters
//		phEnroll:
//			[out] Receives a handle to a fingerprint enroller. This handle 
//			can now be supplied to other functions attempting to do work with this enroller.
//
//		buffer:
//			[in] A handle to the memory reserved for the fingerprint enroller.
//
//		bufferSize:
//			[in] The size of the memory reserved for the fingerprint enroller.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		The size of the reserved memory has to be larger or equal the value given by sizeOf_ID3FINGER_ENROLL() function.
//---------------------------------------------------------------------------
ID3FINGER_API int id3FingerEnroll_Initialize(ID3FINGER_ENROLL* phEnroll, unsigned char* buffer, int bufferSize);

//--------------------------------------------------------------------------------------------------
// Add a template to the current enrollement process.
//
// Parameters
//		hEnroll:
//			[in] A handle to a fingerprint enroller.
//
//		hTemplate:
//			[in] A handle to a reference fingerprint template.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerEnroll_AddView(ID3FINGER_ENROLL hEnroll, ID3FINGER_TEMPLATE hTemplate, unsigned char* quality);

//--------------------------------------------------------------------------------------------------
// Get the quality of the current enrollement process
//
// Parameters
//		hEnroll:
//			[in] A handle to a fingerprint enroller.
//
//		quality:
//			[out] Receive the quality.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerEnroll_GetQuality(ID3FINGER_ENROLL hEnroll, unsigned char* quality);

//--------------------------------------------------------------------------------------------------
// Get the enrolled template record.
//
// Parameters
//		hEnroll:
//			[in] A handle to a fingerprint enroller.
//
//		hTemplate:
//			[in] A handle to a fingerprint template record.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		ID3_E_INSUFFICIENT_BUFFER if the template record is not big enough.
//		An error code if it fails.
//
// Remarks
//		* The fingerprint template record has to be initialized before.
//		* If the enroller mode is set to FingerEnrollMode_Aggregation (default):
//			- the template record has to be big enought to receive all enrolled views
//			- to get the number of enrolled views call the function once and the required number of views will be in templateRecordCapacity
//			- then initilize your template record with the correct size and call the function again
//		* If the enroller mode is set to FingerEnrollMode_Mosaicking:
//			- the template record only has to be big enought to receive one view
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerEnroll_GetTemplateRecord(ID3FINGER_ENROLL hEnroll, ID3FINGER_TRECORD hTemplateRecord, int* templateRecordCapacity);

//--------------------------------------------------------------------------------------------------
// Reset the enroller to begin a new enrollement process.
//
// Parameters
//		hEnroll:
//			[in] A handle to a fingerprint enroller.
//
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerEnroll_Reset(ID3FINGER_ENROLL hEnroll);

//--------------------------------------------------------------------------------------------------
// Returns the CBEFF ID of the implemented enroller algorithm.
//	
// Returns
//		The CBEFF ID.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API unsigned int id3FingerEnroll_CBEFFID();

//--------------------------------------------------------------------------------------------------
// Set the enroller mode.
//
// Parameters
//		hEnroll:
//			[in] A handle to a fingerprint enroller.
//		mode:
//			[in] The desired id3FingerEnrollMode
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerEnroll_SetEnrollMode(ID3FINGER_ENROLL hEnroll, id3FingerEnrollMode mode);

#ifdef __cplusplus
}
#endif


#endif