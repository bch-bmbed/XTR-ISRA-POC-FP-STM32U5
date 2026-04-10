//!doc
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2011 - id3 Semiconductors
//
// $Revision: 2296 $
// $Date: 2015-10-09 17:16:13 +0200 (ven. 09 oct. 2015) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerMatchStructs_h
#define _id3FingerMatchStructs_h

/// <summary>
/// This structure gives information about one verification or identification result.
/// </summary>
typedef struct
{
	/// <summary>
	/// Match/Non-Match decision.
    /// </summary>
	unsigned char Decision;

    /// <summary>
	/// Score returned by the template matcher.
    /// </summary>
	unsigned short Score;
    
	/// <summary>
	/// Similarity rate between the two fingerprints, between 0 and 100.
	/// </summary>
	unsigned char SimilarityRate;

	/// <summary>
	/// ID of the user in the reference list. Zero on comparaison.
	/// </summary>
	int ReferenceUserID;

	/// <summary>
	/// Index of template in Reference Record.
	/// </summary>
	unsigned char IndexInReference;

	/// <summary>
	/// Index of template in Probe Record.
	/// </summary>
	unsigned char IndexInProbe;

}id3FingerMatchResult;

#endif
