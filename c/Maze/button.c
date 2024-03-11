

#include "button.h"



//主菜单按钮设置 
void Button_Main_Menu()
{
	setButtonColors("Button","Dark Gray","Button","Dark Gray",1);
	if(button(GenUIID(0),6,6,3,1,"开始游戏"))
	{
		Enter=1;//进入第二界面 
		DisplayClear();
		display();
	}
	else if(button(GenUIID(0),6,5,3,1,"设置"))
	{
		Enter=4;
		DisplayClear();
		display();
	}
	else if(button(GenUIID(0),6,4,3,1,"介绍"))
	{
		help=1;
		DisplayClear();
		display();
	} 
	else if(button(GenUIID(0),6,3,3,1,"退出游戏"))exit(-1);
}


//第二界面菜单按钮设置 
void Button_Second_Menu()
{
	setButtonColors("Button","Dark Gray","Button","Dark Gray",1);
	if(button(GenUIID(0),5.5,7.5,4,1,"闯关模式"))
	{
		Enter=2;//进入第三界面 
		DisplayClear();
		Auto=1;
		Maze();
		display();
	}
	else if(button(GenUIID(0),5.5,6.5,4,1,"自定义模式"))
	{
		Enter=2;
		DisplayClear();
		Auto=0;
		Button_DIYCreate();
		display();
	}
	else if(button(GenUIID(0),5.5,5.5,4,1,"迷雾模式"))
	{
		DisplayClear();
		Enter=3;//进入迷雾模式 
		Maze();
		display();
    }
    else if(button(GenUIID(0),5.5,4.5,4,1,"「一往无前」模式"))
    {
    	DisplayClear();
    	Enter=2;
    	Go=1;
    	Maze();
    	display();
	}
	else if(button(GenUIID(0),5.5,3.5,4,1,"介绍"))
	{
		help=1;
		DisplayClear();
		Help();
	}
	else if(button(GenUIID(0),5.5,2.5,4,1,"返回"))
	{
		DisplayClear();
		Enter=0;//返回第一界面主菜单 
		display();
	}

}



void Button_MenuList()
{
	setButtonColors("Button","Dark Gray","Button","Dark Gray",0);
	setMenuColors("Button","Dark Gray","Button","Dark Gray",0);
	char *menuListFile[]={"文件",
	"打开 | Ctrl-0",
	"新建 | Ctrl-1",
	"保存 | Ctrl-2"};
	int selection=menuList(GenUIID(0),9,9.5,2,2.5,0.5,menuListFile,sizeof(menuListFile)/ sizeof(menuListFile[0]));
	if(selection==1)Open_File(CurrentFileName);
	if(selection==2)
	{
		Auto=0;
		Button_DIYCreate();//现处于自动建图模式，新建文件等效于进入手动建图模式 
		Open_File(CurrentFileName);
	}
	if(selection==3)Save_File(CurrentFileName);
	
	char *menuListTool[]={"工具",
	"返回 | Ctrl-B",
	"刷新 | Ctrl-R",
	"寻路 | Ctrl-F",
	"寻找所有路径 | Ctrl-A",
	"提示 | Ctrl-T"
	};
	//根据按下情况显示不同的动态标签 
	menuListTool[3]=(Button_find_way_down)?"清空寻路 | Ctrl-F":"寻路 | Ctrl-F";
	menuListTool[4]=(Button_find_all_the_way)?"清空寻路 | Ctrl-A":"可视化寻路 | Ctrl-A";
	menuListTool[5]=Hint?"关闭提示 | Ctrl-T":"提示 | Ctrl-T";
	menuListTool[6]=Item?"关闭道具 | Ctrl-I":"道具 | Ctrl-I";
	
	int decision=menuList(GenUIID(0),11,9.5,2,3,0.5,menuListTool,sizeof(menuListTool)/ sizeof(menuListTool[0]));
	if(decision==1)
	{
		Button_Refresh(); 
		DisplayClear();
		Enter=1;
		//返回到第二菜单界面所有状态量需初始化
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

	
	if(Enter==2)if(button(GenUIID(0),13,9.5,2,0.5,"介绍"))
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
		DrawTextString("剩余：");
		char boomnum[10];
		sprintf(boomnum, "%d", boom);
		DrawTextString(boomnum);
		if(!Item)
		{
			if(button(GenUIID(0),7.5,9.5,1.5,0.5,"炸弹"))
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
					DrawTextString("炸弹不足");
				}
			}	
			if(button(GenUIID(0),7.5,9.5,1.5,0.5,"取消"))
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
	char *menuListFile[]={"文件",
	"打开 | Ctrl-0",
	"新建 | Ctrl-1",
	"保存 | Ctrl-2"};
	int selection=menuList(GenUIID(0),9,9.5,2,2.5,0.5,menuListFile,sizeof(menuListFile)/ sizeof(menuListFile[0]));
	if(selection==1)Open_File(CurrentFileName);
	if(selection==2)
	{
		Auto=0;
		Button_DIYCreate();//如果现处于自动建图模式，新建文件等效于进入手动建图模式 
		Open_File(CurrentFileName);
	}
	if(selection==3)Save_File(CurrentFileName);
	
	char *menuListTool[]={"工具",
	"返回 | Ctrl-B",
	"刷新 | Ctrl-R",
	"寻路 | Ctrl-F",
	"寻找所有路径 | Ctrl-A",
	"提示 | Ctrl-T",
	"重新开始 | Ctrl-P"
	};
	//根据按下情况显示不同的动态标签 
	menuListTool[3]=(Button_find_way_down)?"清空寻路 | Ctrl-F":"寻路 | Ctrl-F";
	menuListTool[4]=(Button_find_all_the_way)?"清空寻路 | Ctrl-A":"可视化寻路 | Ctrl-A";
	menuListTool[5]=Hint?"关闭提示 | Ctrl-T":"提示 | Ctrl-T";
	
	int decision=menuList(GenUIID(0),11,9.5,2,3,0.5,menuListTool,sizeof(menuListTool)/ sizeof(menuListTool[0]));
	if(decision==1)
	{
		Button_Refresh(); 
		DisplayClear();
		Enter=1;
		//返回到第二菜单界面所有状态量需初始化
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
	
	if(Enter==2)if(button(GenUIID(0),13,9.5,2,0.5,"介绍"))
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
			DrawTextString("没路啦");
		}
		else
		{
			int i;
			Find_the_shortest_road(Bx,By);
			//for(i=min-1;i>=0;i--)
			//printf("(%d，%d)",path1[i],path2[i]);
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
			DrawTextString("没路啦");
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
	Auto=0;//记录进入手动建图的状态 
	Is=0;//关闭实时打印移动物
	//生成只含围墙的空白地图 
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
	static int inEdit1=0,inEdit2=0;//维持量，保持编辑状态可以一直执行 
	static int start=0,end=0;//记录起点和终点数量，防止产生多个 
	double dx,dy;
	if(DIY)
	{
		if(button(GenUIID(0),11,7,1,0.5,Button_DIYKey==0?"起点":(Button_DIYKey==1?"终点":"墙"))||inEdit1){
		inEdit1=1;
		if(Button_DIYKey==0)//设置起点 
		{
			dx=floor((x+0.15-0.25)/0.3);dy=floor((y+0.15-0.25)/0.3);//精确坐标换算，保证“点哪亮哪” 
			if(dx>=2&&dy>=2&&dx<=L-3&&dy<=L-3&&Event==BUTTON_DOWN)//限制编辑区域 
			{
				if(start)//判断是否已经存在起点，若存在则清除（下面判断终点数量同理） 
				{
					SetEraseMode(TRUE);
					sp(Bx,By,0.3);
					SetEraseMode(FALSE);
					block(Bx,By,8,0.3);
				}
				Map[(int)dx][(int)dy]=ACS; 
				Bx=dx;By=dy;//记录起点坐标 
				sp(dx,dy,0.3);
				Is=1;//已存在起点，开启实时打印起点坐标 
				start++;
			}
		}
		else if(Button_DIYKey==1)//设置终点 
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
				Ex=dx;Ey=dy;//记录终点坐标 
				end++;
			}
		}
		else if(Button_DIYKey==2)//设置墙 
		{
			dx=floor((x+0.15-0.25)/0.3);dy=floor((y+0.15-0.25)/0.3);
			if(dx>=2&&dy>=2&&dx<=L-3&&dy<=L-3&&Event==BUTTON_DOWN&&!((int)dx==Bx&&(int)dy==By)&&!((int)dx==Ex&&(int)dy==Ey))//限制编辑区域的同时判断是否与已设置的起点或终点重合 
			{
				Map[(int)dx][(int)dy]=BLK;//保存地图中墙的位置信息（上面保存起点、终点同理） 
				DrawWall(dx,dy,0.3);
			}
		}
	}
	
	if((start||end)&&inEdit1&&Button_DIYKey!=2)//保证在起点或终点未设置前无法进行下一类元素的设置 
	{
		if(button(GenUIID(0),12,7,1,0.5,"下一个"))
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
		if(inEdit2||button(GenUIID(0),12,7,1.5,0.5,"消除模式"))
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
			if(button(GenUIID(0),12,7,1.5,0.5,"退出消除模式"))inEdit2=0;
		}
	}
	
	if(Button_DIYKey)if(button(GenUIID(0),10,7,1,0.5,"返回"))
	{
		Button_DIYKey--;
		DisplayClear();
		display();
	}
}
}


void Button_Refresh()
{
	//清空已记录的寻路以及地图信息
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
		if(Auto)Maze();//如果是自动建图模式则重新生成迷宫 
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
		}//如果是手动编辑模式则只清空并生成围墙 
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
	char *menuListFile[]={"文件",
	"打开 | Ctrl-0",
	"新建 | Ctrl-1",
	"保存 | Ctrl-2"};
	int selection=menuList(GenUIID(0),9,9.5,2,2.5,0.5,menuListFile,sizeof(menuListFile)/ sizeof(menuListFile[0]));
	if(selection==1)
	{
		Open_File(CurrentFileName);
		Is=1;
	}
	if(selection==2)
	{
		DisplayClear();
		Button_DIYCreate();//如果现处于手动建图模式，新建文件等效于刷新地图 
		display();
		Open_File(CurrentFileName);
	}
	if(selection==3)Save_File(CurrentFileName);
	
	char *menuListTool[]={"工具",
	"返回 | Ctrl-B",
	"刷新 | Ctrl-R",
	"寻找最短路径 | Ctrl-S",
	"编辑 | Ctrl-E",
	};
	menuListTool[4]=DIY?"退出编辑 | Ctrl-E":"编辑 | Ctrl-E";
	menuListTool[3]=Button_find_the_shortest_way?"清除 | Ctrl-S":"寻找最短路径 | Ctrl-S"; 
	int decision=menuList(GenUIID(0),11,9.5,2,3,0.5,menuListTool,sizeof(menuListTool)/ sizeof(menuListTool[0]));
	if(decision==1)
	{
		Button_Refresh(); 
		DisplayClear();
		Enter=1;
		//返回到第二菜单界面所有状态量需初始化 
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
	
	if(Enter==2)if(button(GenUIID(0),13,9.5,2,0.5,"介绍"))
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
	char *menuListFile[]={"文件",
	"打开 | Ctrl-0",
	"新建 | Ctrl-1",
	"保存 | Ctrl-2"};
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
	
	char *menuListTool[]={"工具",
	"返回 | Ctrl-B",
	"刷新 | Ctrl-R",
	"开启迷雾 | Ctrl-S",
	"寻路 | Ctrl-F",
	"重新开始 | Ctrl-P" 
	};
	menuListTool[3]=(Button_Start==0)?"开启迷雾 | Ctrl-S":"关闭迷雾 | Ctrl-S";
	menuListTool[4]=(Button_find_way_down==0)?"寻路 | Ctrl-F":"清空寻路 | Ctrl-F";
	int decision=menuList(GenUIID(0),11,9.5,2,2.5,0.5,menuListTool,sizeof(menuListTool)/ sizeof(menuListTool[0]));
	if(decision==1)//返回时需要初始化当前界面所有状态量及变量 
	{
		cancelTimer(TIMER_BLINK1500,mseconds1500);
		Enter=1;
		life=5;
		Button_Refresh();
		DisplayClear();
		display();
	}
	if(decision==2)//刷新时需要初始化当前界面所有状态量及变量 
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
	else if(decision==4&&Button_Start)Tip=1;//未关闭迷雾时使用寻路会提示警告 
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
	
	if(Enter==3)if(button(GenUIID(0),13,9.5,2,0.5,"介绍"))
	{
		help=1;
		DisplayClear();
		Button_stop();
		Help();
	}	
}


void Button_stop()
{
	cancelTimer(TIMER_BLINK1500);//按下停止键后停止计时 
	Timer33=0;
	Timer3=0;
	Button_Stop=1;
	Button_Start=0;
	display();
	Display();
}

void Button_start()
{
	startTimer(TIMER_BLINK1500, mseconds1500);//按下开始键后开始计时 
	Timer33=1;
	Button_Start=1;
	Button_Stop=0;
	display();
	Display();
}



Button_Difficulty()
{
	if(button(GenUIID(0),6,6,3,1,"简单"))
	{
		Difficulty=2;
		Enter=0;
		DisplayClear();
		display();
	}
	else if(button(GenUIID(0),6,5,3,1,"普通"))
	{
		Difficulty=1;
		Enter=0;
		DisplayClear();
		display();
	}
	else if(button(GenUIID(0),6,4,3,1,"困难"))
	{
		Difficulty=0;
		Enter=0;
		DisplayClear();
		display();
	} 
}
