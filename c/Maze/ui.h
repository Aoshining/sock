#ifndef UI_H
#define UI_H

static double theta=0;
extern char  Color[14][100];


//������ 
extern void sp(double px,double py,double l);
//��ǽ 
extern void DrawWall(int px,int py,double size);
//�׽��� 
extern void Homepage();
extern void Dun();
//��֩���� 
extern void DrawNet(int x,int y,double size);
extern void forward(double distance);
//�����߳�ΪС���� ������������ת��  �����߿� 
extern void block(int x,int y,int color,double size);
//�����߳�ΪС���� ������������ת�� ���߿� 
extern void Block(int x,int y,int color,double size);
//��ը�� 
extern void DrawBoom(int x,int y,double size);
//���յ� 
extern void DrawEnd(int x,int y,double size);
//��win 
extern void DrawWin(int x,int y,double size);
//��fail 
extern void DrawFail(int x, int y,double size);
//������ 
extern void DrawBackground();
//������
extern void DrawRankFrame(double x,double y);
 

#endif
