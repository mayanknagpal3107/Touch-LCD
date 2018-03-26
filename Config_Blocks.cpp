
#ifndef	ConfigBlocks
#define ConfigBlocks	1

#include "Config_Pages.h"
#include "Lcd_Class.cpp"

#define THEME_1		1
#define THEME_2		2
#define THEME_3		3
#define THEME_4		4

class Config_Blocks : public LCD_Class{
	
	public:
		void Make_Box(int theme,int x,int y,int width,int height,int boxcolor,char* text,unsigned char *font,int alignment,int fontcolor);
		void Auto_Display_Blocks(int no_of_boxes,struct Page B,int theme);
		void Configure_Pages();
		void Set_Default_Page(char _page,int Background,int theme);
		void Set_Custom_Page(char _page,int Background,int theme,int bcolor,int btcolor);
		void Clear_Box(int theme,int j,int no,int Background);
		void Select_Box(char page,int box_no,int background,int theme,int type);
		void Deselect_Box(char page,int box_no,int background,int theme);
		
		
};

void Config_Blocks :: Make_Box(int theme,int x,int y,int width,int height,int boxcolor,char* text,unsigned char *font,int alignment,int fontcolor){
	
	if(theme==1)
	{
		Draw_Rect(x,y,width,height,boxcolor); 
	}
	else if(theme==2)
	{
		Fill_Rect(x,y,width,height,boxcolor); 
	}
	else if(theme==3)
	{
		Draw_Rou_Rect(x,y,width,height,7,boxcolor); 
	}
	else if(theme==4)
	{
		Draw_Rou_Rect(x,y,width,height,7,boxcolor); 
	}
	
	Show_Aligned_Text(x,y,x+width,y+height,font,text,alignment,fontcolor);	
	
}



/*
void Config_Blocks :: Auto_Display_Blocks(int no_of_boxes,struct Page B,int theme){
	
	int X=0;
	int Y=0;
	
	for(int i=0;i<no_of_boxes;i++){
		
		if( (X + B.Box_Width[i] + B.Right_Clearance) >= GetMaxX()){
			
			X=0;
			Y = Y + B.Box_Height[i] + B.Box_Vert_Spacing;			
			if( (Y + B.Box_Height[i] + B.Bottom_Clearance) >= GetMaxY())	break;
		}
		
		B.Box_Xpos[i] =  X + B.Left_Clearance;
		B.Box_Ypos[i] =  Y +  B.Top_Clearance;
		
		Make_Box(theme,B.Box_Xpos[i],B.Box_Ypos[i],B.Box_Width[i],B.Box_Height[i],B.Box_Color[i],B.Boxes_Texts[i],ft10x20,ALINE_BOTTOM,B.Box_Text_Color[i]);
		
		X = X + B.Box_Width[i] + B.Box_Horz_Spacing;
		
	}
}*/

void Config_Blocks :: Set_Default_Page(char page,int Background,int theme){
	
	LCD_Clear(Background);
	
	for(int j=0;j<Total_Pages;j++){
		
		if(page==Commands[j]){
			
			for(int i=0;i<_Page[j].Total_Boxes;i++){
				
				//Draw_Rou_Rect(B[i].Xpos+8, B[i].Ypos+5, B[i].Box_Width, B[i].Box_Height, 7, BLACK);
				Make_Box(theme,_Page[j].Box_Xpos[i],_Page[j].Box_Ypos[i],_Page[j].Box_Width[i],_Page[j].Box_Height[i],_Page[j].Box_Color[i],_Page[j].Boxes_Texts[i],ft18x34,ALINE_CENTER,_Page[j].Box_Text_Color[i]);
			}
		}
	}	
}

void Config_Blocks :: Set_Custom_Page(char page,int Background,int theme,int bcolor,int btcolor){
	
	LCD_Clear(Background);
	
	for(int j=0;j<Total_Pages;j++){
		
		if(page==Commands[j]){
			
			for(int i=0;i<_Page[j].Total_Boxes;i++){
				
				_Page[j].Box_Color[i] = bcolor;
				_Page[j].Box_Text_Color[i] = btcolor;
				
				//Draw_Rou_Rect(B[i].Xpos+8, B[i].Ypos+5, B[i].Box_Width, B[i].Box_Height, 7, BLACK);
				Make_Box(theme,_Page[j].Box_Xpos[i],_Page[j].Box_Ypos[i],_Page[j].Box_Width[i],_Page[j].Box_Height[i],bcolor,_Page[j].Boxes_Texts[i],ft18x34,ALINE_CENTER,btcolor);
			}
		}
	}	
}

void Config_Blocks :: Clear_Box(int theme,int j,int no,int Background){
	
	if(theme==1){
		Fill_Rect(_Page[j].Box_Xpos[no], _Page[j].Box_Ypos[no], _Page[j].Box_Width[no], _Page[j].Box_Height[no], Background);		
	}
	else if(theme==2){
		Fill_Rect(_Page[j].Box_Xpos[no], _Page[j].Box_Ypos[no], _Page[j].Box_Width[no], _Page[j].Box_Height[no], Background);
	}
	else if(theme==3){
		Draw_Rou_Rect(_Page[j].Box_Xpos[no], _Page[j].Box_Ypos[no], _Page[j].Box_Width[no], _Page[j].Box_Height[no], 7, Background);
	}
	else if(theme==4){
		Draw_Rou_Rect(_Page[j].Box_Xpos[no], _Page[j].Box_Ypos[no], _Page[j].Box_Width[no], _Page[j].Box_Height[no], 7, Background);
	}
}

void Config_Blocks :: Select_Box(char page,int box_no,int background,int theme,int type){
	
	for(int j=0;j<Total_Pages;j++){
		
		if(page==Commands[j]){
			
			/*for(int i=0;i<_Page[j].Total_Boxes;i++){
				
				if(strcmp(text,_Page[j].Boxes_Texts[i])==0){*/
					
					int i = box_no;
					
					int width =  _Page[j].Box_Width[i];
					int height =  _Page[j].Box_Height[i];
					int x = _Page[j].Box_Xpos[i];
					int y = _Page[j].Box_Ypos[i];
					
					if(type==INSTANT){
						
						/*Clear_Box(theme,j,i,background);
						_Page[j].Box_Xpos[i] =  _Page[j].Box_Xpos[i] + (_Page[j].Box_Width[i]/6);
						_Page[j].Box_Ypos[i] =  _Page[j].Box_Ypos[i] + (_Page[j].Box_Height[i]/6);						
						_Page[j].Box_Width[i]		=	(_Page[j].Box_Width[i]*2)/3;
						_Page[j].Box_Height[i]		=	(_Page[j].Box_Height[i]*2)/3;*/
						Make_Box(theme,_Page[j].Box_Xpos[i],_Page[j].Box_Ypos[i],_Page[j].Box_Width[i],_Page[j].Box_Height[i],_Page[j].Box_Text_Color[i],_Page[j].Boxes_Texts[i],ft10x20,ALINE_CENTER,_Page[j].Box_Color[i]);
						/*_Page[j].Box_Width[i] = width;
						_Page[j].Box_Height[i] = height;
						_Page[j].Box_Xpos[i] = x;
						_Page[j].Box_Ypos[i] = y;*/
					}
					/*if(type==SHADOWED){
						
						Clear_Box(theme,j,i,background);
						_Page[j].Box_Xpos[i] =  _Page[j].Box_Xpos[i] + 8;//(_Page[j].Box_Width/10);
						_Page[j].Box_Ypos[i] =  _Page[j].Box_Ypos[i] + 5;
						Make_Box(theme,_Page[j].Box_Xpos[i],_Page[j].Box_Ypos[i],_Page[j].Box_Width[i],_Page[j].Box_Height[i],_Page[j].Box_Color[i],_Page[j].Boxes_Texts[i],ft10x20,ALINE_BOTTOM,_Page[j].Box_Text_Color[i]);
						_Page[j].Box_Width[i] = width;
						_Page[j].Box_Height[i] = height;
						_Page[j].Box_Xpos[i] = x;
						_Page[j].Box_Ypos[i] = y;
					}
					if(type==ANIMATION){
						
						int speed=4;
						
						int x_end = _Page[j].Box_Xpos[i] + (_Page[j].Box_Width[i]/8);
						int y_end = _Page[j].Box_Ypos[i] + (_Page[j].Box_Height[i]/9);
						
						while(1){
							
							if( (_Page[j].Box_Xpos[i]>=x_end) && (_Page[j].Box_Ypos[i]>=y_end) )	break;	
							
							Clear_Box(theme,j,i,background);
							
							if(_Page[j].Box_Xpos[i]<x_end) _Page[j].Box_Xpos[i] = _Page[j].Box_Xpos[i] + speed;
							if(_Page[j].Box_Ypos[i]<y_end) _Page[j].Box_Ypos[i] = _Page[j].Box_Ypos[i] + speed;
							
							_Page[j].Box_Width[i]		=	_Page[j].Box_Width[i]-(2*speed);
							_Page[j].Box_Height[i]		=	_Page[j].Box_Height[i]-(2*speed);
							Make_Box(theme,_Page[j].Box_Xpos[i],_Page[j].Box_Ypos[i],_Page[j].Box_Width[i],_Page[j].Box_Height[i],_Page[j].Box_Color[i],_Page[j].Boxes_Texts[i],ft10x20,ALINE_BOTTOM,_Page[j].Box_Text_Color[i]);
							
						}
						
						_Page[j].Box_Width[i] = width;
						_Page[j].Box_Height[i] = height;
						
						_Page[j].Box_Xpos[i] = x;
						_Page[j].Box_Ypos[i] = y;
					}*/
				//}
			//}
		}
	}
}

void Config_Blocks :: Deselect_Box(char _page,int box_no,int background,int theme){
	
	for(int j=0;j<Total_Pages;j++){
		
		if(_page==Commands[j]){
			
			/*for(int i=0;i<_Page[j].Total_Boxes;i++){
				
				if(strcmp(text,_Page[j].Boxes_Texts[i])==0){*/
					
					int i = box_no;
					
					Make_Box(theme,_Page[j].Box_Xpos[i],_Page[j].Box_Ypos[i],_Page[j].Box_Width[i],_Page[j].Box_Height[i],_Page[j].Box_Color[i],_Page[j].Boxes_Texts[i],ft18x34,ALINE_BOTTOM,_Page[j].Box_Text_Color[i]);
				//}
			//}
		}
	}
}
#endif
