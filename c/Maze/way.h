#ifndef WAY_H
#define WAY_H
#include"basic.h"
//DFS �Զ�Ѱ· 
extern void Find_the_road(int x,int y);
extern void Find_the_shortest_road(int x ,int y);
//��ӡ�Ѿ����·��
extern void Print_way1();
extern void Print_way2(); 
//Ѱ·
void Button_Find_the_road();
//��ʾѰ·����
void Button_Find_all_the_road(); 
//��ʾ 
void Button_Hint();


extern int road[2000][2];//��¼
extern int step;//����˳�� 
extern int visit[50][50];//��¼�Ƿ����
extern int Map[L][L];//��¼�Թ���ͼ 
extern int Get_the_end;//״̬�����ж��Ƿ񵽴��յ� 
extern int All_the_way[L*L][2];//��¼Ѱ·���������е������ 
extern int All_step;//��¼������
extern int Button_find_way_down;//״̬�����ж�"Find the way"�Ƿ�ִ�� 
extern int Button_find_all_the_way;//״̬�����ж�"Find all the way"�Ƿ�ִ�� 
extern int Time_i;
extern int Time_j;
extern int path1[L*L],path2[L*L]; 
extern int min;//��С·
extern int no_way;//״̬�����ж��Ƿ���· 
extern int Bx,By;//�ƶ���ʵʱλ������ 
extern int Timer1;//��ʱ��1��״̬ 
extern int Timer2;//��ʱ��2��״̬ 
extern int mseconds500; //·����ʾ��ʱ��ʱ���� 
extern int mseconds1000;//Ѱ·������ʾʱ���� 
extern int All_way_visit[L][L];//ÿ�����״̬ �ж��Ƿ������ 
#endif



