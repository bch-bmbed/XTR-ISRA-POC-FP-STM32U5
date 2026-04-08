#include "next_bio_port.h"
#include <string.h>

/* Mapping CubeMX */
#define NEXT_CS_GPIO_Port         NB6510_CS_GPIO_Port
#define NEXT_CS_Pin               NB6510_CS_Pin

#define NEXT_RESET_GPIO_Port      NB6510_RESET_GPIO_Port
#define NEXT_RESET_Pin            NB6510_RESET_Pin

#define NEXT_AWAKE_GPIO_Port      NB6510_AWAKE_GPIO_Port
#define NEXT_AWAKE_Pin            NB6510_AWAKE_Pin

#define NEXT_DRDY_GPIO_Port       NB6510_DRDY_GPIO_Port
#define NEXT_DRDY_Pin             NB6510_DRDY_Pin

static NBResult NB_API NEXT_GetTimestamp(void *pContext, NBUInt32 *pui32Tick)
{
    (void)pContext;

    if (pui32Tick == NULL)
    {
        return NB_ERROR_ARGUMENT_NULL;
    }

    *pui32Tick = HAL_GetTick();
    return NB_OK;
}

static NBResult NB_API NEXT_AwakeGetValue(void *pContext, NBDevicePinValue *pValue)
{
    GPIO_PinState state;

    (void)pContext;

    if (pValue == NULL)
    {
        return NB_ERROR_ARGUMENT_NULL;
    }

    state = HAL_GPIO_ReadPin(NEXT_AWAKE_GPIO_Port, NEXT_AWAKE_Pin);

    *pValue = (state == GPIO_PIN_SET) ? NBDevicePinValueHigh : NBDevicePinValueLow;

    return NB_OK;
}

static NBResult NB_API NEXT_ResetSetValue(void *pContext, NBDevicePinValue value)
{
    (void)pContext;

    if (value == NBDevicePinValueUnknown)
    {
        return NB_ERROR_ARGUMENT;
    }

    HAL_GPIO_WritePin(
        NEXT_RESET_GPIO_Port,
        NEXT_RESET_Pin,
        (value == NBDevicePinValueHigh) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    return NB_OK;
}

static NBResult NB_API NEXT_DelayMicroseconds(void *pContext, NBUInt32 us)
{
    uint32_t start;
    uint32_t ticks;

    (void)pContext;

    start = DWT->CYCCNT;
    ticks = us * (HAL_RCC_GetHCLKFreq() / 1000000U);

    while ((DWT->CYCCNT - start) < ticks)
    {
    }

    return NB_OK;
}

static NBResult NB_API NEXT_SendReceiveData(
    void *pContext,
    NBUInt8 *pTxBuffer,
    NBUInt16 txLength,
    NBUInt8 *pRxBuffer,
    NBUInt16 rxLength)
{
    HAL_StatusTypeDef status;

    (void)pContext;

    if ((pTxBuffer == NULL) || (pRxBuffer == NULL))
    {
        return NB_ERROR_ARGUMENT_NULL;
    }

    if (txLength != rxLength)
    {
        return NB_ERROR_ARGUMENT;
    }

    NEXT_Select();

    status = HAL_SPI_TransmitReceive(&hspi1, pTxBuffer, pRxBuffer, rxLength, 1000U);

    NEXT_Deselect();

    return (status == HAL_OK) ? NB_OK : NB_ERROR_FAILED;
}

static uint32_t NEXT_Reverse32(uint32_t x)
{
    x = ((x & 0x55555555U) << 1) | ((x >> 1) & 0x55555555U);
    x = ((x & 0x33333333U) << 2) | ((x >> 2) & 0x33333333U);
    x = ((x & 0x0F0F0F0FU) << 4) | ((x >> 4) & 0x0F0F0F0FU);

    return (x << 24) |
           ((x & 0x0000FF00U) << 8) |
           ((x & 0x00FF0000U) >> 8) |
           (x >> 24);
}

static NBResult NB_API NEXT_DoCrc32(
    void *pContext,
    const NBByte *data,
    NBSizeType len,
    NBUInt32 *crc)
{
    NBSizeType i;
    int j;
    uint32_t c;

    (void)pContext;

    if ((data == NULL) || (crc == NULL))
    {
        return NB_ERROR_ARGUMENT_NULL;
    }

    c = 0xFFFFFFFFU;

    for (i = 0; i < len; i++)
    {
        uint32_t byte = NEXT_Reverse32(data[i]);

        for (j = 0; j < 8; j++)
        {
            if ((int32_t)(c ^ byte) < 0)
            {
                c = (c << 1) ^ 0x04C11DB7U;
            }
            else
            {
                c <<= 1;
            }

            byte <<= 1;
        }
    }

    *crc = NEXT_Reverse32(~c);

    return NB_OK;
}

NBResult NEXT_GetDeviceIO(NBDeviceIO *io)
{
    if (io == NULL)
    {
        return NB_ERROR_ARGUMENT_NULL;
    }

    memset(io, 0, sizeof(*io));

    /* nAWAKE is active low on NB-65210-S */
    io->bIsAwakeHigh       = NBFalse;
    io->pContext           = NULL;
    io->pDestroyContext    = NULL;
    io->pDelayMicroseconds = NEXT_DelayMicroseconds;
    io->pGetTimestamp      = NEXT_GetTimestamp;
    io->pResetSetValue     = NEXT_ResetSetValue;
    io->pAwakeGetValue     = NEXT_AwakeGetValue;
    io->pSendReceiveData   = NEXT_SendReceiveData;
    io->pDoCrc32           = NEXT_DoCrc32;
    io->pGetRandomBytes    = NULL;

    return NB_OK;
}

void NEXT_ResetLow(void)
{
    HAL_GPIO_WritePin(NEXT_RESET_GPIO_Port, NEXT_RESET_Pin, GPIO_PIN_RESET);
}

void NEXT_ResetHigh(void)
{
    HAL_GPIO_WritePin(NEXT_RESET_GPIO_Port, NEXT_RESET_Pin, GPIO_PIN_SET);
}

void NEXT_Select(void)
{
    HAL_GPIO_WritePin(NEXT_CS_GPIO_Port, NEXT_CS_Pin, GPIO_PIN_RESET);
}

void NEXT_Deselect(void)
{
    HAL_GPIO_WritePin(NEXT_CS_GPIO_Port, NEXT_CS_Pin, GPIO_PIN_SET);
}

GPIO_PinState NEXT_AwakeRead(void)
{
    return HAL_GPIO_ReadPin(NEXT_AWAKE_GPIO_Port, NEXT_AWAKE_Pin);
}

GPIO_PinState NEXT_DataReadyRead(void)
{
    return HAL_GPIO_ReadPin(NEXT_DRDY_GPIO_Port, NEXT_DRDY_Pin);
}
