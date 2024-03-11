#include "basic.h"
#include "model.h"
//迷雾 
void Fog_model()
{

	
	if(Timer3==0)
	{
		display();
	}
	else if(Timer3==1)//实现闪烁式显示地图 
	{
		StartFilledRegion(1);
		SetPenColor("Gray");
	    MovePen(0.4,0.4);
		DrawLine(8.4,0);
		DrawLine(0,8.4);
		DrawLine(-8.4,0);
		DrawLine(0,-8.4);
		EndFilledRegion();
		SetPenColor("Black");
//		DrawNet(15,15,10);
		int i,j;
		for(i=-1;i<=1;i++)
			for(j=-1;j<=1;j++)
				switch(Map[Bx+i][By+j])
				{
					case BLK:DrawWall(Bx+i,By+j,0.3);break;
					case ACS:block(Bx+i,By+j,8,0.2);break;
					case TRP2:block(Bx+i,By+j,8,0.2);DrawNet(Bx+i,By+j,0.3);break;
					case EXT:DrawEnd(Bx+i,By+j,0.3);break;
					case BOM:DrawBoom(Bx+i,By+j,0.25);break;
				};
	}
}


//生命值 
void Life()
{
	if(!heat&&(!life||(Map[Bx-1][By]==BLK&&Map[Bx+1][By]==BLK&&Map[Bx][By-1]==BLK&&Map[Bx][By+1]==BLK)))
	{
		DrawFail(10,5,0.3);
		lose=1;
	}
	else if(life>0)
	{
		SetPenColor("Dark Gray");
		MovePen(1.7,9.4);
		DrawTextString("HP");
		if(life==5)SetPenColor("Light Gray");
		else if(life==4)SetPenColor("Dark3 Green");
		else if(life==3)SetPenColor("Dark1 Green");
		else if(life==2)SetPenColor("Dark2 Green");
		else if(life==1)SetPenColor("Black");
		drawRectangle(2,9.37,life,0.2,1);
		if(Map[Bx][By]==TRP)Map[Bx][By]=TRP2;
	}
}

//炸弹 
void Boom()
{
	if(Map[Bx][By]==BOM)
	{
		Map[Bx][By]=ACS;
		boom++;
	}
}
