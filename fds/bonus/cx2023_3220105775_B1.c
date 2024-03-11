// Author: Wang Aozhe;    ID:3220105775;    No.01

#include <stdio.h>
struct Node;
typedef struct Node *Stack;
struct Node{
    int n;
    Stack next;
};

void Push(int x,Stack s)
{
    Stack tmp=malloc(sizeof(Stack));
    tmp->n=x;
    tmp->next=s->next;
    s->next=tmp;
}

void Pop(Stack s)
{
    s->next=s->next->next;
}

int main()
{
    Stack s1=malloc(sizeof(Stack)),s2=malloc(sizeof(Stack));
    s1->next=NULL;
    s2->next=NULL;
    int num;
    int time=0;
    scanf("%d",&num);
    for(int i=0;i<num;i++)
    {
        getchar();
        char op=getchar();//printf("%c",op);if(i==3)return 0;
        if(op=='I')
        {
            int e;
            scanf("%d",&e);
            Push(e,s1);
        }
        else
        {
            
            if(s2->next)
            {
                printf("%d 1\n",s2->next->n);
                Pop(s2);
                continue;
            }
            if(!s1->next)
            {
                printf("ERROR\n");
                continue;
            }
            while(s1->next)
            {
                Push(s1->next->n,s2);
                Pop(s1);
                time+=2;
            }
            time++;
            printf("%d %d\n",s2->next->n,time);
            Pop(s2);
            time=0;
            
        }
    }
    return 0;
}