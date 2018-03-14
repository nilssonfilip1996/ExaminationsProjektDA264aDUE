/*
 * uart.h
 *
 * Created: 2018-02-20 20:08:06
 *  Author: nilss
 */ 


#ifndef UART_H_
#define UART_H_

void usart0_init(void);
void usart0_transmit(unsigned char data);
void usart0_send_Packet(uint8_t addr, unsigned char cmd);
char usart0_receive(void);
void usart0_putString(uint8_t addr,char* StringPtr);


#endif /* UART_H_ */