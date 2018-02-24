/*
 * common.h
 *
 * Created: 2018-02-20 20:11:07
 *  Author: nilss
 */ 


#ifndef COMMON_H_
#define COMMON_H_

#ifndef F_CPU
/* 84 MHz clock speed, needs to be defined before including delay.h */
#define F_CPU 84000000UL
#endif
#include <util/delay.h>

#define BAUD    9600

/* TODO: Define RTC 7-bit slave address */
#define DS1307                  (uint8_t)0x68

/* TODO: Define EEPROM 7-bit slave address */
#define AT24C32                 (uint8_t)0x50

/* Un-comment to activate the ADC-EEPROM Reference Application */
//#define APP_ADC_EEPROM




#endif /* COMMON_H_ */