/*
 * next_bio.h
 *
 *  Created on: 8 avr. 2026
 *      Author: benjamin.chalant
 */

#ifndef NEXT_BIO_PORT_H
#define NEXT_BIO_PORT_H

#include "main.h"
#include "NBDevices.h"
#include "NBDevice.h"

extern SPI_HandleTypeDef hspi1;

/* Port / low-level IO */
NBResult NEXT_GetDeviceIO(NBDeviceIO *io);

void NEXT_ResetLow(void);
void NEXT_ResetHigh(void);
void NEXT_Select(void);
void NEXT_Deselect(void);

GPIO_PinState NEXT_AwakeRead(void);
GPIO_PinState NEXT_DataReadyRead(void);

#endif /* NEXT_BIO_PORT_H */
