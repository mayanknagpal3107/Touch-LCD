void get_serial_data(void);
void decode_data(void);

char left[10], right[10], pump[10], front[10], back[10];

unsigned int serial_data[20]={0};
int Start1=0;
int rxlength1=0;
//int storeflag=1;
char str1[10]={0};

void get_serial_data(void)
{

	unsigned int c=0;
	
	c = uart_getc();
	
	if(c & UART_NO_DATA){
		c=0;
	}
	else{
		//  if sync is recieved
		if(c==255 && rxlength1==0){
			
		}		
		//  start storing packet if sync received
		else{
			
			if(rxlength1==5){
				serial_data[rxlength1++] = c;
				
				decode_data();
				serial_data[rxlength1] = 0;
				c=rxlength1;
				//softuart_puts(itoa(rxlength1,buff,10));
				rxlength1=0;
				Start1=0;
				
				return ;
			}
			
			else{
				//softuart_puts(itoa(rxlength1,buff,10));
				serial_data[rxlength1++] = c;
				
			}
		}
	}
	
	return ;	
	
}

void decode_data(){
	
	if(serial_data[0]==100)
	{// command for current status of motors
	/*
		l_crntH=serial_data[1]&0b00000011;
		l_crntL=serial_data[2];
		r_crntH=serial_data[3]&0b00000011;
		r_crntL=serial_data[4];
		p_crntH=serial_data[5]&0b00000011;
		p_crntL=serial_data[6];
		fBrsh_crntH=serial_data[7]&0b00000011;
		fBrsh_crntL=serial_data[8];
		bBrsh_crntH=serial_data[9]&0b00000011;
		bBrsh_crntL=serial_data[10];
		
		l_crnt=(l_crntH*256)+l_crntL;
		r_crnt=(r_crntH*256)+r_crntL;
		p_crnt=(p_crntH*256)+p_crntL;
		fBrsh_crnt=(fBrsh_crntH*256)+fBrsh_crntL;
		bBrsh_crnt=(bBrsh_crntH*256)+bBrsh_crntL;
	*/
		
		unsigned int flag=0;
	
		itoa((int)((serial_data[1]-127)/5),left,10);
		itoa((int)((serial_data[2]-127)/5),right,10);
		itoa((int)((serial_data[3]-127)/5),pump,10);
		itoa((int)((serial_data[4]-127)/5),front,10);
		itoa((int)((serial_data[5]-127)/5),back,10);
		
		FILL_RECTANGLE(205,33,310,145,WHITE);
		FILL_RECTANGLE(265,150,310,230,WHITE);
		FILL_RECTANGLE(5,158,310,230,WHITE);
		
	//	LCD_Clear(WHITE);
	//	Print_Text(10,5,ft18x34,"CURRENT STATUS IN MOTORS",RED);
		
	//	Print_Text(10,30,ft18x34,"Left Motor        :",BLUE);
//		itoa(l_crnt,str1,10);

		if(serial_data[1]>182 || serial_data[1]<75 )
		{Print_Text(210,30,ft18x34,left,RED);
		flag=1;
		}
		else{Print_Text(210,30,ft18x34,left,GREEN);}
		
		
	//	Print_Text(10,50,ft18x34,"Right Motor       :",BLUE);
//		itoa(r_crnt,str1,10);
		
		if(serial_data[2]>182 || serial_data[2]<75)
		{Print_Text(210,50,ft18x34,right,RED);
		flag=1;
		}
		else{Print_Text(210,50,ft18x34,right,GREEN);}
		
		
	//	Print_Text(10,70,ft18x34,"Pump Motor        :",BLUE);
//		itoa(p_crnt,str1,10);
		if(serial_data[3]>240 || serial_data[3]<16 )
		{Print_Text(210,70,ft18x34,pump,RED);
		flag=1;
		}
		else
		{Print_Text(210,70,ft18x34,pump,GREEN);
		}
		
	//	Print_Text(10,90,ft18x34,"Front Brush Motor :",BLUE);
//		itoa(fBrsh_crnt,str1,10);
		Print_Text(210,90,ft18x34,front,GREEN);
		
		
	//	Print_Text(10,110,ft18x34,"Back Brush Motor  :",BLUE);
//		itoa(bBrsh_crnt,str1,10);
		Print_Text(210,110,ft18x34,back,GREEN);
		
		FILL_RECTANGLE(220,95,310,135,WHITE);
		
		Print_Text(10,150,ft18x34,"Overall SYSTEM  HEALTH :",BLUE);
		
	//	Print_Text(10,150,ft18x34,"Overall SYSTEM  HEALTH :",MAGENTA);
		if(flag==1)
		{Print_Text(265,150,ft18x34,"ALERT HIGH CURRENT",RED);
		flag=0;
		}
		else
		{
		Print_Text(265,150,ft18x34,"GOOD",GREEN);
		}
	}	
}