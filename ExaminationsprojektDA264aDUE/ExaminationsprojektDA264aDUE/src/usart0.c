/*
 * usart0.c
 *
 * For USART communication the TX1 is used. 
 *
 * Created: 2018-02-20 20:07:46
 *  Author: Filip Nilsson
 */ 
#include "asf.h"
#include "usart0.h"
#include "DelayFunctions.h"
#include "createHamming.h"


#define TXEN0 6

#define USART0_BASE_ADDRESS (0x40098000U)
uint32_t *const ptr_USART0_CR = (uint32_t *) (USART0_BASE_ADDRESS + 0x0000U);	//Control register
uint32_t *const ptr_USART0_MR = (uint32_t *) (USART0_BASE_ADDRESS + 0x0004U);	//Mode register
uint32_t *const ptr_USART0_SR = (uint32_t *) (USART0_BASE_ADDRESS + 0x0014U);	//Status register
uint32_t *const ptr_USART0_THR = (uint32_t *) (USART0_BASE_ADDRESS + 0x001CU);	//Transmit holding register
uint32_t *const ptr_USART0_BRGR = (uint32_t *) (USART0_BASE_ADDRESS + 0x0020U);	//Baud-rate generator

void usart0_init(void){
	pmc_enable_periph_clk(ID_USART0);
	*ptr_USART0_CR |= (1u<<TXEN0);					//Enable TXEN.
	*ptr_USART0_MR |= (1<<6) | (1<<7);
	*ptr_USART0_MR &= ~((1<<5) | (1<<4));
	PIOA->PIO_PDR |= (PIO_PA10) | (PIO_PA11);
	*ptr_USART0_BRGR |= (0b1000100010111<<0);			//Set baudrate(1200). CD==0b1000100010111.
}

void usart0_transmit(unsigned char data){
	while(!(*ptr_USART0_SR & (1u<<1)));
	while(!(*ptr_USART0_SR & (1u<<9)));	
		
	*ptr_USART0_THR = data;
}

void usart0_send_Packet(uint8_t addr, unsigned char cmd)
{
	usart0_transmit(addr);//send receiver address
	delayMicroseconds(10000);
 	usart0_transmit(cmd);//send command
 	delayMicroseconds(10000);
}


void usart0_putString(uint8_t addr,char* StringPtr){
	while (*StringPtr != 0x00){
		usart0_send_Packet(addr,*StringPtr);
		delayMicroseconds(10000);
		StringPtr++;
	}	
	
	delayMicroseconds(10000);
}