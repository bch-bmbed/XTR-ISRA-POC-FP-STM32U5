//!doc
//--------------------------------------------------------------------------------------------------
// This file contains fingerprint-related enumerations
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2011 - id3 Semiconductors
//
// $Revision: 2288 $
// $Date: 2015-10-08 16:20:59 +0200 (jeu. 08 oct. 2015) $
//-------------------------------------------------------------------------------------------------- 

#ifndef _id3FingerEnums_h
#define _id3FingerEnums_h

#include "id3FingerTemplateEnums.h"

/// <summary>
/// Finger position codes, as defined in ISO/IEC 19794-2:2011
/// </summary>
typedef enum
{
	/// <summary>
	/// Unknown finger
	/// </summary>
	FingerPosition_Unknown = 0,

	/// <summary>
	/// Right thumb
	/// </summary>
	FingerPosition_RightThumb = 1, 

	/// <summary>
	/// Right index finger
	/// </summary>
	FingerPosition_RightIndex = 2, 

	/// <summary>
	/// Right middle finger
	/// </summary>
	FingerPosition_RightMiddle = 3, 

	/// <summary>
	/// Right ring finger
	/// </summary>
	FingerPosition_RightRing = 4, 

	/// <summary>
	/// Right little finger
	/// </summary>
	FingerPosition_RightLittle = 5, 

	/// <summary>
	/// Left thumb
	/// </summary>
	FingerPosition_LeftThumb = 6, 

	/// <summary>
	/// Left index finger
	/// </summary>
	FingerPosition_LeftIndex = 7, 

	/// <summary>
	/// Left middle finger
	/// </summary>
	FingerPosition_LeftMiddle = 8, 

	/// <summary>
	/// Left ring finger
	/// </summary>
	FingerPosition_LeftRing = 9, 

	/// <summary>
	/// Left little finger
	/// </summary>
	FingerPosition_LeftLittle = 10
          
} id3FingerPosition;

/// <summary>
/// Impression type of a finger image, as defined in ISO/IEC 19794-2:2011.
/// </summary>
typedef enum
{
	/// <summary>
	/// Live-scan plain
	/// </summary>
	FingerImpression_LiveScanPlain = 0,

	/// <summary>
	/// Live-scan rolled
	/// </summary>
	FingerImpression_LiveScanRolled = 1,

	/// <summary>
	/// Nonlive-scan plain
	/// </summary>
	FingerImpression_NonliveScanPlain = 2,

	/// <summary>
	/// Nonlive-scan rolled
	/// </summary>
	FingerImpression_NonliveScanRolled = 3,

	/// <summary>
	/// Latent impression
	/// </summary>
	FingerImpression_LatentImpression = 4,

	/// <summary>
	/// Latent tracing
	/// </summary>
	FingerImpression_LatentTracing = 5,

	/// <summary>
	/// Latent photo
	/// </summary>
	FingerImpression_LatentPhoto = 6,

	/// <summary>
	/// Latent lift
	/// </summary>
	FingerImpression_LatentLift = 7,

	/// <summary>
	/// Live-scan swipe
	/// </summary>
	FingerImpression_LiveScanSwipe = 8,

	/// <summary>
	/// Vertical roll
	/// </summary>
	FingerImpression_VerticalRoll = 9,

	/// <summary>
	/// Live-scan optical contactless plain
	/// </summary>
	FingerImpression_LiveScanOpticalContactlessPlain = 24,

	/// <summary>
	/// Other
	/// </summary>
	FingerImpression_Other = 28,

	/// <summary>
	/// Unknown
	/// </summary>
	FingerImpression_Unknown = 29

} id3FingerImpression;

/// <summary>
/// Finger image quality.
/// </summary>
typedef enum
{
	/// <summary>
	/// Low quality
	/// </summary>
	FingerImageQuality_Low = 20,

	/// <summary>
	/// Fair quality
	/// </summary>
	FingerImageQuality_Fair = 40,

	/// <summary>
	/// Good quality
	/// </summary>
	FingerImageQuality_Good = 60,

	/// <summary>
	/// Very good quality
	/// </summary>
	FingerImageQuality_VeryGood = 80,

	/// <summary>
	/// Excellent quality
	/// </summary>
	FingerImageQuality_Excellent = 100,

	/// <summary>
	/// Quality value not reported
	/// </summary>
	FingerImageQuality_NotReported = 254,

	/// <summary>
	/// Failed to compute quality value
	/// </summary>
	FingerImageQuality_FailedToCompute = 255

} id3FingerImageQuality;

#endif
