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

void MouseEventProcess(int x,int y,int button,int event)
{
	double a,b;
	a=ScaleXInches(x);
	b=ScaleYInches(y);
	static double p=0.0,q=0.0;
	static bool Draw=FALSE;
	switch(event)
	{
		case BUTTON_DOWN:
			if(button==LEFT_BUTTON)Draw=TRUE;break;
		case BUTTON_UP:
			if(button==LEFT_BUTTON)Draw=FALSE;break;
		case MOUSEMOVE:
			if(Draw)
			{
				DrawLine(a-p,b-q);
				MovePen(a,b);
			}
			break;
		default:break;
	}
	p=a;
	q=b;
}
void Main()
{
	InitGraphics();
	registerMouseEvent(MouseEventProcess);
}




