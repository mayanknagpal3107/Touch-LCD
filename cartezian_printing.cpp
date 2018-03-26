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
#include <math.h>
#include "uart.h"
#include "uart.c"

#include "LCD_FUNCTIONS.c"
#include "Touch_Class.cpp"
#include <compat/deprecated.h>

//#define rad_to_deg 180/M_PI 


Touch_Class	Touch;


int main()								
{
	double x=0,y=0,xbackup,ybackup,r=50,TH=3;
	char str[10]={0};
	
	//y=x*tan(TH);	
	LCD_Reset(); 
	LCD_BL_ON();
	LCD_Clear(BLACK);
	
	Touch.Init_Touch();
	uart_init(UART_BAUD_SELECT(115200,F_CPU));
	//DRAW_LINE(160,120,(unsigned int)r*cos(TH)+160,(unsigned int)r*sin(TH)+120,RED);
	//while(1);
	
	while(1)		//TH<360
	{
		//LCD_Clear(BLACK);
		x=(r*cos((TH*M_PI)/180))*2;
		y=(r*sin((TH*M_PI)/180))*2;
		xbackup = 	(r*cos(((TH-1)*M_PI)/180));
		ybackup	=	(r*sin(((TH-1)*M_PI)/180));
		//if(x<0) x=x+160;
		//if(y<0) y=y+120;
		uart_puts("\n\r\n\r");
		uart_puts("Angle:- ");
		uart_puts(itoa((int)TH,str,10));
		
		DRAW_LINE(160,120,xbackup+160,ybackup+120,BLACK);
		DRAW_LINE(160,120,x+160,y+120,RED);
		//x=10;
		//y=20;
		
		uart_puts("\n");
		uart_puts("X: ");
		uart_puts(itoa(x,str,10));
		uart_puts("\n");
		uart_puts("Y: ");
		uart_puts(itoa(y,str,10));
		
		TH=TH+1;
		if(TH>360) TH = 0;
		//x++;
		//_delay_ms(1);
	}
}