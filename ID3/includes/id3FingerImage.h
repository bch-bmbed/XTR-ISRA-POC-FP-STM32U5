#ifndef _id3fingerimage_h
#define _id3fingerimage_h

#ifndef ID3FINGER_API
#define ID3FINGER_API extern
#endif

#ifdef __cplusplus
extern "C" {
#endif


//--------------------------------------------------------------------------------------------------
//   Downscale an image.
//
// Parameters
// 		[in/out] image              The image
// 		[in] input_width        The input width
// 		[in] input_height       The input height
//		[in] input_resolution   The input resolution
//		[in] output_resolution  The output resolution
// 		[out] output_width       The output width
// 		[out] output_height      The output height
//
// Returns
//      ID3_SUCCESS if the function succeeds. An error code if it fails.
// 
// Remarks
//      The downscale is done in place.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerImage_Downscale(unsigned char* image, int input_width, int input_height, int input_resolution, int output_resolution, int* output_width, int* output_height);

#ifdef __cplusplus
}
#endif

#endif
