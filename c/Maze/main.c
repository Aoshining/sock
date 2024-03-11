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


int Map[L][L];//��¼�Թ���ͼ 
int Bx=2,By=2;//�ƶ���ʵʱλ������ 
int visit[50][50]={0};//��¼�Ƿ����
int road[2000][2];//��¼
int step=0;//����˳�� 
int Ex,Ey;//�������� 
int Difficulty=2;//�Թ����Ӷ� 
int All_the_way[L*L][2];//��¼Ѱ·���������е������ 
int All_step;//��¼������ 
int mseconds500 = 5; //·����ʾ��ʱ��ʱ���� 
int mseconds1000 = 1;//Ѱ·������ʾʱ���� 
int mseconds1500=1000;
int Time_i=0;
int Time_j=0;
int Timer1=0;//��ʱ��1��״̬ 
int Timer2=0;//��ʱ��2��״̬ 
int Timer3=0;//��ʱ��3��״̬ 
int Timer33=0;//��ʱ��3��״̬ 
int Time=0;//��¼ʱ�� 
char time1[10];//����ʱ������ 
int Level=1;//��¼�ؿ� 
char level[10];//����ؿ����� 
double life=5;//����ֵ
int boom=0;//ը������ 
int All_way_visit[L][L];//ÿ�����״̬ �ж��Ƿ������ 
double Cx,Cy;int Cevent;//��¼����ʵʱ���꼰������� 
char Name[100];
int path1[L*L],path2[L*L]; 
int trace[2][2];//��¼�ƶ������һ�������ϲ� 
int trap[2];//��¼�ƶ���ȵ������һ�� 

int no_way=0;//״̬�����ж��Ƿ���· 
int Get_the_end=0;//״̬�����ж��Ƿ񵽴��յ� 
int Button_find_way_down=0;//״̬�����ж�"Find the way"�Ƿ�ִ�� 
int Button_find_all_the_way=0;//״̬�����ж�"Find all the way"�Ƿ�ִ�� 
int Button_Stop=0;//״̬�����ж�"Button_stop"�Ƿ�ִ�� 
int Button_Start=0;//״̬�����ж�"Button_start"�Ƿ�ִ�� 
int Button_find_the_shortest_way=0;//״̬���жϡ�find the shortest way���Ƿ��� 
int Min=L*L;
int Button_DIYKey=0; //״̬�����жϰ���"Start"/"End"/"Wall"�Ƿ��� 
int Is=1;//״̬�����ж��Ƿ��ӡ�ƶ����� 
int Enter=5;//״̬�����жϽ������ĸ����� 
int Auto=1;//״̬�����ж��Ƿ�����Զ���ͼģʽ
int Go=0;//״̬�����ж��Ƿ����һ����ǰģʽ
int Item=0;//״̬�����ж��Ƿ�򿪵����� 
int DIY=0;//״̬�����ж��Ƿ���˱༭�˵�  
int Tip=0;//״̬�����ж��Ƿ�������� 
int Winer=0;//״̬�����ж��Ƿ��ʤ 
int winer=0;//״̬�����ж��Ƿ�������� 
int link=0;//״̬����ȷ���Ƿ������� 
int Get_in=0;//״̬����ȷ���Ƿ��������� 
int rank1=0;//״̬�����ж������Ƿ��� 
int Hint=0;//״̬�����ж���ʾ�Ƿ�� 
int lose=0;//״̬������¼��Ϸ�Ƿ���� 
int heat=0;//״̬������¼��Ϸ�Ƿ�ʤ�� 
char CurrentFileName[MAX_PATH];//�����ļ���ز��������ļ��� 
int min=0;//��С· 
int help=1;//״̬�����жϽ����Ƿ�� 
// ��ɫ�� 
char Color[][100]={"Blue","Black","Red","Green","Gray","Yellow","White","Dark Gray","Light Gray","Brown","Orange","Violet","Magenta","Cyan"}; 
struct Ranking *Head,*tail;

//ʵʱ��ʾ 
void display(void);

//����ģʽ������ʵʱ��ʾ 
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
			if(!help)Button_Main_Menu();//���˵���ʵʱ��ʾ 
			else Help();
		}
		else if(Enter==1)
		{
			if(!help)Button_Second_Menu();//���˵���ʵʱ��ʾ
			else Help(); 
		}
		
		else if(Enter==2)//�Զ���ͼ���ֶ���ͼ��ʵʱ��ʾ 
		{
			if(!help)
			{
				Print_Maze();
				if(Button_find_the_shortest_way==1)
				{
					if(no_way==1)
					{
						MovePen(11.5,6.25);
						DrawTextString("û·��");
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
						DrawTextString("ƽ������"); 
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
					if(Tip==1)DrawTextString("��ر���ʾ����ʹ��Ѱ·����");
					if(Tip==2)DrawTextString("�޷��ҵ���·"); 
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
	else if(Enter==3)//����ģʽ��ʵʱ��ʾ 
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
				DrawTextString(time1);//ʵʱ��ʾʱ�� 
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
				DrawTextString(time1);//ʵʱ��ʾʱ�� 
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
				cancelTimer(TIMER_BLINK1500);//�����յ���ֹͣ��ʱ 
				Timer33=0;
				Timer3=0;
				Winer=1;
			}
			if(Tip)
			{
				MovePen(11.5,6.5);
				DrawTextString("���ȹر�����!");
			}
			if(Winer==1&&winer==0)
			{
				MovePen(9.4,7.7);
				setTextBoxColors("Button","Dark Gray","Button","Dark Gray",1);
				SetPenColor("Dark Gray");
				DrawTextString("����������"); 
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
		DrawTextString(time1);//ʵʱ��ʾʱ�� 
		SetPenColor("Black");
		SetPointSize(1);
		Fog_model();sp(Bx,By,0.3);
		Button_MenuList3();
		if(Tip)
		{
			MovePen(11.5,6.5);
			DrawTextString("���ȹر�����!");
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
