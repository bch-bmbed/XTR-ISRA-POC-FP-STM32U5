//!doc
//--------------------------------------------------------------------------------------------------
// This file contains templates enumerations
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2011 - id3 Semiconductors
//
// $Revision: 2647 $
// $Date: 2016-04-14 11:57:10 +0200 (jeu. 14 avr. 2016) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerTemplateEnums_h
#define _id3FingerTemplateEnums_h

// Finger Template Formats
typedef enum
{
	FingerTemplateFormat_Unknown = 0,				// Specify this format when the input format is unknown.

	FingerTemplateFormat_Incits378 = 1,				// ANSI INCITS 378-2004
	FingerTemplateFormat_Iso19794 = 2,				// ISO/IEC 19794-2:2005
	FingerTemplateFormat_Iso19794CompactCard = 3,	// ISO/IEC 19794-2:2005 compact card format
	FingerTemplateFormat_Incits378_2009 = 4,		// ANSI INCITS 378-2009
	FingerTemplateFormat_Iso19794_2011 = 5,			// ISO/IEC 19794-2:2010

	FingerTemplateFormat_IEFM256 = 100,				// Internal format of that SDK. 256 bytes templates: 16 bytes header, 80 minutiae (max) x 3 bytes per minutia.
	FingerTemplateFormat_IEFM784 = 101				// Internal format of that SDK. 784 bytes templates: 16 bytes header, 128 minutiae (max) x 6 bytes per minutia.
} id3FingerTemplateFormat;

#endif
