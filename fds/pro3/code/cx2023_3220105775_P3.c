#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAXM 1000

int M,N;//M: the number of vertexs  N: the number of edges

struct AdjSpot{
	int v;//Adjacent Vertex
	int l;//Length of Edge
	struct AdjSpot *next;//Another Adjacent Vertexs
}*Spot[MAXM+1];//Adjacency Table

struct Graph{
	int shortpath;//Determine whether to take the shortest or second shortest path: value 1 for shortest, 0 for second shortest
	int dist[2];//Record the shortest and second shortest distances between the current vertex and the beginning vertex
	int path[2];//Record the last vertex of the shortest and second shortest paths
}Map[MAXM+1];

typedef struct{
	int v;//Vertex
	int dist;//the shortest or second shortest distance between the vertex and the beginning
	int path;//Record whether it's the shortest or second shortest path: value 0 for shorteset, 1 for second shortest
}Element;//the Element in the Priority Queue

struct PriorityQueue{
	int size;//the size of Priority Queue
	Element E[MAXM+1];
};
typedef struct PriorityQueue *PQ;

void Insert(int v,int dist,int path,PQ H)//Insert Element into the Min Heap
{
	for(int i=1;i<=H->size;i++)
	{
		if(H->E[i].v==v&&H->E[i].path==path)
		//If an element of the same type already exists in the min heap, replace it and PercolateUp.
		{
			while(H->E[i/2].dist>dist)
			{
				H->E[i]=H->E[i/2];
				i/=2;
			}
			H->E[i].v=v;
			H->E[i].dist=dist;
			H->E[i].path=path;
			return;
		}
	}
	int i=++H->size;//If not, add a new element to the end of the heap.
	while(H->E[i/2].dist>dist)
	{
		H->E[i]=H->E[i/2];
		i/=2;
	}
	H->E[i].v=v;
	H->E[i].dist=dist;
	H->E[i].path=path;
}

Element DeleteMin(PQ H)//Delete and return the top element and PercolateDown
{
	Element min=H->E[1];
	Element last=H->E[H->size--];
	int i,child;
	for(i=1;i*2<=H->size;i=child)
	{
		child=i*2;
		if(child!=H->size&&H->E[child].dist>H->E[child+1].dist)child++;
		if(last.dist>H->E[child].dist)H->E[i]=H->E[child];
		else break;
	}
	H->E[i]=last;
	return min;
}

void Dijkstra()//n is the number of vertexs
{
	for(int i=1;i<=M;i++)//Initialize all distances
		Map[i].dist[0]=Map[i].dist[1]=INT_MAX;
	Map[1].dist[0]=0;//The shortest path from the starting point to itself is 0
	PQ H=malloc(sizeof(struct PriorityQueue));
	H->size=0;
	H->E[0].dist=-1;//Initialize the Min Heap
	Insert(1,Map[1].dist[0],0,H);
	while(H->size)//Until the Min Heap is empty
	{
		Element min=DeleteMin(H);
		int minv=min.v;//Record the vertex with the unknown shortest path
		int minl=min.dist;//Record the distance of the unknown shortest path
		int minpath=min.path;//Record whether the unknown shortest path is the shortest or second shortest path
		struct AdjSpot *p=Spot[minv];
		while(p)//Iterate over all vertexs adjacent to this vertex to update their shortest or second shortest paths
		{
			if(minl+p->l<Map[p->v].dist[0])
			{
				Map[p->v].dist[1]=Map[p->v].dist[0];
				Map[p->v].dist[0]=minl+p->l;
				Map[p->v].path[1]=Map[p->v].path[0];
				Map[p->v].path[0]=minv;
				Insert(p->v,Map[p->v].dist[0],0,H);
			}
			else if(minl+p->l!=Map[p->v].dist[0]&&minl+p->l<Map[p->v].dist[1])
			{
				Map[p->v].dist[1]=minl+p->l;
				Map[p->v].path[1]=minv;
				if(minpath==1)Map[p->v].shortpath=1;
				else Map[p->v].shortpath=0;//If the second shortest path originates from the shortest path, then make shortpath=0
				Insert(p->v,Map[p->v].dist[1],1,H);
			}
			p=p->next;
		}
	}
	free(H);
}

void connect(int a,int b,int l)//Generate the Adjacency Table
{
	struct AdjSpot *pa;
	pa=malloc(sizeof(struct AdjSpot));
	pa->v=b;
	pa->l=l;
	pa->next=Spot[a];
	Spot[a]=pa;
}

void ReadGraph()//Generate the Graph
{
	scanf("%d %d",&M,&N);
	for(int i=1;i<=M;i++)Spot[i]=NULL;
	for(int i=0;i<N;i++)
	{
		int a,b,l;
		scanf("%d %d %d",&a,&b,&l);
		connect(a,b,l);
	}
}

void Print2ndPath()
{
	int path[2*N]; path[0]=M;//Record the second shortest path
	int numpath=1;//Record the number vertexs of the second shortest path
	int shortflag=0;//Record whether having gone from the shortest to the second shortest path once
	int spot=M;//Destination
	while(spot!=1)//Go back to the beginning
	{
		if(Map[spot].shortpath==1||shortflag)
		{
			path[numpath++]=Map[spot].path[0];
			spot=Map[spot].path[0];
		}
		else if(Map[spot].shortpath==0)
		{
			path[numpath++]=Map[spot].path[1];
			spot=Map[spot].path[1];
			shortflag=1;
		}
	}
	printf("%d",Map[M].dist[1]);
	for(int i=numpath-1;i>=0;i--)
	 	printf(" %d",path[i]);
}

int main()
{
	ReadGraph();
	Dijkstra();
	Print2ndPath();
	return 0;
}