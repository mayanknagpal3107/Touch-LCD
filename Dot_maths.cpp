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

	//Print_Text(300,5,ft14x25,"CURRENT STATUS IN MOTORS",WHITE);
	//while(1);	
	while(1)
	{
		y++;
		if(y>100) y=0;
		x=1;
		while(x)
		{
			//LCD_Clear(BLACK);
			x++;
			if(x>100) x=0; //y=0;}
			Print_Char(x,y,ft18x34,'.',WHITE);
			_delay_ms(20);
		}
	}
}