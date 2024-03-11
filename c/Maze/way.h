#ifndef WAY_H
#define WAY_H
#include"basic.h"
//DFS 自动寻路 
extern void Find_the_road(int x,int y);
extern void Find_the_shortest_road(int x ,int y);
//打印已经输出路线
extern void Print_way1();
extern void Print_way2(); 
//寻路
void Button_Find_the_road();
//显示寻路过程
void Button_Find_all_the_road(); 
//提示 
void Button_Hint();


extern int road[2000][2];//记录
extern int step;//行走顺序 
extern int visit[50][50];//记录是否访问
extern int Map[L][L];//记录迷宫地图 
extern int Get_the_end;//状态量，判断是否到达终点 
extern int All_the_way[L*L][2];//记录寻路过程中所有点的坐标 
extern int All_step;//记录坐标编号
extern int Button_find_way_down;//状态量，判断"Find the way"是否被执行 
extern int Button_find_all_the_way;//状态量，判断"Find all the way"是否被执行 
extern int Time_i;
extern int Time_j;
extern int path1[L*L],path2[L*L]; 
extern int min;//最小路
extern int no_way;//状态量。判断是否有路 
extern int Bx,By;//移动物实时位置坐标 
extern int Timer1;//计时器1的状态 
extern int Timer2;//计时器2的状态 
extern int mseconds500; //路径显示计时器时间间隔 
extern int mseconds1000;//寻路过程显示时间间隔 
extern int All_way_visit[L][L];//每个点的状态 判断是否输出过 
#endif



