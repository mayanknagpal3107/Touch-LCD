#include <avr/eeprom.h>
#include "uart.h"

#include "Config_Blocks.cpp"
#include "Touch_Class.cpp"
#include "uart.c"

#define BAUDRATE	 	9600
#define Pwd_Length	 	10
#define  Name_Length	20
// request sent to master

#define OK 	1

#define LOGIN_USER		101		// request for user login
#define ADD_USER		102		// request for adding thumb of user
#define EDIT_USER		103		// request for editing an existing user
#define DELETE_USER		104	 	// request for deleting an existing user
#define ADD_SOUND		106		// request for adding voice tag of a new user
#define ADD_NAME		107		// request for adding name of a new user
#define ERASE_ALL		108		// request to delete all users from memory
#define	OPEN_DOOR		109		// request to open the door
#define CLOSE_DOOR		110		// request to close the door

// response sent from master

#define LOGIN_SUCCESS		21		// response for a successfull login
#define LOGIN_FAILURE 		22		// response for failure in login
#define TIMEOUT				23		// response for failure due to timeout
#define ADD_SUCCESS			30		// user info is sucessfully added
#define ADD_ERROR			31		// error in adding fingerprint
#define	THUMB_SUCCESS		32		// fingerprint is successfully added 
#define	FINGER_EXIST		33		// fingerprint already exist
#define	FINGER_FULL 		34		// fingerprint module memory full
#define SOUND_ADD_SUCCESS 	35
#define DATA_ERASED			36
#define ERASE_ERROR			37
#define THUMB_FAIL			38
#define USER_DELETED		39
#define DEL_ERROR			40
#define SEARCH_RESULT		41
#define NAME_LENGTH			42
#define FP_NOT_FOUND		43


/***********************************************************************************************************
************************************* GLOBAL VARIABLES   *************************************************/

unsigned char Password_Index=0;
unsigned int c,i=0;
unsigned int k=0;
unsigned int arr[5];

unsigned int users_found=0;
int index=0;
int TIME_OUT_FLAG = 0;
char temp[20]={0};
int Change_Password=0;
char USER_NAME[20]={0};
unsigned int Name_Size = 0;
int flag_sound_recording_started = 0;
int global_interrupt=0;
int global_Light=0;

char buffer[20];
//char buffer[20]={0};
int base_angle=90;
int shoulder_angle=90;
int elbow_angle=90;
int wrist_angle=90;
int gripper_angle=90;
int rot_angle=0;
int angle=0;
int flag=0;
unsigned int angle_H=0;
unsigned int angle_L=0;
int autosteps=1;
#define speed 25
#define delay 50

/**********************************************************************************************************/

class Device_Class : public Config_Blocks,public Touch_Class{

/***** PUBLIC FUNCTIONS CAN BE ACCESSED BY OTHER FUNCTIONS OUTSIDE THE FILE IN WHICH THEY ARE DEFINED ********/
		
	public:
	
	
	void 	Print_Start() ;
	void	Device_Init() ;
	void 	default_page();
	void 	Print_Pad_Status(char*);
	int 	Read_Pad(char *input,char* Text,int Fontcolor,int Backcolor,int length,int mod);
	void	Device_Run()  ;
	void	RobotLogin();
   	void	Run_AdminLogin();	
	void	sendData(int command,int payload1,int payload2);
	int 	Check_MasterResponsePacket();
	int 	Validate_Password( char* password);
	void	Change_AdminPassword();
	int		Access_UserInfo();
	void	Erase_All();
	void	Add_NewUser();
	void	Get_UserName(unsigned int length);
	void    ShoulderLogin();
	void    CameraLogin();
	void    SoundLogin(); 
	void    LightLogin();
	void	SendDataLight1();
	void    SendDataLight2();
	void    set_control_page();
	void    send_command_servoMotor();
	void 	send_command_dcMotor();
	void 	auto_adjust();
	
};


/*
void Device_Class :: sendData(int command1,int payload,int command2)
{

	uart_putc(255);
	uart_putc(command1);
	uart_putc(payload);
	uart_putc(command2);
	uart_putc(255);
	
}




void Device_Class :: SendDataLight1()

{
  //int l=0;
  //int l1;
  //while(1)
  //{
    if((global_Light>=0)&&(global_Light<250))
	{
     global_Light=global_Light+25;
    
  //}	
	uart_putc(255);
	uart_putc(189);
	uart_putc(global_Light);
	uart_putc(189);
	uart_putc(255);
  }	
 // return;
}

void Device_Class :: SendDataLight2()

{
  //int l=0;
  //int l1;
  //while(1)
  //{
    if((global_Light<=255)&&(global_Light>=24))
	{
     global_Light=global_Light-25;
    
  //}	
	uart_putc(255);
	uart_putc(189);
	uart_putc(global_Light);
	uart_putc(189);
	uart_putc(255);
  }	
 // return;
}


/***********************************************************************************************************
**************************** printed when FP_LOCK LCD boots ***************************************************/

void Device_Class :: Print_Start(){

/*
	LCD_Clear(WHITE);

	Show_Text(130,40,"GRIDBOTS",ft18x34,RED);

	Show_Text(80,100,"MOTOR CONTROLLER",ft18x34,GREEN5);
	Show_Text(80,190,"www.charles14.com",ft18x34,BLUE);
	
	wait_ms(1000);
	
	LCD_Clear(WHITE);
	Show_Text(140,60,"IDP",ft18x34,RED);
	Show_Text(60,100,"COMMON APPLICATIONS",ft18x34,GREEN5);
	Show_Text(100,190,"AHMEDABAD",ft18x34,BLUE);
	
	wait_ms(1000);
*/

	LCD_Clear(WHITE);

	Show_Text(115,110,"WELCOME",ft18x34,RED);
	
	_delay_ms(2000);

	LCD_Clear(WHITE);

	Show_Text(30,10,"UnderWater Robot Controller",ft18x34,RED);
	Show_Text(150,60,"by",ft18x34,GREEN);
	Show_Text(50,110,"GRIDBOTS TECHNOLOGIES",ft18x34,BLUE);
	Show_Text(110,160,"Pvt. Ltd.",ft18x34,BLUE);
	
	_delay_ms(2000);


}

/********************************************************************
Device_Class ::  Device_Init() function
	
	- initialize lcd, touchscreen, uart and print device info 
**********************************************************************/

void Device_Class:: Device_Init(){
	
	Lcd_Init();
	LCD_BL_ON();
	uart_init( UART_BAUD_SELECT(115200,F_CPU) );
	
	sei();
	_delay_ms(100);
	uart_puts("start");
	
	wait_ms(100);	
	
	//Init_Touch();	
	Print_Start();
	wait_ms(1000);
}



void Device_Class :: set_control_page(){


      LCD_Clear(WHITE);
//	 Make_Box(int theme,int x,int y,int width,int height,int boxcolor,char* text,unsigned char *font,int alignment,int fontcolor);
	Show_Text(1,40,"GRIDBOTS TECHNOLOGIES PVT. LTD.",ft18x34,RED);

	Show_Text(50,70,"HANDHELD CONTROLLER",ft18x34,GREEN5);
	
    Make_Box(THEME_3,70,140,180,40,BLUE,"INIT",ft18x34,ALINE_CENTER,YELLOW);//shoulder
	
	
}

long int count=50;
int direction=1;
int dc_direction=1;
void Device_Class ::send_command_servoMotor(){
	
	while(1){
		
		if(Sense_Touch())
		{
			//count=50;

			if(Check_Coordinates(45,50,95,90) )//ANG+
			{
				
				
				//itoa(count,buffer,10);
				//Make_Box(THEME_3,120,50,60,50,BLACK,(char*)buffer,ft18x34,ALINE_CENTER,YELLOW);
				
				end:
				Make_Box(THEME_2,10,50,30,40,RED,"0",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,45,50,50,40,GREEN,"ANG+",ft18x34,ALINE_CENTER,WHITE);
				//Make_Box(THEME_3,120,50,60,50,BLUE,"50",ft18x34,ALINE_CENTER,YELLOW);
				Make_Box(THEME_2,100,50,50,40,BLUE,"NUT",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,155,50,50,40,RED,"ANG-",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,210,50,50,40,RED,"180",ft18x34,ALINE_CENTER,WHITE);
				_delay_ms(100);
				uart_putc('+');
				
			}
			
			if(Check_Coordinates(155,50,205,90) )//ANG-
			{
				//count--;
				Make_Box(THEME_2,10,50,30,40,RED,"0",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,45,50,50,40,RED,"ANG+",ft18x34,ALINE_CENTER,WHITE);
				//Make_Box(THEME_3,120,50,60,50,BLUE,"50",ft18x34,ALINE_CENTER,YELLOW);
				Make_Box(THEME_2,100,50,50,40,BLUE,"NUT",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,155,50,50,40,GREEN,"ANG-",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,210,50,50,40,RED,"180",ft18x34,ALINE_CENTER,WHITE);

				//itoa(count,buffer,10);
				//Make_Box(THEME_3,120,50,60,50,BLACK,(char*)buffer,ft18x34,ALINE_CENTER,YELLOW);
				
				//end1:
				
				_delay_ms(100);
				uart_putc('-');
				
			}
			
			if(Check_Coordinates(100,50,150,90) )//NEUTRAL
			{
				//count--;
				Make_Box(THEME_2,10,50,30,40,RED,"0",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,45,50,50,40,RED,"ANG+",ft18x34,ALINE_CENTER,WHITE);
				//Make_Box(THEME_3,120,50,60,50,BLUE,"50",ft18x34,ALINE_CENTER,YELLOW);
				Make_Box(THEME_2,100,50,50,40,GREEN,"NUT",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,155,50,50,40,RED,"ANG-",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,210,50,50,40,RED,"180",ft18x34,ALINE_CENTER,WHITE);
				//itoa(count,buffer,10);
				//Make_Box(THEME_3,120,50,60,50,BLACK,(char*)buffer,ft18x34,ALINE_CENTER,YELLOW);
				
				//end1:
				
				_delay_ms(100);
				uart_putc('0');
				
			}
			
			if(Check_Coordinates(10,50,40,90) )//0deg
			{
				//count--;
				Make_Box(THEME_2,10,50,30,40,GREEN,"0",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,45,50,50,40,RED,"ANG+",ft18x34,ALINE_CENTER,WHITE);
				//Make_Box(THEME_3,120,50,60,50,BLUE,"50",ft18x34,ALINE_CENTER,YELLOW);
				Make_Box(THEME_2,100,50,50,40,BLUE,"NUT",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,155,50,50,40,RED,"ANG-",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,210,50,50,40,RED,"180",ft18x34,ALINE_CENTER,WHITE);
				//itoa(count,buffer,10);
				//Make_Box(THEME_3,120,50,60,50,BLACK,(char*)buffer,ft18x34,ALINE_CENTER,YELLOW);
				
				//end1:
				
				_delay_ms(100);
				uart_putc('o');
				
			}
			
			if(Check_Coordinates(210,50,260,90) )//180deg
			{
				//count--;
				Make_Box(THEME_2,10,50,30,40,RED,"0",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,45,50,50,40,RED,"ANG+",ft18x34,ALINE_CENTER,WHITE);
				//Make_Box(THEME_3,120,50,60,50,BLUE,"50",ft18x34,ALINE_CENTER,YELLOW);
				Make_Box(THEME_2,100,50,50,40,BLUE,"NUT",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,155,50,50,40,RED,"ANG-",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,210,50,50,40,GREEN,"180",ft18x34,ALINE_CENTER,WHITE);
				//itoa(count,buffer,10);
				//Make_Box(THEME_3,120,50,60,50,BLACK,(char*)buffer,ft18x34,ALINE_CENTER,YELLOW);
				
				//end1:
				
				_delay_ms(100);
				uart_putc('z');
				
			}
			
			
            if(Check_Coordinates(200,180,680,210) ){//back{
			
				Make_Box(THEME_3,200,180,80,40,RED,"BACK",ft18x34,ALINE_CENTER,WHITE);
				Halt_Till_Touch_Release();
				
				Device_Run();
				break;
			}
		
			
		}
	}
}


void Device_Class ::send_command_dcMotor(){
	
	while(1){
		
		if(Sense_Touch())
		{

			if(Check_Coordinates(40,40,140,80) )//fwd
			{
				Make_Box(THEME_2,130,120,60,40,BLUE,"STOP",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,40,40,100,40,GREEN,"fwd",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,180,40,120,40,RED,"back",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,60,120,50,40,RED,"right",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,210,120,40,40,RED,"left",ft18x34,ALINE_CENTER,WHITE);
				uart_putc('f');
				//uart_putc(103);
				//uart_putc(96);
				//uart_putc(01);
				//uart_putc(255);
				//uart_putc(direction);
				//uart_putc(255);
			}
			
			if(Check_Coordinates(180,40,300,80) )//back
			{
				Make_Box(THEME_2,130,120,60,40,BLUE,"STOP",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,40,40,100,40,RED,"fwd",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,180,40,120,40,GREEN,"back",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,60,120,50,40,RED,"right",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,210,120,40,40,RED,"left",ft18x34,ALINE_CENTER,WHITE);
				uart_putc('b');
				//uart_putc(103);
				//uart_putc(96);
				//uart_putc(02);
				//uart_putc(255);
			}
			
			if(Check_Coordinates(100,120,190,160) )//STOP
			{
				Make_Box(THEME_2,130,120,60,40,GREEN,"STOP",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,40,40,100,40,RED,"fwd",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,180,40,120,40,RED,"back",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,60,120,50,40,RED,"right",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,210,120,40,40,RED,"left",ft18x34,ALINE_CENTER,WHITE);
				uart_putc('s');
				//uart_putc(103);
				//uart_putc(00);
				//uart_putc(00);
				//uart_putc(255);
			}
			if(Check_Coordinates(60,120,110,160) )//right
			{
				Make_Box(THEME_2,130,120,60,40,BLUE,"STOP",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,40,40,100,40,RED,"fwd",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,180,40,120,40,RED,"back",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,60,120,50,40,GREEN,"right",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,210,120,40,40,RED,"left",ft18x34,ALINE_CENTER,WHITE);
				uart_putc('r');
				//uart_putc(103);
				//uart_putc(00);
				//uart_putc(00);
				//uart_putc(255);
			}
			if(Check_Coordinates(210,120,250,160) )//left
			{
				Make_Box(THEME_2,130,120,60,40,BLUE,"STOP",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,40,40,100,40,RED,"fwd",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,180,40,120,40,RED,"back",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,60,120,50,40,RED,"right",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_2,210,120,40,40,GREEN,"left",ft18x34,ALINE_CENTER,WHITE);
				uart_putc('l');
				//uart_putc(103);
				//uart_putc(00);
				//uart_putc(00);
				//uart_putc(255);
			}
			
			if(Check_Coordinates(200,180,680,210) ){//clock{
			
				Make_Box(THEME_3,200,180,80,40,RED,"BACK",ft18x34,ALINE_CENTER,WHITE);
				Halt_Till_Touch_Release();
				
				Device_Run();
				break;
			}
		
			
		}
	}
}

void Device_Class ::auto_adjust(){

	while(1){
		
		if(Sense_Touch())
		{
			//autosteps=36;
			/*if(Check_Coordinates(20,50,100,90) )//steps+
			{
				
				autosteps++;
				/*if(autosteps>){
					Make_Box(THEME_3,120,50,60,50,BLUE,"LIMIT",ft18x34,ALINE_CENTER,YELLOW);
					goto end2;
				}
				
				itoa(autosteps,buffer,10);
				Make_Box(THEME_3,120,50,60,50,BLACK,(char*)buffer,ft18x34,ALINE_CENTER,YELLOW);
				
				end2:
				Make_Box(THEME_3,20,50,80,40,BLUE,"STEPS+",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_3,200,50,80,40,RED,"STEPS-",ft18x34,ALINE_CENTER,WHITE);
				
				//unsigned char aa=autosteps;
				
				eeprom_write_byte((uint8_t*)1,autosteps);
				_delay_ms(100);
			/*	uart_putc(255);
				uart_putc(104);
				uart_putc(autosteps);
				uart_putc(00);
				uart_putc(255);
			}
			
			if(Check_Coordinates(200,50,280,90) )//steps-
			{
				autosteps--;
				
				if(autosteps<0){
					Make_Box(THEME_3,120,50,60,50,BLUE,"LIMIT",ft18x34,ALINE_CENTER,YELLOW);
					goto end1;
				}
				
				itoa(autosteps,buffer,10);
				Make_Box(THEME_3,120,50,60,50,BLACK,(char*)buffer,ft18x34,ALINE_CENTER,YELLOW);
				
				end1:
				Make_Box(THEME_3,20,50,80,40,RED,"STEPS+",ft18x34,ALINE_CENTER,WHITE);
								
				Make_Box(THEME_3,200,50,80,40,BLUE,"STEPS-",ft18x34,ALINE_CENTER,WHITE);

				//unsigned char bb=autosteps;
				eeprom_write_byte((uint8_t*)1,autosteps);
				_delay_ms(100);
				/*uart_putc(255);
				uart_putc(104);
				uart_putc(autosteps);
				uart_putc(00);
				uart_putc(255);*/
			}
			
			
            if(Check_Coordinates(200,180,680,220) ){//back{
			
				Make_Box(THEME_3,200,180,80,40,RED,"BACK",ft18x34,ALINE_CENTER,WHITE);
				Halt_Till_Touch_Release();
				
				Device_Run();
				break;
			}
			/*if(Check_Coordinates(50,180,130,220) ){//back{
				
				int rd_steps=eeprom_read_byte((uint8_t*)1);
			
				//Make_Box(THEME_3,50,180,80,40,RED,"START",ft18x34,ALINE_CENTER,WHITE);
				Make_Box(THEME_3,50,180,80,40,RED,"START",ft18x34,ALINE_CENTER,WHITE);
				itoa(rd_steps,buffer,10);
				Make_Box(THEME_3,120,50,60,50,BLACK,(char*)buffer,ft18x34,ALINE_CENTER,YELLOW);
				//Halt_Till_Touch_Release();
				uart_putc(255);
				uart_putc(104);
				uart_putc(rd_steps);
				uart_putc(00);
				uart_putc(255);
				
				//Device_Run();
				//break;
			}
			if(Check_Coordinates(200,180,680,210) ){//clock{
			
				Make_Box(THEME_3,200,180,80,40,RED,"BACK",ft18x34,ALINE_CENTER,WHITE);
				Halt_Till_Touch_Release();
				
				Device_Run();
				break;
			}*/
			
		
	}

	
}
/**************************************************

	Function : Device_Run()

**************************************************/

void Device_Class :: Device_Run()
{

	
     LCD_Clear(WHITE);
//	 Make_Box(int theme,int x,int y,int width,int height,int boxcolor,char* text,unsigned char *font,int alignment,int fontcolor);
	//Show_Text(1,40,"GRIDBOTS TECHNOLOGIES PVT. LTD.",ft18x34,RED);

	//Show_Text(50,70,"HANDHELD CONTROLLER",ft18x34,GREEN5);

    Make_Box(THEME_3,70,40,180,40,BLUE,"AUTO",ft18x34,ALINE_CENTER,YELLOW);//shoulder

    Make_Box(THEME_3,70,140,180,40,BLUE,"MANUAL",ft18x34,ALINE_CENTER,YELLOW);//shoulder
	
	while(1)
	{
	
	if(Sense_Touch())
	{

				
				if(Check_Coordinates(70,140,250,180) )//init
				{
					 Make_Box(THEME_3,70,140,180,40,YELLOW,"MANUAL",ft18x34,ALINE_CENTER,BLUE);//
					 _delay_ms(100);
                       LCD_Clear(OFF_WHITE);
					//Halt_Till_Touch_Release();
					flag=1;
					//wait_ms(200);
				    
					Make_Box(THEME_3,70,70,180,40,BLUE,"SERVO MOTOR",ft18x34,ALINE_CENTER,WHITE);
					Make_Box(THEME_3,70,150,180,40,BLUE,"DC MOTOR",ft18x34,ALINE_CENTER,WHITE);
					//Make_Box(THEME_3,200,180,80,40,RED,"BACK",ft18x34,ALINE_CENTER,WHITE);
					while(1)
					{
					
						if(Sense_Touch())
						{

					
							if(Check_Coordinates(70,70,250,110) )//stepper
							{
								//buffer=0;
								Make_Box(THEME_3,70,70,180,40,GREEN,"SERVO MOTOR",ft18x34,ALINE_CENTER,WHITE);
								_delay_ms(100);
								LCD_Clear(OFF_WHITE);
								
								Make_Box(THEME_2,10,50,30,40,RED,"0",ft18x34,ALINE_CENTER,WHITE);
								Make_Box(THEME_2,45,50,50,40,RED,"ANG+",ft18x34,ALINE_CENTER,WHITE);
								//Make_Box(THEME_3,120,50,60,50,BLUE,"50",ft18x34,ALINE_CENTER,YELLOW);
								Make_Box(THEME_2,100,50,50,40,BLUE,"NUT",ft18x34,ALINE_CENTER,WHITE);
								Make_Box(THEME_2,155,50,50,40,RED,"ANG-",ft18x34,ALINE_CENTER,WHITE);
								Make_Box(THEME_2,210,50,50,40,RED,"180",ft18x34,ALINE_CENTER,WHITE);
								
								//Make_Box(THEME_3,40,120,100,40,RED,"CLOCK",ft18x34,ALINE_CENTER,WHITE);
								//Make_Box(THEME_3,180,120,120,40,RED,"ANTI-CLOCK",ft18x34,ALINE_CENTER,WHITE);
								Make_Box(THEME_3,200,180,80,40,BLUE,"BACK",ft18x34,ALINE_CENTER,WHITE);
								send_command_servoMotor();
								
							}
							
							
							
							
							if(Check_Coordinates(70,150,250,190) )//DC motor
							{
								Make_Box(THEME_3,70,150,180,40,GREEN,"DC MOTOR",ft18x34,ALINE_CENTER,WHITE);
								
								_delay_ms(100);
								LCD_Clear(OFF_WHITE);
								
												
								//Make_Box(THEME_3,40,40,100,40,BLUE,"MOVE",ft18x34,ALINE_CENTER,WHITE);
								Make_Box(THEME_2,130,120,60,40,BLUE,"STOP",ft18x34,ALINE_CENTER,WHITE);
								Make_Box(THEME_2,40,40,100,40,RED,"fwd",ft18x34,ALINE_CENTER,WHITE);
								Make_Box(THEME_2,180,40,120,40,RED,"back",ft18x34,ALINE_CENTER,WHITE);
								Make_Box(THEME_2,60,120,50,40,RED,"right",ft18x34,ALINE_CENTER,WHITE);
								Make_Box(THEME_2,210,120,40,40,RED,"left",ft18x34,ALINE_CENTER,WHITE);
								Make_Box(THEME_2,200,180,80,40,BLUE,"BACK",ft18x34,ALINE_CENTER,WHITE);
								send_command_dcMotor();
							}
							
								
						}

					}
					//Make_Box(THEME_3,10,130,180,40,BLUE,"GRIPPER",ft18x34,ALINE_CENTER,YELLOW);//elbow
					//Make_Box(THEME_3,10,190,180,40,BLUE,"BASE",ft18x34,ALINE_CENTER,YELLOW);//elbow
					
					
						
				}
				if(Check_Coordinates(70,40,250,80) ){// auto
					 Make_Box(THEME_3,70,40,180,40,YELLOW,"AUTO",ft18x34,ALINE_CENTER,BLUE);//shoulder
					
					  LCD_Clear(OFF_WHITE);
					  
					  
					Show_Text(50,30,"APRIL FOOL",ft18x34,RED);
					
					//Make_Box(THEME_3,20,50,80,40,RED,"STEPS+",ft18x34,ALINE_CENTER,WHITE);
								
					//Make_Box(THEME_3,120,50,60,50,BLUE,"1",ft18x34,ALINE_CENTER,YELLOW);
								
					//Make_Box(THEME_3,200,50,80,40,RED,"STEPS-",ft18x34,ALINE_CENTER,WHITE);
															
					//Make_Box(THEME_3,50,180,80,40,RED,"START",ft18x34,ALINE_CENTER,WHITE);
					Make_Box(THEME_3,200,180,80,40,RED,"BACK",ft18x34,ALINE_CENTER,WHITE);
					auto_adjust();
					
				}
				
				
			
        }
		
	}	
  return;
}


/*if(Check_Coordinates(270,140,310,170) )//elbow-
				{
					Make_Box(THEME_3,270,140,40,30,CYAN,"-",ft18x34,ALINE_CENTER,WHITE);
					

					elbow_angle-=10;
					if(elbow_angle<0){
						Make_Box(THEME_3,270,90,40,30,RED,"X",ft18x34,ALINE_CENTER,YELLOW);
                        goto dd;
					}
					else{
						itoa(elbow_angle,buffer,10);
						Make_Box(THEME_3,270,90,40,30,RED,(char*)buffer,ft18x34,ALINE_CENTER,YELLOW);
					}
					uart_putc(255);
		            uart_putc(03);
		            uart_putc(elbow_angle);
		            uart_putc(50);
		            uart_putc(50);
		            uart_putc(255);
					dd:
					Halt_Till_Touch_Release();
					Make_Box(THEME_3,270,140,40,30,BLUE,"-",ft18x34,ALINE_CENTER,WHITE);
					//RobotLogin();
					wait_ms(200);
				    
						
				}
				if(Check_Coordinates(100,60,150,90) )//wrist+
				{
					Make_Box(THEME_3,100,60,50,30,CYAN,"+",ft18x34,ALINE_CENTER,WHITE);//wrist+
					
					wrist_angle+=10;
					if(wrist_angle>180){
						Make_Box(THEME_3,100,60,50,30,RED,"X",ft18x34,ALINE_CENTER,WHITE);//wrist+
                        goto cc;
					}
					else{
						itoa(wrist_angle,buffer,10);
						Make_Box(THEME_3,100,60,50,30,CYAN,(char*)buffer,ft18x34,ALINE_CENTER,BLACK);//wrist+
					}
					uart_putc(255);
		            uart_putc(05);
		            uart_putc(wrist_angle);
		            uart_putc(50);
		            uart_putc(50);
		            uart_putc(255);

					cc:
					
					Halt_Till_Touch_Release();
					Make_Box(THEME_3,100,60,50,30,BLUE,"+",ft18x34,ALINE_CENTER,WHITE);//wrist+
					//RobotLogin();
					wait_ms(200);
				    
					
					
						
				}
				if(Check_Coordinates(170,60,220,90) )//wrist-
				{
					Make_Box(THEME_3,170,60,50,30,CYAN,"-",ft18x34,ALINE_CENTER,WHITE);//wrist-
					
					wrist_angle-=10;
					if(wrist_angle<0){
						Make_Box(THEME_3,100,60,50,30,RED,"X",ft18x34,ALINE_CENTER,BLACK);//wrist+
                        goto bb;
					}
					else{
						itoa(wrist_angle,buffer,10);
						Make_Box(THEME_3,100,60,50,30,CYAN,(char*)buffer,ft18x34,ALINE_CENTER,BLACK);//wrist+
					}
					uart_putc(255);
		            uart_putc(05);
		            uart_putc(wrist_angle);
		            uart_putc(50);
		            uart_putc(50);
		            uart_putc(255);

                    bb:
					
					Halt_Till_Touch_Release();
					Make_Box(THEME_3,170,60,50,30,BLUE,"-",ft18x34,ALINE_CENTER,WHITE);//wrist-
					//RobotLogin();
					wait_ms(200);
				    
					
					
						
				}
				if(Check_Coordinates(100,120,150,150) )//gripper+
				{
					Make_Box(THEME_3,100,120,50,30,CYAN,"+",ft18x34,ALINE_CENTER,WHITE);//wrist+
					
					gripper_angle+=10;
					if(gripper_angle>180){
						Make_Box(THEME_3,100,120,50,30,RED,"X",ft18x34,ALINE_CENTER,BLACK);//wrist+
                        goto sk;
					}
					else{
						itoa(gripper_angle,buffer,10);
						Make_Box(THEME_3,100,120,50,30,CYAN,(char*)buffer,ft18x34,ALINE_CENTER,BLACK);//wrist+
					}
					uart_putc(255);
		            uart_putc(04);
		            uart_putc(gripper_angle);
		            uart_putc(50);
		            uart_putc(50);
		            uart_putc(255);
					sk:
					Halt_Till_Touch_Release();
					Make_Box(THEME_3,100,120,50,30,BLUE,"+",ft18x34,ALINE_CENTER,WHITE);//wrist+
					//RobotLogin();
					wait_ms(200);
				    
					
					
						
				}
				if(Check_Coordinates(170,120,220,150) )//gripper-
				{
					Make_Box(THEME_3,170,120,50,30,CYAN,"-",ft18x34,ALINE_CENTER,WHITE);//wrist-
					
					gripper_angle-=10;
					if(gripper_angle<0){
						Make_Box(THEME_3,100,120,50,30,CYAN,"X",ft18x34,ALINE_CENTER,WHITE);//wrist+
                        goto aa;
					}
					else{
						itoa(gripper_angle,buffer,10);
						Make_Box(THEME_3,100,120,50,30,CYAN,(char*)buffer,ft18x34,ALINE_CENTER,WHITE);//wrist+
					}
					uart_putc(255);
		            uart_putc(04);
		            uart_putc(gripper_angle);
		            uart_putc(50);
		            uart_putc(50);
		            uart_putc(255);
					aa:
					Halt_Till_Touch_Release();
					Make_Box(THEME_3,170,120,50,30,BLUE,"-",ft18x34,ALINE_CENTER,WHITE);//wrist-
					//RobotLogin();
					wait_ms(200);
				    
					
					
						
				}*/
			
				
				

