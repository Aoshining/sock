#include"display.h"

void display()
{	
	if(Enter!=3)
	{
		DisplayClear();
		DrawBackground();
		if(Enter==0)
		{
			if(!help)Button_Main_Menu();//主菜单的实时显示 
			else Help();
		}
		else if(Enter==1)
		{
			if(!help)Button_Second_Menu();//副菜单的实时显示
			else Help(); 
		}
		
		else if(Enter==2)//自动建图和手动建图的实时显示 
		{
			if(!help)
			{
				Print_Maze();
				if(Button_find_the_shortest_way==1)
				{
					if(no_way==1)
					{
						MovePen(12,5);
						DrawTextString("没路啦");
					} 
					else{
						int i;
						for(i=min-1;i>=0;i--)
						Block(path1[i],path2[i],3,0.2);
					}
					
				}
				
				Print_way1();
				Print_way2();
				
				if(Auto)Life();
				if(Auto&&!Go)
				{
					Button_MenuList();
					Boom();
					MovePen(0.5,9.4);
					sprintf(level, "%d", Level);
					if(Enter==2&&!help)
					{
						DrawTextString("平行宇宙"); 
						DrawTextString(level);
						Button_Boom(Cx,Cy,Cevent);
					}
					
				}
				else if(!Auto)Button_MenuList2();
				else if(Go)Button_MenuList4();
				if(DIY)Button_DIY(Cx,Cy,Cevent);
				if(Hint)
				{
					Button_Hint();
				}
				if(Tip)
				{
					MovePen(11.5,6.25);
					if(Tip==1)DrawTextString("请关闭提示后再使用寻路功能");
					if(Tip==2)DrawTextString("无法找到出路"); 
				}
				if(Is&&Enter==2)sp(Bx,By,0.3);
				if(Map[Bx][By]==EXT&&Go)
				{
					heat=1;
					DrawWin(10,5,0.3);
				}
				else if(Map[Bx][By]==EXT)
				{
					Level++;
					Button_Refresh(); 
				}
			}
			else Help();
		}
		else if(Enter==4)Button_Difficulty();
		else if(Enter==5)Homepage();
	}
	else if(Enter==3)//迷雾模式的实时显示 
	{
		DisplayClear();
		DrawBackground();
		if(!help)
		{
			Button_MenuList3();
			if(Enter==3)
			{
				Button_rank();
				Life();
			}
			if(rank1==1)
			{
				char a[5][1000];
				int i=0,k=5;
				struct Ranking *p;
				p=Head;
				for(i=0;i<5;i++)
				{
					sprintf(a[i],"%d           %s         %d",i+1,p->Name,p->score);
					p=p->Next;
					MovePen(11,k);
					DrawTextString(a[i]);
					k=k-0.5;
				}
			}
			
			if(Timer3==0&&Enter==3)
			{
	//			InitConsole();
	//			printf("!!"); 
				MovePen(12,6.8);
				sprintf(time1, "%d", Time);
				DrawTextString(time1);
				Print_Maze();
				sp(Bx,By,0.3);
			}
			if(Button_Stop==1)
			{
				MovePen(12,6.8);
				sprintf(time1, "%d", Time);
				DrawTextString(time1);//关闭迷雾时也需要显示时间 	
				sp(Bx,By,0.3);
				//Print_way1();
				Print_Maze();
				Print_way1();
			}
			if(Button_find_way_down==1&&Timer1==0)
			Print_way1();
			if(Map[Bx][By]==EXT) 
			{
				heat=1;
				DrawWin(10,5,0.3);
				cancelTimer(TIMER_BLINK1500);//到达终点则停止计时 
				Timer33=0;
				Timer3=0;
				Winer=1;
			}
			if(Tip)
			{
				MovePen(11.5,6.5);
				DrawTextString("请先关闭迷雾!");
			}
			if(Winer==1&&winer==0)
			{
				MovePen(10.9,5.72);
				DrawTextString("请输入姓名"); 
				textbox(GenUIID(0),12,5.5,2,0.5, Name, sizeof(Name));
			}
			if(winer==1)
			{
				if(link!=0&&Get_in==0)
				{	
								
					Add_rank(Name,Time); 
					Get_in=1;
					InitConsole();
						printf("%d",Head->score);

			
				}			
			}
		}
		else Help();	
	}
}
void Display()
{	

	
	if(Timer33==1&&!help)
	{
		DisplayClear(); 
		DrawBackground();
		if(Enter==3)
		{
			Button_rank();
			Life();
		}
		
		MovePen(12,6.8);
		sprintf(time1, "%d", Time);
		DrawTextString(time1);//实时显示时间 
		Fog_model();
		Button_MenuList3();
		if(Tip)
		{
			MovePen(11.5,6.5);
			DrawTextString("请先关闭迷雾!");
		}
		if(rank1==1)
		{
			char a[5][1000];
			int i=0,k=5;
			struct Ranking *p;
			p=Head;
			for(i=0;i<5;i++)
			{
				sprintf(a[i],"%d           %s         %d",i+1,p->Name,p->score);
				p=p->Next;
				MovePen(11,k);
				DrawTextString(a[i]);
				k=k-0.5;
			}
		}
	} 
	
}
