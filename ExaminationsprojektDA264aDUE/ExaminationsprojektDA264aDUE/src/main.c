/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "uart.h"
#include "DelayFunctions.h"

char String[]="JESPER";

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	uart0_init();
	ioport_init();
	delayInit();
	
	ioport_enable_pin(PIO_PB27_IDX);
	ioport_set_pin_dir(PIO_PB27_IDX, IOPORT_DIR_OUTPUT);

	
	while(1){
		//ioport_set_pin_level(PIO_PB27_IDX, HIGH);
// 		delayMicroseconds(100000);
// 		uart0_transmit('e');
// 		delayMicroseconds(100000);
// 		uart0_transmit('e');
// 		delayMicroseconds(100000);
// 		uart0_transmit('e');
		uart_putString(String);
		delayMicroseconds(100000);
		//uart0_transmit('\n');
 		delayMicroseconds(100000);
 		//uart0_transmit('\r');
		//ioport_set_pin_level(PIO_PB27_IDX, LOW);
		delayMicroseconds(1000);
	}

	/* Insert application code here, after the board has been initialized. */
}
