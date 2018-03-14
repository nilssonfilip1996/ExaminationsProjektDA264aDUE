/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 *
 *Author(s): Filip Nilsson and Jesper Anderberg
 */
#include <asf.h>
#include "usart0.h"
#include "DelayFunctions.h"
#include "LCDFunctions.h"
#include "lcdApplication.h"
#include "createHamming.h"
#include "consoleFunctions.h"

#define RADDR 0x01		//0x55

char String[]="XHELLO";
uint8_t test1[] = {1,0,0,0};
uint8_t test2[] = {0,1,0,0};
uint8_t test3[] = {0,0,1,0};
uint8_t test4[] = {0,0,0,1};
uint8_t testaddr[] = {1,0,1,0};

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	usart0_init();
	ioport_init();
	delayInit();
	lcdInit();
	configureConsole();
	
	ioport_enable_pin(PIO_PB27_IDX);
	ioport_set_pin_dir(PIO_PB27_IDX, IOPORT_DIR_OUTPUT);

	
	while(1){
		uint8_t hammingMSG1 = createHammingCode(test1);
		uint8_t hammingMSG2 = createHammingCode(test2);
		uint8_t hammingMSG3 = createHammingCode(test3);
		uint8_t hammingMSG4 = createHammingCode(test4);
		uint8_t hammingADDR = createHammingCode(testaddr);
 		usart0_send_Packet(hammingADDR,hammingMSG1);
		delayMicroseconds(1000);
		usart0_send_Packet(hammingADDR,hammingMSG2);
 		delayMicroseconds(10000);
		usart0_send_Packet(hammingADDR,hammingMSG3);
		delayMicroseconds(1000);
		lcdClearDisplay();
		usart0_send_Packet(hammingADDR,hammingMSG4);
		delayMicroseconds(10000);
		usart0_send_Packet(hammingADDR,0x20);
		delayMicroseconds(10000);
		//lcdWriteAsciiString("")
		lcdWrite4DigitNumber(1248);
	}

}
