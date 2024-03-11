#ifndef MAP_H
#define MAP_H



extern int Bx,By;//移动物实时位置坐标 
extern int Ex,Ey;//出口坐标 
extern int Map[L][L];//记录迷宫地图 
extern double life;//生命值 
extern int trap[2];//踩到陷阱的前一步 
extern int trace[2][2];//倒数两步 
extern int Go;//状态量，判断一往无前模式是否打开 
extern int Difficulty;//难度系数 
extern int Auto;//状态量，判断是否自动开图 
extern int Enter;//状态量，判断目前的界面

//控制主要移动物 
void MoveBlock(int key,int event);
//随机开图 
void Digmap(int **map,int x,int y);
void Createmap(int **map);
//建立随机迷宫 
void Maze();
//打印地图
void Print_Maze();

#endif
