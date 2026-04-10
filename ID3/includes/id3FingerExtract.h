//!doc
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2011 - id3 Semiconductors
// $Revision: 3154 $
// $Date: 2017-04-26 11:51:33 +0200 (mer. 26 avr. 2017) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerExtract_h
#define _id3FingerExtract_h

#ifndef ID3FINGER_API
	#define ID3FINGER_API extern
#endif

#include "id3FingerTemplate.h"
#include "id3FingerExtractEnums.h"

// Handle to a FingerExtract object
typedef void* ID3FINGER_EXTRACT;

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------------------------------------
// Returns the size of the buffer required to create a template extractor.
//
// Parameters
//		imageWidth:
//			[in] The width (in pixels) of the images from which templates will be created.
//
//		imageHeight:
//			[in] The height (in pixels) of the images from which templates will be created.
//	
// Returns
//		The size (in octets).
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int sizeOf_ID3FINGER_EXTRACT(int imageWidth,int imageHeight);

//---------------------------------------------------------------------------
// Initializes a fingerprint template extractor.
//
// Parameters
//		phExtract:
//			[out] Receives a handle to a fingerprint template extractor. This handle 
//			can now be supplied to other functions attempting to do work with this extractor.
//
//		imageWidth:
//			[in] The width of the images from which minutiae will be extracted.
//
//		imageHeight:
//			[in] The height of the images from which minutiae will be extracted.
//
//		buffer:
//			[in] A handle to the memory reserved for the template extractor.
//
//		bufferSize:
//			[in] The size of the memory reserved for the template extractor.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		The size of the reserved memory has to be larger or equal the value given by sizeOf_ID3FINGER_EXTRACT() function.
//---------------------------------------------------------------------------
ID3FINGER_API int id3FingerExtract_Initialize(ID3FINGER_EXTRACT* phExtract, int imageWidth, int imageHeight, unsigned char* buffer, int bufferSize);

//---------------------------------------------------------------------------
// Extracts a fingerprint template from a fingerprint image.
//
// Parameters
//		hExtract:
//			[in] A handle to a fingerprint extractor.
//
//		rawImage:
//			[in] The raw image data.
//
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		mode:
//			[in] The expected mode.
//
//		imageResolution:
//			[in] The input image resolution, in DPI.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		* The fingerprint template has to be initialized before.
//		* The size of the image has to be the same as those specified during extractor initialization.
//		* The image buffer is overwritten: it should be saved if needed further.
//		* Scaling is applied to templates whatever the chosen mode. Set imageDPI=500 disable scaling.
//		* Minutiae number is limited to 80 (with respect to template format). Use id3FingerExtract_CreateAndPruneTemplate function to create smallest templates.
//
// See Also
//		id3FingerExtractMode
//---------------------------------------------------------------------------
ID3FINGER_API int id3FingerExtract_CreateTemplate(ID3FINGER_EXTRACT hExtract, unsigned char* rawImage, ID3FINGER_TEMPLATE hTemplate, id3FingerExtractMode mode,unsigned short imageResolution);

//---------------------------------------------------------------------------
// Extracts a fingerprint template from a fingerprint image and prune the resulting minutiae.
//
// Parameters
//		hExtract:
//			[in] A handle to a fingerprint extractor.
//
//		rawImage:
//			[in] The raw image data.
//
//		hTemplate:
//			[in] A handle to a fingerprint template.
//
//		mode:
//			[in] The expected mode.
//
//		imageResolution: 
//			[in] The input image resolution, in DPI.
//
//		mcountMax
//			[in] The maximum number of minutiae per template (limited to 80). Use "0" if you don't need a particular pruning.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		* The fingerprint template has to be initialized before.
//		* The size of the image has to be the same as those specified during extractor initialization.
//		* The image buffer is overwritten: it should be saved if needed further.
//		* Scaling is applied to templates whatever the chosen mode. Set imageDPI=500 disable scaling.
//		* Minutiae pruning is applied considering minutiae qualities, and has impact on recognition accuracy. Highest value is 80 (truncated beyond). Value higher than 50 are strongly advised. Ask id3 for precise guidance.
//
// See Also
//		id3FingerExtractMode
//---------------------------------------------------------------------------
ID3FINGER_API int id3FingerExtract_CreateAndPruneTemplate(ID3FINGER_EXTRACT hExtract, unsigned char* rawImage, ID3FINGER_TEMPLATE hTemplate, id3FingerExtractMode mode,unsigned short imageResolution,unsigned char mcountMax);

//--------------------------------------------------------------------------------------------------
// Returns the CBEFF ID of the implemented minutiae extractor algorithm.
//	
// Returns
//		The CBEFF ID.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API unsigned int id3FingerExtract_CBEFFID();

#ifdef __cplusplus
}
#endif


#endif
