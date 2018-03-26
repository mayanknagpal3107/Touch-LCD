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
#include <math.h>
#include "LCD_FUNCTIONS.c"
#include <compat/deprecated.h>


int main()								
{

//	Device.Device_Init();
//	LCD_Clear(WHITE);
	unsigned int x=1, y=1, z=1;
	LCD_Reset(); 
	LCD_BL_ON();
	LCD_Clear(BLACK);

	//DRAW_RECTANGLE(10,10,50,50,RED);
	FILL_RECTANGLE(10,10,50,50,RED);
	while(1);
}