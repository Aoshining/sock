#ifndef BUTTON_H
#define BUTTON_H
#include "way.h"
#include "basic.h"
//关闭迷雾 
void Button_stop();
//手动建图
void Button_DIYCreate();
//手动编辑的按钮
void Button_DIY(double x,double y,int Event);
//刷新地图
void Button_Fefresh(); 
void Button_Main_Menu();
void Button_Second_Menu();
void Button_MenuList();
void Button_Boom(double x,double y,int Event);
void Button_MenuList4();
void Button_Find_the_shortest_road();
void Button_DIYCreate();
void Button_DIY(double x,double y,int Event);
void Button_Refresh();
void Button_MenuList2();
void Button_MenuList3();
void Button_stop();
void Button_start();
void Button_Difficulty();

extern int Enter;//状态量，判断进入了哪个界面 
extern int Auto;//状态量，判断是否进入自动建图模式
extern int help;//状态量，判断介绍是否打开
extern int Go;//状态量，判断是否进入一往无前模式
extern char CurrentFileName[MAX_PATH];//存入文件相关操作所需文件名 
extern int Hint;//状态量，判断提示是否打开 
extern int Item;//状态量，判断是否打开道具栏 
extern int boom;//炸弹数量 
extern int Level;//记录关卡 
extern double life;//生命值
extern int Tip;//状态量，判断是否给出警告 
extern int trace[2][2];//记录移动物的上一步和上上步 
extern int lose;//状态量，记录游戏是否结束 
extern int Button_find_the_shortest_way;//状态量判断“find the shortest way”是否按下 
extern int Is;//状态量，判断是否打印移动物体 
extern int DIY;//状态量，判断是否打开了编辑菜单  
extern int Button_DIYKey; //状态量，判断按键"Start"/"End"/"Wall"是否按下 
extern int Ex,Ey;//出口坐标 
extern int heat;//状态量，记录游戏是否胜利 
extern int Button_Start;//状态量，判断"Button_start"是否被执行 
extern int Button_Stop;//状态量，判断"Button_stop"是否被执行 
extern int rank1;//状态量，判断排名是否按下
extern int Time;//记录时长 
extern int Timer3;//计时器3的状态 
extern int Timer33;//计时器3的状态 
extern double Cx,Cy;
extern int Cevent;//记录鼠标的实时坐标及按下情况 
extern int mseconds1500;
extern char Name[100];
extern int Winer;//状态量，判断是否获胜 
extern int winer;//状态量，判断是否输入完成 
extern int Get_in;//状态量，确认是否输入链表 
extern int Difficulty;//迷宫复杂度 
#endif
