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
#include <compat/deprecated.h>
#include <stdlib.h>
#include "uart.h"
#include "uart.c"

#include "LCD_FUNCTIONS.c"
#include "ft18x34.h"

//#include "Config_Pages.h"
//Touch_Class	Touch;


int main()								
{
	char x=0,y=0,r=50,TH=1,strxy[5]={0};
	//unsigned int x=1, y=1, z=1;
	
	//y=x*tan(TH);
	uart_init(UART_BAUD_SELECT(115200,F_CPU));
	
	LCD_Reset(); 
	LCD_BL_ON();
	LCD_Clear(BLACK);
	Print_Char(10,10,ft18x34,'J',WHITE);
	Print_Char(20,10,ft18x34,'A',WHITE);
	Print_Char(30,10,ft18x34,'Y',WHITE);
	Print_Char(40,10,ft18x34,'D',WHITE);
	Print_Char(50,10,ft18x34,'E',WHITE);
	Print_Char(60,10,ft18x34,'E',WHITE);
	Print_Char(70,10,ft18x34,'P',WHITE);
	
	DRAW_LINE(10,50,500,800,WHITE);
	
	while(1)
	{
			x++;
			if(x>100) x=0; //y=0;}
			
			_delay_ms(20);
	}
}
