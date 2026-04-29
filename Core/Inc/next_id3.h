/*
 * next_id3.h
 *
 *  Created on: 10 avr. 2026
 *      Author: benjamin.chalant
 */

#ifndef NEXT_ID3_H
#define NEXT_ID3_H

#include "main.h"
#include "id3Errors.h"
#include "id3FingerTemplate.h"
#include "id3FingerExtract.h"
#include "id3FingerExtractEnums.h"
#include "id3FingerTemplateEnums.h"

int NEXT_ID3_SmokeTest(void);
int NEXT_ID3_ExtractFromNextCapture(void);
int NEXT_ID3_TestTwoTemplates(void);

int NEXT_ID3_BenchmarkCaptureSettings(void);
int NEXT_ID3_BenchmarkImageVariants(void);
int NEXT_ID3_BenchmarkScanEx(void);
int NEXT_ID3_BenchmarkFingerDetectCapture(void);

#endif /* NEXT_ID3_H */
