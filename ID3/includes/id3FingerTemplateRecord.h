//!doc
//--------------------------------------------------------------------------------------------------
// This file contains declaration of record management functions
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2011 - id3 Semiconductors
//
// $Revision: 2487 $
// $Date: 2016-02-03 16:22:10 +0100 (mer. 03 févr. 2016) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerTemplateRecord_h
#define _id3FingerTemplateRecord_h

#ifndef ID3FINGER_API
	#define ID3FINGER_API extern
#endif

#include "id3FingerTemplate.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* ID3FINGER_TRECORD;				// Handle to a fingerprint Template Record object

//--------------------------------------------------------------------------------------------------
// Returns the size of the buffer required to create a fingerprint template record.
//
// Parameters
//		maxTemplateCount:
//			[in] The expected maximum number of templates to be stored in the record.
//
// Returns
//		The size (in octets).
//
// Remarks
//		maxTemplateCount can't be higher than ID3FINGER_TRECORD_TEMPLATECOUNT.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int sizeOf_ID3FINGER_TRECORD(int maxTemplateCount);

//--------------------------------------------------------------------------------------------------
// Initializes a fingerprint template record.
//
// Parameters
//		phFTR:
//			[out] A handle to the fingerprint template record.
//
//		buffer:
//			[in] A handle to the memory allocated for the record.
//
//		bufferSize:
//			[in] The size of the memory allocated for the record.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		The number of templates in the record is limited by the allocated memory size.
//		The buffer size has to be higher or equal the value given by sizeOf_ID3FINGER_TRECORD() function.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplateRecord_Initialize(ID3FINGER_TRECORD* hFTR,unsigned char* buffer,int bufferSize);

//--------------------------------------------------------------------------------------------------
// Copies a fingerprint template record.
//
// Parameters
//		hSrcFTR:
//			[in] A handle to the input fingerprint template record.
//
//		hDstFTR:
//			[in] A handle to the output fingerprint template record.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks:
//		The output fingerprint template record has to be initialized before.
//		The record's templates are also copied.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplateRecord_Copy(ID3FINGER_TRECORD hFTR, ID3FINGER_TRECORD hClonedFTR);

//--------------------------------------------------------------------------------------------------
// Creates a fingerprint template record from a data buffer in a specified format.
//
// Parameters
//		hFTR:
//			[in] A handle to a fingerprint template record.
//
//		data:
//			[in] A data buffer that contains the fingerprint template record.
//
//		dataSize:
//			[in] The size of the data buffer.
//
//		format:
//			[in] Specifies the format. See id3FingerTemplateFormat for details.
//
//		workingBuffer:
//			[in] An (optional) handle to a buffer allowing conversion from some standardized formats (NULL if no working buffer is used).
//
//		workingBufferSize:
//			[in] The size of the working buffer (0 if no working buffer is used).
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		* The fingerprint template record has to be initialized before.
//		* WorkingBuffer must be non-null and of sufficient length (see ID3FINGER_STANDARDFORMATLOADING_BUFFERSIZE constant) for all ISO/ANSI formats except FingerTemplateFormat_Iso19794CompactCard.
//		* If the format is FingerTemplateFormat_Unknown, the function tries loading the record in all the formats defined in id3FingerTemplateFormat except Compact Card ISO (which has no header).
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplateRecord_FromBuffer(ID3FINGER_TRECORD hFTR, const unsigned char* data, int dataSize, unsigned char format,const unsigned char* workingBuffer,int workingBufferSize);

//--------------------------------------------------------------------------------------------------
// Outputs a fingerprint template record to a buffer in a specified format.
//
// Parameters
//		hFTR:
//			[in] A handle to a finger template record.
//
//		format:
//			[in] Specifies the format. See id3FingerTemplateFormat for details.
//
//		data:
//			[in] A handle to the output data buffer.
//
//		dataSize:
//			[in,out] The size of the output data buffer.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		If the data buffer size is insufficient, the function returns ID3_E_INSUFFICIENT_BUFFER and the
//		parameter dataSize receives the size of the required buffer.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplateRecord_ToBuffer(ID3FINGER_TRECORD hFTR, unsigned char format, unsigned char* data, int* dataSize);

//--------------------------------------------------------------------------------------------------
// Gets the number of templates in a fingerprint record.
//
// Parameters
//		hFTR:
//			[in] A handle to a fingerprint template record.
//
//		count:
//			[out] Receives the number of templates in the record.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplateRecord_GetTemplateCount(ID3FINGER_TRECORD hFTR, unsigned char* count);

//--------------------------------------------------------------------------------------------------
// Gets a template handle of a fingerprint record.
//
// Parameters
//		hFTR:
//			[in] A handle to a fingerprint template record.
//
//		index:
//			[in] The index of the fingerprint template to be retrieved.
//
//		phTemplate:
//			[out] Receives the template handle.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		The retrieved fingerprint template is not a copy.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplateRecord_GetTemplate(ID3FINGER_TRECORD hFTR, unsigned char index, ID3FINGER_TEMPLATE* phTemplate);

//--------------------------------------------------------------------------------------------------
// Adds a copy of an input fingerprint template to a record.
//
// Parameters
//		hFTR:
//			[in] A handle to a finger template record.
//
//		hTemplate:
//			[in] A handle to the template to be added.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplateRecord_AddTemplate(ID3FINGER_TRECORD hFTR, ID3FINGER_TEMPLATE hTemplate);

//--------------------------------------------------------------------------------------------------
// Removes a specified fingerprint template from the record.
//
// Parameters
//		hFTR:
//			[in] A handle to a finger template record.
//
//		hTemplate:
//			[in] A handle to the template to be removed.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplateRecord_RemoveTemplate(ID3FINGER_TRECORD hFTR, ID3FINGER_TEMPLATE hTemplate);

//--------------------------------------------------------------------------------------------------
// Removes a fingerprint template from a record at a specified index.
//
// Parameters
//		hFMR:
//			[in] A handle to a finger template record.
//
//		index:
//			[in] Index of the fingerprint template to be removed.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplateRecord_RemoveTemplateAt(ID3FINGER_TRECORD hFTR, unsigned char index);

#ifdef __cplusplus
}
#endif

#endif
