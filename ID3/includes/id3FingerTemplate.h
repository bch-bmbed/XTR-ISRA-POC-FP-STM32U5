//!doc
//--------------------------------------------------------------------------------------------------
// This file contains declaration of template management functions
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2011 - id3 Semiconductors
//
// $Revision: 2702 $
// $Date: 2016-05-09 08:33:47 +0200 (lun. 09 mai 2016) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerTemplate_h
#define _id3FingerTemplate_h

#ifndef ID3FINGER_API
	#define ID3FINGER_API extern
#endif

#include "id3FingerEnums.h"
#include "id3FingerMinutia.h"
#include "id3FingerErrors.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ID3FINGER_STANDARDFORMATLOADING_BUFFERSIZE 2048

// Handle to a fingerprint Template object
typedef void* ID3FINGER_TEMPLATE;

//--------------------------------------------------------------------------------------------------
// Returns the size of the buffer required to create a fingerprint template.
//		
// Returns
//		The size (in octets).
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int sizeOf_ID3FINGER_TEMPLATE(void);

//--------------------------------------------------------------------------------------------------
// Initializes a fingerprint template with empty data.
//
// Parameters
//		phTemplate:
//			[out] A handle to the fingerprint template to be initialized.
//
//		buffer:
//			[in] A handle to the memory allocated for the template.
//
//		bufferSize:
//			[in] The size of the memory allocated for the template.
//		
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		The memory size has to be larger or equal the value given by sizeOf_ID3FINGER_TEMPLATE() function.
//		The buffer is reset. If you need to create a template inplace from a previously created buffer, see id3FingerTemplate_InitializeFromBuffer function.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_Initialize(ID3FINGER_TEMPLATE* phTemplate, unsigned char* buffer, int bufferSize);

//--------------------------------------------------------------------------------------------------
// Initializes a fingerprint template inplace from pre-existing data.
//
// Parameters
//		phTemplate:
//			[out] A handle to the fingerprint template to be initialized.
//
//		buffer:
//			[in] A handle to the memory containing the template.
//
//		bufferSize:
//			[in] The size of the memory containing the template.
//		
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		* The memory size has to be larger or equal the value given by sizeOf_ID3FINGER_TEMPLATE() function.
//		* The data in the buffer must comply the FingerTemplateFormat_IEFM784 format.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_InitializeFromBuffer(ID3FINGER_TEMPLATE* phTemplate, unsigned char* buffer, int bufferSize);

//--------------------------------------------------------------------------------------------------
// Copies a fingerprint template.
//
// Parameters
//		hSrcTemplate:
//			[in] A handle to the input fingerprint template.
//
//		hDstTemplate:
//			[in] A handle to the output fingerprint template.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		The output fingerprint template has to be initialized before.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_Copy(ID3FINGER_TEMPLATE hSrcTemplate, ID3FINGER_TEMPLATE hDstTemplate);

//--------------------------------------------------------------------------------------------------
// Load a fingerprint template from a data buffer in the specified format.
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template object.
//
//		data:
//			[in] The handle to the data buffer containing the standardized-data.
//
//		dataSize:
//			[in] The size of the data buffer.
//
//		format:
//			[in] The standardized-data format. See id3FingerTemplateFormat for details.
//
//		workingBuffer:
//			[in] An (optional) handle to a buffer allowing conversion from some standardized formats (NULL if no working buffer is used).
//
//		workingBufferSize:
//			[in] The size of the working buffer (0 if no working buffer is used).
//		
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		* The template has to be initialized before.
//		* WorkingBuffer must be non-null and of sufficient length (see ID3FINGER_STANDARDFORMATLOADING_BUFFERSIZE constant) for all ISO/ANSI formats except FingerTemplateFormat_Iso19794CompactCard.
//		* If the format is FingerTemplateFormat_Unknown, the function tries loading the record in all the formats defined in id3FingerTemplateFormat except Compact Card ISO (which has no header).
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_FromBuffer(ID3FINGER_TEMPLATE hTemplate, const unsigned char* data, int dataSize, unsigned char format, const unsigned char* workingBuffer,int workingBufferSize);

//--------------------------------------------------------------------------------------------------
// Outputs a fingerprint template to a data buffer in the specified format.
//
// Parameters
//		hTemplate:
//			[in] A handle to the fingerprint template.
//
//		format:
//			[in] Specifies the format. See id3FingerTemplateFormat for details.
//
//		data:
//			[in] A data buffer handle.
//
//		dataSize:
//			[in,out] The size of the input buffer/output data.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		If the data buffer size is insufficient, the function returns ID3_E_INSUFFICIENT_BUFFER and the
//		dataSize parameter receives the size of the required buffer.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_ToBuffer(ID3FINGER_TEMPLATE hTemplate, unsigned char format, unsigned char* data, int* dataSize);

//--------------------------------------------------------------------------------------------------
// Gets the finger position.
//
// Parameters
//		hTemplate:
//			[in] A handle to the fingerprint template.
//
//		position:
//			[out] Receives the finger position. See id3FingerPosition for details.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_GetFingerPosition(ID3FINGER_TEMPLATE hTemplate, id3FingerPosition* position);

//--------------------------------------------------------------------------------------------------
// Gets the finger image quality.
//
// Parameters
//		hTemplate:
//			[in] A handle to the fingerprint template.
//
//		quality:
//			[out] Receives the finger image quality. See id3FingerImageQuality for details.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_GetImageQuality(ID3FINGER_TEMPLATE hTemplate, unsigned char* quality);

//--------------------------------------------------------------------------------------------------
// Gets the resolution, in pixels per inch (DPI/PPI), of the image from which the fingerprint template was extracted.
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		hRes:
//			[out] Receives the resolution of the image, in pixels per inch.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_GetImageResolution(ID3FINGER_TEMPLATE hTemplate, unsigned short* res);

//--------------------------------------------------------------------------------------------------
// Gets the height, in pixels, of the image from which the fingerprint template was extracted.
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		height:
//			[out] Receives the height of the image in pixels.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// See Also
//		id3FingerTemplate_GetImageWidth
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_GetImageHeight(ID3FINGER_TEMPLATE hTemplate, unsigned short* height);

//--------------------------------------------------------------------------------------------------
// Gets the width, in pixels, of the image from which the fingerprint template was extracted.
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		width:
//			[out] Receives the width of the image in pixels.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// See Also
//		id3FingerTemplate_GetImageHeight
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_GetImageWidth(ID3FINGER_TEMPLATE hTemplate, unsigned short* width);

//--------------------------------------------------------------------------------------------------
// Gets the number of minutiae.
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		mcount:
//			[out] Receives the number of minutiae.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_GetMinutiaCount(ID3FINGER_TEMPLATE hTemplate, unsigned char* mcount);

//--------------------------------------------------------------------------------------------------
// Gets the minutiae.
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		minutiae:
//			[out] Receives the minutiae.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		The output buffer must be large enough to receives all minutiae. 
//		See id3FingerTemplate_GetMinutiaCount function.
//
// See Also
//		id3FingerTemplate_GetMinutiaCount
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_GetMinutiae(ID3FINGER_TEMPLATE hTemplate, id3FingerMinutia* minutiae);

//--------------------------------------------------------------------------------------------------
// Sets the finger position.
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		position:
//			[in] The finger position. See id3FingerPosition for details.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_SetFingerPosition(ID3FINGER_TEMPLATE hTemplate, id3FingerPosition position);

//--------------------------------------------------------------------------------------------------
// Sets the fingerprint image-quality.
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		quality:
//			[in] Finger image quality. See id3FingerImageQuality for details.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_SetImageQuality(ID3FINGER_TEMPLATE hTemplate, unsigned char quality);

//--------------------------------------------------------------------------------------------------
// Sets the image resolution, in pixels per inch (PPI), of the image from which a fingerprint template was extracted.
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		res:
//			[in] Resolution in pixels per inch (PPI).
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		This function do NOT change the templates minutiae coordinates, which are scaled at 500 DPI, but will affect the minutiae exported on standard formats.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_SetImageResolution(ID3FINGER_TEMPLATE hTemplate, unsigned short res);

//--------------------------------------------------------------------------------------------------
// Sets the height, in pixels, of the image from which the fingerprint template was extracted.
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		height:
//			[in] Height of the image in pixels.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// See Also
//		id3FingerTemplate_SetImageWidth
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_SetImageHeight(ID3FINGER_TEMPLATE hTemplate, unsigned short height);

//--------------------------------------------------------------------------------------------------
// Sets the width, in pixels, of the image from which the fingerprint template was extracted.
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		width:
//			[in] Width of the image in pixels.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// See Also
//		id3FingerTemplate_SetImageHeight
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_SetImageWidth(ID3FINGER_TEMPLATE hTemplate, unsigned short width);

//--------------------------------------------------------------------------------------------------
// Sets the minutiae (remove existing ones).
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		minutiae:
//			[in] A handle to the minutiae array.
//
//		mcount:
//			[in] The number of minutiae in the array.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Warning
//		Due to template internal coding:
//		* minutiae which coordinate value X or Y is higher than 511 will be rejected.
//		* only the first 80 minutiae will be considered.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_SetMinutiae(ID3FINGER_TEMPLATE hTemplate, id3FingerMinutia* minutiae, unsigned char mcount);

//--------------------------------------------------------------------------------------------------
// Change the scale of the minutiae coordinates by a ratio s = ratioNumerator / ratioDenominator.
//
// Parameters
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		ratioNumerator:
//			[in] The numerator of the scaling ratio.
//
//		ratioDenominator:
//			[in] The denominator of the scaling ratio.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		* Both the template extractor and loading functions of this SDK automatically handle templates resolution by scaling them to 500 DPI (expected by the template matcher). 
//		* Other minutia resolutions may have a deep negative impact on recognition accuracy. Consider this function very carrefully.
//		* The ratioNumerator value shall be chosen respecting the constraint X * natioNumerator <= MAX_INT32_VALUE, where
//			- MAX_INT32_VALUE = 2147483647 (max value of a signed int coded on 32 bits)
//			- X is the maximum absolute value of minutiae coordinates in the template.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerTemplate_Scale(ID3FINGER_TEMPLATE hTemplate, unsigned short ratioNumerator,unsigned short ratioDenominator);

#ifdef __cplusplus
}
#endif

#endif
