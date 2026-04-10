//!doc
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2011 - id3 Semiconductors
//
// $Revision: 2288 $
// $Date: 2015-10-08 16:20:59 +0200 (jeu. 08 oct. 2015) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerMatchEnums_h
#define _id3FingerMatchEnums_h

/// <summary>
/// Matching acceptance threshold.
/// </summary>
typedef enum
{
	/// <summary>
	/// False Match Rate = 1%
	/// </summary>
	FingerMatchThreshold_FMR100 = 1925,

	/// <summary>
	/// False Match Rate = 0.1%
	/// </summary>
	FingerMatchThreshold_FMR1000 = 2742,

	/// <summary>
	/// False Match Rate = 0.01%
	/// </summary>
	FingerMatchThreshold_FMR10000 = 3764,

	/// <summary>
	/// False Match Rate = 0.001%
	/// </summary>
	FingerMatchThreshold_FMR100000 = 4948,

	/// <summary>
	/// False Match Rate = 0.0001%
	/// </summary>
	FingerMatchThreshold_FMR1000000 = 7161,

	/// <summary>
	/// Low security level (False Match Rate = 1%)
	/// </summary>
	FingerMatchThreshold_LowSecurity = FingerMatchThreshold_FMR100,

	/// <summary>
	/// Medium security level (False Match Rate = 0.1%)
	/// </summary>
	FingerMatchThreshold_MediumSecurity = FingerMatchThreshold_FMR1000,

	/// <summary>
	/// High security level (False Match Rate = 0.01%)
	/// </summary>
	FingerMatchThreshold_HighSecurity = FingerMatchThreshold_FMR10000,

	/// <summary>
	/// Very high security level (False Match Rate = 0.001%)
	/// </summary>
	FingerMatchThreshold_VeryHighSecurity = FingerMatchThreshold_FMR100000

}id3FingerMatchThreshold;

/// <summary>
/// Matching decision.
/// </summary>
typedef enum
{
	/// <summary>
	/// Decision that the recognition biometric sample(s) and the biometric reference are not from the same source.
	/// </summary>
	FingerMatchDecision_NonMatch = 0,

	/// <summary>
	/// Decision that the recognition biometric sample(s) and the biometric reference are from the same source.
	/// </summary>
	FingerMatchDecision_Match = 1

} id3FingerMatchDecision;

#endif
