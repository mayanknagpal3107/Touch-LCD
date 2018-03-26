
/***********************************************************
************************************************************
	
	H File :: LCD Class 
	
************************************************************
************************************************************/
#ifndef LCD
#define LCD 1
/*
#include "Delay_Class.h"

using namespace Delay;
*/
class LCD_Class{
	
	public:
		//////		LCD Functions		//////
		void 	Lcd_Init();
		void	Show_Text			(int xpos, int ypos,char *data,unsigned char*_font,int COLOR); 
		void	Show_Char			(int xpos, int ypos,unsigned char Char,unsigned char*_font,int COLOR);
		void    Show_Aligned_Text	(int lt, int rt,int top,int bot,unsigned char*_font,char *text,int align,int COLOR);
		void  	Clear_Screen		(int color);
		void 	Draw_Line			(int x1, int y1,int x2,int y2,int color);
		void  	Draw_Rect			(int xpos,int ypos, int length, int breadth, int color);
	//	void    Draw_Triangle		(int x,int y,int base,int height,int color);
	//	void    Draw_Triangle_Invert(int x,int y,int base,int height,int color);
		void  	Fill_Rect			(int xpos,int ypos, int length, int breadth, int color);
		void 	Draw_Rou_Rect		(int xpos,int ypos,int length,int breadth,int radius, int color);
	//	void  	Draw_Circle			(int xpos,int ypos,int radius,int color);
		void  	Draw_Table			(int x,int y,int row, int column, int height,int width,int color);
		void  	Goto_xy				(int xpos,int ypos);
				
};

void LCD_Class :: Lcd_Init(){

	LCD_Reset(); 
	//LCD_Clear(WHITE);
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////				LCD FUNCTIONS		//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/***************************************
	
	Function :  Show_data_On_LCD
	
	Parameters:-
	xpos and y position are the starting cordinates of the text/data
	data must be in string format  "........." 
	if clearscreen=1 clear the screen before writing data 
	
***************************************/
void LCD_Class :: Show_Text(int xpos, int ypos,char *data,unsigned char*_font,int COLOR){
	
	Print_Text(xpos,ypos,_font,data,COLOR);
}


void LCD_Class :: Show_Char(int xpos, int ypos,unsigned char Char,unsigned char*_font,int COLOR){
	
	Print_Char(xpos,ypos,_font,Char,COLOR);
}

void LCD_Class :: Show_Aligned_Text(int lt, int rt,int top,int bot,unsigned char*_font,char *text,int align,int COLOR){
	
	LcdFont(_font);
	SetFgColor(COLOR);	
	DrawText(lt,rt,top,bot,text,align);
}

/***************************************
	
	Function : Clear_Screen
	
***************************************/
void LCD_Class :: Clear_Screen(int COLOR){	

	LCD_Clear(COLOR);
}
/***************************************
	
	Function :	Draw_Line
	
	Parameters:-
	(x1,y1) starting point cordinate of the line
	(x2,y2) terminating point cordinate of the line
	color must be BLACK 
	comment--range of x cordinate 0-127
	range of y cordinate 0-63 
	
***************************************/
void LCD_Class :: Draw_Line( int x1, int y1,int x2,int y2,int color){

	DRAW_LINE(x1,y1,x2,y2,color);
}
/***************************************
	
	Function : Draw_Rect
	
	Parameters:-
	(xpos,ypos)=upper left cornor cordinate
	length=range in x position
	breadth=range in y position
	color must be BLACK

***************************************/
void LCD_Class :: Draw_Rect( int xpos, int ypos, int length, int breadth, int color)
{
	
	DRAW_RECTANGLE(xpos,ypos,xpos+length,ypos+breadth,color);
}

void LCD_Class :: Fill_Rect( int xpos, int ypos, int length, int breadth, int color)
{
	FILL_RECTANGLE(xpos,ypos,xpos+length,ypos+breadth,color);
	
}


/***************************************
	
	Function : Draw_Rou_Rect
	
	Parameters:-
	(xpos,ypos)=upper left cornor cordinate
	length=range in x position
	breadth=range in y position
	color must be BLACK
	radius= round edges radius (in ticks)

***************************************/
void LCD_Class :: Draw_Rou_Rect(int xpos,int ypos,int length,int breadth,int radius, int color)
{
	DRAW_RRECT(xpos,ypos,xpos+length,ypos+breadth,radius,color,1);
}

/***************************************
	
	Function : Draw_Circle
	
	Parameters:-
	xpos and ypos are the centre of the circle
	radius=radius of the circle in pixels

***************************************/
/*void LCD_Class :: Draw_Circle(int xpos,int ypos,int radius,int color)  
{	
	DRAW_CIRCLE(xpos,ypos,radius,color,1);
}
*/
/***************************************
	
	Function : Draw_Table
	
	Parameters:-
	row=no.of rows
	column= no. of columns
	height= width of each cell( y range)
	width=length of each cell (x range) 

***************************************/
void LCD_Class :: Draw_Table( int x, int y, int rows, int columns, int rowspacing,int columnspacing,int color)
{
	for(int i=0;i<rows+1;i++){
		
		DRAW_LINE(x, (rowspacing*i)+i, x+(columnspacing*columns)+columns, (rowspacing*i)+i, color);
	}
	for(int i=0;i<columns+1;i++){
		
		DRAW_LINE((columnspacing*i)+i, y, (columnspacing*i)+i, y+(rowspacing*rows)+rows, color);
	}	
}
/*
void  LCD_Class :: Draw_Triangle(int x,int y,int base,int height,int color)
{
	DRAW_LINE((x-(base/2)),(y+height),(x+(base/2)),(y+height),color);  // base draw
	DRAW_LINE((x-(base/2)),(y+height),x,y,color);  // left side draw
	DRAW_LINE(x,y,(x+(base/2)),(y+height),color);  // right side draw
}

void  LCD_Class :: Draw_Triangle_Invert(int x,int y,int base,int height,int color)
{
	DRAW_LINE((x-(base/2)),(y-height),(x+(base/2)),(y-height),color);  // base draw
	DRAW_LINE((x-(base/2)),(y-height),x,y,color);  // left side draw
	DRAW_LINE(x,y,(x+(base/2)),(y-height),color);  // right side draw
}
*/
/***************************************
	
	Function : LCD_Goto
	
	Parameters:-
	(xpos,ypos)= desired point cordinate

***************************************/
void LCD_Class :: Goto_xy( int xpos,int ypos)
{
	
	
}


#endif
