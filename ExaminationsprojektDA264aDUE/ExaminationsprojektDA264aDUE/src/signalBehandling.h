/*
 * signalBehandling.h
 *
 * Created: 2018-03-14 15:03:45
 *  Author: nilss
 */ 


#ifndef SIGNALBEHANDLING_H_
#define SIGNALBEHANDLING_H_

#define CHECK_PIN PIO_PB26_IDX	//Ardiuno Due pin 22 used to measure work load

void TCO_Handler(void);
uint8_t getCounter(void);
int16_t* getMvBuffer(void);
void reset_counter(void);
uint16_t getDcOffset(void);

#endif /* SIGNALBEHANDLING_H_ */