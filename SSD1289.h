/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/**************************************************************************************************
*	  			  SSD1289 color Graphical LCD Display Driver
* File name		: SSD1289.h
* Programmer 	: jaruwit supa
* Web presence  : www.circuitidea.com
* Note			: SSD1289 16 bit interface.for 8 bit use 74lv573 to latch HI byte
* Language		: avrGCC
* Hardware		: atmega16
* Date			: 01/05/2009
************************************************************************************************/

#ifndef __SSD1289X16_H__
#define __SSD1289X16_H__

/* _____CONFIG DEFINES_____________________________________________________ */
//#define LCD_8_BIT_MODE	// 8 bit bus data using latch. Need jumpper for 8 bit or 16 bit
//#define LCD_BL_HARDWARE	// black light jumper

/* _____HARDWARE DEFINES____________y_________________________________________ */
//#define LCD_LO_DDR  DDRC
//#define LCD_LO_PORT PORTC
//#define LCD_LO_PIN  PINC


#define LCD_LO_DDR  DDRB
#define LCD_LO_PORT PORTB
#define LCD_LO_PIN  PINB

#ifdef LCD_8_BIT_MODE
	#define LCD_HI_DDR  LCD_LO_DDR
	#define LCD_HI_PORT LCD_LO_PORT
	#define LCD_HI_PIN  LCD_LO_PIN
#else
	//#define LCD_HI_DDR  DDRA
	//#define LCD_HI_PORT PORTA
	//#define LCD_HI_PIN  PINA
	
	#define LCD_HI_DDR  DDRC
	#define LCD_HI_PORT PORTC
	#define LCD_HI_PIN  PINC
	
#endif

#define LCD_CS_DDR  DDRA//D
#define LCD_CS_PORT PORTA//D
#define LCD_CS_PIN  PINA//D
#define LCD_CS_BIT  0//5

#define LCD_RS_DDR  DDRA
#define LCD_RS_PORT PORTA
#define LCD_RS_PIN  PINA
#define LCD_RS_BIT  1

#define LCD_WR_DDR  DDRA
#define LCD_WR_PORT PORTA
#define LCD_WR_PIN  PINA
#define LCD_WR_BIT  2

#define LCD_RD_DDR  DDRA
#define LCD_RD_PORT PORTA
#define LCD_RD_PIN  PINA
#define LCD_RD_BIT  3

#define LCD_RST_DDR  DDRD
#define LCD_RST_PORT PORTD
#define LCD_RST_PIN  PIND
#define LCD_RST_BIT  6

#ifndef LCD_BL_HARDWARE
	#define LCD_BL_DDR  DDRD
	#define LCD_BL_PORT PORTD
	#define LCD_BL_PIN  PIND
	#define LCD_BL_BIT  5
#endif

#ifdef LCD_8_BIT_MODE
	//#define LCD_LATCH_DDR  DDRD
	//#define LCD_LATCH_PORT PORTD
	//#define LCD_LATCH_PIN  PIND
	//#define LCD_LATCH_BIT  0
	
	#define LCD_LATCH_DDR  DDRD
	#define LCD_LATCH_PORT PORTD
	#define LCD_LATCH_PIN  PIND
	#define LCD_LATCH_BIT  4
#endif

#define LCD_SET_CS()  LCD_CS_PORT  |=  (1<<LCD_CS_BIT)
#define LCD_CLR_CS()  LCD_CS_PORT  &= ~(1<<LCD_CS_BIT)
#define LCD_DIR_CS(x) LCD_CS_DDR   |=  (1<<LCD_CS_BIT)

#define LCD_SET_RS()  LCD_RS_PORT  |=  (1<<LCD_RS_BIT)
#define LCD_CLR_RS()  LCD_RS_PORT  &= ~(1<<LCD_RS_BIT)
#define LCD_DIR_RS(x) LCD_RS_DDR   |=  (1<<LCD_RS_BIT)

#define LCD_SET_WR()  LCD_WR_PORT  |=  (1<<LCD_WR_BIT)
#define LCD_CLR_WR()  LCD_WR_PORT  &= ~(1<<LCD_WR_BIT)
#define LCD_DIR_WR(x) LCD_WR_DDR   |=  (1<<LCD_WR_BIT)

#define LCD_SET_RD()  LCD_RD_PORT  |=  (1<<LCD_RD_BIT)
#define LCD_CLR_RD()  LCD_RD_PORT  &= ~(1<<LCD_RD_BIT)
#define LCD_DIR_RD(x) LCD_RD_DDR   |=  (1<<LCD_RD_BIT)

#define LCD_SET_RST()  LCD_RST_PORT |= (1<<LCD_RST_BIT)
#define LCD_CLR_RST()  LCD_RST_PORT &= ~(1<<LCD_RST_BIT)
#define LCD_DIR_RST(x) LCD_RST_DDR  |= (1<<LCD_RST_BIT)

#define LCD_SET_LATCH()  LCD_LATCH_PORT |=  (1<<LCD_LATCH_BIT)
#define LCD_CLR_LATCH()  LCD_LATCH_PORT &= ~(1<<LCD_LATCH_BIT)
#define LCD_DIR_LATCH(x) LCD_LATCH_DDR  |=  (1<<LCD_LATCH_BIT)

#ifndef LCD_BL_HARDWARE
	#define LCD_BL_OFF()	LCD_BL_DDR  |=  (1<<LCD_BL_BIT); \
							LCD_BL_PORT &= ~(1<<LCD_BL_BIT)
	#define LCD_BL_ON()		LCD_BL_DDR  |=  (1<<LCD_BL_BIT); \
							LCD_BL_PORT |=  (1<<LCD_BL_BIT)
#else
	#define LCD_BL_OFF()
	#define LCD_BL_ON()
#endif

#ifdef LCD_8_BIT_MODE
	#define LCD_INPUT()		LCD_LO_DDR = 0x00
	#define LCD_OUTPUT()	LCD_LO_DDR = 0xFF //; DDRA = 0xFF; PORTA = 0xFF

	#define LCD_MODE()		LCD_SET_LATCH(); \
							LCD_DIR_LATCH(1);

	#define LCD_SET_DBH(x)	LCD_SET_LATCH(); \
							LCD_HI_PORT = x; \
							LCD_CLR_LATCH();

	#define LCD_SET_DBL(x)	LCD_LO_PORT = x

	// read back not support in 8 bit bus
	#define LCD_GET_DBH()	LCD_HI_PIN
	#define LCD_GET_DBL()	LCD_LO_PIN
#else
	#define LCD_INPUT()		LCD_LO_DDR = 0x00; \
							LCD_HI_DDR = 0x00
	#define LCD_OUTPUT()	LCD_LO_DDR = 0xFF; \
							LCD_HI_DDR = 0xFF
	#define LCD_MODE()

	#define LCD_SET_DBH(x)	LCD_HI_PORT = x
	#define LCD_SET_DBL(x)	LCD_LO_PORT = x

	#define LCD_GET_DBH()	LCD_HI_PIN
	#define LCD_GET_DBL()	LCD_LO_PIN
#endif



/* _____DEFINE MACRO_________________________________________________________ */
// fast write is macro define. prevent call routine
#define LCD_FAST_WRITE(val)		LCD_CLR_CS(); \
								LCD_SET_RS(); \
								LCD_SET_DBH(val>>8); \
								LCD_SET_DBL(val); \
								LCD_CLR_WR(); \
								LCD_SET_WR(); \
							    LCD_SET_CS()
								
/* _____PUBLIC DEFINE_____________________________________________________ */
//#define Horizontal
#define Vertical

#ifdef Horizontal
	// Horizontal and vertical screen size
	#define SCREEN_HOR_SIZE    240UL
	#define SCREEN_VER_SIZE    320UL
#else
	// Horizontal and vertical screen size
	#define SCREEN_HOR_SIZE    320UL
	#define SCREEN_VER_SIZE    240UL
#endif

// color
#define BLACK                       RGB(0x00, 0x00, 0x00)
#define WHITE                       RGB(0xFF, 0xFF, 0xFF)
#define RED                         RGB(0xFF, 0x00, 0x00)
#define GREEN                       RGB(0x00, 0xFF, 0x00)
#define BLUE                        RGB(0x00, 0x00, 0xFF)
#define YELLOW                      RGB(0xFF, 0xFF, 0x00)
#define MAGENTA                     RGB(0xFF, 0x00, 0xFF)
#define CYAN                        RGB(0x00, 0xFF, 0xFF)
#define GRAY                        RGB(0x80, 0x80, 0x40)
#define SILVER                      RGB(0xA0, 0xA0, 0x80)
#define GOLD                        RGB(0xA0, 0xA0, 0x40)

#define OFF_WHITE					 RGB(200,200,200)
#define PARROT_GREEN				 RGB(100,200,60)
#define BABY_PINK					 RGB(250,180,220)
#define LIGHT_PINK					 RGB(240,130,200)
#define WEIRD_GREEN					 RGB(103,221,47)
#define WEIRD_COLOR					 RGB(101,170,160)
#define PINK						 RGB(230,30,150)
#define FONT_COLOR					 RGB(23,84,106)

/********************************* extra shades ******************************************************/

#define RED1                         RGB(235, 0x00, 0x00)
#define RED2                         RGB(220, 0x00, 0x00)
#define RED3                         RGB(205, 0x00, 0x00)
#define RED4                         RGB(190, 0x00, 0x00)
#define RED5                         RGB(175, 0x00, 0x00)
#define RED6                         RGB(160, 0x00, 0x00)
#define RED7                         RGB(145, 0x00, 0x00)
#define RED8                         RGB(130, 0x00, 0x00)


#define BLUE1                        RGB(0x00, 0x00, 230)
#define BLUE2                        RGB(0x00, 0x00, 210)
#define BLUE3                        RGB(0x00, 0x00, 190)
#define BLUE4                        RGB(0x00, 0x00, 170)
#define BLUE5                        RGB(0x00, 0x00, 150)
#define BLUE6                        RGB(0x00, 0x00, 130)
#define BLUE7                        RGB(0x00, 0x00, 110)
#define BLUE8                        RGB(0x00, 0x00, 90)
#define BLUE9                        RGB(0x00, 0x00, 70)

#define GREEN1                       RGB(0x00, 230, 0x00)
#define GREEN2                       RGB(0x00, 210, 0x00)
#define GREEN3                       RGB(0x00, 190, 0x00)
#define GREEN4                       RGB(0x00, 170, 0x00)
#define GREEN5                       RGB(0x00, 150, 0x00)
#define GREEN6                       RGB(0x00, 130, 0x00)
#define GREEN7                       RGB(0x00, 110, 0x00)
#define GREEN8                       RGB(0x00, 90, 0x00)
#define GREEN9                       RGB(0x00, 70, 0x00)

#define BROWN0                         RGB(115, 0x00, 0x00)
#define BROWN1                         RGB(100, 0x00, 0x00)
#define BROWN2                         RGB(85, 0x00, 0x00)
#define BROWN3                         RGB(70, 0x00, 0x00)
#define BROWN4                         RGB(55, 0x00, 0x00)
#define BROWN5                         RGB(40, 0x00, 0x00)

#define PINK0                         RGB(230, 50, 150)
#define PINK1                         RGB(230, 70, 150)
#define PINK2                         RGB(230, 30, 150)
#define PINK3                         RGB(210, 30, 150)
#define PINK4                         RGB(190, 30, 150)
#define PINK5                         RGB(170, 30, 150)
#define PINK6                         RGB(150, 30, 150)

#define YELLOW1                      RGB(255, 220, 0x00)
#define YELLOW2                      RGB(220, 220, 0x00)
#define YELLOW3                      RGB(200, 200, 0x00)
#define YELLOW4                      RGB(180, 180, 0x00)
#define YELLOw5                      RGB(160, 160, 0x00)
#define YELLOW6                      RGB(140, 140, 0x00)
#define YELLOW7                      RGB(120, 120, 0x00)
#define YELLOW8                      RGB(100, 100, 0x00)

/***********************************************************************************************************/




//  custom colors

#define Color1                      RGB(0x60, 0x60, 0x60)



/* _____PUBLIC VARIABLE_____________________________________________________ */
extern unsigned int _color;

/* _____PUBLIC FUNCTIONS_____________________________________________________ */
extern void LCD_Reset(void);
extern void LCD_SetCursor(unsigned int x, unsigned int y);
extern void LCD_SetArea(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
extern void LCD_PutPixel(unsigned int x, unsigned int y);
extern void LCD_Bar(unsigned int left, unsigned int top, unsigned int right, unsigned int bottom, unsigned int color);
extern void LCD_Clear(unsigned int color);
extern void LCD_DrawSymbol(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char t, const unsigned char *pImage);
extern void LCD_DrawImage(unsigned int x, unsigned int y, const unsigned char *pImage);

/* _____DEFINE MACRO_________________________________________________________ */
#define GetMaxX() 		((unsigned int)SCREEN_HOR_SIZE-1)
#define GetMaxY() 		((unsigned int)SCREEN_VER_SIZE-1)

#define RGB(red, green, blue)	((unsigned int)( (( red >> 3 ) << 11 ) | \
								(( green >> 2 ) << 5  ) | \
								( blue  >> 3 )))

#define SetColor(color) _color = color
#define GetColor()      _color


/* _____PUBLIC DEFINE________________________________________________________ */
#define PutPixel(x,y)				LCD_PutPixel(x,y)
#define FillRectangle(x1,y1,x2,y2)	LCD_Bar(x1, y1, x2, y2, GetColor())

#define Bevel(x1,y1,x2,y2,r) 		RoundRectangle(x1,y1,x2,y2,r,0)
#define BevelFill(x1,y1,x2,y2,r)	RoundRectangle(x1,y1,x2,y2,r,1)



#endif
