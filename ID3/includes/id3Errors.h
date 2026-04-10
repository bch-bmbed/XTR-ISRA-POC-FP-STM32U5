//!doc
//--------------------------------------------------------------------------------------------------
// Copyright (c) id3 Technologies
// All Rights Reserved.
//
// $Revision: 2598 $
// $Date: 2016-04-12 14:16:42 +0200 (mar. 12 avr. 2016) $
//--------------------------------------------------------------------------------------------------
#ifndef _id3Errors_h
#define _id3Errors_h

#define ID3_SUCCESS							0		// No error

#define ID3_E_LICENSE_NOT_FOUND				-1		// No license was found.
#define ID3_E_LICENSE_INVALID				-2		// License is not valid or a required module is not licensed.
#define ID3_E_LICENSE_EXPIRED				-3		// The license has expired.
#define ID3_E_LICENSE_ERROR					-4		// License Error. Installation code may not match hardware ID.
#define ID3_E_LICENSE_ALREADY_FULFILLED		-5		// The license is already fulfilled by another user (or computer).
#define ID3_E_LICENSE_MODULE_ERROR			-6		// A required module is not licensed or the usage limit has been reached.
#define ID3_E_LICENSE_WRITE_ERROR			-7		// The license file cannot be accessed in write mode.

#define ID3_E_INVALID_HANDLE				-10		// The handle is invalid.
#define ID3_E_INVALID_PARAMETER				-11		// The parameter is incorrect.
#define ID3_E_INVALID_FORMAT				-12		// Invalid format
#define ID3_E_INSUFFICIENT_BUFFER			-13		// The data area passed to a system call is too small.
#define ID3_E_LIBRARY_NOT_FOUND				-14		// A required library could not be found.
#define ID3_E_TIMEOUT_EXPIRED				-15		// The function has been terminated because the timeout value has expired.
#define ID3_E_MEMORY_ERROR					-16		// A memory error occurred.
#define ID3_W_CANCELLED						-17		// The action was cancelled by the user.
#define ID3_E_INVALID_EXTRACT_MODE			-18		// The provided extract mode is not compatible with the current extractor.
#define ID3_E_INVALID_DPI					-19		// The provided image resolution is not compatible with the current extract mode.

#endif
