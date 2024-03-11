#include"basic.h"
#include"map.h"
#include"ui.h"



void Maze()
{
	//�������ָ�룬���ڸ��������Ե�ͼ���б༭ 
	int **map=(int**)malloc(L*sizeof(int*)); 
	int k;
	for (k=0;k<L;k++) 
	{
		map[k]=(int*)calloc(L,sizeof(int));
	}
	Createmap(map);
	//��ӡ�����ɵĵ�ͼ 
	Bx=2;By=2;
	int i,j;
	for(i=0;i<L;i++)
		{
			for(j=0;j<L;j++)
			{
				//��ӡ��� 
				if(i==2&&j==2)
				{
					sp(i,j,0.3);
					continue;
				}
				//��ӡǽ��ͨ·�����塢�յ� 
				switch(map[i][j])
				{
					case BLK:DrawWall(i,j,0.3);break;
//					case ACS:printf("  ");break;
					case TRP:DrawNet(i,j,0.3);break;
					case EXT:Block(i,j,1,0.1);break;
				}
			}
			
		}
	//��ָ������ݱ�����ȫ�ֶ�ά������	
	for(i=0;i<L;i++)
		for(j=0;j<L;j++)
			Map[i][j]=map[i][j];
	//�ͷ�ָ���ڴ� 
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
				//��ӡǽ��ͨ·�����塢�յ� 
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


void Digmap(int **map,int x,int y)//(x,y)Ϊ���ڵ���� 
{
	map[x][y]=ACS;//ʹ���Ϊͨ· 
	
	//ʹ���������ĸ������������������direction�����е�λ�ô�λ����ʹ����·��������� 
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
		int distance=1+(Difficulty==0?0:RandomInteger(0,Difficulty));//distanceΪÿ���ڵľ��룬����distance�Ķ����֪DifficultyԽ���Ӷ�Խ�� 
		int dx=x,dy=y;//(dx,dy)Ϊ��ǰλ�� 
		while(distance>0)
		{
			//�������������һ�������ƶ�һ�� 
			dx+=direction[j][0];
			dy+=direction[j][1];
			
			if(map[dx][dy]==ACS)break;//��ֹ�߻�ͷ· 
			
			//����Ƿ��ڴ�������������ҷ���������������ͨ·�������������һ��ͨ·��ʱ��·����һ�������ڴ���·�� 
			int corner=0;
			if(map[dx][dy-1]==ACS)corner++;
			if(map[dx][dy+1]==ACS)corner++;
			if(map[dx-1][dy]==ACS)corner++;
			if(map[dx+1][dy]==ACS)corner++;
			if(corner>1)break;
			
			distance--;//ÿ��һ�ξ���-1 
			map[dx][dy]=ACS;//�������������ʹ����ط�Ϊͨ· 
		}
		if(distance<=0)Digmap(map,dx,dy);//�Ե�ǰλ��Ϊ�´��ڵ�������ݹ� 
	}
}



void Createmap(int **map)
{
	//����Ȧȫ������Ϊͨ·����ֹ�ڴ� 
	int i;
	for(i=0;i<L;i++)
	{
		map[0][i]=ACS;
		map[i][0]=ACS;
		map[L-1][i]=ACS;
		map[i][L-1]=ACS;
	}
	Digmap(map,2,2);//�ԣ�3��3��Ϊ��㿪�� 
	//�����Ͻ�������������յ� 
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
	//�������ը��
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
	
	//����������壬��������Ϊ�߳���ƽ���� 
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

