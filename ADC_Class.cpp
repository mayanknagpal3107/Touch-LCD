
#include <avr/io.h>
#include <compat/deprecated.h>

#ifndef adc 
#define adc

class ADC_Class{
	
	public:
		unsigned int readADC(int channel);
};


unsigned int ADC_Class :: readADC(int channel){
	
	uint16_t value=0;
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADIF);// Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

	ADMUX = channel;
	
	ADMUX |= (1 << REFS0); // Set ADC reference to internal 2.56v
	//ADMUX |= (1 << REFS1);
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

	ADCSRA |= (1 << ADEN);  // Enable ADC

	for(int i=0;i<2;i++){
		
		ADCSRA |= (1 << ADSC);  // Start A2D Conversions 
			
		 //Wait for conversion to complete
	   while(!(ADCSRA & (1<<ADIF)));
		
	   //Clear ADIF by writing one to it
	   ADCSRA|=(1<<ADIF);	
		
		value = ADCH;
		//value = ADCL+(ADCH<<8);	
	}
	return value;
}

#endif