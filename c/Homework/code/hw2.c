#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#define PI 3.1415926

double cangle = 0.0;

void forward(double distance);
void turn(double angle);
void draw();

void Main()
{
	double cx,cy;
	int i;

	InitGraphics();
	cx=GetWindowWidth()/2;
	cy=GetWindowHeight()/2;
	SetPenColor("green");
	SetPenSize(2);

	for(i=0;i<18;i++)
	{
		MovePen(cx,cy);
		draw();
		cangle+=20.0;
	}
}

void draw()
{
	forward(1);
	turn(60);
	forward(1);
	turn(60);
	forward(1);
	turn(60);
	forward(1);
	turn(60);
	forward(1);
}

void forward(double distance)
{
	double dx,dy;

	dx=distance*sin(cangle*PI/180);
	dy=distance*cos(cangle*PI/180);
	DrawLine(dx,dy);
}

void turn(double angle)
{
	cangle+=angle;
}

void Move(double distance)
{
	double x, y;

	x = GetCurrentX() + distance * sin(cangle * PI / 180);
	y = GetCurrentY() + distance * cos(cangle * PI / 180);
	MovePen(x, y);
}

