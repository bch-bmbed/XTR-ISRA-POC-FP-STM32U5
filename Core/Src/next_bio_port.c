#include "next_bio_port.h"
#include <string.h>

/* ==== Mapping réel CubeMX ==== */

#define NEXT_CS_GPIO_Port        NB6510_CS_GPIO_Port
#define NEXT_CS_Pin              NB6510_CS_Pin

#define NEXT_RESET_GPIO_Port     NB6510_RESET_GPIO_Port
#define NEXT_RESET_Pin           NB6510_RESET_Pin

#define NEXT_AWAKE_GPIO_Port     NB6510_AWAKE_GPIO_Port
#define NEXT_AWAKE_Pin           NB6510_AWAKE_Pin

/* =============================== */

static NBResult NB_API NEXT_GetTimestamp(void *pContext, NBUInt32 *pui32Tick)
{
    if (!pui32Tick) return NB_ERROR_ARGUMENT_NULL;

    *pui32Tick = HAL_GetTick();

    return NB_OK;
}

static NBResult NB_API NEXT_AwakeGetValue(void *pContext, NBDevicePinValue *pValue)
{
    if (!pValue) return NB_ERROR_ARGUMENT_NULL;

    GPIO_PinState s =
        HAL_GPIO_ReadPin(
            NEXT_AWAKE_GPIO_Port,
            NEXT_AWAKE_Pin);

    *pValue =
        (s == GPIO_PIN_SET) ?
            NBDevicePinValueHigh :
            NBDevicePinValueLow;

    return NB_OK;
}

static NBResult NB_API NEXT_ResetSetValue(void *pContext, NBDevicePinValue value)
{
    HAL_GPIO_WritePin(
        NEXT_RESET_GPIO_Port,
        NEXT_RESET_Pin,
        (value == NBDevicePinValueHigh) ?
        GPIO_PIN_SET :
        GPIO_PIN_RESET);

    return NB_OK;
}

static NBResult NB_API NEXT_DelayMicroseconds(void *pContext, NBUInt32 us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks =
        us * (HAL_RCC_GetHCLKFreq() / 1000000);

    while ((DWT->CYCCNT - start) < ticks);

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

    if (!pTxBuffer) return NB_ERROR_ARGUMENT_NULL;
    if (!pRxBuffer) return NB_ERROR_ARGUMENT_NULL;
    if (txLength != rxLength) return NB_ERROR_ARGUMENT;

    NEXT_Select();
    status = HAL_SPI_TransmitReceive(&hspi1, pTxBuffer, pRxBuffer, rxLength, 1000);
    NEXT_Deselect();

    return (status == HAL_OK) ? NB_OK : NB_ERROR_FAILED;
}

/* CRC32 minimal */

static uint32_t reverse32(uint32_t x)
{
    x = ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
    x = ((x & 0x33333333) << 2) | ((x >> 2) & 0x33333333);
    x = ((x & 0x0F0F0F0F) << 4) | ((x >> 4) & 0x0F0F0F0F);

    return (x << 24) |
           ((x & 0xFF00) << 8) |
           ((x >> 8) & 0xFF00) |
           (x >> 24);
}

static NBResult NB_API NEXT_DoCrc32(
    void *pContext,
    const NBByte *data,
    NBSizeType len,
    NBUInt32 *crc)
{
    uint32_t c = 0xFFFFFFFF;

    for (size_t i=0;i<len;i++)
    {
        uint32_t byte = reverse32(data[i]);

        for (int j=0;j<8;j++)
        {
            if ((int32_t)(c ^ byte) < 0)
                c = (c << 1) ^ 0x04C11DB7;
            else
                c <<= 1;

            byte <<= 1;
        }
    }

    *crc = reverse32(~c);

    return NB_OK;
}

NBResult NEXT_GetDeviceIO(NBDeviceIO *io)
{
    if (!io) return NB_ERROR_ARGUMENT_NULL;

    memset(io, 0, sizeof(*io));

    io->bIsAwakeHigh       = NBFalse;
    io->pContext           = NULL;
    io->pDestroyContext    = NULL;
    io->pAwakeGetValue     = NEXT_AwakeGetValue;
    io->pResetSetValue     = NEXT_ResetSetValue;
    io->pDelayMicroseconds = NEXT_DelayMicroseconds;
    io->pSendReceiveData   = NEXT_SendReceiveData;
    io->pGetTimestamp      = NEXT_GetTimestamp;
    io->pDoCrc32           = NEXT_DoCrc32;
    io->pGetRandomBytes    = NULL;

    return NB_OK;
}

void NEXT_ResetLow(void)
{
    HAL_GPIO_WritePin(
        NEXT_RESET_GPIO_Port,
        NEXT_RESET_Pin,
        GPIO_PIN_RESET);
}

void NEXT_ResetHigh(void)
{
    HAL_GPIO_WritePin(
        NEXT_RESET_GPIO_Port,
        NEXT_RESET_Pin,
        GPIO_PIN_SET);
}

void NEXT_Select(void)
{
    HAL_GPIO_WritePin(
        NEXT_CS_GPIO_Port,
        NEXT_CS_Pin,
        GPIO_PIN_RESET);
}

void NEXT_Deselect(void)
{
    HAL_GPIO_WritePin(
        NEXT_CS_GPIO_Port,
        NEXT_CS_Pin,
        GPIO_PIN_SET);
}

GPIO_PinState NEXT_AwakeRead(void)
{
    return HAL_GPIO_ReadPin(
        NEXT_AWAKE_GPIO_Port,
        NEXT_AWAKE_Pin);
}
