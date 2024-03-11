#include "basic.h"
#include "ui.h"
#include "help.h"
#include "file.h"
#include "map.h"
#include "rank.h"
#include "way.h"
#include "move.h"
#include "model.h"
#include "callback.h"


int Map[L][L];//记录迷宫地图 
int Bx=2,By=2;//移动物实时位置坐标 
int visit[50][50]={0};//记录是否访问
int road[2000][2];//记录
int step=0;//行走顺序 
int Ex,Ey;//出口坐标 
int Difficulty=2;//迷宫复杂度 
int All_the_way[L*L][2];//记录寻路过程中所有点的坐标 
int All_step;//记录坐标编号 
int mseconds500 = 5; //路径显示计时器时间间隔 
int mseconds1000 = 1;//寻路过程显示时间间隔 
int mseconds1500=1000;
int Time_i=0;
int Time_j=0;
int Timer1=0;//计时器1的状态 
int Timer2=0;//计时器2的状态 
int Timer3=0;//计时器3的状态 
int Timer33=0;//计时器3的状态 
int Time=0;//记录时长 
char time1[10];//保存时长数据 
int Level=1;//记录关卡 
char level[10];//保存关卡数据 
double life=5;//生命值
int boom=0;//炸弹数量 
int All_way_visit[L][L];//每个点的状态 判断是否输出过 
double Cx,Cy;int Cevent;//记录鼠标的实时坐标及按下情况 
char Name[100];
int path1[L*L],path2[L*L]; 
int trace[2][2];//记录移动物的上一步和上上步 
int trap[2];//记录移动物踩到陷阱的一步 

int no_way=0;//状态量。判断是否有路 
int Get_the_end=0;//状态量，判断是否到达终点 
int Button_find_way_down=0;//状态量，判断"Find the way"是否被执行 
int Button_find_all_the_way=0;//状态量，判断"Find all the way"是否被执行 
int Button_Stop=0;//状态量，判断"Button_stop"是否被执行 
int Button_Start=0;//状态量，判断"Button_start"是否被执行 
int Button_find_the_shortest_way=0;//状态量判断“find the shortest way”是否按下 
int Min=L*L;
int Button_DIYKey=0; //状态量，判断按键"Start"/"End"/"Wall"是否按下 
int Is=1;//状态量，判断是否打印移动物体 
int Enter=5;//状态量，判断进入了哪个界面 
int Auto=1;//状态量，判断是否进入自动建图模式
int Go=0;//状态量，判断是否进入一往无前模式
int Item=0;//状态量，判断是否打开道具栏 
int DIY=0;//状态量，判断是否打开了编辑菜单  
int Tip=0;//状态量，判断是否给出警告 
int Winer=0;//状态量，判断是否获胜 
int winer=0;//状态量，判断是否输入完成 
int link=0;//状态量，确认是否建立链表 
int Get_in=0;//状态量，确认是否输入链表 
int rank1=0;//状态量，判断排名是否按下 
int Hint=0;//状态量，判断提示是否打开 
int lose=0;//状态量，记录游戏是否结束 
int heat=0;//状态量，记录游戏是否胜利 
char CurrentFileName[MAX_PATH];//存入文件相关操作所需文件名 
int min=0;//最小路 
int help=1;//状态量，判断介绍是否打开 
// 颜色库 
char Color[][100]={"Blue","Black","Red","Green","Gray","Yellow","White","Dark Gray","Light Gray","Brown","Orange","Violet","Magenta","Cyan"}; 
struct Ranking *Head,*tail;

//实时显示 
void display(void);

//迷雾模式的特殊实时显示 
void Display();



void Main()
{
	SetWindowTitle("My Maze");
	SetWindowSize(15,10);
	InitGraphics();
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent( MouseEventProcess);
	registerTimerEvent(TimerEventProcess);
	registerCharEvent(CharEventProcess);	
}




void display(void)
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
						MovePen(11.5,6.25);
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
				if(Is&&Enter==2&&!help)sp(Bx,By,0.3);
				if(Map[Bx][By]==EXT&&Go)
				{
					heat=1;
					DrawWin(10,5,0.3);
				}
				else if(Auto&&!Go&&Map[Bx][By]==EXT)
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
			if(Enter==3&&!help)
			{
				Button_rank();
				Life();
			}
			if(rank1==1)
			{
				char a[5][1000];
				double k=4.5;
				int i=0;
				struct Ranking *p;
				p=Head;
				DrawRankFrame(10,5);
				for(i=0;i<5;i++)
				{
					sprintf(a[i],"%d               %s                                %d",i+1,p->Name,p->score);
					p=p->Next;
					MovePen(10.1,k);
					DrawTextString(a[i]);
					k=k-0.6;
				}
			}
			
			if(Timer3==0&&Enter==3&&!help)
			{
	//			InitConsole();
	//			printf("!!"); 
				MovePen(13.5,8);
				sprintf(time1, "%d", Time);
				SetPointSize(60);
				SetPenColor("Dark1 Green");
				DrawTextString(time1);//实时显示时间 
				SetPenColor("Black");
				SetPointSize(1);
				Print_Maze();
				sp(Bx,By,0.3);
			}
			if(Button_Stop==1&&!help)
			{
				MovePen(13.5,8);
				sprintf(time1, "%d", Time);
				SetPointSize(60);
				SetPenColor("Dark1 Green");
				DrawTextString(time1);//实时显示时间 
				SetPenColor("Black");
				SetPointSize(1);	
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
				MovePen(9.4,7.7);
				setTextBoxColors("Button","Dark Gray","Button","Dark Gray",1);
				SetPenColor("Dark Gray");
				DrawTextString("请输入姓名"); 
				textbox(GenUIID(0),9,7.1,2,0.5, Name, sizeof(Name));
			}
			if(winer==1)
			{
				if(link!=0&&Get_in==0)
				{	
								
					Add_rank(Name,Time); 
					Get_in=1;
//					InitConsole();
//					printf("%d",Head->score);

			
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
		
		MovePen(13.5,8);
		sprintf(time1, "%d", Time);
		SetPointSize(60);
		SetPenColor("Dark1 Green");
		DrawTextString(time1);//实时显示时间 
		SetPenColor("Black");
		SetPointSize(1);
		Fog_model();sp(Bx,By,0.3);
		Button_MenuList3();
		if(Tip)
		{
			MovePen(11.5,6.5);
			DrawTextString("请先关闭迷雾!");
		}
		if(rank1==1)
		{
			char a[5][1000];
				double k=4.5;
				int i=0;
			struct Ranking *p;
			p=Head;
			DrawRankFrame(10,5);
			for(i=0;i<5;i++)
			{
				sprintf(a[i],"%d               %s                                %d",i+1,p->Name,p->score);
				p=p->Next;
				MovePen(10.1,k);
				DrawTextString(a[i]);
				k=k-0.6;
			}
		}
	} 
	
}
