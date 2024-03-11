#ifndef RANK_H
#define RANK_H


//建立空链表 
void Build_a_leaderboard();
//添加排名 
void Add_rank(char *name,int grade);
//显示排名 
void Button_rank();


struct Ranking{
	char Name[100];
	int score;
	struct Ranking *Next;
};
extern struct Ranking *Head,*tail;
extern int link;//状态量，确认是否建立链表
extern int rank1;//状态量，判断排名是否按下

#endif

