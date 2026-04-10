//!doc
//--------------------------------------------------------------------------------------------------
// Copyright (c) id3 Technologies
//
// $Revision: 2487 $
// $Date: 2016-02-03 16:22:10 +0100 (mer. 03 févr. 2016) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3Types_h
#define _id3Types_h

#include <stdint.h>

#if defined(_WIN32) || defined(__WIN32__)
	#define ID3STDCALL __stdcall
	#define ID3CALL __cdecl
	#ifndef ID3API
		#define ID3API extern 
	#endif
#else
	#define ID3CALL
	#define ID3STDCALL
	#define ID3API __attribute__ ((visibility("default")))
#endif

#endif
