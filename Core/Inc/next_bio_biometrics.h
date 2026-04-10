/*
 * next_bio_biometrics.h
 *
 *  Created on: 10 avr. 2026
 *      Author: benjamin.chalant
 */

#ifndef NEXT_BIO_BIOMETRICS_H
#define NEXT_BIO_BIOMETRICS_H

#include "main.h"
#include "NBErrors.h"
#include "NBBiometricsContext.h"
#include "NBBiometricsLibrary.h"
#include "NBBiometricsTemplate.h"
#include "NBBiometricsTypes.h"

#define NEXT_MAX_TEMPLATE_SIZE   4096U

typedef struct
{
    NBByte data[NEXT_MAX_TEMPLATE_SIZE];
    NBSizeType size;
    NBInt quality;
    NBBool valid;
} NEXT_TemplateBuffer;

NBResult NEXT_BiometricsInit(void);
void NEXT_BiometricsDeinit(void);
HNBBiometricsContext NEXT_BiometricsGetContext(void);

NBResult NEXT_ExtractTemplate(NEXT_TemplateBuffer *pOut);
NBResult NEXT_TestVerifyTwoScans(void);

#endif /* NEXT_BIO_BIOMETRICS_H */
