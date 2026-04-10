//!doc
//--------------------------------------------------------------------------------------------------
// This file contains minutiae's structures and enumerations
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2011 - id3 Semiconductors
//
// $Revision: 2849 $
// $Date: 2016-07-06 14:12:17 +0200 (mer. 06 juil. 2016) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerMinutia_h
#define _id3FingerMinutia_h

/// <summary>
/// Finger Minutia
/// </summary>
typedef struct
{
	/// <summary>
	/// x-coordinate
	/// </summary>
	unsigned short X;

	/// <summary>
	/// y-coordinate
	/// </summary>
	unsigned short Y;

	/// <summary>
	/// Angle (unit = 1.40625°)
	/// </summary>
	unsigned char Angle;

} id3FingerMinutia;

#endif
