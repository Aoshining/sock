#ifndef MAP_H
#define MAP_H



extern int Bx,By;//�ƶ���ʵʱλ������ 
extern int Ex,Ey;//�������� 
extern int Map[L][L];//��¼�Թ���ͼ 
extern double life;//����ֵ 
extern int trap[2];//�ȵ������ǰһ�� 
extern int trace[2][2];//�������� 
extern int Go;//״̬�����ж�һ����ǰģʽ�Ƿ�� 
extern int Difficulty;//�Ѷ�ϵ�� 
extern int Auto;//״̬�����ж��Ƿ��Զ���ͼ 
extern int Enter;//״̬�����ж�Ŀǰ�Ľ���

//������Ҫ�ƶ��� 
void MoveBlock(int key,int event);
//�����ͼ 
void Digmap(int **map,int x,int y);
void Createmap(int **map);
//��������Թ� 
void Maze();
//��ӡ��ͼ
void Print_Maze();

#endif
