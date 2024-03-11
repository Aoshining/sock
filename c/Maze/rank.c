#include"basic.h"
#include"rank.h"
#include"ui.h"

void Build_a_leaderboard()
{
	int i=1;
	struct Ranking *p=(struct Ranking *)malloc(sizeof(struct Ranking));
	Head=p;
	tail=p;
	for(i=1;i<5;i++)
	{
		strcpy(tail->Name,"Empty");
		tail->score=10000;
		p=(struct Ranking *)malloc(sizeof(struct Ranking));
		tail->Next=p;
		tail=tail->Next;	
	}
	strcpy(tail->Name,"Empty");
	tail->score=10000;
	tail->Next=NULL;

	
}


void Add_rank(char *name,int grade)
{
	struct Ranking *p1,*p2,*p;
	int k=0;
	if(grade<=Head->score)
	{
		p=(struct Ranking *)malloc(sizeof(struct Ranking));
		strcpy(p->Name,name);
		p->score=grade;
		p->Next=Head;
		Head=p;	
	}
	else{
		p1=Head;
		p2=Head->Next;
		int i=1;
		for(i=1;i<5;i++)
		{
			if(p2->score<grade)
			{
				p1=p1->Next;
				p2=p2->Next;
			}
			else
			{
				p=(struct Ranking *)malloc(sizeof(struct Ranking));
				strcpy(p->Name,name);
				p->score=grade;
				p1->Next=p;
				p->Next=p2;
				p1=p;
				break;
			}
		}
	}
}



void Button_rank()
{		

	if(link==0)
		{
			Build_a_leaderboard();
			link++;
		}
	if(button(GenUIID(0),8,9.5,1,0.5,rank1?"πÿ±’≈≈√˚":"≈≈√˚"))
	{
		if(rank1==0)
		{
			char a[5][1000];
							double k=4.5;
				int i=0;
			struct Ranking *p;
			p=Head;
			DrawRankFrame(10,5);
			for(i=0;i<5;i++)
			{
				sprintf(a[i],"%d               %s                                %d",i+1,p->Name,p->score);
				p=p->Next;
				MovePen(10.1,k);
				DrawTextString(a[i]);
				k=k-0.6;
			}
			rank1++;
		}
		else if(rank1==1)
		{
			char a[5][1000];
					double k=4.5;
				int i=0;
			struct Ranking *p;
			p=Head;
			SetEraseMode(TRUE);
			DrawRankFrame(10,5);
			for(i=0;i<5;i++)
			{
				sprintf(a[i],"%d               %s                                %d",i+1,p->Name,p->score);
				p=p->Next;
				MovePen(10.1,k);
				DrawTextString(a[i]);
				k=k-0.6;
			}
			SetEraseMode(FALSE);
			rank1--;
			display();
		}
	}
}
