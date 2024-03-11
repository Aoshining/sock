#include "basic.h"
#include "way.h"







void Find_the_road(int x,int y)
{
	int Nx,Ny,i;
	int direction[4][2]={{1,0},{-1,0},{0,-1},{0,1}};
	//记录步骤 
	road[step][0]=x;
	road[step][1]=y;
	step++;
	//标记已经走过 
	visit[x][y]=1;
	
	if(Map[x][y]==EXT)//判断是否为出口 
	{
		Get_the_end=1;
		return ;//回调上一层 
	}
	for(i=0;i<4;i++)
	{
		Nx=x+direction[i][0];
		Ny=y+direction[i][1];
		if((Map[Nx][Ny]==ACS||Map[Nx][Ny]==BOM)&&visit[Nx][Ny]==0||Map[Nx][Ny]==EXT&&visit[Nx][Ny]==0)//判断下一步是否走过，是否为路线，是否为终点 
		{
			visit[Nx][Ny]=1;
			All_the_way[All_step][0]=Nx;
			All_the_way[All_step][1]=Ny;
			All_step++;
			Find_the_road(Nx,Ny);
			if(Get_the_end==1)
			return ;//回调上一层 
		}
	}
	//无路可走的情况 
	visit[Nx][Ny]=0;
	All_the_way[All_step][0]=x;
	All_the_way[All_step][1]=y;
	All_step++;
	step--;
	return;	
}




void Print_way1()
{
	int i;
	if(Button_find_way_down==1&&Time_i==0)
		for(i=0;i<step;i++)
		{
		Block(road[i][0],road[i][1],0,0.2);
		}
//		InitConsole();
//		for(i=0;i<step;i++)
//		{
//			printf("%d %d\n",road[i][0],road[i][1]);
//		}
	
}




void Print_way2()
{
	int i;
	if(Button_find_all_the_way==1&&Time_j==0)
		for(i=0;i<step;i++)
		{
		Block(road[i][0],road[i][1],5,0.2);
		}
	
}





void Find_the_shortest_road(int bx,int by)
{  
	//InitConsole();
	struct {
	int x;
	int y;
	int pre;
	}path[10000];
	int i=0,j=1,Px,Py,k;
	int Visit[L][L]={0};
	Visit[bx][by]=1;
	path[1].x=bx;
	path[1].y=by;
	path[1].pre=0;
	int dir[4][2]={{1,0},{-1,0},{0,-1},{0,1}};
	while(i!=j)
	{
		i++;
		for(k=0;k<=3;k++)
		{
			Px=path[i].x+dir[k][0];
			Py=path[i].y+dir[k][1];
			if(Map[Px][Py]!=BLK&&Visit[Px][Py]==0)
			{
				j++;
				path[j].x=Px;
				path[j].y=Py;
				//printf("(%d %d)",path[j].x,path[j].y);
				path[j].pre=i;
				Visit[Px][Py]=1;
				if(Map[Px][Py]==EXT)
				{
					path1[min]=path[j].x;
			    	path2[min]=path[j].y;
			    	min++;
			    	while(path[j].pre!=0)
			    	{
			     		j=path[j].pre;
			    		path1[min]=path[j].x;
			     		path2[min]=path[j].y;
			     		min++;
			    	}
			    return;
			   }
			} 
		}
	} 
	MovePen(11.5,6.25);
	DrawTextString("没路啦");
	no_way++; 
}

void Button_Find_the_road()
{
		if(Button_find_way_down==0)//判断是否已执行过 
		{
			Find_the_road(Bx,By);
			Timer1=1;//记录计时器状态 
		    startTimer(TIMER_BLINK500, mseconds500);//开始计时 
		    Button_find_way_down++;
		}
		else if(Button_find_way_down==1)//判断是否已执行过 
		{
			int i,j;
			 Button_find_way_down--;
			 SetEraseMode(TRUE); //清楚显示路径 
			for(i=0;i<step;i++)
			{
				Block(road[i][0],road[i][1],4,0.2);
			}			
			SetEraseMode(FALSE);
			
			for(i=0;i<step;i++)
			{
				block(road[i][0],road[i][1],8,0.2);
			}			
			
			
			for(i=0;i<L;i++)
			for(j=0;j<L;j++) 
  			{
  				
   				All_way_visit[i][j]=0;
   				visit[i][j]=0;
  			} 
  			All_step=0;
  			step=0;
  			Get_the_end=0;
		}
		
}

void Button_Find_all_the_road()
{
		if(Button_find_all_the_way==0)//判断是否已执行过 
		{
			Timer2=1;//记录计时器状态
			Find_the_road(Bx,By);
			startTimer(TIMER_BLINK1000, mseconds1000);//开始计时
			Button_find_all_the_way++;
		}
		else if(Button_find_all_the_way==1)//判断是否已执行过 
		{
			int i,j;
			Button_find_all_the_way--;
			SetEraseMode(TRUE);//清除显示路径 
			for(i=0;i<step;i++)
			{
				Block(road[i][0],road[i][1],5,0.2);
			}		
			SetEraseMode(FALSE);
			for(i=0;i<step;i++)
			{
				block(road[i][0],road[i][1],8,0.2);
			}		
			
			for(i=0;i<L;i++)
			for(j=0;j<L;j++) 
  			{
  				
   				All_way_visit[i][j]=0;
   				visit[i][j]=0;
  			} 
  			All_step=0;
  			step=0;
  			Get_the_end=0;
		}

}

void Button_Hint()
{
		Find_the_road(Bx,By);
		if(Map[road[1][0]][road[1][1]]==EXT)
		{
			int i,j;
			for(i=0;i<L;i++)
				for(j=0;j<L;j++) 
  				{		
   					All_way_visit[i][j]=0;
   					visit[i][j]=0;
  				} 
  			All_step=0;
  			step=0;
  			Get_the_end=0;
			return;
		}
		

		Block(road[1][0],road[1][1],3,0.2);
		int i,j;
		for(i=0;i<L;i++)
			for(j=0;j<L;j++) 
	  		{		
	   			All_way_visit[i][j]=0;
	   			visit[i][j]=0;
	  		} 
	  	All_step=0;
	 	step=0;
	  	Get_the_end=0;
}
