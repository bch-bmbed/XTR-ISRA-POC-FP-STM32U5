/*
 * next_id3.h
 *
 *  Created on: 10 avr. 2026
 *      Author: benjamin.chalant
 */

#ifndef NEXT_ID3_H
#define NEXT_ID3_H

#include "main.h"
#include "id3FingerExtract.h"
#include "id3FingerExtractEnums.h"
#include "id3FingerTemplate.h"
#include "id3FingerTemplateEnums.h"
#include "id3FingerMatch.h"
#include "id3FingerMatchEnums.h"
#include "id3FingerMatchStructs.h"
#include "id3Errors.h"

#define NEXT_ID3_TEMPLATE_OBJ_BUFFER_SIZE   2048
#define NEXT_ID3_IMAGE_WIDTH                300
#define NEXT_ID3_IMAGE_HEIGHT               400
#define NEXT_ID3_IMAGE_DPI                  385

typedef struct
{
    ID3FINGER_TEMPLATE hTemplate;
    uint8_t buffer[NEXT_ID3_TEMPLATE_OBJ_BUFFER_SIZE];
    uint8_t valid;
} NEXT_ID3_Template;

int NEXT_ID3_SmokeTest(void);

int NEXT_ID3_ExtractTemplateFromImage(const uint8_t *pImage, NEXT_ID3_Template *pTemplate);
int NEXT_ID3_MatchTemplates(const NEXT_ID3_Template *pRef,
                            const NEXT_ID3_Template *pProbe,
                            id3FingerMatchResult *pResult);

#endif /* NEXT_ID3_H */
