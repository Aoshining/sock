#ifndef BUTTON_H
#define BUTTON_H
#include "way.h"
#include "basic.h"
//�ر����� 
void Button_stop();
//�ֶ���ͼ
void Button_DIYCreate();
//�ֶ��༭�İ�ť
void Button_DIY(double x,double y,int Event);
//ˢ�µ�ͼ
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

extern int Enter;//״̬�����жϽ������ĸ����� 
extern int Auto;//״̬�����ж��Ƿ�����Զ���ͼģʽ
extern int help;//״̬�����жϽ����Ƿ��
extern int Go;//״̬�����ж��Ƿ����һ����ǰģʽ
extern char CurrentFileName[MAX_PATH];//�����ļ���ز��������ļ��� 
extern int Hint;//״̬�����ж���ʾ�Ƿ�� 
extern int Item;//״̬�����ж��Ƿ�򿪵����� 
extern int boom;//ը������ 
extern int Level;//��¼�ؿ� 
extern double life;//����ֵ
extern int Tip;//״̬�����ж��Ƿ�������� 
extern int trace[2][2];//��¼�ƶ������һ�������ϲ� 
extern int lose;//״̬������¼��Ϸ�Ƿ���� 
extern int Button_find_the_shortest_way;//״̬���жϡ�find the shortest way���Ƿ��� 
extern int Is;//״̬�����ж��Ƿ��ӡ�ƶ����� 
extern int DIY;//״̬�����ж��Ƿ���˱༭�˵�  
extern int Button_DIYKey; //״̬�����жϰ���"Start"/"End"/"Wall"�Ƿ��� 
extern int Ex,Ey;//�������� 
extern int heat;//״̬������¼��Ϸ�Ƿ�ʤ�� 
extern int Button_Start;//״̬�����ж�"Button_start"�Ƿ�ִ�� 
extern int Button_Stop;//״̬�����ж�"Button_stop"�Ƿ�ִ�� 
extern int rank1;//״̬�����ж������Ƿ���
extern int Time;//��¼ʱ�� 
extern int Timer3;//��ʱ��3��״̬ 
extern int Timer33;//��ʱ��3��״̬ 
extern double Cx,Cy;
extern int Cevent;//��¼����ʵʱ���꼰������� 
extern int mseconds1500;
extern char Name[100];
extern int Winer;//״̬�����ж��Ƿ��ʤ 
extern int winer;//״̬�����ж��Ƿ�������� 
extern int Get_in;//״̬����ȷ���Ƿ��������� 
extern int Difficulty;//�Թ����Ӷ� 
#endif
