#include <stdio.h>

const int size = 6; 
int set[size];
void init()
{
	for(int i=0;i<size;i++)
	{
		set[i] = i;
	}
}
//0 1 2 3 4
//0 0 1 3 4

//findParent(2)
//2-->1-->0-->0
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
void unions(int a, int b)
{
	int parA = findParent(a);
	int parB = findParent(b);
	if(parA!=parB)
	{
		set[parB] = parA;
	}
	else
	{
		printf("Union Return A Cycle!\n");
	}
}
void printAll()
{
	for(int i=0;i<size;i++)
	{
		printf("set[%d]: %d\n",i,set[i]);
	}
	printf("============\n");
}
int main()
{
	init();
	unions(1,2);
	unions(0,1);
	unions(2,0); //Here Disjoint Set Detect A Cyclic Connection Between Node 0,1, and 2
	unions(1,4);
	printAll();
}