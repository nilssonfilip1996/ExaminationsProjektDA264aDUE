/*
 * uart.c
 *
 * Created: 2018-02-20 20:07:46
 *  Author: nilss
 */ 
#include "asf.h"
#include "usart0.h"
#include "DelayFunctions.h"
#include "createHamming.h"

//define receive parameters
#define SYNC 0XAA// synchro signal


#define TXEN0 6
#define CHRL0 6
#define CHRL1 7

#define USART0_BASE_ADDRESS (0x40098000U)
uint32_t *const ptr_USART0_CR = (uint32_t *) (USART0_BASE_ADDRESS + 0x0000U);	//Control register
uint32_t *const ptr_USART0_MR = (uint32_t *) (USART0_BASE_ADDRESS + 0x0004U);	//Mode register
uint32_t *const ptr_USART0_SR = (uint32_t *) (USART0_BASE_ADDRESS + 0x0014U);	//Status register
uint32_t *const ptr_USART0_THR = (uint32_t *) (USART0_BASE_ADDRESS + 0x001CU);	//Transmit holding register
uint32_t *const ptr_USART0_BRGR = (uint32_t *) (USART0_BASE_ADDRESS + 0x0020U);	//Baud-rate generator

void usart0_init(void){
	pmc_enable_periph_clk(ID_USART0);
	*ptr_USART0_CR |= (1u<<TXEN0);					//Set TXEN.
	*ptr_USART0_MR |= (1<<CHRL1) | (1<<CHRL0);
	*ptr_USART0_MR &= ~((1<<5) | (1<<4));
	PIOA->PIO_PDR |= (PIO_PA10) | (PIO_PA11);
	*ptr_USART0_BRGR |= (0b1000100010111<<0);			//Set baudrate(9600). CD==0b1000100011==546
}

void usart0_transmit(unsigned char data){
	while(!(*ptr_USART0_SR & (1u<<1)));
	while(!(*ptr_USART0_SR & (1u<<9)));	
	
	
			
	*ptr_USART0_THR = data;
}

void usart0_send_Packet(uint8_t addr, unsigned char cmd)
{
// 	usart0_transmit(SYNC);//send synchro byte
// 	delayMicroseconds(10000); 
	usart0_transmit(addr);//send receiver address
	delayMicroseconds(10000);
 	usart0_transmit(cmd);//send command
 	delayMicroseconds(10000);
}


void usart0_putString(uint8_t addr,char* StringPtr){
	while (*StringPtr != 0x00){
		usart0_send_Packet(addr,*StringPtr);
		delayMicroseconds(1000);
		StringPtr++;
	}
	//usart0_send_Packet(addr,0x00);	
	delayMicroseconds(1000);
}