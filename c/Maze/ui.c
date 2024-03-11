#include"basic.h"
#include"ui.h"

void sp(double px,double py,double l)
{
	//边框
	double x=0.25+px*0.3;
	double y=0.25+py*0.3;
//	MovePen(x-l/2,y-l/2);
//	DrawLine(l,0);
//	DrawLine(0,l);
//	DrawLine(-l,0);
//	DrawLine(0,-l);
	StartFilledRegion(1);
	SetPenColor("Black");
	MovePen(x+l/2,y);
	DrawArc(l/2,0,360);
	EndFilledRegion();
	StartFilledRegion(1);
	SetPenColor("Black");
	MovePen(x+l/2.2,y);
	DrawArc(l/2.2,0,360);
	EndFilledRegion();
	
		//网格
	SetPenSize(2.5);
	SetPenColor("Gray");
	MovePen(x,y-l/10);
	DrawLine(0,l/2.2+l/10);
	MovePen(x,y-l/10);
	int i=0;
	for(i=0;i<=12;i++)
	{
		MovePen(x,y);
		DrawLine(cos(PI/6*i)*(l/2.2),sin(PI/6*i)*(l/2));
	}
	MovePen(x+l/2.6,y);
	DrawArc(l/2.6,0,360);
//	MovePen(x+l/4.4,y);
//	DrawArc(l/4.4,0,360);
	//眼睛 
	StartFilledRegion(1);
	SetPenColor(Color[1]);
	MovePen(x+l/50,y-l/10);
	DrawLine(l/3,l/3);
	DrawArc(sqrt(2)*l/6,45,-180); 
	EndFilledRegion();
	StartFilledRegion(1);
	MovePen(x-l/50,y-l/10);
	DrawArc(sqrt(2)*l/6,-45,-180);
	DrawLine(l/3,-l/3);
	EndFilledRegion();
	StartFilledRegion(1);
	SetPenColor(Color[6]);
	MovePen(x+l/15,y-l/10);
	DrawLine(l/4,l/4);
	DrawArc(sqrt(2)*l/8,45,-180);
	EndFilledRegion();
	StartFilledRegion(1);
	SetPenColor(Color[6]);
	MovePen(x-l/15,y-l/10);
	DrawArc(sqrt(2)*l/8,-45,-180);
	DrawLine(l/4,-l/4); 
	EndFilledRegion();
	SetPenColor(Color[1]);
	SetPenSize(1);
		 
}




void DrawWall(int px,int py,double size)
{
 	double x=0.25+px*0.3;
 	double y=0.25+py*0.3;
 	x=x-size/2;
 	y=y-size/2;
	SetPenColor("Dark1 Green"); 
	StartFilledRegion(1);
	MovePen(x,y);
 	DrawLine(size,0);
 	DrawLine(0,size);
 	DrawLine(-size,0);
	DrawLine(0,-size);
	EndFilledRegion();
	SetPenColor("White");
	MovePen(x,y+size/3);
	DrawLine(size,0);
 	MovePen(x,y+size*2/3);
	 DrawLine(size,0);
 	MovePen(x+size/2,y+size/3);
 	DrawLine(0,size/3);
// 	MovePen(x+size/3,y);
// 	DrawLine(0,size/3);
// 	MovePen(x+size/3,y+2*size/3);
// 	DrawLine(0,size/3);
 	
 	MovePen(x,y);
 	DrawLine(size,0);
	DrawLine(0,size);
	DrawLine(-size,0);
	DrawLine(0,-size); 
	SetPenColor(Color[1]);
	SetPenSize(1);
		 
}



void Homepage()
{
	DefineColor("Mred",1.0*189/256,1.0*7/256,1.0*20/256);
	DefineColor("Button",1.0*172/256,1.0*200/256,1.0*185/256);
	
	SetPenColor("White");
	StartFilledRegion(1);
	MovePen(0,0);
	DrawLine(15,0);
	DrawLine(0,10);
	DrawLine(-15,0);
	DrawLine(0,-10);
	EndFilledRegion();
	
	SetPenColor("Mred");
	drawRectangle(1.7,4.6,11.8,3.2,1);
	
	SetPenColor("White");
	SetPenSize(30);
	MovePen(2,5);Dun();
	DrawLine(0,2.5);Dun();
	DrawLine(0.8,-2.4);Dun();
	DrawLine(0.8,2.4);Dun();
	DrawLine(0,-2.5);Dun();
	
	
	MovePen(4,7.5);Dun();
	DrawLine(0.8,-1.2);Dun();
	DrawLine(0.8,1.2);Dun();
	MovePen(4.8,6.3);Dun();
	DrawLine(0,-1.3);Dun();
	
	MovePen(6,5);Dun();
	DrawLine(0,2.5);Dun();
	DrawLine(0.8,-2.4);Dun();
	DrawLine(0.8,2.4);Dun();
	DrawLine(0,-2.5);Dun();
	
	MovePen(8,5);Dun();
	DrawLine(0.8,2.5);Dun();
	DrawLine(0.8,-2.5);Dun();
	MovePen(8,5);
	DrawLine(0.3,0.9375);
	DrawLine(1,0);
	DrawLine(0.3,-0.9375);
	
	MovePen(10,7.5);Dun();
	DrawLine(1.3,0);Dun();
	DrawLine(-1.3,-2.5);Dun();
	DrawLine(1.3,0);Dun();
	
	MovePen(11.75,5);Dun();
	DrawLine(1.3,0);Dun();
	DrawLine(-1.3,0);Dun();
	DrawLine(0,1.25);Dun();
	DrawLine(1.3,0);Dun();
	DrawLine(-1.3,0);Dun();
	DrawLine(0,1.25);Dun();
	DrawLine(1.3,0);Dun();
	
	SetPenColor("Red");
	SetPenSize(1);
	MovePen(5.8,2);
	SetPointSize(16);
	DrawTextString("「Press Any Key To Continue」"); 
	SetPenSize(1);
	SetPointSize(1);
}



void Dun()
{
	double x=GetCurrentX(),y=GetCurrentY(),size=(double)GetPenSize();
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x-size/100+0.1,y-size/100+0.1);
	DrawLine(size/50-0.2,0);
	DrawLine(0,size/50-0.2);
	DrawLine(-size/50+0.2,0);
	DrawLine(0,-size/50+0.2);
	EndFilledRegion();
	MovePen(x,y);
	SetPenSize((int)size);		 
}




void DrawNet(int x,int y,double size){
	SetPenColor("Black");
	double cx,cy;
	double r;
	r=0.5*size;
	cx=0.25+(x)*0.3;
	cy=0.25+(y)*0.3;

	double a=0.5*(sqrt(5.0)-1);
	int i,j;
	
	MovePen(cx-a*r/2,cy-r*cos(0.1*PI));
	for(i=0;i<10;i++){	
		forward(a*r);
		theta=theta+36;
	}
	
	for(i=0;i<10;i++){
		theta=theta+36;
		MovePen(cx,cy);
		forward(r);	
	}
	MovePen(cx+size/4,cy);
	DrawArc(size/4,0,360);
	
	MovePen(cx+0.75*r,cy);
	DrawArc(0.75*r,0,360);

	MovePen(cx+0.25*r,cy);
	DrawArc(0.25*r,0,360);
		SetPenSize(1);
		 
}



void forward(double distance){
    double radians;
	radians = theta/ 180 * PI;
	DrawLine(distance * cos(radians), distance * sin(radians));
}


void block(int x,int y,int color,double size)
{
	size=size*1.5;
	//dx dy 为方块中间点坐标 
	double dx=0.25+0.2*1.5*x;
	double dy=0.25+0.2*1.5*y;
	//填充颜色 
	StartFilledRegion(1);
	SetPenColor(Color[color]);
	MovePen(dx-size/2,dy-size/2);
	DrawLine(size,0);
	DrawLine(0,size);
	DrawLine(-size,0);
	DrawLine(0,-size);
	EndFilledRegion();	 
}

void Block(int x,int y,int color,double size)
{
	size=size*1.5;
	//dx dy 为方块中间点坐标 
	double dx=0.25+0.2*1.5*x;
	double dy=0.25+0.2*1.5*y;
	//填充颜色 
	StartFilledRegion(1);
	SetPenColor(Color[color]);
	MovePen(dx-size/2,dy-size/2);
	DrawLine(size,0);
	DrawLine(0,size);
	DrawLine(-size,0);
	DrawLine(0,-size);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(dx-size/2,dy-size/2);
	DrawLine(size,0);
	DrawLine(0,size);
	DrawLine(-size,0);
	DrawLine(0,-size); 		 
}


void DrawBoom(int x,int y,double size)
{
	double dx=0.25+x*0.3;
	double dy=0.25+y*0.3;
	SetPenSize(3);
	SetPenColor("Brown");
	MovePen(dx,dy);
	DrawLine(size/1.8,size/1.8);
	SetPenSize(1);
	SetPenColor("Red");
	DrawLine(size/10,size/10);
	MovePen(dx+size/1.8,dy+size/1.8);
	DrawLine(-size/10,size/10);
	MovePen(dx+size/1.8,dy+size/1.8);
	DrawLine(size/10,-size/10);

	StartFilledRegion(1);
	SetPenColor("Black");
	MovePen(dx+size/2,dy);
	DrawArc(size/2,0,360);
	EndFilledRegion();
	StartFilledRegion(1);
	SetPenColor("Black");
	MovePen(dx+size/4,dy+size*sqrt(3)/4);
	DrawLine(size/10,size/10);
	DrawLine(size/5,-size/5);
	DrawLine(-size/10,-size/10);
	DrawLine(-size/5,size/5);
	EndFilledRegion();
	SetPenSize(1); 
}

void DrawEnd(int x,int y,double size)
{
	//dx dy 为方块左下角坐标 
	double dx=0.25+0.3*x-size/2;
	double dy=0.25+0.3*y-size/2;
	SetPenColor("Dark2 Green");
	StartFilledRegion(1);
	MovePen(dx,dy);
 	DrawLine(size,0);
 	DrawLine(0,size);
 	DrawLine(-size,0);
	DrawLine(0,-size);
	EndFilledRegion();
	
	SetPenColor("Dark3 Green");
	StartFilledRegion(1);
	MovePen(dx,dy);
 	DrawLine(size/3,size/6);
 	DrawLine(0,size*2/3);
 	DrawLine(-size/3,size/6);
	DrawLine(0,-size);
	EndFilledRegion();
	StartFilledRegion(1);
	MovePen(dx+size,dy);
 	DrawLine(-size/3,size/6);
 	DrawLine(0,size*2/3);
 	DrawLine(size/3,size/6);
	DrawLine(0,-size);
	EndFilledRegion();
	
	StartFilledRegion(1);
	SetPenColor("Yellow");
	MovePen(dx+size/2+size/8,dy+size/2+size/3);
	DrawArc(size/16,0,360);
	EndFilledRegion();
	
	StartFilledRegion(1);
	SetPenColor("Blue");
	MovePen(dx+size/2-size/24,dy+size/2);
	DrawArc(size/16,0,360);
	EndFilledRegion();
	
	StartFilledRegion(1);
	SetPenColor("Orange");
	MovePen(dx+size/2+size/8,dy+size/2-size/3);
	DrawArc(size/16,0,360);
	EndFilledRegion();
	
}

void DrawWin(int x,int y,double size){
	SetPenColor("Dark1 Green"); 
	
	StartFilledRegion(1);
	MovePen(x,y+5*size);
	DrawLine(size,0);
	DrawLine(size, -4*size);
	DrawLine(size, 4*size);
	DrawLine(size,0);
	DrawLine(size, -4*size);
	DrawLine(size, 4*size);
	DrawLine(size,0);
	DrawLine(-1.5*size, -5*size);
	DrawLine(-size,0);
	DrawLine(-size, 4*size);
	DrawLine(-size, -4*size);
	DrawLine(-size,0);
	DrawLine(-1.5*size, 5*size);
	EndFilledRegion();

	StartFilledRegion(1);
	MovePen(x+7.5*size,y+5*size);
	DrawLine(3*size,0);
	DrawLine(0,-size);
	DrawLine(-size,0);
	DrawLine(0,-3*size);
	DrawLine(size,0);
	DrawLine(0,-size);
	DrawLine(-3*size,0);
	DrawLine(0,size);
	DrawLine(size,0);
	DrawLine(0,3*size);
	DrawLine(-size,0);
	DrawLine(0,size);
	EndFilledRegion();

	StartFilledRegion(1);
	MovePen(x+11*size,y+5*size);
	DrawLine(2*size,0);
	DrawLine(2*size, -4*size);
	DrawLine(0, 4*size);
	DrawLine(size,0);
	DrawLine(0, -5*size);
	DrawLine(-2*size, 0);
	DrawLine(-2*size, 4*size);
	DrawLine(0, -4*size);
	DrawLine(-size, 0);
	DrawLine(0, 5*size);
	EndFilledRegion();
}

void DrawFail(int x, int y,double size){
	SetPenColor("Dark1 Green"); 
	
	StartFilledRegion(1);
	MovePen(x,y+5*size);
	DrawLine(4*size, 0);
	DrawLine(0, -size);
	DrawLine(-3*size, 0);
	DrawLine(0, -size);
	DrawLine(2*size,0);
	DrawLine(0, -size);
	DrawLine(-2*size, 0);
	DrawLine(0, -2*size);
	DrawLine(-size, 0);
	DrawLine(0, 5*size);
	EndFilledRegion();

	StartFilledRegion(1);
	MovePen(x+3*size,y);
	DrawLine(2*size, 5*size);
	DrawLine(size, 0);
	DrawLine(2*size, -5*size);
	DrawLine(-size, 0);

	DrawLine(-size,1.5*size);
	DrawLine(-size,0);
	DrawLine(-size,-1.5*size);
	DrawLine(-size,0);
	EndFilledRegion();

	SetPenColor("Dark5 Green");
	StartFilledRegion(1);
	MovePen(x+5*size,y+2.5*size);
	DrawLine(size,0);
	DrawLine(-0.5*size,1.5*size);
	DrawLine(-0.5*size,-1.5*size);
	EndFilledRegion();

	SetPenColor("Dark1 Green");
	StartFilledRegion(1);
	MovePen(x+8.5*size,y+5*size);
	DrawLine(3*size,0);
	DrawLine(0,-size);
	DrawLine(-size,0);
	DrawLine(0,-3*size);
	DrawLine(size,0);
	DrawLine(0,-size);
	DrawLine(-3*size,0);
	DrawLine(0,size);
	DrawLine(size,0);
	DrawLine(0,3*size);
	DrawLine(-size,0);
	DrawLine(0,size);
	EndFilledRegion();

	StartFilledRegion(1);
	MovePen(x+12*size,y+5*size);
	DrawLine(size,0);
	DrawLine(0,-4*size);
	DrawLine(3*size,0);
	DrawLine(0,-size);
	DrawLine(-4*size,0);
	DrawLine(0,5*size);
	EndFilledRegion();

}

void DrawBackground()
{
	DefineColor("Dark1 Green",48.0/256,72.0/256,76.0/256);
	DefineColor("Dark2 Green",16.0/256,44.0/256,48.0/256);
	DefineColor("Dark1 Yellow",90.0/256,80.0/256,40.0/256);
	DefineColor("Dark2 Yellow",220.0/256,190.0/256,100.0/256);
	DefineColor("Dark3 Green",79.0/256,97.0/256,93.0/256);
	DefineColor("Dark4 Green",182.0/256,195.0/256,190.0/256);
	DefineColor("Dark5 Green",208.0/256,213.0/256,210.0/256);
	int i;
	MovePen(0,0);
	SetPenColor("Dark5 Green");
	StartFilledRegion(1);
	DrawLine(0,10);
	DrawLine(15,0);
	DrawLine(0,-10);
	DrawLine(-15,0);	
	EndFilledRegion();
	
	
		MovePen(8,0);
	SetPenColor("Dark4 Green");
	StartFilledRegion(1);
	DrawLine(0,1.5);
	DrawLine(2.5,0);
	DrawLine(0,-1.5);
	DrawLine(-2.5,0);	
	EndFilledRegion();
	MovePen(6,0);
	SetPenColor("Dark3 Green");
	StartFilledRegion(1);
	DrawLine(0,0.5);
	DrawLine(2.5,0);
	DrawLine(0,-0.5);
	DrawLine(-2.5,0);	
	EndFilledRegion();
	

	
	
	
	
	MovePen(0,0);
	SetPenColor("Dark1 Green");
	StartFilledRegion(1);
	DrawLine(0,8);
	DrawLine(1,0);
	DrawLine(0,-8);
	DrawLine(-1,0);	
	EndFilledRegion();
	
	for(i=0;i<4;i++)
	{
		MovePen(0,i*2);
		SetPenColor("Dark2 Yellow");
		StartFilledRegion(1);
		DrawLine(0,0.8);
		DrawLine(0.8,0);
		DrawLine(0,-0.8);
		DrawLine(-0.8,0);	
		EndFilledRegion();
	}
	
	
	
	
	
	

		for(i=0;i<3;i++)
	{
		MovePen(3+i*3.5,0);
		SetPenColor("Dark1 Green");
		StartFilledRegion(1);
		DrawLine(0,2);
		DrawLine(0.5,0);
		DrawLine(0,-2);
		DrawLine(-0.5,0);	
		EndFilledRegion();
		MovePen(2.8+i*3.5,1.8);
		SetPenColor("Dark1 Green");
		StartFilledRegion(1);
		DrawLine(0,0.2);
		DrawLine(0.9,0);
		DrawLine(0,-0.2);
		DrawLine(-0.9,0);	
		EndFilledRegion();
	}
	
	MovePen(0.5,0);
	SetPenColor("Dark2 Green");
	StartFilledRegion(1);
	DrawLine(0,5.5);
	DrawLine(2,0);
	DrawLine(0,-5.5);
	DrawLine(-2,0);
	EndFilledRegion();
	
	MovePen(12.5,0);
	SetPenColor("Dark1 Green");
	StartFilledRegion(1);
	DrawLine(0,4.5);
	DrawLine(2.5,0);
	DrawLine(0,-4.5);
	DrawLine(-2.5,0);
	EndFilledRegion();
	
	MovePen(10.5,0);
	SetPenColor("Dark2 Green");
	StartFilledRegion(1);
	DrawLine(0,3.5);
	DrawLine(3,0);
	DrawLine(0,-3.5);
	DrawLine(-3,0);
	EndFilledRegion();
	
	MovePen(11,0.5);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.5);
	DrawLine(0.5,0);
	DrawLine(0,-0.5);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(11,1.5);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.5);
	DrawLine(0.5,0);
	DrawLine(0,-0.5);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(11,2.5);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.5);
	DrawLine(0.5,0);
	DrawLine(0,-0.5);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(11.6,0.5);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.5);
	DrawLine(0.5,0);
	DrawLine(0,-0.5);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(11.6,1.5);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.5);
	DrawLine(0.5,0);
	DrawLine(0,-0.5);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(11.6,2.5);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.5);
	DrawLine(0.5,0);
	DrawLine(0,-0.5);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	
	MovePen(1,3);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.25);
	DrawLine(0.5,0);
	DrawLine(0,-0.25);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(1,3.5);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.25);
	DrawLine(0.5,0);
	DrawLine(0,-0.25);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(1,4);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.25);
	DrawLine(0.5,0);
	DrawLine(0,-0.25);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(1,4.5);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.25);
	DrawLine(0.5,0);
	DrawLine(0,-0.25);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(1,5);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.25);
	DrawLine(0.5,0);
	DrawLine(0,-0.25);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(1.6,3);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.25);
	DrawLine(0.5,0);
	DrawLine(0,-0.25);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(1.6,3.5);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.25);
	DrawLine(0.5,0);
	DrawLine(0,-0.25);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(1.6,4);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.25);
	DrawLine(0.5,0);
	DrawLine(0,-0.25);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(1.6,4.5);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.25);
	DrawLine(0.5,0);
	DrawLine(0,-0.25);
	DrawLine(-0.5,0);	
	EndFilledRegion();
	MovePen(1.6,5);
	SetPenColor("Dark1 Yellow");
	StartFilledRegion(1);
	DrawLine(0,0.25);
	DrawLine(0.5,0);
	DrawLine(0,-0.25);
	DrawLine(-0.5,0);	
	EndFilledRegion();

	
	
	MovePen(2.5,0);
	SetPenColor("Dark2 Green");
	StartFilledRegion(1);
	DrawLine(0,1);
	DrawLine(3.5,0);
	DrawLine(0,-1);
	DrawLine(-3.5,0);	
	EndFilledRegion();
	
	MovePen(2.6,1);
	SetPenColor("Dark1 Green");
	StartFilledRegion(1);
	DrawLine(0,0.5);
	DrawLine(3.3,0);
	DrawLine(0,-0.5);
	DrawLine(-3.3,0);	
	EndFilledRegion();
	

	for(i=0;i<8;i++)
	{
		MovePen(2.7+i*0.4,1.1);
		SetPenColor("Dark3 Green");
		StartFilledRegion(1);
		DrawLine(0,0.35);
		DrawLine(0.15,0);
		DrawLine(0,-0.35);
		DrawLine(-0.15,0);	
		EndFilledRegion();
	}
	
		for(i=0;i<3;i++)
	{
		MovePen(3+i*1,0);
		SetPenColor("Dark1 Yellow");
		StartFilledRegion(1);
		DrawLine(0,0.5);
		DrawLine(0.5,0);
		DrawLine(0,-0.5);
		DrawLine(-0.5,0);	
		EndFilledRegion();
	}
	
		for(i=0;i<4;i++)
	{
		MovePen(14,0.5+i);
		SetPenColor("Dark2 Yellow");
		StartFilledRegion(1);
		DrawLine(0,0.5);
		DrawLine(0.5,0);
		DrawLine(0,-0.5);
		DrawLine(-0.5,0);	
		EndFilledRegion();
	}


		MovePen(2.5,2);
		SetPenColor("Dark1 Green");
		StartFilledRegion(1);
		DrawLine(0,1);
		DrawLine(8,0);
		DrawLine(0,-1);
		DrawLine(-8,0);	
		EndFilledRegion();
		
		for(i=0;i<8;i++)
	{
		MovePen(3+i*1,2.1);
		SetPenColor("Dark3 Green");
		StartFilledRegion(1);
		DrawLine(0,0.25);
		DrawLine(0.5,0);
		DrawLine(0,-0.25);
		DrawLine(-0.5,0);	
		EndFilledRegion();
	}
	
	
		for(i=0;i<3;i++)
	{
		MovePen(3.5+i*3,3);
		SetPenColor("Dark1 Green");
		StartFilledRegion(1);
		DrawLine(0,1);
		DrawLine(0.1,0);
		DrawLine(0,-1);
		DrawLine(-0.1,0);	
		EndFilledRegion();
		MovePen(3.5+i*3,4);
		SetPenColor("Gray");
		StartFilledRegion(1);
		DrawLine(0,0.1);
		DrawLine(-0.2,0);
		DrawLine(0,-0.1);
		DrawLine(0.2,0);	
		EndFilledRegion();
		MovePen(3.4+i*3,4.1);
		SetPenColor("Gray");
		StartFilledRegion(1);
		DrawLine(0,0.1);
		DrawLine(-0.2,0);
		DrawLine(0,-0.1);
		DrawLine(0.2,0);	
		EndFilledRegion();
	}
	
	SetPenColor("Black");
	
}



void DrawRankFrame(double x,double y)
{//输入框左上点的坐标！
		SetPenColor("Dark4 Green");
		StartFilledRegion(1);
		MovePen(x,y);
		DrawLine(4,0);
		DrawLine(0,-3);
 		DrawLine(-4,0);
 		DrawLine(0,3);	
		EndFilledRegion();
		SetPenColor("Black");
		MovePen(x,y);
		DrawLine(4,0);
		DrawLine(0,-3);
 		DrawLine(-4,0);
 		DrawLine(0,3);
 		int i;
 		for(i=1;i<6;i++)
		{
 		MovePen(x,y-i*0.6);
 		DrawLine(4,0);
 		}
 		MovePen(x,y);
 		DrawLine(0,-3);
 		MovePen(x+0.5,y);
		DrawLine(0,-3);
 		MovePen(x+2.5,y);
		DrawLine(0,-3);
}
