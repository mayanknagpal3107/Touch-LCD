
#ifndef	pagestructure
#define	pagestructure	1

#include "LCD_FUNCTIONS.c"
//#include "ft10x20.h"
#include "ft18x34.h"
#include "ft10x20.h"
#include "font.h"

/***************************************

******		Total no of pages 	********

	- main page , submenus all..
	
****************************************/

#define Total_Pages	 	5

/*************************************************************************

	       ************    HOME PAGE CONFIGURATION		************
	
*************************************************************************/

/*
#define Home_Total_boxes 	2	//  total boxes 
char* Home_Text[Home_Total_boxes] 		= {"USER LOGIN","ADMIN LOGIN"};
int   Home_Box_Color[Home_Total_boxes]	= { GREEN6		,  BLUE5	 };	 	 
int   Home_Text_Color[Home_Total_boxes]	= {  YELLOW4	,  YELLOW4 	 };
int   Home_Box_Width [Home_Total_boxes]	= {  200		,  200 	   	 };
int   Home_Box_Height[Home_Total_boxes]	= {  40			,  40 	 	 };
int   Home_Box_Xpos[Home_Total_boxes]	= {  60			,  60 	 	 };
int   Home_Box_Ypos[Home_Total_boxes] 	= {  50			,  150 	 	 };
*/
#define Home_Total_boxes 	3	//  total boxes 
char* Home_Text[Home_Total_boxes] 		= {"+" 		  ,	  "90"     ,   "-" 	  }    ;//,   "BASE"  };
int   Home_Box_Color[Home_Total_boxes]	= {  BLUE		  ,	RED	      ,	 BLUE       }   ;// ,    RED          };	 	 
int   Home_Text_Color[Home_Total_boxes]	= {  WHITE	      ,	GREEN	  , 	WHITE    }  ;//,    GREEN   };
int   Home_Box_Width [Home_Total_boxes]	= {  60		      , 60		  ,		60	      } ;//,     60   };
int   Home_Box_Height[Home_Total_boxes]	= {  30          ,  30		  ,		30	       };//,      30   };
int   Home_Box_Xpos[Home_Total_boxes]	= {  60	  	  	,	140		  ,		220	      } ;//,      250  };
int   Home_Box_Ypos[Home_Total_boxes] 	= {  200		  ,	200	  	  ,		200	       };//,      180  };




/*************************************************************************

	       ************    ROBOT PAGE CONFIGURATION 	***********
	
*************************************************************************/

#define Robot_Total_boxes 	5	//  total boxes 

char* Robot_Text[Robot_Total_boxes] 	 = {"+" 		  ,	  "ANGLE"     ,   "-" 	 };
int   Robot_Box_Color[Robot_Total_boxes] = {  GREEN		  ,	   RED	      ,	 GREEN    };	  
int   Robot_Text_Color[Robot_Total_boxes]= {  WHITE	      ,	GREEN	  , 	WHITE    };//,
int   Robot_Box_Width [Robot_Total_boxes]= {  60		  , 60		  ,		60	     };
int   Robot_Box_Height[Robot_Total_boxes]= {  30       ,	30		  ,		30	     };//   ,    50    , 30 };
int   Robot_Box_Xpos[Robot_Total_boxes]	 = {  10	  	,	10		  ,		10	     };//    ,    110   , 230  };
int   Robot_Box_Ypos[Robot_Total_boxes]  = {  20		,	80	  	  ,		160	     };//  ,    170   , 180 };

/*************************************************************************

	************    SHOULDER PAGE CONFIGURATION		************
	
*************************************************************************/

#define Shoulder_Total_boxes 	3	//  total boxes 
char* Shoulder_Text[Shoulder_Total_boxes] 		= {"+"     ,"ANGLE"      , "-"   };
int   Shoulder_Box_Color[Shoulder_Total_boxes]	= {  CYAN   ,  RED  	 ,  CYAN   };
int   Shoulder_Text_Color[Shoulder_Total_boxes]	= {  BLACK	,  GREEN     ,  BLACK	};
int   Shoulder_Box_Width[Shoulder_Total_boxes]	= {  110	,  110 	     ,  110	    };
int   Shoulder_Box_Height[Shoulder_Total_boxes]	= {  50		,  50 	     ,  50		};
int   Shoulder_Box_Xpos[Shoulder_Total_boxes]	= {  320	,  320 	     ,  320		};
int   Shoulder_Box_Ypos[Shoulder_Total_boxes] 	= {  20		,  80 	     ,  160     }; 



/*************************************************************************

	************    LIGHT PAGE CONFIGURATION		************
	
*************************************************************************/

#define Light_Total_boxes 	3	//  total boxes 
char* Light_Text[Light_Total_boxes] 		= { "Light +","Light -" , "BACK"   };
int   Light_Box_Color[Light_Total_boxes]	= {  BLUE    ,  BLUE  	 ,  GREEN   };
int   Light_Text_Color[Light_Total_boxes]	= {  CYAN	 ,  CYAN     ,  BLACK	};
int   Light_Box_Width[Light_Total_boxes]	= {  110	 ,  110 	 ,  60	    };
int   Light_Box_Height[Light_Total_boxes]	= {  50		 ,  50 	     ,  40		};
int   Light_Box_Xpos[Light_Total_boxes]	    = {  30		 ,  180 	 ,  210		};
int   Light_Box_Ypos[Light_Total_boxes] 	= {  50		 ,  50 	     ,  180     }; 


/*************************************************************************

	************    CAMERA PAGE CONFIGURATION		************
	
*************************************************************************/

#define Camera_Total_boxes 	4	//  total boxes 
char* Camera_Text[Camera_Total_boxes] 		= {"CAM UP"     ,"CAM DOWN"  , "CAM Stop",  "BACK"   };
int   Camera_Box_Color[Camera_Total_boxes]	= {  BLUE   ,  BLUE  	     ,  BLUE     ,  GREEN   };
int   Camera_Text_Color[Camera_Total_boxes]	= {  CYAN	,  CYAN          ,  CYAN     ,  BLACK	};
int   Camera_Box_Width[Camera_Total_boxes]	= {  110	,  110 	         ,  110	     ,   60     };
int   Camera_Box_Height[Camera_Total_boxes]	= {  50		,  50 	         ,  50		 ,   40     };
int   Camera_Box_Xpos[Camera_Total_boxes]	= {  30		,  180 	         ,  105		 ,   210    };
int   Camera_Box_Ypos[Camera_Total_boxes] 	= {  30		,  30 	         ,  100      ,   180    }; 


/*************************************************************************

	************    SOUND PAGE CONFIGURATION		************
	
*************************************************************************/
/*
#define Sound_Total_boxes 	7	//  total boxes 
char* Sound_Text[Sound_Total_boxes] 		= {"1"      ,  "2"      ,  "3"  ,  "4"  , " 5"    ,  "6"   ,  "BACK"   };
int   Sound_Box_Color[Sound_Total_boxes]	= {  BLUE   ,  BLUE  	 ,  BLUE ,  BLUE ,  BLUE  ,   BLUE  ,  GREEN   };
int   Sound_Text_Color[Sound_Total_boxes]	= {  CYAN	,  CYAN      ,  CYAN ,  CYAN ,  CYAN  ,   CYAN  ,  BLACK	};
int   Sound_Box_Width[Sound_Total_boxes]	= {  60	    ,  60 	     ,   60  ,  60   ,  60     ,   60   ,   60	    };
int   Sound_Box_Height[Sound_Total_boxes]	= {  40		,  40 	     ,  40	 ,  40   ,  40     ,   40    ,  40	    };
int   Sound_Box_Xpos[Sound_Total_boxes]	    = {  30		,  120 	     ,  210	 ,  30   ,  120     ,   210  ,  210	    };
int   Sound_Box_Ypos[Sound_Total_boxes] 	= {  30		,  30 	     ,  30   ,  100  ,  100     ,   100    ,  180    }; 

/*************************************************************************

	************    Num_Pad PAGE CONFIGURATION		************
	
*************************************************************************/

/*
#define Num_Pad_Total_boxes 	13	//  total boxes 
char* Num_Pad_Text[Num_Pad_Total_boxes] 		= {	"0"	  ,  "1",	"2 abc"	  , "3 def" ,"4 ghi", "5 jkl" , "6 mno" 	, "7 pqrs", "8 tuv", "9 wxyz", "Ok" ,  "Cancel" , ""};
int   Num_Pad_Box_Color[Num_Pad_Total_boxes] 	= { MAGENTA,MAGENTA,MAGENTA  ,  MAGENTA  , MAGENTA, MAGENTA ,  MAGENTA   ,  MAGENTA  , MAGENTA , MAGENTA , MAGENTA ,  MAGENTA		,   MAGENTA};
int   Num_Pad_Text_Color[Num_Pad_Total_boxes]	= {  CYAN  , CYAN  ,  CYAN 	  ,  CYAN   ,  CYAN ,  CYAN   ,   CYAN  ,  CYAN   ,  CYAN  ,  CYAN  ,   CYAN	,   CYAN	,   CYAN};
int   Num_Pad_Box_Width [Num_Pad_Total_boxes]	= {  78	  ,	78		,  78 	  ,  78		,  78  	,   78   ,   78   ,  78		,  78  ,   78   ,    78    ,   78   	,   78   };
int   Num_Pad_Box_Height[Num_Pad_Total_boxes]	= {  58	  ,	58		,  58 	  ,  58		,  58  	,   58   ,   58   ,  58		,  58  	,   58   ,   58    ,   58   	,   58  };
int   Num_Pad_Box_Xpos[Num_Pad_Total_boxes]	 	= {  242  ,	2		,  82 	  ,  162	,  2  	,   82   ,   162  ,  2		,  82   ,   162   ,   242   ,   242   	,   242   };
int   Num_Pad_Box_Ypos[Num_Pad_Total_boxes]  	= {  122  ,	2		,  2 	  ,  2		,  62   ,   62   ,   62   ,  122	,  122  ,   122   ,   2    ,   62   	,   181   };

*/
/*************************************************************************

	************    GENERAL PAGE 	************
	
*************************************************************************/
typedef struct Page{

    int *Box_Color;
	int *Box_Width;
	int *Box_Height;
    int *Box_Xpos;    
    int *Box_Ypos;    
    int *Box_Text_Color;    
	char **Boxes_Texts;
	int Total_Boxes;
};

struct Page _Page[Total_Pages]={

{Home_Box_Color, Home_Box_Width,Home_Box_Height,Home_Box_Xpos,Home_Box_Ypos,Home_Text_Color, Home_Text , Home_Total_boxes},
{Robot_Box_Color, Robot_Box_Width,Robot_Box_Height,Robot_Box_Xpos,Robot_Box_Ypos,Robot_Text_Color, Robot_Text , Robot_Total_boxes},
{Shoulder_Box_Color, Shoulder_Box_Width,Shoulder_Box_Height,Shoulder_Box_Xpos,Shoulder_Box_Ypos,Shoulder_Text_Color, Shoulder_Text , Shoulder_Total_boxes},
{Camera_Box_Color, Camera_Box_Width,Camera_Box_Height,Camera_Box_Xpos,Camera_Box_Ypos,Camera_Text_Color, Camera_Text ,Camera_Total_boxes},  
//{Sound_Box_Color, Sound_Box_Width,Sound_Box_Height,Sound_Box_Xpos,Sound_Box_Ypos,Sound_Text_Color, Sound_Text ,Sound_Total_boxes}, 
{Light_Box_Color, Light_Box_Width,Light_Box_Height,Light_Box_Xpos,Light_Box_Ypos,Light_Text_Color, Light_Text ,Light_Total_boxes},

};

#define _HomePage 0
#define _Robot    1
#define _Shoulder 2
#define _Camera   3
//#define _Sound    4
#define _Light  4
int Commands[5] = {   _HomePage,
					   _Robot,
                       _Shoulder,
                       _Camera,
					  // _Sound,
					  _Light,
};

#define AUTO_ARRANGE       0
#define MANUAL_ARRANGE     1

#define ANIMATION		0
#define SHADOWED		1
#define INSTANT			2

#endif