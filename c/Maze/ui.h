#ifndef UI_H
#define UI_H

static double theta=0;
extern char  Color[14][100];


//画人物 
extern void sp(double px,double py,double l);
//画墙 
extern void DrawWall(int px,int py,double size);
//首界面 
extern void Homepage();
extern void Dun();
//画蜘蛛网 
extern void DrawNet(int x,int y,double size);
extern void forward(double distance);
//画出边长为小方块 根据数组坐标转化  不带边框 
extern void block(int x,int y,int color,double size);
//画出边长为小方块 根据数组坐标转化 带边框 
extern void Block(int x,int y,int color,double size);
//画炸弹 
extern void DrawBoom(int x,int y,double size);
//画终点 
extern void DrawEnd(int x,int y,double size);
//画win 
extern void DrawWin(int x,int y,double size);
//画fail 
extern void DrawFail(int x, int y,double size);
//画背景 
extern void DrawBackground();
//画排名
extern void DrawRankFrame(double x,double y);
 

#endif
