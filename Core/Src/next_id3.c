/*
 * next_id3.c
 *
 *  Created on: 10 avr. 2026
 *      Author: benjamin.chalant
 */

#include "next_id3.h"
#include "logger_xtr.h"
#include <string.h>
#include <stdlib.h>

int NEXT_ID3_SmokeTest(void)
{
    int result;
    int templateObjSize;
    ID3FINGER_TEMPLATE hTemplate = NULL;
    uint8_t *pTemplateBuffer = NULL;

    log_printf(LOG_DBG, "ID3 smoke test start\r\n");

    templateObjSize = sizeOf_ID3FINGER_TEMPLATE();
    log_printf(LOG_DBG, "ID3 template object size=%d\r\n", templateObjSize);

    if (templateObjSize <= 0)
    {
        log_printf(LOG_DBG, "Invalid ID3 template size\r\n");
        return -1;
    }

    pTemplateBuffer = (uint8_t *)malloc((size_t)templateObjSize);
    if (pTemplateBuffer == NULL)
    {
        log_printf(LOG_DBG, "ID3 template malloc failed\r\n");
        return -2;
    }

    memset(pTemplateBuffer, 0, (size_t)templateObjSize);

    result = id3FingerTemplate_Initialize(&hTemplate, pTemplateBuffer, templateObjSize);
    log_printf(LOG_DBG, "id3FingerTemplate_Initialize -> %d\r\n", result);

    if (result == ID3_SUCCESS)
    {
        log_printf(LOG_DBG, "ID3 smoke test OK\r\n");
    }

    free(pTemplateBuffer);
    return result;
}

//int NEXT_ID3_ExtractTemplateFromImage(const uint8_t *pImage, NEXT_ID3_Template *pTemplate)
//{
//    int result;
//    int extractorBufferSize;
//    uint8_t *pExtractorBuffer = NULL;
//    uint8_t *pWorkingImage = NULL;
//    ID3FINGER_EXTRACT hExtract = NULL;
//    unsigned char imageQuality = 0;
//
//    if ((pImage == NULL) || (pTemplate == NULL))
//    {
//        return ID3_E_INVALID_ARGUMENT;
//    }
//
//    memset(pTemplate, 0, sizeof(*pTemplate));
//
//    extractorBufferSize = sizeOf_ID3FINGER_EXTRACT(NEXT_ID3_IMAGE_WIDTH, NEXT_ID3_IMAGE_HEIGHT);
//    if (extractorBufferSize <= 0)
//    {
//        return ID3_E_INVALID_ARGUMENT;
//    }
//
//    pExtractorBuffer = (uint8_t *)malloc((size_t)extractorBufferSize);
//    if (pExtractorBuffer == NULL)
//    {
//        return ID3_E_OUT_OF_MEMORY;
//    }
//
//    /* Important: le SDK id3 indique que l'image d'entrée est écrasée */
//    pWorkingImage = (uint8_t *)malloc((size_t)(NEXT_ID3_IMAGE_WIDTH * NEXT_ID3_IMAGE_HEIGHT));
//    if (pWorkingImage == NULL)
//    {
//        free(pExtractorBuffer);
//        return ID3_E_OUT_OF_MEMORY;
//    }
//
//    memcpy(pWorkingImage,
//           pImage,
//           (size_t)(NEXT_ID3_IMAGE_WIDTH * NEXT_ID3_IMAGE_HEIGHT));
//
//    result = id3FingerTemplate_Initialize(
//        &pTemplate->hTemplate,
//        pTemplate->buffer,
//        sizeof(pTemplate->buffer));
//    if (result != ID3_SUCCESS)
//    {
//        free(pWorkingImage);
//        free(pExtractorBuffer);
//        return result;
//    }
//
//    result = id3FingerExtract_Initialize(
//        &hExtract,
//        NEXT_ID3_IMAGE_WIDTH,
//        NEXT_ID3_IMAGE_HEIGHT,
//        pExtractorBuffer,
//        extractorBufferSize);
//    if (result != ID3_SUCCESS)
//    {
//        free(pWorkingImage);
//        free(pExtractorBuffer);
//        return result;
//    }
//
//    result = id3FingerExtract_CreateTemplate(
//        hExtract,
//        pWorkingImage,
//        pTemplate->hTemplate,
//        FingerExtractMode_HighSpeed370DPI,
//        NEXT_ID3_IMAGE_DPI);
//    if (result != ID3_SUCCESS)
//    {
//        free(pWorkingImage);
//        free(pExtractorBuffer);
//        return result;
//    }
//
//    result = id3FingerTemplate_GetImageQuality(pTemplate->hTemplate, &imageQuality);
//    if (result == ID3_SUCCESS)
//    {
//        log_printf(LOG_DBG, "ID3 template image quality=%u\r\n", (unsigned int)imageQuality);
//    }
//
//    pTemplate->valid = 1U;
//
//    free(pWorkingImage);
//    free(pExtractorBuffer);
//
//    return ID3_SUCCESS;
//}
//
//int NEXT_ID3_MatchTemplates(const NEXT_ID3_Template *pRef,
//                            const NEXT_ID3_Template *pProbe,
//                            id3FingerMatchResult *pResult)
//{
//    int result;
//    int matcherBufferSize;
//    uint8_t *pMatcherBuffer = NULL;
//    ID3FINGER_MATCH hMatcher = NULL;
//
//    if ((pRef == NULL) || (pProbe == NULL) || (pResult == NULL))
//    {
//        return ID3_E_INVALID_ARGUMENT;
//    }
//
//    if ((pRef->valid == 0U) || (pProbe->valid == 0U))
//    {
//        return ID3_E_INVALID_ARGUMENT;
//    }
//
//    memset(pResult, 0, sizeof(*pResult));
//
//    matcherBufferSize = sizeOf_ID3FINGER_MATCH();
//    if (matcherBufferSize <= 0)
//    {
//        return ID3_E_INVALID_ARGUMENT;
//    }
//
//    pMatcherBuffer = (uint8_t *)malloc((size_t)matcherBufferSize);
//    if (pMatcherBuffer == NULL)
//    {
//        return ID3_E_OUT_OF_MEMORY;
//    }
//
//    result = id3FingerMatch_Initialize(&hMatcher, pMatcherBuffer, matcherBufferSize);
//    if (result != ID3_SUCCESS)
//    {
//        free(pMatcherBuffer);
//        return result;
//    }
//
//    result = id3FingerMatch_SetThreshold(hMatcher, FingerMatchThreshold_MediumSecurity);
//    if (result != ID3_SUCCESS)
//    {
//        free(pMatcherBuffer);
//        return result;
//    }
//
//    result = id3FingerMatch_CompareTemplates(
//        hMatcher,
//        pRef->hTemplate,
//        pProbe->hTemplate,
//        pResult);
//
//    free(pMatcherBuffer);
//    return result;
//}
