#include <stdio.h>
#include <stdlib.h>
const int size = 9; 
const int nodeSize = 7;
int set[size];
void init()
{
	for(int i=0;i<size;i++)
	{
		set[i] = i;
	}
}
int findParent(int a)
{
	if(a==set[a])
	{
		return a;
	}
	//This is Path Compression Where We Substitute
	//All Node Parent to Be The Highest Parent in The Line
	return set[a] = findParent(set[a]);
}
bool unions(int a, int b)
{
	int parA = findParent(a);
	int parB = findParent(b);
	if(parA!=parB)
	{
		set[parB] = parA;
		return true;
	}
	return false;
}
void printAll()
{
	for(int i=0;i<size;i++)
	{
		printf("set[%d]: %d\n",i,set[i]);
	}
	printf("============\n");
}
struct edge
{
	int nodeA;
	int nodeB;
	int weight;
};
struct edge* edges[size];
struct edge* createEdge(int a, int b, int w)
{
	struct edge* newEdge = (struct edge*)malloc(sizeof(struct edge));
	newEdge->nodeA = a;
	newEdge->nodeB = b;
	newEdge->weight = w;
	return newEdge;
}
void initEdges()
{
	//The edges weight is a bit different from the picture
	//since I want to show the disjoint set function as cycle detector	
	edges[0] = createEdge(0,1,6);
	edges[1] = createEdge(1,2,2);
	edges[2] = createEdge(2,3,30);
	edges[3] = createEdge(3,4,10);
	edges[4] = createEdge(4,5,2);
	edges[5] = createEdge(5,6,3);
	edges[6] = createEdge(4,6,1);
	edges[7] = createEdge(3,5,22);
	edges[8] = createEdge(1,6,10);
}
void sort(struct edge* arr[], int size)
{
	for(int i=0;i<size-1;i++)
	{
		for(int j=0;j<size-i-1;j++)
		{
			if(arr[j+1]->weight < arr[j]->weight)
			{
				struct edge* temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}
void kruskal()
{
	sort(edges,size);
	struct edge* mstSet[nodeSize-1];
	int currentSet = 0;
	int currentIdx = 0;
	while(currentSet < nodeSize-1)
	{
		bool flag = unions(edges[currentIdx]->nodeA,edges[currentIdx]->nodeB);
		if(flag)
		{
			mstSet[currentSet] = edges[currentIdx];
			currentSet++;	
		}
		currentIdx++;
	}
	printf("MST Set: \n");
	for(int i=0;i<nodeSize-1;i++)
	{
		printf("edge[%d]: %d %d %d\n",i,mstSet[i]->nodeA, mstSet[i]->nodeB, mstSet[i]->weight);
	}
	printf("\n");
}
int main()
{
	init();
	initEdges();
	kruskal();
}