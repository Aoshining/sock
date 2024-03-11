#pragma once//header file protection

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
#define N 3//地图边长
#define BLK 0//断路标识
#define ACS 1//通路标识
#define PRC 2//公主标识
#define MST 3//怪物标识
#define HINT 4//线索标识

class Castle{

private:
	struct Map{
		int p=ACS;//将地图全都初始化为通路
		int upladder=0;//记录该点是否可以向上移动一步
		int downladder=0;//记录该点是否可以向下移动一步
	}map[N][N][N];//三维城堡地图
	int px,py,pz;//玩家位置坐标
	int Bx,By,Bz=0;//起点坐标
	int Ex,Ey,Ez;//终点坐标
	void Digmap();//逐层设置断路
	void Createmap();//创建地图，生成各个元素
	int Path(int z);//判断第z层是否有死路
	vector<string> way;//记录当前可走路径


public:
	int game=1;//游戏状态
	void move(string dirt);//根据玩家输入的命令移动玩家位置
	void choice();//提示当前位置可执行选择
	Castle();//构造函数初始化
};

