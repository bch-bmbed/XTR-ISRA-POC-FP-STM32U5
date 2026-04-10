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

NBResult NEXT_BiometricsInit(void);
void NEXT_BiometricsDeinit(void);
HNBBiometricsContext NEXT_BiometricsGetContext(void);

NBResult NEXT_TestExtractTemplate(void);

#endif /* NEXT_BIO_BIOMETRICS_H */
