//!doc
//--------------------------------------------------------------------------------------------------
// This file contains definition of SDK error codes
//--------------------------------------------------------------------------------------------------
// Copyright (c) 2011 - id3 Semiconductors
//
// $Revision: 2487 $
// $Date: 2016-02-03 16:22:10 +0100 (mer. 03 févr. 2016) $
//--------------------------------------------------------------------------------------------------

#ifndef _id3FingerErrors_h
#define _id3FingerErrors_h

#include "id3Errors.h"

#define ID3_E_RECORD_FORMAT_LIMITATION	-20		// The maximum number of representations of a single finger has been reached.
#define ID3_E_EMPTY_RECORD				-21		// The finger record object is empty.

#define ID3_W_SEARCH_LIMITATION			-30		// Though the given buffer allow a bigger value, user count is limited to 65536.
#define ID3_E_SEARCH_BAD_USERLIST		-31		// Reference user list has no been configured yet or is invalid.

#endif
