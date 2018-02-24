/*
 * uart.c
 *
 * Created: 2018-02-20 20:07:46
 *  Author: nilss
 */ 
#include "asf.h"
#include "DelayFunctions.h"

#define UART_BASE_ADDRESS (0x400E0800)
uint32_t *const ptr_UART_CR = (uint32_t *) (UART_BASE_ADDRESS + 0x0000U);	//Control register
uint32_t *const ptr_UART_MR = (uint32_t *) (UART_BASE_ADDRESS + 0x0004U);	//Mode register
uint32_t *const ptr_UART_SR = (uint32_t *) (UART_BASE_ADDRESS + 0x0014U);	//Status register
uint32_t *const ptr_UART_THR = (uint32_t *) (UART_BASE_ADDRESS + 0x001CU);	//Transmit holding register
uint32_t *const ptr_UART_BRGR = (uint32_t *) (UART_BASE_ADDRESS + 0x0020U);	//Baud-rate generator

void uart0_init(void){
	*ptr_UART_CR |= (1u<<6);					//Set TXEN.
	*ptr_UART_BRGR |= (0b1000100011<<0);	//Set baudrate(9600). CD==0b1000100011==546
}

void uart0_transmit(unsigned char data){
	while(!(*ptr_UART_SR & (1u<<1)));
				
	*ptr_UART_THR = data;
}

void uart_putString(char* StringPtr){
	while (*StringPtr != 0x00){
		uart0_transmit(*StringPtr);
		delayMicroseconds(100000);
		StringPtr++;
	}
}