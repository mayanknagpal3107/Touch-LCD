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
	double x=0,y=0,xbackup=0,ybackup=0,r=110,TH=3;
	char str[10]={0};
	char disx=170,disy=130;
	float dist=250;
	int xdisp=0, ydisp=0;
		
	LCD_Reset(); 
	LCD_BL_ON();
	LCD_Clear(BLACK);

	Touch.Init_Touch();
	uart_init(UART_BAUD_SELECT(115200,F_CPU));
	DRAW_RRECT(10,10,70,70,0,RED,1);
	
	while(1)		
	{
		
		xbackup = x;
		ybackup = y;
		
		x = (r*cos((TH*M_PI)/180));
		y = (r*sin((TH*M_PI)/180));
		
		xdisp = (x*dist/300)+160;
		ydisp = (y*dist/300)+120;
		
		uart_puts("\n\r\n\r");
		uart_puts("Angle:- ");
		itoa((int)TH,str,10);
		uart_puts(str);
		
		DRAW_LINE(160,120,xbackup+160,ybackup+120,BLACK);
		DRAW_LINE(160,120,x+160,y+120,RED);
		DRAW_CIRCLE(xdisp,ydisp,3,RED,0);
		
		Print_Char(10,10,ft18x34,str[0],WHITE);
		Print_Char(50,50,ft18x34,str[1],WHITE);

		uart_puts("\n");
		uart_puts("X: ");
		uart_puts(itoa(x,str,10));
		uart_puts("\n");
		uart_puts("Y: ");
		uart_puts(itoa(y,str,10));
		
		TH=TH+2;
		if(TH>360) TH = 0;
		_delay_ms(100);
	}
}