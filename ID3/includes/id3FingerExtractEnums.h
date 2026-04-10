//!doc
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2015 - id3 Technologies
//
// $Revision: 3154 $
// $Date: 2017-04-26 11:51:33 +0200 (mer. 26 avr. 2017) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerExtractEnums_h
#define _id3FingerExtractEnums_h

/// <summary>
/// Extractor mode selection.
/// </summary>
typedef enum
{
	/// <summary>
	/// Low Speed (highest accuracy) at 500DPI
	/// </summary>
	FingerExtractMode_LowSpeed = 0,

	/// <summary>
	/// High Speed (lowest accuracy) at 500DPI
	/// </summary>
	FingerExtractMode_HighSpeed = 1,

		/// <summary>
	/// Low Speed (highest accuracy) at 370DPI
	/// </summary>
	FingerExtractMode_LowSpeed370DPI = 10,

	/// <summary>
	/// High Speed (lowest accuracy) at 370DPI
	/// </summary>
	FingerExtractMode_HighSpeed370DPI = 11,

	/// <summary>
	/// Small Sensor at 500DPI (only works on _xlmem extractor)
	/// </summary>
	FingerExtractMode_SmallSensor = 20,
	
	/// <summary>
	/// Small Sensor at 370DPI (only works on _xlmem extractor)
	/// </summary>
	FingerExtractMode_SmallSensor370DPI = 21,
}id3FingerExtractMode;

#endif
