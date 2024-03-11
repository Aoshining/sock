#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
 
void KeyboardEventProcess(int key,int event);
void CharEventProcess(char c);
void TimerEventProcess(int timerID);

static char text[80];
static int textlen=0,spot=-1;
static bool Display=FALSE;
 
void Main() 
{
	InitGraphics();
	MovePen(0.1,6.75);
	registerKeyboardEvent(KeyboardEventProcess);
    registerCharEvent(CharEventProcess);
	registerTimerEvent(TimerEventProcess);
	startTimer(1,500);
}
 
void CharEventProcess(char c)
{
	if(c==VK_ESCAPE)exit(0);
	if(c==VK_BACK||c==VK_DELETE)return;
	if(c==VK_RETURN){
	 	SetEraseMode(TRUE);
		if(Display)
		{
			DrawTextString("_");
			MovePen(GetCurrentX()-TextStringWidth("_"),GetCurrentY());
		}
		InitConsole();
	 	printf("%s\n", text);
		system("pause");
		FreeConsole();
		MovePen(0.1,6.75);
   		DrawTextString(text);
   		SetEraseMode(FALSE);
   		MovePen(0.1,6.75);
   		textlen=0;
   		spot=-1;
   		text[0]='\0';
    }
	else{
		char str[2]={'\0'};
		str[0]=c;
		if(spot==textlen-1){
			text[textlen++]=c;
			text[textlen]='\0';
			DrawTextString(str);
			spot++;
		}
		else{
			int i;
			string subtext;
			subtext=SubString(text,spot+1,textlen); 
			SetEraseMode(TRUE);
			DrawTextString(subtext);
			MovePen(GetCurrentX()-TextStringWidth(subtext),GetCurrentY());
			SetEraseMode(FALSE);
			DrawTextString(str);
			DrawTextString(subtext);
			MovePen(GetCurrentX()-TextStringWidth(subtext),GetCurrentY());
			textlen++;
			spot++;
			for(i=textlen;i>=spot+1;i--){
				text[i]=text[i-1];
			}
			text[spot]=c;
		}
   	    if (Display) 
		{
			SetEraseMode(TRUE);
			MovePen(GetCurrentX()-TextStringWidth(str), GetCurrentY());
 			DrawTextString("_");
 			MovePen(GetCurrentX()-TextStringWidth("_"),GetCurrentY());
 			SetEraseMode(FALSE);
 			DrawTextString(str);
		}
		else
		{
			MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());
			DrawTextString(str);
		}
	}	
}

void KeyboardEventProcess(int key,int event)
{
	static char str[2]={'\0'};
	switch(event){
		case KEY_DOWN:
			if(key==VK_DELETE||key==VK_BACK){
				if(spot<0)return;
				int i;
				SetEraseMode(TRUE);
                if (Display) 
				{
 	          	   DrawTextString("_");
 	          	   MovePen(GetCurrentX()-TextStringWidth("_"), GetCurrentY());
		        }
 	 			str[0]=text[spot];
				MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());
				DrawTextString(str);
				if(spot==textlen)MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());
				else
				{
					string s1,s2;
					s1=SubString(text,spot+1,textlen);
					s2=SubString(text,spot,textlen); 
					SetEraseMode(TRUE);
					DrawTextString(s1);
					SetEraseMode(FALSE);
					MovePen(GetCurrentX()-TextStringWidth(s2),GetCurrentY());
					DrawTextString(s1);
					MovePen(GetCurrentX()-TextStringWidth(s1),GetCurrentY());
				}
		        for(i=spot;i<textlen;i++)
				{
		        	text[i]=text[i+1];
		        }
		        text[--textlen]='\0';
				spot--;
 				SetEraseMode(FALSE);					
			}
			else if(key==VK_LEFT)
			{
				if(spot<0)return;
				if (Display)
				{
	 	     	   	SetEraseMode(TRUE);
 	              	DrawTextString("_");
 	         	   	SetEraseMode(FALSE);
		           	MovePen(GetCurrentX()-TextStringWidth("_"), GetCurrentY());
		       	}
		       	str[0]=text[spot--];
		       	MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());
				
			}
			else if(key==VK_RIGHT){
				if(spot>=textlen)return; 
				if (Display) 
				{
	 	     	   	SetEraseMode(TRUE);
 	              	DrawTextString("_");
 	         	   	SetEraseMode(FALSE);
		           	MovePen(GetCurrentX()-TextStringWidth("_"), GetCurrentY());
		       	}
		       	str[0]=text[++spot];
		       	MovePen(GetCurrentX()+TextStringWidth(str),GetCurrentY());
			}
	}
}
 
void TimerEventProcess(int timerID)
{
	if(Display)
	{
		SetEraseMode(TRUE);
		DrawTextString("_");
		SetEraseMode(FALSE);
	}
	else DrawTextString("_");
	Display=!Display;
	MovePen(GetCurrentX()-TextStringWidth("_"),GetCurrentY());
}
