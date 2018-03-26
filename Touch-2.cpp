/**********************************************************************************************************
* 

* File name		: main.cpp
* Programmer 	: 
* Note			: 
* Language		: avrGCC
* Hardware		: atmega32
* Date			: 

***********************************************************************************************************/

//#include "Device_Class.cpp"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "uart.h"
#include "uart.c"

#include <math.h>
#include "LCD_FUNCTIONS.c"
#include "Touch_Class.cpp"
#include <compat/deprecated.h>

Touch_Class	Touch;


int main()								
{
	char x=0,y=0,r=50,TH=1,strxy[5]={0};
	
	//y=x*tan(TH);
	uart_init(UART_BAUD_SELECT(115200,F_CPU));
	
	//LCD_Reset(); 
	//LCD_BL_ON();
	//LCD_Clear(BLACK);
	
	Touch.Init_Touch();
	
	while(1)
	{
		uart_puts("hello\n");
		x=Touch.Sense_X_Touch();
		y=Touch.Sense_Y_Touch();
		
		uart_puts(itoa(x,strxy,10));
		uart_puts("\n");
		uart_puts(itoa(y,strxy,10));
		uart_puts("\n");
		uart_puts("\n");
		_delay_ms(200);
	}
}