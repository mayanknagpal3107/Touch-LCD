#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "uart.h"
#include "uart.c"

#define X_plus 		7
#define X_minus 	6
#define Y_plus 		5
#define Y_minus 	4

unsigned int x=0,y=0;

unsigned int ADCconvert(unsigned char Channel)
{
	unsigned int ADdata,adcprt;
	DDRA &= ~(1<<Channel);
	ADCSRA = (1<<ADEN)|0x07;
	ADMUX = (1<<REFS0)|Channel;
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA&(1<<ADIF)));
	ADCSRA |= (1<<ADIF);
	ADdata = ADCL;
	adcprt = ADCH;
	//ADdata |= (ADCH<<8);
	return ADdata;		
}

int TouchX()
{
	//unsigned int x_return=0;
	
	sbi(DDRA,X_plus);
	sbi(DDRA,Y_plus);
	
	sbi(PORTA,X_plus);
	cbi(PORTA,Y_plus);
	
	sbi(PORTA,X_minus);
	cbi(DDRA,X_minus);
	x = ADCconvert(X_minus);
	return x;
}

int TouchY()
{
	//unsigned int x_return=0;
	
	sbi(DDRA,X_minus);
	sbi(DDRA,Y_minus);
	
	sbi(PORTA,X_minus);
	cbi(PORTA,Y_minus);
	
	sbi(PORTA,Y_plus);
	cbi(DDRA,Y_plus);
	y = ADCconvert(Y_plus);
	return y;
}


int main()
{
	
	char str[3]={0};
	uart_init(UART_BAUD_SELECT(115200,F_CPU));
	while(1)
	{
		//x=TouchX();
		x=TouchX();	
		y=TouchY();		
		_delay_ms(200);
		
		uart_puts("\n\r");
		uart_puts("\nX = ");
		uart_puts(itoa(x,str,10));
		
		uart_puts("\nY = ");
		uart_puts(itoa(y,str,10));
		
		//x=0,y=0;
	}
	return 0;
}































































































































































































































