#include <avr/io.h>
#include <compat/deprecated.h>
#include "stdlib.h"
#include "Delay_Class.cpp"
#include "ADC_Class.cpp"

//  lcd size
#define Lcd_X_Pixels	320
#define Lcd_Y_Pixels	240

//  touch pad 8-bit y-axis adc values
#define X_Min	35//40
#define X_Max	230//218 

//  touch pad 8-bit x-axis adc values
#define Y_Min	45//29
#define Y_Max	215//230

//  slope for converting touch values to lcd (128x64) co-ordinates
#define X_Slope		(float)Lcd_X_Pixels/((float)X_Max-(float)X_Min)
#define Y_Slope		(float)Lcd_Y_Pixels/((float)Y_Max-(float)Y_Min)

//  touch screen pin sequence 
//  top to bottom pins as seen from front side(ie. connector on left bottom side)
							//    sequence given by me.
#define Touchx_Pin		7			//  1
#define Touchy_Pin		5			//  2
#define Touchxsupp_Pin	6			//  3
#define Touchysupp_Pin	4 			//  4
#define Touch_DDR	  	DDRA		
#define Touch_PORT  	PORTA		

using namespace Delay;

/**************************************************

	Class : Touch_Class

**************************************************/

class Touch_Class : public virtual ADC_Class{
	
	private:		
	char buff[5];	
		
	public:
		
		//  variables
		int X_Touch;
		int Last_X_Touch;
		int Y_Touch;
		int Last_Y_Touch;
		int ver_X_touch;
		int ver_Y_touch;
		int xadc;
		int yadc;
		
		int X_Notouch;
		int Y_Notouch;	
		
		// functions
		void 	Init_Touch();		
		void 	Set_Notouch();
		int 	Check_Notouch();
		void 	Sense_X_Touch();
		void 	Sense_Y_Touch();
		int 	Sense_Touch();
		int 	Check_Coordinates(int x_down,int x_up,int y_down,int y_up);
		void 	Halt_Till_Touch_Release();
};

/**************************************************

	Function : Init_Touch()

**************************************************/

void Touch_Class :: Init_Touch(){
	
	//  initialize the x axis and y axis
	
	Set_Notouch();	//  set untouch value
}

/**************************************************

	Function : Check_Notouch()

**************************************************/

int Touch_Class :: Check_Notouch(){
	
	//  check if the currently sensed xtouch and ytouch are initial untouch values or not
	if( /***/(/**/(Y_Touch>=(Y_Notouch-2))/**/||/**/(Y_Touch<=(Y_Notouch+2))/**/)/***/ &&  /***/(/**/(X_Touch>=(X_Notouch-2))/**/||/**/(X_Touch<=(X_Notouch+2))/**/)/***/ ){
		return 0;
	}
}

/**************************************************

	Function : Set_Notouch()

**************************************************/

void Touch_Class :: Set_Notouch(){
	
	//   read initial xtouch and ytouc and set as no touch value
	
	wait_ms(500);	
	Sense_Y_Touch();		//  sense ytouch
	Y_Notouch = Y_Touch;
	_delay_ms(1);	
	Sense_X_Touch();		//  sense xtouch
	X_Notouch = X_Touch;
}

/**************************************************

	Function : Sense_X_Touch()
	
	//						   	  	y1
	//							   (+)
	//						   	  
	//						   	    |	
	//						   	    |	
	// 			x1 	   <-----------------------> (-) x2
	//  -to adc for  X-Touch  		|	
	//				   	  			|	
	//				   	  
	//				   	 			y2
	//				   	  		   (-)	
	
**************************************************/

void Touch_Class :: Sense_X_Touch(){

	Touch_DDR &= ~(1<<Touchx_Pin);			//  set x1 as input to read the xtouch value
	//Touch_PORT &= ~(1<<Touchx_Pin);			//  set x1 as input to read the xtouch value
	
	//Touch_PORT &= ~(1<<Touchxsupp_Pin);		//  set x2 as input to drain current;
	Touch_DDR &= ~(1<<Touchxsupp_Pin);		//  set x2 as input to drain current;
	
	Touch_DDR |= (1<<Touchy_Pin)|(1<<Touchysupp_Pin);		// set y1 and y2 as output
	Touch_PORT |= (1<<Touchy_Pin);			//  pull y2 high 
	Touch_PORT &= ~(1<<Touchysupp_Pin);	//  pull y1 low
	
	xadc=readADC(Touchx_Pin); 		//  read adc value from x2 for xtouch
	X_Touch=(float)(xadc-X_Min)*X_Slope;	//  convert adc value into lcd x coordinates 
	//X_Touch=Lcd_X_Pixels-X_Touch;	//  inversing due to reversal of lcd and touchpad
	
}

/**************************************************

	Function : Sense_Y_Touch()
	
	//				   	  y1-to adc for  Y-Touch
	//				   	  
	//				   	  |	
	//				   	  |	
	// x1 (+) <-----------------------> (-) x2
	//				   	  |	
	//				   	  |	
	//				   	  
	//				   	  y2
	//				   	 (-)	
	
**************************************************/

void Touch_Class :: Sense_Y_Touch(){

	Touch_DDR &= ~(1<<Touchy_Pin);			//  set y1 as input to read the xtouch value		
	//Touch_PORT &= ~(1<<Touchy_Pin);			//  set y1 as input to read the xtouch value		
	
	//Touch_PORT &= ~(1<<Touchysupp_Pin);		//  set y2 as input to drain current;
	Touch_DDR &= ~(1<<Touchysupp_Pin);		//  set y2 as input to drain current;
	
	Touch_DDR |= (1<<Touchx_Pin)|(1<<Touchxsupp_Pin);		// set x1 and x2 as output
	Touch_PORT |= (1<<Touchx_Pin);			//  pull x2 high 
	Touch_PORT &= ~(1<<Touchxsupp_Pin);	//  pull x1 low
	
	yadc=readADC(Touchy_Pin);		//  read adc value from y2 for ytouch
	Y_Touch=(float)(yadc-Y_Min)*Y_Slope;	//  convert adc value into lcd y coordinates 
	
	Y_Touch=Lcd_Y_Pixels-Y_Touch;	//  inversing due to reversal of lcd and touchpad
}

/**************************************************

	Function : Sense_Touch()
	
	-	return 1 if valid touch is sensed
	
	:-	check this function continously if sensed then 
		check function Check_Coordinates() for checking 
		co-ordinates 
	
**************************************************/

int Touch_Class :: Sense_Touch(){
	
	Sense_X_Touch();	//  sense xtouch
	_delay_ms(1);
	Sense_Y_Touch();	//  sense ytouch
	
	if( (X_Touch<0 && X_Touch>Lcd_X_Pixels) || (Y_Touch<0 && Y_Touch>Lcd_Y_Pixels)){
		return 0;
	}
	
	//  check if the sensed touch is out of the active area (ie. lcd size) then return 0;
	if(yadc<Y_Min || yadc>Y_Max || xadc<X_Min || xadc>X_Max){
		return 0;
	}
	
	//  check if notouch  is being sensed then return 0
	if(Check_Notouch()){
		return 0;
	}
	else{
		
		_delay_ms(100);		
		Sense_Y_Touch();	//  sense xtouch	
		_delay_ms(1);		
		Sense_X_Touch();	//  sense ytouch
		
		
		 ver_X_touch=X_Touch;
		 ver_Y_touch=Y_Touch;
	
		//  again sense the x and y touch to get correct touch co-ordinates
		_delay_ms(100);		
		Sense_Y_Touch();	//  sense xtouch	
		_delay_ms(1);		
		Sense_X_Touch();	//  sense ytouch
		
		
		if(Check_Notouch())		return 0;
		
		if(abs(ver_X_touch-X_Touch)<=5||abs(ver_Y_touch-Y_Touch)<=5)
		{
			return 1;
		}
		else
		{
			return 0;
		}
		
		
		
	}
	return 1;
}

/**************************************************

	Function : Check_Coordinates()

**************************************************/

int Touch_Class :: Check_Coordinates(int x_down,int y_down,int x_up,int y_up){

	int ret = 0;
	
	//  check if the X co-ordinates are within the sensed touch area 
	if(X_Touch<x_up && X_Touch>x_down){
		ret = 1;
	}
	else{
		return 0;
	}
	
	//  check if the X co-ordinates are within the sensed touch area 
	if(Y_Touch<y_up && Y_Touch>y_down){
		ret = 1;
	}
	else{
		ret = 0;
	}
	
	//  store current touch values as last values
	Last_X_Touch = X_Touch;
	Last_Y_Touch = Y_Touch;
	/*if(ret==1){
		X_Touch=0;
		Y_Touch=0;
	}*/
	
	return ret;
}

/**************************************************

	Function : Halt_Till_Touch_Release()

**************************************************/

void Touch_Class :: Halt_Till_Touch_Release(){
	
	int ret = 1;
	
	while(ret){
		
		Sense_Touch();	//  sense the touch 
		
		//  check if the current touched and last touched values are same 
		// if yes the loop until release
		if( /***/(/**/(Y_Touch<=(Last_Y_Touch-5))/**/||/**/(Y_Touch>=(Last_Y_Touch+5))/**/)/***/ &&  /***/(/**/(X_Touch<=(Last_X_Touch-5))/**/||/**/(X_Touch>=(Last_X_Touch+5))/**/)/***/ ){
			X_Touch=0;
			Y_Touch=0;
			ret = 0;
		}
		else{
			ret = 1;
		}
	}
}


