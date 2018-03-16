/*
* misc.c
*
* Created: 2018-03-14 17:48:34
*  Author: nilss
*/
#include "asf.h"
uint8_t zero[4] = {0,0,0,0};
uint8_t one[4] = {1,0,0,0};
uint8_t two[4] = {0,1,0,0};
uint8_t three[4] = {1,1,0,0};
uint8_t four[4] = {0,0,1,0};
uint8_t five[4] = {1,0,1,0};
uint8_t six[4] = {0,1,1,0};
uint8_t seven[4] = {1,1,1,0};
uint8_t eight[4] = {0,0,0,1};
uint8_t nine[4] = {1,0,0,1};
	

	


uint8_t *getHundreds(uint32_t outval){
	uint8_t temp =outval%100;
	uint16_t hundreds = outval-temp;
	if (hundreds==000)
	{
		return zero;
	}
	else if(hundreds==100){
		return one;
	}
	else if(hundreds==200){
		return two;
	}
	else if(hundreds==300){
		return three;
	}
	else if(hundreds==400){
		return four;
	}
	else if(hundreds==500){
		return five;
	}
	else if(hundreds==600){
		return six;
	}
	else if(hundreds==700){
		return seven;
	}
	else if(hundreds==800){
		return eight;
	}
	else if(hundreds==900){
		return nine;
	}
}

uint8_t *getSingles(uint32_t outval){
	uint8_t singles = outval%10;
	
		if (singles==0)
		{
			return zero;
		}
		else if(singles==1){
			return one;
		}
		else if(singles==2){
			return two;
		}
		else if(singles==3){
			return three;
		}
		else if(singles==4){
			return four;
		}
		else if(singles==5){
			return five;
		}
		else if(singles==6){
			return six;
		}
		else if(singles==7){
			return seven;
		}
		else if(singles==8){
			return eight;
		}
		else if(singles==9){
			return nine;
		}
}

uint8_t *getTens(uint32_t outval){
	uint8_t temp =outval%100;
	uint8_t singles = outval%10;
	uint8_t tens = (temp -singles)/10;
	
	if (tens==0)
	{
		return zero;
	}
	else if(tens==1){
		return one;
	}
	else if(tens==2){
		return two;
	}
	else if(tens==3){
		return three;
	}
	else if(tens==4){
		return four;
	}
	else if(tens==5){
		return five;
	}
	else if(tens==6){
		return six;
	}
	else if(tens==7){
		return seven;
	}
	else if(tens==8){
		return eight;
	}
	else if(tens==9){
		return nine;
	}
}
