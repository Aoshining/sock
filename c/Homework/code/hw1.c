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
void Main()
{
	double cx,cy;
	InitGraphics();
	cx=GetWindowWidth()/2;
	cy=GetWindowHeight()/2;
	MovePen(cx,cy);
	DrawLine(0.0,-1.0);
	DrawLine(0.5,0.0);
	DrawLine(0.0,1.3);
	DrawLine(-0.5,1.2);
	DrawLine(-0.25,-0.6);
	DrawLine(0.0,0.25);
	DrawLine(0.075,0.0);
	DrawLine(0.0,0.15);
	DrawLine(-0.35,0.0);
	DrawLine(0.0,-0.15);
	DrawLine(0.275,0.0);
	DrawLine(0.0,-0.25);
	DrawLine(-0.2,-0.48);
	DrawLine(0.0,0.73);
	DrawLine(0.0,-0.73);
	DrawLine(-0.05,-0.12);
	DrawLine(1.0,0.0);
	DrawLine(-1.0,0.0);
	DrawLine(0.0,-1.3);
	DrawLine(0.75,0.0);
	DrawLine(0.0,1.0);
	DrawLine(-0.25,0.0);
	MovePen(cx-0.1,cy);
	DrawLine(-0.2,0.0);
	DrawLine(0.0,-0.25);
	DrawLine(0.2,0.0);
	DrawLine(0.0,0.25);
}

