//!doc
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2015 - id3 Semiconductors
//
// $Revision: 2702 $
// $Date: 2016-05-09 08:33:47 +0200 (lun. 09 mai 2016) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerIdentify_h
#define _id3FingerIdentify_h

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

// Handle to a FingerIdentify object
typedef void* ID3FINGER_IDENTIFY;

//--------------------------------------------------------------------------------------------------
// Returns the size of the buffer required to create a fingerprint identificator.
//
// Parameters
//		userCount:
//			[in] The maximum number of user to be referenced by search functions.
//	
// Returns
//		The size (in octets).
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int sizeOf_ID3FINGER_IDENTIFY(unsigned int userCount);

//---------------------------------------------------------------------------
// Initializes a fingerprint identificator.
//
// Parameters
//		phIdentificator:
//			[out] Receives a handle to the fingerprint identificator.
//
//		buffer:
//			[in] A handle to the memory reserved for the fingerprint identificator.
//
//		bufferSize:
//			[in] The size of the memory reserved for the fingerprint identificator.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//
// Remarks
//		The size of the memory has to be higher or equal the value given by sizeOf_ID3FINGER_IDENTIFY() function.
//---------------------------------------------------------------------------
ID3FINGER_API int id3FingerIdentify_Initialize(ID3FINGER_IDENTIFY* phIdentificator,unsigned char* buffer,int bufferSize);

// --------------------------------------------------------------------------------------------------
// Gets the maximum number of users that can be searched.
//
// Parameters
// 		hIdentificator:
// 			[in] A handle to a fingerprint matcher.
//
// 		count:
// 			[out] Receives the maximum number of users.
//
// Returns
// 		ID3_SUCCESS if the function succeeds.
// 		An error code if it fails.
//
// Remarks
//		This maximum number of users depends on the buffer size used while initializing the object. See sizeOf_ID3FINGER_IDENTIFY function.
// --------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerIdentify_GetMaxUserCount(ID3FINGER_IDENTIFY hIdentificator, unsigned int* count);

//--------------------------------------------------------------------------------------------------
// Gets the identification's acceptance threshold.
//
// Parameters
//		hIdentificator:
//			[in] A handle to a fingerprint identificator.
//
//		param:
//			[out] Receives the threshold. See id3FingerMatchThreshold for details.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerIdentify_GetThreshold(ID3FINGER_IDENTIFY hIdentificator,int* param);

//--------------------------------------------------------------------------------------------------
// Sets the identification's acceptance threshold.
//
// Parameters
//		hIdentificator:
//			[in] A handle to a fingerprint identificator.
//
//		param:
//			[in] The desired threshold. See id3FingerMatchThreshold for a list of possible values.
//
// Returns
//		ID3_SUCCESS if the function succeeds.
//		An error code if it fails.
//--------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerIdentify_SetThreshold(ID3FINGER_IDENTIFY hIdentificator,int param);

// -------------------------------------------------------------------------------------------------------
// Parse the reference user list against which probe templates will be searched.
//
// Parameters
// 		hIdentificator:
// 			[in] A handle to a fingerprint identificator.
//
// 		UserIDs:
// 			[in] The list of user IDs that will be searched.
//
//		UserIDsCount:
//			[in] The number of user IDs in the list.
//
//		GetTemplatesCount:
//			[in] A function pointer returning the number of templates for each user.
//
//		GetTemplate:
//			[in] A function pointer returing templates for each user. Templates must be in IEFM256 format.
//
//		GetTemplatePosition:
//			[in] An optionnal function pointer returning the finger position for each user template. Set null if unused.
//
// 		optionalArgument:
// 			[in] An optionnal argument to provide to GetTemplatesCount,GetTemplate and GetTemplatePosition functions when calling them. Set null if unused.
//
// Returns
// 		ID3_SUCCESS if the function succeeds.
// 		An error code if it fails.
//
// Remarks
//		This function allows flexible connection to a fingeprint database, i.e.
//			- templates which are not consecutive into the memory,
//			- encrypted templates,
//			- management of several templates per user,
//			- management of database subsets (gender, ...).
//		The position function is not mandatory, as finger position is already given in the finger template data. It is strongly advised to furnished one in case of a slow retrieving function or in a multifinger context to speed up the searches.
//		The function that retrieves templates expects each one to be available until the next retrievial.
//		The optional argument allows parsing additional/contextual parameters when calling the three functions. Use structs to parse several parameters.
// --------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerIdentify_SetReferenceUserList(
	ID3FINGER_IDENTIFY hIdentificator,
	int* UserIDs,
	unsigned int UserIDsCount,
	unsigned char (*GetTemplatesCount)(int UserID,void* optionalArgument),
	void* (*GetTemplate)(int UserID,unsigned char templateIndex,void* optionalArgument),
	id3FingerPosition (*GetTemplatePosition)(int UserID,unsigned char templateIndex,void* optionalArgument),
	void* optionalArgument);

// --------------------------------------------------------------------------------------------------
// Search a record into the reference users list.
//
// Parameters
// 		hIdentificator:
// 			[in] A handle to a fingerprint identificator.
//
// 		probe:
// 			[in] A handle to the probe template record.
//
// 		hMatchResults:
// 			[in] A handle to an array of id3FingerMatchResult where search results will be written.
//
// 		maxCandidatesCount:
// 			[in] The maximum number of returned candidates.
// 			[out] The number of returned candidates.
//
// Returns
// 		ID3_SUCCESS if the function succeeds.
// 		An error code if it fails.
//
// Remarks
//		The reference user list has to be set up before searching using id3FingerIdentify_SetReferenceUserList function.
// --------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerIdentify_SearchRecord(ID3FINGER_IDENTIFY hIdentificator,ID3FINGER_TRECORD probe,id3FingerMatchResult *hMatchResults,int* maxCandidatesCount);

// --------------------------------------------------------------------------------------------------
// Search a template into the reference users list.
//
// Parameters
// 		hIdentificator:
// 			[in] A handle to a fingerprint identificator.
//
// 		probe:
// 			[in] A handle to the probe template.
//
// 		hMatchResults:
// 			[in] A handle to an array of id3FingerMatchResult where search results will be written.
//
// 		maxCandidatesCount:
// 			[in] The maximum number of returned candidates.
// 			[out] The number of returned candidates.
//
// Returns
// 		ID3_SUCCESS if the function succeeds.
// 		An error code if it fails.
//
// Remarks
//		The reference user list has to be set up before searching using id3FingerIdentify_SetReferenceUserList function.
// --------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerIdentify_SearchTemplate(ID3FINGER_IDENTIFY hIdentificator,ID3FINGER_TEMPLATE probe,id3FingerMatchResult *hMatchResults,int* maxCandidatesCount);

// --------------------------------------------------------------------------------------------------
// Gets detailed information about the last search.
//
// Parameters
// 		hIdentificator:
// 			[in] A handle to a fingerprint identificator.
//
// 		rank:
// 			[in] The candidate's rank (starting 0).
//
// 		position:
// 			[in] The fingerprint position. See id3FingerPosition for details.
//
// 		hMatchResult:
// 			[out] Receives the search information.
//
// Returns
// 		ID3_SUCCESS if the function succeeds.
// 		An error code if it fails.
// --------------------------------------------------------------------------------------------------
ID3FINGER_API int id3FingerIdentify_GetSearchDetails(ID3FINGER_IDENTIFY hIdentificator,int rank,unsigned char position,id3FingerMatchResult* hMatchResult);



ID3FINGER_API unsigned int id3FingerMatch_CBEFFID();

#ifdef __cplusplus
}
#endif


#endif
