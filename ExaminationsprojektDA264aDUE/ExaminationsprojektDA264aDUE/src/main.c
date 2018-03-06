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

#define RADDR 0x55

char String[]="H";

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	usart0_init();
	ioport_init();
	delayInit();
	
	ioport_enable_pin(PIO_PB27_IDX);
	ioport_set_pin_dir(PIO_PB27_IDX, IOPORT_DIR_OUTPUT);

	
	while(1){
		//usart0_putString(String);
		usart0_send_Packet(RADDR, 'A');
		delayMicroseconds(100000);
	}

}
