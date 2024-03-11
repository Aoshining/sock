// Author: Wang Aozhe;    ID:3220105775;    No.02

#include <stdio.h>
#include <malloc.h>

struct PriorityQueue{
	int size;
	int n[50000];
};
typedef struct PriorityQueue *PQ;

void Insert(int num,PQ H)
{
	int i=++H->size;
	while(H->n[i/2]>num)
	{
		H->n[i]=H->n[i/2];
		i/=2;
	}
	H->n[i]=num;
}

void Down(int idx,PQ H)
{
    int tmp=H->n[idx];
    int i,child;
	for(i=idx;i*2<=H->size;i=child)
	{
		child=i*2;
		if(child!=H->size&&H->n[child]>H->n[child+1])child++;
		if(tmp>H->n[child])H->n[i]=H->n[child];
		else break;
	}
	H->n[i]=tmp;
}

int DeleteMin(PQ H)
{
	int min=H->n[1];
	int last=H->n[H->size--];
	int i,child;
	for(i=1;i*2<=H->size;i=child)
	{
		child=i*2;
		if(child!=H->size&&H->n[child]>H->n[child+1])child++;
		if(last>H->n[child])H->n[i]=H->n[child];
		else break;
	}
	H->n[i]=last;
	return min;
}

int main()
{
	int N,M;
    scanf("%d %d",&N,&M);
	PQ run1=(PQ)malloc(sizeof(struct PriorityQueue));
	PQ run2=(PQ)malloc(sizeof(struct PriorityQueue));
	run1->size=run2->size=0;
	run1->n[0]=run2->n[0]=-1;
	int out[N];
	int id=0;
	int n;
	for(int i=0;i<N;i++)
	{
		scanf("%d",&n);
		if(i<M)
		{
			//Insert(n,run1);
            run1->n[++run1->size]=n;
			continue;
		}
        if(i==M)
            for(int j=run1->size/2;j>0;j--)Down(j,run1);
		int min=run1->n[1];
		out[id++]=min;
		if(min>n)
        {
            DeleteMin(run1);
            run2->n[++run2->size]=n;
        }
		else{
            //Insert(n,run1);
            run1->n[1]=n;
            Down(1,run1);
            //printf("%d\n",run1->n[1]);
        }
		if(run1->size==0)
		{
			printf("%d",out[0]);
			for(int j=1;j<id;j++)printf(" %d",out[j]);
			printf("\n");
			id=0;
			free(run1);
			run1=run2;
            for(int j=run1->size/2;j>0;j--)Down(j,run1);
			run2=(PQ)malloc(sizeof(struct PriorityQueue));
			run2->size=0;
			run2->n[0]=-1;
		}
	}
    if(run1->size)
    {
        if(id)
        {
            printf("%d",out[0]);
            for(int j=1;j<id;j++)printf(" %d",out[j]);
        }
        else printf("%d",DeleteMin(run1));
        while(run1->size)
            printf(" %d",DeleteMin(run1));
        printf("\n");
    }
	if(run2->size)
	{
        for(int j=run2->size/2;j>0;j--)Down(j,run2);
		printf("%d",DeleteMin(run2));
		while(run2->size)
            printf(" %d",DeleteMin(run2));
	}
    return 0;
}