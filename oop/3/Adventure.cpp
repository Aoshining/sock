#include "Adventure.h"

using namespace std;

Castle::Castle()
{
	Createmap();
}

void Castle::Createmap()//创建地图，生成各个元素
{
	Bx=rand()%N;//随机生成起点的x、y轴坐标，z轴坐标已初始化为0（最底层）
	By=rand()%N;
	px=Bx;py=By;pz=Bz;
	
	int a,b,c;
	while(1)//随机生成怪物坐标
	{
		a=rand()%N;b=rand()%N;c=rand()%N;
		if(!(a==Bx&&b==By&&c==Bz))
		{
			map[a][b][c].p=MST;
			break;
		}
	}

	Digmap();
	
	for(int i=0;i<N-1;i++)//随机生成层与层之间楼梯坐标
	{
		int l=N-1;
		while(l)
		{
			a=rand()%N;b=rand()%N;
			if(map[a][b][i].p==ACS&&map[a][b][i+1].p==ACS)
			{
				map[a][b][i].upladder=map[a][b][i+1].downladder=1;
				l--;
			}
		}
	}
	
	while(1)//随机生成公主坐标
	{
		a=rand()%N;b=rand()%N;c=rand()%(N-1)+1;
		if(map[a][b][c].p==ACS)
		{
			map[a][b][c].p=PRC;
			Ex=a;Ey=b;Ez=c;
			break;
		}
	}
	
	while(1)//随机生成线索坐标
	{
		a=rand()%N;b=rand()%N;c=rand()%N;
		if(!(a==Bx&&b==By&&c==Bz)&&map[a][b][c].p==ACS)
		{
			map[a][b][c].p=HINT;
			break;
		}
	}
}

int Castle::Path(int z)//判断第z层是否有死路
{
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
		{
			if(map[i][j][z].p==ACS||map[i][j][z].p==MST)
			{
				if(!(i-1>=0&&map[i-1][j][z].p==ACS||i+1<N&&map[i+1][j][z].p==ACS||j-1>=0&&map[i][j-1][z].p==ACS||j+1<N&&map[i][j+1][z].p==ACS))return 0;
			}
		}	
	return 1;
}

void Castle::Digmap()//逐层设置断路
{
	int a,b;
	for(int i=0;i<N;i++)
	{
		int block=N;
		while(block)
		{
			a=rand()%N;b=rand()%N;
			if(!(a==Bx&&b==By&&i==Bz)&&map[a][b][i].p==ACS&&!(a==N/2&&b==N/2))
			{
				map[a][b][i].p=BLK;
				if(Path(i))block--;
				else map[a][b][i].p=ACS;
			}
		}
	}
}

void Castle::choice()
{
	cout << endl;
	if(px==Bx&&py==By&&pz==Bz)//大厅提示语
		cout << "Welcome to the lobby." << endl;
	else if(map[px][py][pz].p==HINT)//线索提示语
	{
		cout << "Trigger clues!" << endl;
		cout << "The lobby is at (" << Bx+1 << "," << By+1 << "," << Bz+1 << ")" << endl;
		cout << "The princess is at (" << Ex+1 << "," << Ey+1 << "," << Ez+1 << ")" << endl;
	}
		
	else if(map[px][py][pz].p==PRC&&game==1)//公主提示语及对话触发
	{
		game=2;
		cout << "You have found the princess!" << endl;
		cout << "YOU: Dear Princess, forgive me for being late." << endl;
		cout << "PRINCESS: Thanks to your courage and determination, I was able to regain my freedom! Thanks, my hero." << endl;
		cout << "YOU: Never mind. I won't let you get hurt again. Let's escape the castle together!" << endl;
		cout << "(Now you need to return to the lobby)" <<endl;
	}

	
	int monstersign=0;//标记周围是否有怪物出没
	if(px-1>=0&&(map[px-1][py][pz].p==ACS||map[px-1][py][pz].p==MST||map[px-1][py][pz].p==HINT||map[px-1][py][pz].p==PRC))
	{
		if(map[px-1][py][pz].p==MST)monstersign=1;
		way.push_back("west");
	}
	if(px+1<N&&(map[px+1][py][pz].p==ACS||map[px+1][py][pz].p==MST||map[px+1][py][pz].p==HINT||map[px+1][py][pz].p==PRC))
	{
		if(map[px+1][py][pz].p==MST)monstersign=1;
		way.push_back("east");
	}
	if(py+1<N&&(map[px][py+1][pz].p==ACS||map[px][py+1][pz].p==MST||map[px][py+1][pz].p==HINT||map[px][py+1][pz].p==PRC))
	{
		if(map[px][py+1][pz].p==MST)monstersign=1;
		way.push_back("north");
	}
	if(py-1>=0&&(map[px][py-1][pz].p==ACS||map[px][py-1][pz].p==MST||map[px][py-1][pz].p==HINT||map[px][py-1][pz].p==PRC))
	{
		if(map[px][py-1][pz].p==MST)monstersign=1;
		way.push_back("south");
	}
	if(map[px][py][pz].upladder==1&&(map[px][py][pz+1].p==ACS||map[px][py][pz+1].p==MST||map[px][py][pz+1].p==HINT||map[px][py][pz+1].p==PRC))
		way.push_back("up");
	if(map[px][py][pz].downladder==1&&(map[px][py][pz-1].p==ACS||map[px][py][pz-1].p==MST||map[px][py][pz-1].p==HINT||map[px][py][pz-1].p==PRC))
		way.push_back("down");
	
	cout << "There are " << way.size() << " exits: ";
	if(way.size()>1)
	{
		for(int i=0;i<way.size()-2;i++)
			cout << way[i] << ", ";
		cout << way[way.size()-2] << " and " << way[way.size()-1] << "." << endl;
	}
	else cout << way[0] << "." << endl;
	if(monstersign)cout << "The monster is around you. Please be careful." << endl;
	cout << "Enter your command:" << endl;
}

void Castle::move(string dirt)
{
	dirt=dirt.substr(3);//识别有效方位指令
	if(dirt=="west")
	{
		vector<string>::iterator iter=std::find(way.begin(),way.end(),dirt);
		if(iter!=way.end())px--;
		else cout << "This direction is blocked." << endl;
	}
	else if(dirt=="east")
	{
		vector<string>::iterator iter=std::find(way.begin(),way.end(),dirt);
		if(iter!=way.end())px++;
		else cout << "This direction is blocked." << endl;
	}
	else if(dirt=="north")
	{
		vector<string>::iterator iter=std::find(way.begin(),way.end(),dirt);
		if(iter!=way.end())py++;
		else cout << "This direction is blocked." << endl;
	}
	else if(dirt=="south")
	{
		vector<string>::iterator iter=std::find(way.begin(),way.end(),dirt);
		if(iter!=way.end())py--;
		else cout << "This direction is blocked." << endl;
	}
	else if(dirt=="up")
	{
		vector<string>::iterator iter=std::find(way.begin(),way.end(),dirt);
		if(iter!=way.end())pz++;
		else cout << "This direction is blocked." << endl;
	}
	else if(dirt=="down")
	{
		vector<string>::iterator iter=std::find(way.begin(),way.end(),dirt);
		if(iter!=way.end())pz--;
		else cout << "This direction is blocked." << endl;
	}
	else cout << "Please input valid command, such as 'go west'." << endl;

	if(map[px][py][pz].p==MST)//游戏失败提示语
	{
		game=0;
		cout << "The monster attacked you." << endl << "Mission failed." <<endl;
	}
	else if(px==Bx&&py==By&&pz==Bz&&game==2)//游戏胜利提示语
	{
		game=0;
		cout << "Successfully rescued the princess!" <<endl;
	}
	vector<string> delway;
	swap(way,delway);
}

