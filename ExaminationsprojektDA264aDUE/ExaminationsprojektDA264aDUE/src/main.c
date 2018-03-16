/**
* Main-file of the DUE implementation.
* The power of an input signal is computed after given intervals.
* The Power is then seperated into hundreds, tens and singles and sent to a hamming encoder.
* The resulting 8-bit hamming message is then sent through the USART and eventually received by the .
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
#include "conf_tc.h"
#include "adcdac.h"
#include "misc.h"
#include "signalBehandling.h"
#include <fastmath.h>

#define RADDR 0x01		//0x55

char String[]="XHELLO";
uint8_t testaddr[] = {1,0,1,0};
uint32_t sum = 0;
double rms = 0;
uint32_t effekt = 0;
char str1[5];




int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	usart0_init();
	ioport_init();
	delayInit();
	lcdInit();
	configure_tc();
	adc_setup();
	dac_setup();
	//configureConsole();	//Only for debugging purposes.
	//ioport_set_pin_dir(CHECK_PIN, IOPORT_DIR_OUTPUT);
	uint8_t hammingaddr = createHammingCode(testaddr);
	

	while(1){
		
		//printf("offset: %d/n", getDcOffset());
		if(getCounter() >= 100){
			tc_stop(TC0,0);
			int16_t* mvBuff = getMvBuffer();
			for(int i=0; i<100; i++){
				sum = sum + (*(mvBuff +i))*(*(mvBuff +i));
			}
			rms = sqrt(sum/100)/1000;
			sum = 0;
			effekt = 1000*((rms*rms)/10);
			
			uint8_t* singles = getSingles(effekt);
			//printf("singles: %d", singles);
			uint8_t* tens = getTens(effekt);
			uint8_t* hundreds = getHundreds(effekt);
			
			uint8_t hammingSingle = createHammingCode(singles);
			uint8_t hammingTens = createHammingCode(tens);
			uint8_t hammingHundreds = createHammingCode(hundreds);
			//printf("HAMMING SINGLES %d", hammingSingle);
			
			usart0_send_Packet(hammingaddr,hammingHundreds);
			usart0_send_Packet(hammingaddr,hammingTens);
			usart0_send_Packet(hammingaddr,hammingSingle);
			usart0_send_Packet(hammingaddr,0x01);
			
			reset_counter();
			tc_start(TC0,0);
		}
		
		
			//do nothing
// 			uint32_t outval = 35;
// 			uint8_t* singles = getSingles(outval);
// 		//	printf("singles: %d", singles);
//  			uint8_t* tens = getTens(outval);
//  			uint8_t* hundreds = getHundreds(outval);
// 			
// 			uint8_t hammingSingle = createHammingCode(singles);
//  			uint8_t hammingTens = createHammingCode(tens);
//  			uint8_t hammingHundreds = createHammingCode(hundreds);
// 			uint8_t hammingaddr = createHammingCode(testaddr);
// // 			printf("HAMMING SINGLES %d", hammingSingle);
// // 			uint8_t test = createHammingCode(test1);
// 			
// 			usart0_send_Packet(hammingaddr,hammingHundreds);
// 			usart0_send_Packet(hammingaddr,hammingTens);
// 			usart0_send_Packet(hammingaddr,hammingSingle);
			
		}

	}
