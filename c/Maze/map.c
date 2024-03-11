#include"basic.h"
#include"map.h"
#include"ui.h"



void Maze()
{
	//定义二级指针，便于各个函数对地图进行编辑 
	int **map=(int**)malloc(L*sizeof(int*)); 
	int k;
	for (k=0;k<L;k++) 
	{
		map[k]=(int*)calloc(L,sizeof(int));
	}
	Createmap(map);
	//打印已生成的地图 
	Bx=2;By=2;
	int i,j;
	for(i=0;i<L;i++)
		{
			for(j=0;j<L;j++)
			{
				//打印起点 
				if(i==2&&j==2)
				{
					sp(i,j,0.3);
					continue;
				}
				//打印墙、通路、陷阱、终点 
				switch(map[i][j])
				{
					case BLK:DrawWall(i,j,0.3);break;
//					case ACS:printf("  ");break;
					case TRP:DrawNet(i,j,0.3);break;
					case EXT:Block(i,j,1,0.1);break;
				}
			}
			
		}
	//将指针的内容保存在全局二维数组中	
	for(i=0;i<L;i++)
		for(j=0;j<L;j++)
			Map[i][j]=map[i][j];
	//释放指针内存 
	int h;
	for(h=0;h<L;h++)free(map[h]);
	free(map);
}

void Print_Maze()
{
	SetPenColor("Light Gray");
	StartFilledRegion(1);
	MovePen(0.4,0.4);
	DrawLine(8.4,0);
	DrawLine(0,8.4);
	DrawLine(-8.4,0);
	DrawLine(0,-8.4);
	EndFilledRegion();
	int i,j;
	for(i=0;i<L;i++)
		{
			for(j=0;j<L;j++)
			{
				//打印墙、通路、陷阱、终点 
				switch(Map[i][j])
				{
					case BLK:DrawWall(i,j,0.3);break;
//					case ACS:Block(i,j,6,0.2);break;
					case TRP2:DrawNet(i,j,0.3);break;
					case EXT:DrawEnd(i,j,0.3);break;
					case BOM:DrawBoom(i,j,0.25);break;
				}
			}
			
		}
}


void Digmap(int **map,int x,int y)//(x,y)为开挖的起点 
{
	map[x][y]=ACS;//使起点为通路 
	
	//使上下左右四个方向随机化（与其在direction数组中的位置错位），使得挖路方向随机化 
	int direction[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
	int i;
	for(i=0;i<4;i++)
	{
		int r=RandomInteger(0,3)%4;
		int tmp0=direction[0][0];
		direction[0][0]=direction[r][0];
		direction[r][0]=tmp0;
		
		int tmp1=direction[0][1];
		direction[0][1]=direction[r][1];
		direction[r][1]=tmp1;
	}
	
	int j;
	for(j=0;j<4;j++)
	{
		int distance=1+(Difficulty==0?0:RandomInteger(0,Difficulty));//distance为每次挖的距离，根据distance的定义可知Difficulty越大复杂度越低 
		int dx=x,dy=y;//(dx,dy)为当前位置 
		while(distance>0)
		{
			//向上下左右随机一个方向移动一格 
			dx+=direction[j][0];
			dy+=direction[j][1];
			
			if(map[dx][dy]==ACS)break;//防止走回头路 
			
			//检查是否挖穿（如果上下左右方向中有至少两个通路则产生“环”，一个通路来时的路，另一个则是挖穿的路） 
			int corner=0;
			if(map[dx][dy-1]==ACS)corner++;
			if(map[dx][dy+1]==ACS)corner++;
			if(map[dx-1][dy]==ACS)corner++;
			if(map[dx+1][dy]==ACS)corner++;
			if(corner>1)break;
			
			distance--;//每挖一次距离-1 
			map[dx][dy]=ACS;//如无上述情况则使这个地方为通路 
		}
		if(distance<=0)Digmap(map,dx,dy);//以当前位置为下次挖的起点来递归 
	}
}



void Createmap(int **map)
{
	//将外圈全部设置为通路，防止挖穿 
	int i;
	for(i=0;i<L;i++)
	{
		map[0][i]=ACS;
		map[i][0]=ACS;
		map[L-1][i]=ACS;
		map[i][L-1]=ACS;
	}
	Digmap(map,2,2);//以（3，3）为起点开挖 
	//在右上角区域随机产生终点 
	int a,b;
	while(1)
	{
		a=RandomInteger(0,L/2-1);b=RandomInteger(0,L/2-1);
		if(a>1&&b>1&&map[L-a][L-b]==ACS)
		{
			map[L-a][L-b]=EXT;
			Ex=L-a;Ey=L-b;
			break;
		}
	}
	Ex=L-a;
	Ey=L-b;
	//随机产生炸弹
	if(Auto&&!Go&&Enter==2)
	{
		for(i=3;i>0;i--)
		{
			while(1)
			{
				a=RandomInteger(0,L-3);b=RandomInteger(0,L-3);
				if(a>1&&b>1&&map[a][b]==ACS)
				{
					map[a][b]=BOM;
					break;
				}
			}
		}
	}
	
	//随机产生陷阱，陷阱数量为边长的平方根 
	int j;
	for(j=(int)sqrt((double)L);j>0;j--)
	{
		while(1)
		{
			a=RandomInteger(0,L-3);b=RandomInteger(0,L-3);
			if(a>1&&b>1&&map[a][b]==BLK)
			{
				map[a][b]=TRP;
				break;
			}
		}
	}
}

