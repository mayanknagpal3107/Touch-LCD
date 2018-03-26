#undef LCD_8_BIT_MODE
#include <string.h> 
#include <avr/io.h> 		// include I/O definitions (port names, pin names, etc)
#include <util/delay.h>
#include <stdlib.h>
//#include "uart.c"
//#include "uart.h"
#include "SSD1289.h"
#include "SSD1289.c"
//#include "Graphic.h"

#include "ft18x34.h"
#include "font.h"
#include "font.c"


#include <avr/interrupt.h> 

/*************************** define global variables ******************************************/	

	/* These types must be 16-bit, 32-bit or larger integer */
	
	typedef int				INT;
	typedef unsigned int	UINT;

	/* These types must be 8-bit integer */
/*	typedef signed char		CHAR;
	typedef unsigned char	UCHAR;*/
	typedef unsigned char	BYTE;

	/* These types must be 16-bit integer */
/*	typedef short			SHORT;
	typedef unsigned short	USHORT;
	typedef unsigned short	WORD;
	typedef unsigned short	WCHAR;*/

	/* These types must be 32-bit integer */
/*	typedef long			LONG;
	typedef unsigned long	ULONG;
	typedef unsigned long	DWORD;*/

	/* Boolean type */
	typedef enum { FALSE = 0, TRUE } BOOL;
	
	unsigned int pixel			;	// color pixel
	//unsigned int bmpHeight=128	;	// height of image 
	//unsigned int bmpWidth=149	;	// width of image
	
	BYTE cc=0;			// color counter
    BYTE B,G,R;			// color B,G,R

    UINT HCount = 0;	// Horizontal counter
	BYTE padding;		// pad size
    BYTE p;				// pad counter
	
	
/**************************************************************************************************************/

void FILL_RECTANGLE(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,unsigned int fill_color){
	
#ifdef Vertical
	unsigned int temp = y2;
	y2 = GetMaxY() - y1;
	y1 = GetMaxY() - temp;
#endif
	
	SetColor(fill_color);
	FillRectangle(x1, y1, x2, y2);
}


/****************************************************************************************************
* Function     : void DRAW_RECTANGLE(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,unsigned int fill_color)
* Description  : Draw a rectangle on a graphic LCD filled with specified color
* Input        : x1,y1 - starting coordinates
*              : x2,y2 - ending coordinates	        
*****************************************************************************************************/

void DRAW_RECTANGLE(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,unsigned int fill_color)
{	


#ifdef Vertical	// 	added by peyul
	unsigned int temp = y2;
	y2 = GetMaxY() - y1;
	y1 = GetMaxY() - temp;
#endif

	
	SetColor(fill_color);			  // fill rectangle with specified color
	
	/*DRAW_LINE(x1, y1, x2, y1,fill_color);    // top
    DRAW_LINE(x1, y2, x2, y2,fill_color);    // bottom
    DRAW_LINE(x1, y1, x1, y2,fill_color);    // left
    DRAW_LINE(x2, y1, x2, y2,fill_color);    // right*/
	
	FillRectangle(x1, y1, x2, y1);    // top
    FillRectangle(x1, y2, x2, y2);    // bottom
    FillRectangle(x1, y1, x1, y2);    // left
    FillRectangle(x2, y1, x2, y2);    // right
}

/***********************************************************************************************
* Function     : void DRAW_LINE(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,unsigned int fill_color)
* Description  : Draw a line on a graphic LCD using Bresenham's
* Input        : x1,y1 - starting coordinates
*              : x2,y2 - ending coordinates
************************************************************************************************/

void DRAW_LINE(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,unsigned int fill_color)
{
	
#ifdef Vertical	// 	added by peyul
	unsigned int temp = y1;
	y1 = GetMaxY() - y1;
	y2 = GetMaxY() - y2;
#endif
	
	SetColor(fill_color);			  
	
	signed int  x, y, addx, addy, dx, dy;
	signed long P;
	int i;

	dx = abs((signed int)(x2 - x1));
	dy = abs((signed int)(y2 - y1));
	x = x1;
	y = y1;

	addx = addy = 1;
	if(x1 > x2)
		addx = -1;
	if(y1 > y2)
		addy = -1;

	if (dx >= dy)
	{
		P = 2L*dy - dx;
		for (i=0; i<=dx; ++i)
		{
	  		PutPixel(x, y);
			if(P < 0)
	  		{
	    		P += 2*dy;
	    		x += addx;
	  		}
			else
			{
	    		P += 2*dy - 2*dx;
	    		x += addx;
	    		y += addy;
	  		}
		}
	}
	else
	{
		P = 2L*dx - dy;
		for(i=0; i<=dy; ++i)
		{
	  		PutPixel(x, y);
	  		if(P < 0)
	  		{
	    		P += 2*dx;
	    		y += addy;
	  		}
	  		else
	  		{
	    		P += 2*dx - 2*dy;
	    		x += addx;
	    		y += addy;
	  		}
		}
	}
}

/*******************************************************************************************************************
* Function    : void DRAW_RRECT(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned char rad, unsigned char fill,unsigned int fill_color )
* Description : Draws a beveled figure on the screen. 
* Input       : x1, y1 - coordinate position of the upper left center
*		      : x2, y2 - coordinate position of the lower right center
*             : rad - defines the redius of the circle,
*             : fill - fill yes or no
********************************************************************************************************************/
void DRAW_RRECT(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius,  unsigned int fill_color, unsigned char fill)
{	
	
#ifdef Vertical	// 	added by peyul
	unsigned int temp = y2;
	y2 = GetMaxY() - y1;
	y1 = GetMaxY() - temp;
#endif
	
	SetColor(fill_color);
	signed int a, b, P;
	signed int bx, ay;

	if (fill)
	{
		a = 0;       // increment by 1
		b = radius;  // decrement by 1 using P
		P = 1 - radius;
		bx = b;
		ay = a;
		
		FillRectangle(x1, y1-radius+1, x2, y2+radius-1);
		do
		{
			if (bx != b)
			{
				FillRectangle(x1-bx, y1-ay, x1-bx, y2+ay); // left in
				FillRectangle(x2+bx, y1-ay, x2+bx, y2+ay); // right in
				bx = b;
			}
      		ay = a;
			if (a != b)
			{ 
				FillRectangle(x1-a, y1-b, x1, y2+b); // left out
				FillRectangle(x2  , y1-b, x2+a, y2+b); // rigth out
      		}
			if(P < 0)
				P+= 3 + 2*a++;
			else
				P+= 5 + 2*(a++ - b--);
		} while(a <= b);

		if (fill && (bx != b))
		{
			FillRectangle(x1-bx, y1-ay, x1-bx, y2+ay); // left in
			FillRectangle(x2+bx, y1-ay, x2+bx, y2+ay); // right in
		}
	}

	// draw broder
	{
		a = 0;       // increment by 1
		b = radius;  // decrement by 1 using P
		P = 1 - radius;
		bx = b;
		ay = a;

		do
		{
			if (a && (a != b))
			{
				PutPixel(x1-b, y1-a);
				PutPixel(x1-b, y2+a);
				PutPixel(x2+b, y1-a);
				PutPixel(x2+b, y2+a);
			}
			PutPixel(x1-a, y1-b);
			PutPixel(x2+a, y1-b);
			PutPixel(x1-a, y2+b);
			PutPixel(x2+a, y2+b);

			if(P < 0)
				P+= 3 + 2*a++;
			else
				P+= 5 + 2*(a++ - b--);
		} while(a <= b);

		FillRectangle(x1       , y1-radius, x2       , y1-radius);	// top
		FillRectangle(x1       , y2+radius, x2       , y2+radius);	// bottom
		FillRectangle(x1-radius, y1       , x1-radius, y2       );	// left
		FillRectangle(x2+radius, y1       , x2+radius, y2       );	// right
	}
}
/********************************************************************************************************************
* Function    : void DRAW_CIRCLE(unsigned int x, unsigned int y, unsigned int radius, unsigned char fill, unsigned int fill_color)
* Description : Draw a circle on the screen. 
* Input       : x,y - the center of the circle
*             : rad - defines the redius of the circle,
*             : fill - fill yes or no
**************************************************************************************************************************/


void DRAW_CIRCLE(unsigned int x, unsigned int y, unsigned int radius, unsigned int fill_color, unsigned char fill)
{
	
#ifdef Vertical	// 	added by peyul
	y = GetMaxY() - y; 	
#endif
	
	
   SetColor(fill_color);
   signed int a, b, P;
   a = 0;
   b = radius;
   P = 1 - radius;

   do
   {
      if(fill)
      {
         FillRectangle(x-a, y+b, x+a, y+b);
         FillRectangle(x-a, y-b, x+a, y-b);
         FillRectangle(x-b, y+a, x+b, y+a);
         FillRectangle(x-b, y-a, x+b, y-a);
      }
      else
      {
         PutPixel(a+x, b+y);
         PutPixel(b+x, a+y);
         PutPixel(x-a, b+y);
         PutPixel(x-b, a+y);
         PutPixel(b+x, y-a);
         PutPixel(a+x, y-b);
         PutPixel(x-a, y-b);
         PutPixel(x-b, y-a);
      }

      if(P < 0)
         P+= 3 + 2*a++;
      else
         P+= 5 + 2*(a++ - b--);
    } while(a <= b);
}


void Print_Text(int x,int y,unsigned char* FONT,char* text,int COL){

	LcdFont(FONT);
	SetFgColor(COL);
	SetCursorX(x);
	SetCursorY(y);	
	DrawStr(text);
}

void Print_Char(int x,int y,unsigned char* FONT,unsigned char character,int COL){

	LcdFont(FONT);
	SetFgColor(COL);
	SetCursorX(x);
	SetCursorY(y);	
	DrawChar(character);
}

/*
void bmpShow(unsigned int x, unsigned int y)
{
	//FRESULT res;
    //WORD br;			// File Read count
	unsigned int bmpHeight=320	;
	unsigned int bmpWidth=240	;

	BYTE buffer[512];	// file copy buffer
	unsigned int i;		// buffer counter
	unsigned int pixel;	// color pixel

	BYTE cc;			// color counter
    BYTE B,G,R;			// color B,G,R

    UINT HCount = 0;	// Horizontal counter
	BYTE padding;		// pad size
    BYTE p;				// pad counter

	unsigned char pix_val=0;
	
// *** 24 bit True color Image ***
    padding = (4 - ((bmpWidth*3) % 4))%4;
    cc = 0;						// start with B-R-G

	// set draw area
	LCD_SetArea(x, y, x+bmpWidth-1, y+bmpHeight-1);
    
		unsigned int ch =0 ;
		
        while(1)
        {
            ch = uart_getc();
				
			if(!(ch & UART_NO_DATA)){
				
				pix_val = ch;
				
				switch (cc)
				{
					case 0: B = pix_val >> 3; cc++; break;
					case 1: G = pix_val >> 2; cc++; break;
					case 2: R = pix_val >> 3; cc=0;
							pixel = (R << 11) | (G << 5) | B ;
							LCD_FAST_WRITE(pixel);
							
							HCount++;
							if (HCount >= bmpWidth)			// not same line
							{
								HCount = 0;					// reset Horizontal count
								if (padding)				// padding data
								{
									p = padding;			// assign padding
									cc = 3;					// start padding mode
								}
							}
							break;
						
					default:								// padding
							p--;
							if (!p)							// end of padding
								cc=0;						//   start B-G-R
							break;
				}
			}
   		}
    //} while (res || br == sizeof(buffer));  	// error or eof 

	// restore area
	LCD_SetArea(0, 0, GetMaxX(), GetMaxY());
}*/