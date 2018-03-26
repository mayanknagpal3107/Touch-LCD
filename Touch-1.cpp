//#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "uart.h"
#include "uart.c"
#include "Touch_Class.cpp"
//#include "Lcd_Class.cpp"
#include "SSD1289.c"
#include "SSD1289.h"

unsigned int x=0,y=0;
Touch_Class	Touch;
//Lcd_Class	LCD;

int main()
{
	char strxy[3]={0};
	uart_init(UART_BAUD_SELECT(115200,F_CPU));
	
	Touch.Init_Touch();
	while(1)
	{
		uart_puts("\nhello\n");
				
	//	x=Touch.Sense_X_Touch();
	//	y=Touch.Sense_Y_Touch();
		//Touch.Halt_Till_Touch_Release();
		
		itoa(x,strxy,10);
		uart_puts(strxy);
		uart_puts("\n");
		itoa(y,strxy,10);
		uart_puts(strxy);
		
		uart_puts("\n");
		_delay_ms(200);
	}
	return 0;
}


























































































































































































































