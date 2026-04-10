/*
 * next_bio_device.h
 *
 *  Created on: 8 avr. 2026
 *      Author: benjamin.chalant
 */

#ifndef NEXT_BIO_DEVICE_H
#define NEXT_BIO_DEVICE_H

#include "next_bio_port.h"
#include "next_bio_flash.h"

NBResult NEXT_DeviceInit(void);
void NEXT_DeviceDeinit(void);

HNBDevice NEXT_DeviceGetHandle(void);
NBBool NEXT_DeviceIsReady(void);

NBResult NEXT_ApplyCalibrationFromFlash(void);

#endif /* NEXT_BIO_DEVICE_H */
