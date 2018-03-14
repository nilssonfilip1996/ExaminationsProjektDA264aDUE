/*
 * lcdApplication.c
 *
 * Created: 2015-09-10 08:44:50
 *  Author: Filip Nilsson & Jesper Anderberg
 */ 

#include "lcdApplication.h"
#include "LCDFunctions.h"
#include "DelayFunctions.h"


/*Writes a four digit number*/
int lcdWrite4DigitNumber(int number)
{
	/* Write code here */
	char buffer[5];				//Four digits + '\0'.
	itoa(number,buffer,10);		//Converts the int value to a char array.
	char *p=buffer;
	while(*p!='\0'){
		delayMicroseconds(1000);
		lcdWrite(*p, 1);
		p++;
	}
	
	return 0;	/* Assuming everything went ok */
}

int lcdWriteAsciiString(const char *string)
/* writes an ascii string up to 40 characters on the LCD display */
{
	while(*string!='\0'){			//In C the last char in a "String" is '\0'. When this char is found, then we have reached the end of the string.
		delayMicroseconds(1000);
		lcdWrite(*string, 1);
		string++;
		
	} 
	
	return 0;	/* Assuming everything went ok */
}

