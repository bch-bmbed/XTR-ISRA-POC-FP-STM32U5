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
NBResult NEXT_TestCalibration(void);
NBResult NEXT_TestCaptureImage(void);
NBResult NEXT_TestCaptureImageToPgm(void);

NBResult NEXT_TestExtractTemplate(void);

// HELPERS GUI

void NEXT_UiBanner(const char *msg);
void NEXT_UiCountdown(const char *msg, uint32_t seconds);
void NEXT_UiShowVerifyResult(int score, int bioStatus);

#endif /* NEXT_BIO_TESTS_H */
