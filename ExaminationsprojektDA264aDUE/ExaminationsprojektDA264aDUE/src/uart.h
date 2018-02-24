/*
 * uart.h
 *
 * Created: 2018-02-20 20:08:06
 *  Author: nilss
 */ 


#ifndef UART_H_
#define UART_H_

void uart0_init(void);
void uart0_transmit(unsigned char data);
char uart0_receive(void);
void uart_putString(char* StringPtr);


#endif /* UART_H_ */