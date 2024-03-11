

#include "button.h"



//���˵���ť���� 
void Button_Main_Menu()
{
	setButtonColors("Button","Dark Gray","Button","Dark Gray",1);
	if(button(GenUIID(0),6,6,3,1,"��ʼ��Ϸ"))
	{
		Enter=1;//����ڶ����� 
		DisplayClear();
		display();
	}
	else if(button(GenUIID(0),6,5,3,1,"����"))
	{
		Enter=4;
		DisplayClear();
		display();
	}
	else if(button(GenUIID(0),6,4,3,1,"����"))
	{
		help=1;
		DisplayClear();
		display();
	} 
	else if(button(GenUIID(0),6,3,3,1,"�˳���Ϸ"))exit(-1);
}


//�ڶ�����˵���ť���� 
void Button_Second_Menu()
{
	setButtonColors("Button","Dark Gray","Button","Dark Gray",1);
	if(button(GenUIID(0),5.5,7.5,4,1,"����ģʽ"))
	{
		Enter=2;//����������� 
		DisplayClear();
		Auto=1;
		Maze();
		display();
	}
	else if(button(GenUIID(0),5.5,6.5,4,1,"�Զ���ģʽ"))
	{
		Enter=2;
		DisplayClear();
		Auto=0;
		Button_DIYCreate();
		display();
	}
	else if(button(GenUIID(0),5.5,5.5,4,1,"����ģʽ"))
	{
		DisplayClear();
		Enter=3;//��������ģʽ 
		Maze();
		display();
    }
    else if(button(GenUIID(0),5.5,4.5,4,1,"��һ����ǰ��ģʽ"))
    {
    	DisplayClear();
    	Enter=2;
    	Go=1;
    	Maze();
    	display();
	}
	else if(button(GenUIID(0),5.5,3.5,4,1,"����"))
	{
		help=1;
		DisplayClear();
		Help();
	}
	else if(button(GenUIID(0),5.5,2.5,4,1,"����"))
	{
		DisplayClear();
		Enter=0;//���ص�һ�������˵� 
		display();
	}

}



void Button_MenuList()
{
	setButtonColors("Button","Dark Gray","Button","Dark Gray",0);
	setMenuColors("Button","Dark Gray","Button","Dark Gray",0);
	char *menuListFile[]={"�ļ�",
	"�� | Ctrl-0",
	"�½� | Ctrl-1",
	"���� | Ctrl-2"};
	int selection=menuList(GenUIID(0),9,9.5,2,2.5,0.5,menuListFile,sizeof(menuListFile)/ sizeof(menuListFile[0]));
	if(selection==1)Open_File(CurrentFileName);
	if(selection==2)
	{
		Auto=0;
		Button_DIYCreate();//�ִ����Զ���ͼģʽ���½��ļ���Ч�ڽ����ֶ���ͼģʽ 
		Open_File(CurrentFileName);
	}
	if(selection==3)Save_File(CurrentFileName);
	
	char *menuListTool[]={"����",
	"���� | Ctrl-B",
	"ˢ�� | Ctrl-R",
	"Ѱ· | Ctrl-F",
	"Ѱ������·�� | Ctrl-A",
	"��ʾ | Ctrl-T"
	};
	//���ݰ��������ʾ��ͬ�Ķ�̬��ǩ 
	menuListTool[3]=(Button_find_way_down)?"���Ѱ· | Ctrl-F":"Ѱ· | Ctrl-F";
	menuListTool[4]=(Button_find_all_the_way)?"���Ѱ· | Ctrl-A":"���ӻ�Ѱ· | Ctrl-A";
	menuListTool[5]=Hint?"�ر���ʾ | Ctrl-T":"��ʾ | Ctrl-T";
	menuListTool[6]=Item?"�رյ��� | Ctrl-I":"���� | Ctrl-I";
	
	int decision=menuList(GenUIID(0),11,9.5,2,3,0.5,menuListTool,sizeof(menuListTool)/ sizeof(menuListTool[0]));
	if(decision==1)
	{
		Button_Refresh(); 
		DisplayClear();
		Enter=1;
		//���ص��ڶ��˵���������״̬�����ʼ��
		Item=0;
		boom=0;
		Level=1; 
		life=5;
		Hint=0;
		display();
	}
	if(decision==2)
	{
		Item=0;
		boom=0;
		Level=1; 
		life=5;
		Hint=0;
		Button_Refresh();
	}
	if(decision==3&&!Hint)Button_Find_the_road();
	else if(decision==3&&Hint)Tip=1;
	if(decision==4&&!Hint)Button_Find_all_the_road();
	else if(decision==4&&Hint)Tip=1;
	if(decision==5)
	{
		Tip=0;
		Hint=!Hint;
		Button_Hint();
	}

	
	if(Enter==2)if(button(GenUIID(0),13,9.5,2,0.5,"����"))
	{
		help=1;
		DisplayClear();
		Help();
	}
}

void Button_Boom(double x,double y,int Event)
{
	setButtonColors("Button","Dark Gray","Button","Dark Gray",0);
		MovePen(7.5,9.2);
		DrawTextString("ʣ�ࣺ");
		char boomnum[10];
		sprintf(boomnum, "%d", boom);
		DrawTextString(boomnum);
		if(!Item)
		{
			if(button(GenUIID(0),7.5,9.5,1.5,0.5,"ը��"))
			{
				Item=1;
				DisplayClear();
				display();
			}
		}
		else if(Item)
		{
			double dx=floor((x+0.15-0.25)/0.3),dy=floor((y+0.15-0.25)/0.3);
			if(dx>=2&&dy>=2&&dx<=L-3&&dy<=L-3&&Event==BUTTON_DOWN&&(Map[(int)dx][(int)dy]==BLK||Map[(int)dx][(int)dy]==TRP||Map[(int)dx][(int)dy]==TRP2))
			{
				if(boom>0)
				{
					SetEraseMode(TRUE);
					DrawWall(dx,dy,0.3);
					SetEraseMode(FALSE);
					Map[(int)dx][(int)dy]=ACS;
					boom--;
				}
				else
				{
					MovePen(4,0.5);
					DrawTextString("ը������");
				}
			}	
			if(button(GenUIID(0),7.5,9.5,1.5,0.5,"ȡ��"))
			{
				Item=0;
				DisplayClear();
				display();
			}
		}
	
	
}



void Button_MenuList4()
{
	setButtonColors("Button","Dark Gray","Button","Dark Gray",0);
	setMenuColors("Button","Dark Gray","Button","Dark Gray",0);
	char *menuListFile[]={"�ļ�",
	"�� | Ctrl-0",
	"�½� | Ctrl-1",
	"���� | Ctrl-2"};
	int selection=menuList(GenUIID(0),9,9.5,2,2.5,0.5,menuListFile,sizeof(menuListFile)/ sizeof(menuListFile[0]));
	if(selection==1)Open_File(CurrentFileName);
	if(selection==2)
	{
		Auto=0;
		Button_DIYCreate();//����ִ����Զ���ͼģʽ���½��ļ���Ч�ڽ����ֶ���ͼģʽ 
		Open_File(CurrentFileName);
	}
	if(selection==3)Save_File(CurrentFileName);
	
	char *menuListTool[]={"����",
	"���� | Ctrl-B",
	"ˢ�� | Ctrl-R",
	"Ѱ· | Ctrl-F",
	"Ѱ������·�� | Ctrl-A",
	"��ʾ | Ctrl-T",
	"���¿�ʼ | Ctrl-P"
	};
	//���ݰ��������ʾ��ͬ�Ķ�̬��ǩ 
	menuListTool[3]=(Button_find_way_down)?"���Ѱ· | Ctrl-F":"Ѱ· | Ctrl-F";
	menuListTool[4]=(Button_find_all_the_way)?"���Ѱ· | Ctrl-A":"���ӻ�Ѱ· | Ctrl-A";
	menuListTool[5]=Hint?"�ر���ʾ | Ctrl-T":"��ʾ | Ctrl-T";
	
	int decision=menuList(GenUIID(0),11,9.5,2,3,0.5,menuListTool,sizeof(menuListTool)/ sizeof(menuListTool[0]));
	if(decision==1)
	{
		Button_Refresh(); 
		DisplayClear();
		Enter=1;
		//���ص��ڶ��˵���������״̬�����ʼ��
		life=5; 
		Go=0;
		display();
	}
	if(decision==2)
	{
		life=5;
		Button_Refresh();
	}
	if(decision==3&&!Hint)
	{
		Button_Find_the_road();
		if(!Get_the_end&&Button_find_way_down)Tip=2;
		else Tip=0;
	}
	else if(decision==3&&Hint)Tip=1;
	if(decision==4&&!Hint)
	{
		Button_Find_all_the_road();
		if(!Get_the_end&&Button_find_all_the_way)Tip=2;
		else Tip=0;
	}
	else if(decision==4&&Hint)Tip=1;
	if(decision==5)
	{
		Tip=0;
		Hint=!Hint;
		Button_Hint();
	}
	if(decision==6)
	{
		if(trace[1][0]||trace[1][1])Map[Bx-trace[0][0]-trace[1][0]][By-trace[0][1]-trace[1][1]]=ACS;
		if(trace[0][0]||trace[0][1])Map[Bx-trace[0][0]][By-trace[0][1]]=ACS;
		trace[0][0]=0;trace[0][1]=0;trace[1][0]=0;trace[1][1]=0;
		Bx=2;By=2;
		life=5;
		lose=0;
		DisplayClear();
		display();
	}
	
	if(Enter==2)if(button(GenUIID(0),13,9.5,2,0.5,"����"))
	{
		help=1;
		DisplayClear();
		Help();
	}
}

void Button_Find_the_shortest_road()
{
	if(Button_find_the_shortest_way==0)
	{
		if(no_way==1)
		{
			MovePen(11.5,6.25);
			DrawTextString("û·��");
		}
		else
		{
			int i;
			Find_the_shortest_road(Bx,By);
			//for(i=min-1;i>=0;i--)
			//printf("(%d��%d)",path1[i],path2[i]);
			for(i=min-1;i>=0;i--)
			Block(path1[i],path2[i],3,0.2);
		}
		Button_find_the_shortest_way++;
	}
	else
	{
		int i;
		Button_find_the_shortest_way--;
		SetEraseMode(TRUE);
		if(no_way==1)
		{
			MovePen(11.5,6.25);
			DrawTextString("û·��");
		}
		else
		{
			for(i=min-1;i>=0;i--)
			Block(path1[i],path2[i],3,0.2);
		}
		
		SetEraseMode(FALSE);
		for(i=0;i<min;i++)
		{
			path1[i]=0;
			path2[i]=0;
		}
		min=0;
		no_way=0;
	}
	
}






void Button_DIYCreate()
{
	DisplayClear();
	Auto=0;//��¼�����ֶ���ͼ��״̬ 
	Is=0;//�ر�ʵʱ��ӡ�ƶ���
	//����ֻ��Χǽ�Ŀհ׵�ͼ 
	int i,j;
	for(i=0;i<L;i++)
	for(j=0;j<L;j++)
			{
				Map[i][j]=ACS;
			}
	for(i=1;i<L-1;i++)
	{
		DrawWall(i,1,0.3);Map[i][1]=BLK;
		DrawWall(1,i,0.3);Map[1][i]=BLK;
		DrawWall(L-1-i,L-2,0.3);Map[L-1-i][L-2]=BLK;
		DrawWall(L-2,L-1-i,0.3);Map[L-2][L-1-i]=BLK;
	}
	display();
}

void Button_DIY(double x,double y,int Event)
{
	setButtonColors("Button","Dark Gray","Button","Dark Gray",0);
	static int inEdit1=0,inEdit2=0;//ά���������ֱ༭״̬����һֱִ�� 
	static int start=0,end=0;//��¼�����յ���������ֹ������� 
	double dx,dy;
	if(DIY)
	{
		if(button(GenUIID(0),11,7,1,0.5,Button_DIYKey==0?"���":(Button_DIYKey==1?"�յ�":"ǽ"))||inEdit1){
		inEdit1=1;
		if(Button_DIYKey==0)//������� 
		{
			dx=floor((x+0.15-0.25)/0.3);dy=floor((y+0.15-0.25)/0.3);//��ȷ���껻�㣬��֤���������ġ� 
			if(dx>=2&&dy>=2&&dx<=L-3&&dy<=L-3&&Event==BUTTON_DOWN)//���Ʊ༭���� 
			{
				if(start)//�ж��Ƿ��Ѿ�������㣬������������������ж��յ�����ͬ�� 
				{
					SetEraseMode(TRUE);
					sp(Bx,By,0.3);
					SetEraseMode(FALSE);
					block(Bx,By,8,0.3);
				}
				Map[(int)dx][(int)dy]=ACS; 
				Bx=dx;By=dy;//��¼������� 
				sp(dx,dy,0.3);
				Is=1;//�Ѵ�����㣬����ʵʱ��ӡ������� 
				start++;
			}
		}
		else if(Button_DIYKey==1)//�����յ� 
		{
			dx=floor((x+0.15-0.25)/0.3);dy=floor((y+0.15-0.25)/0.3);
			if(dx>=2&&dy>=2&&dx<=L-3&&dy<=L-3&&Event==BUTTON_DOWN&&!((int)dx==Bx&&(int)dy==By))
			{
				if(end) 
				{
					SetEraseMode(TRUE);
					DrawEnd(Ex,Ey,0.3);
					SetEraseMode(FALSE);
					block(Ex,Ey,8,0.3);
					Map[Ex][Ey]=ACS;
				}
				Map[(int)dx][(int)dy]=EXT;
				DrawEnd(dx,dy,0.3);
				Ex=dx;Ey=dy;//��¼�յ����� 
				end++;
			}
		}
		else if(Button_DIYKey==2)//����ǽ 
		{
			dx=floor((x+0.15-0.25)/0.3);dy=floor((y+0.15-0.25)/0.3);
			if(dx>=2&&dy>=2&&dx<=L-3&&dy<=L-3&&Event==BUTTON_DOWN&&!((int)dx==Bx&&(int)dy==By)&&!((int)dx==Ex&&(int)dy==Ey))//���Ʊ༭�����ͬʱ�ж��Ƿ��������õ������յ��غ� 
			{
				Map[(int)dx][(int)dy]=BLK;//�����ͼ��ǽ��λ����Ϣ�����汣����㡢�յ�ͬ�� 
				DrawWall(dx,dy,0.3);
			}
		}
	}
	
	if((start||end)&&inEdit1&&Button_DIYKey!=2)//��֤�������յ�δ����ǰ�޷�������һ��Ԫ�ص����� 
	{
		if(button(GenUIID(0),12,7,1,0.5,"��һ��"))
		{
			inEdit1=0;
			Button_DIYKey++;
			start=0;
			DisplayClear();
			display();
		}
	}
	
	if(Button_DIYKey==2)
	{
		if(inEdit2||button(GenUIID(0),12,7,1.5,0.5,"����ģʽ"))
		{
			inEdit2=1;
			dx=floor((x+0.15-0.25)/0.3);dy=floor((y+0.15-0.25)/0.3);
			if(dx>=2&&dy>=2&&dx<=L-3&&dy<=L-3&&Event==BUTTON_DOWN&&!((int)dx==Bx&&(int)dy==By)&&!((int)dx==Ex&&(int)dy==Ey))
			{
				SetEraseMode(TRUE);
				DrawWall(dx,dy,0.3);
				SetEraseMode(FALSE);
				block(dx,dy,8,0.3);
				Map[(int)dx][(int)dy]=ACS;
			}
			if(button(GenUIID(0),12,7,1.5,0.5,"�˳�����ģʽ"))inEdit2=0;
		}
	}
	
	if(Button_DIYKey)if(button(GenUIID(0),10,7,1,0.5,"����"))
	{
		Button_DIYKey--;
		DisplayClear();
		display();
	}
}
}


void Button_Refresh()
{
	//����Ѽ�¼��Ѱ·�Լ���ͼ��Ϣ
	    Button_find_way_down=0;
	    Button_find_all_the_way=0;
		Get_the_end=0;
  		step=0;
  		All_step=0;
  		int i,j;
  		for(i=0;i<L;i++)
  			for(j=0;j<L;j++) 
  			{
   				Map[i][j]=0;
   				visit[i][j]=0;
   				All_way_visit[i][j]=0;
  			}
		trace[0][0]=0;trace[0][1]=0;trace[1][0]=0;trace[1][1]=0;
		DisplayClear();
		if(Auto)Maze();//������Զ���ͼģʽ�����������Թ� 
		else 
		{
			for(i=0;i<min;i++)
			{
				path1[i]=0;
				path2[i]=0;
			}
			min=0;
			no_way=0;
			Button_DIYCreate();
		}//������ֶ��༭ģʽ��ֻ��ղ�����Χǽ 
		lose=0;
		heat=0;
		Button_Start=0;
		Button_Stop=0;
		rank1=0;
		Tip=0;
		Time=0;
		Timer3=0;Timer33=0;
		display();
	
}

void Button_MenuList2()
{
	setButtonColors("Button","Dark Gray","Button","Dark Gray",0);
	setMenuColors("Button","Dark Gray","Button","Dark Gray",0);
	char *menuListFile[]={"�ļ�",
	"�� | Ctrl-0",
	"�½� | Ctrl-1",
	"���� | Ctrl-2"};
	int selection=menuList(GenUIID(0),9,9.5,2,2.5,0.5,menuListFile,sizeof(menuListFile)/ sizeof(menuListFile[0]));
	if(selection==1)
	{
		Open_File(CurrentFileName);
		Is=1;
	}
	if(selection==2)
	{
		DisplayClear();
		Button_DIYCreate();//����ִ����ֶ���ͼģʽ���½��ļ���Ч��ˢ�µ�ͼ 
		display();
		Open_File(CurrentFileName);
	}
	if(selection==3)Save_File(CurrentFileName);
	
	char *menuListTool[]={"����",
	"���� | Ctrl-B",
	"ˢ�� | Ctrl-R",
	"Ѱ�����·�� | Ctrl-S",
	"�༭ | Ctrl-E",
	};
	menuListTool[4]=DIY?"�˳��༭ | Ctrl-E":"�༭ | Ctrl-E";
	menuListTool[3]=Button_find_the_shortest_way?"��� | Ctrl-S":"Ѱ�����·�� | Ctrl-S"; 
	int decision=menuList(GenUIID(0),11,9.5,2,3,0.5,menuListTool,sizeof(menuListTool)/ sizeof(menuListTool[0]));
	if(decision==1)
	{
		Button_Refresh(); 
		DisplayClear();
		Enter=1;
		//���ص��ڶ��˵���������״̬�����ʼ�� 
		DIY=0;
		Is=1;
		Auto=1;
		display();
	}
	if(decision==2)Button_Refresh();
	if(decision==3)Button_Find_the_shortest_road();
	if(decision==4)
	{
		DIY=!DIY;
		Button_DIY(Cx,Cy,Cevent);
	}
	
	if(Enter==2)if(button(GenUIID(0),13,9.5,2,0.5,"����"))
	{
		help=1;
		DisplayClear();
		Help();
	}
}





void Button_MenuList3()
{
	setButtonColors("Button","Dark Gray","Button","Dark Gray",0);
	setMenuColors("Button","Dark Gray","Button","Dark Gray",0);
	char *menuListFile[]={"�ļ�",
	"�� | Ctrl-0",
	"�½� | Ctrl-1",
	"���� | Ctrl-2"};
	int selection=menuList(GenUIID(0),9,9.5,2,2.5,0.5,menuListFile,sizeof(menuListFile)/ sizeof(menuListFile[0]));
	if(selection==1)Open_File(CurrentFileName);
	if(selection==2)
	{
		Button_Refresh();
		Enter=2; 
		Button_Start=0;
		Button_Stop=0;
		cancelTimer(TIMER_BLINK1500,mseconds1500);
		Time=0;
		Timer3=0;Timer33=0;
		Auto=0;
		Button_DIYCreate();
		Open_File(CurrentFileName);
	}
	if(selection==3)Save_File(CurrentFileName);
	
	char *menuListTool[]={"����",
	"���� | Ctrl-B",
	"ˢ�� | Ctrl-R",
	"�������� | Ctrl-S",
	"Ѱ· | Ctrl-F",
	"���¿�ʼ | Ctrl-P" 
	};
	menuListTool[3]=(Button_Start==0)?"�������� | Ctrl-S":"�ر����� | Ctrl-S";
	menuListTool[4]=(Button_find_way_down==0)?"Ѱ· | Ctrl-F":"���Ѱ· | Ctrl-F";
	int decision=menuList(GenUIID(0),11,9.5,2,2.5,0.5,menuListTool,sizeof(menuListTool)/ sizeof(menuListTool[0]));
	if(decision==1)//����ʱ��Ҫ��ʼ����ǰ��������״̬�������� 
	{
		cancelTimer(TIMER_BLINK1500,mseconds1500);
		Enter=1;
		life=5;
		Button_Refresh();
		DisplayClear();
		display();
	}
	if(decision==2)//ˢ��ʱ��Ҫ��ʼ����ǰ��������״̬�������� 
	{
		int i;	     
		for(i=0;i<strlen(Name);i++)
              Name[i]='\0';                                            
	    winer=0;
	    Winer=0;
		Get_in=0;
		life=5;
		cancelTimer(TIMER_BLINK1500,mseconds1500);
		Button_Refresh();
		
	}
	if(decision==3&&!Button_Start)Button_start();
	else if(decision==3&&!Button_Stop)
	{
		Button_stop();
		Tip=0;
	}
	if(decision==4&&!Button_Start)Button_Find_the_road();	
	else if(decision==4&&Button_Start)Tip=1;//δ�ر�����ʱʹ��Ѱ·����ʾ���� 
	if(decision==5)
	{
		Bx=2;
		By=2;
		Button_Start=0;
		Button_Stop=0;
		Button_find_way_down=0;
		cancelTimer(TIMER_BLINK1500,mseconds1500);
		Time=0;
		Timer33=0;
		Timer3=0;
	}
	
	if(lose&&Button_Start)Button_stop();
	
	if(Enter==3)if(button(GenUIID(0),13,9.5,2,0.5,"����"))
	{
		help=1;
		DisplayClear();
		Button_stop();
		Help();
	}	
}


void Button_stop()
{
	cancelTimer(TIMER_BLINK1500);//����ֹͣ����ֹͣ��ʱ 
	Timer33=0;
	Timer3=0;
	Button_Stop=1;
	Button_Start=0;
	display();
	Display();
}

void Button_start()
{
	startTimer(TIMER_BLINK1500, mseconds1500);//���¿�ʼ����ʼ��ʱ 
	Timer33=1;
	Button_Start=1;
	Button_Stop=0;
	display();
	Display();
}



Button_Difficulty()
{
	if(button(GenUIID(0),6,6,3,1,"��"))
	{
		Difficulty=2;
		Enter=0;
		DisplayClear();
		display();
	}
	else if(button(GenUIID(0),6,5,3,1,"��ͨ"))
	{
		Difficulty=1;
		Enter=0;
		DisplayClear();
		display();
	}
	else if(button(GenUIID(0),6,4,3,1,"����"))
	{
		Difficulty=0;
		Enter=0;
		DisplayClear();
		display();
	} 
}
