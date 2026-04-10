//!doc
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2015 - id3 Technologies
//
// $Revision: 2799 $
// $Date: 2016-05-31 15:17:58 +0200 (mar. 31 mai 2016) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerEnrollEnums_h
#define _id3FingerEnrollEnums_h

/// <summary>
/// Enroll mode selection.
/// </summary>
typedef enum
{
	/// <summary>
	/// Aggregation: multiple views
	/// </summary>
	FingerEnrollMode_Aggregation = 0,

	/// <summary>
	// Mosaicking: enrolled templates merged in one view
	/// </summary>
	FingerEnrollMode_Mosaicking = 1,

}id3FingerEnrollMode;

#endif
