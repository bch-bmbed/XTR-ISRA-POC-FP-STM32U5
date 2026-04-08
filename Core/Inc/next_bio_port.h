/*
 * next_bio.h
 *
 *  Created on: 8 avr. 2026
 *      Author: benjamin.chalant
 */

#ifndef INC_NEXT_BIO_PORT_H_
#define INC_NEXT_BIO_PORT_H_

#include "main.h"
#include "NBDevices.h"
#include "NBDevice.h"

extern SPI_HandleTypeDef hspi1;

NBResult NEXT_GetDeviceIO(NBDeviceIO *io);

void NEXT_ResetLow(void);
void NEXT_ResetHigh(void);
GPIO_PinState NEXT_AwakeRead(void);
void NEXT_Select(void);
void NEXT_Deselect(void);

#endif /* INC_NEXT_BIO_PORT_H_ */
