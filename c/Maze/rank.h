#ifndef RANK_H
#define RANK_H


//���������� 
void Build_a_leaderboard();
//������� 
void Add_rank(char *name,int grade);
//��ʾ���� 
void Button_rank();


struct Ranking{
	char Name[100];
	int score;
	struct Ranking *Next;
};
extern struct Ranking *Head,*tail;
extern int link;//״̬����ȷ���Ƿ�������
extern int rank1;//״̬�����ж������Ƿ���

#endif

