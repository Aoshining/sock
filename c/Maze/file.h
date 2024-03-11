#ifndef FILE_H
#define FILE_H


extern char CurrentFileName[MAX_PATH];//存入文件相关操作所需文件名 
extern int Bx,By;//移动物实时位置坐标 
extern int Ex,Ey;//出口坐标 
extern int Map[L][L];//记录迷宫地图 

//读取打开文件 
void Open();
//打开目标文件 
void Open_File(char *path);
//存入当前数据 
void Save();
//选择目标地址 
void Save_File(char *file);

#endif
