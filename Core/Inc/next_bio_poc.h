/*
 * next_bio_poc.h
 *
 *  Created on: 8 avr. 2026
 *      Author: benjamin.chalant
 */

#ifndef NEXT_BIO_TESTS_H
#define NEXT_BIO_TESTS_H

#include "next_bio_device.h"

NBResult NEXT_TestFirmwareVersion(void);
NBResult NEXT_TestSupportedScanFormats(void);
NBResult NEXT_TestScanFormatInfo(void);
NBResult NEXT_TestCaptureImage(void);

#endif /* NEXT_BIO_TESTS_H */
