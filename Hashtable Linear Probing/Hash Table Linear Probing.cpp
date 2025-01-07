#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int size = 6;

struct node
{
	char value[1001];
	char desc[1001];
};
struct node* arr[size];
void init()
{
	for(int i=0;i<size;i++)
	{
		arr[i] = NULL;
	}
}
int hash(char value[])
{
	int val = 0;
	int len = strlen(value);
	for(int i =0;i<len;i++)
	{
		val+=value[i];
		val = val % size;
	}
	return val;
}
struct node* createNewNode(char value[], char desc[])
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	strcpy(newNode->value, value);
	strcpy(newNode->desc, desc);
	return newNode;
}
void insert(char value[],char desc[])
{
	int idx = hash(value);
	int currentIdx = (idx+1)%size;
	struct node* newNode = createNewNode(value, desc);
	if(arr[idx] == NULL)
	{
		arr[idx] = newNode;
		return;
	}
	//1 2 3 4 5
	//idx = 2
	//currentIdx = 3 --> need to stop at idx 2 again
	//if it reach until idx 2 that means the table is full
	while(currentIdx != idx)
	{
		if(arr[currentIdx] == NULL)
		{
			arr[currentIdx] = newNode;
			return;
		}
		currentIdx = (currentIdx+1)%size;
	}
	printf("Hashtable is Full!\n");
}
void erase(char value[])
{
	int idx = hash(value);
	int currentIdx = (idx+1)%size;
	
	if(arr[idx]!=NULL&&strcmp(arr[idx]->value, value) == 0)
	{	
		free(arr[idx]);
		arr[idx] = NULL;
		return;
	}
	while(currentIdx!=idx)
	{
		if(arr[currentIdx]!=NULL&&strcmp(arr[currentIdx]->value,value)==0)
		{
			free(arr[currentIdx]);
			arr[currentIdx] = NULL;
			return;	
		}
		currentIdx = (currentIdx+1)%size;	
	}
	printf("Word %s is Not Found!\n",value);
}
void printAll()
{
	for(int i=0;i<size;i++)
	{
		printf("Index %d: \n",i);
		if(arr[i]!=NULL)
		{
			printf("Word: %s\n",arr[i]->value);
			printf("Description: %s\n",arr[i]->desc);
		}
		else
		{
			printf("NULL\n");
		}
	}
	printf("=============\n");
}
struct node* search(char value[])
{
	int key = hash(value);
	int currentIndex = (key+1)%size;
	if(arr[key]!=NULL&&strcmp(arr[key]->value, value)==0)
	{
		printf("Description: %s\n",arr[key]->desc);
		return arr[key];
	}
	while(currentIndex!=key)
	{
		if(arr[currentIndex]!=NULL&&strcmp(arr[currentIndex]->value, value)==0)
		{
			printf("Description: %s\n",arr[currentIndex]->desc);
			return arr[currentIndex];
		}
		currentIndex = (currentIndex+1)%size;
	}
	printf("Word %s is Not Found!\n",value);
}
int main()
{
	init();
	insert("GN","pak tua");
	insert("A", "huruf pertama Alphabet");
	insert("A", "huruf pertama Alphabet Kali?");
	insert("A", "huruf pertama Alphabet Kali??");
	insert("F", "huruf keenam Alphabet!");
	insert("A", "huruf pertama Alphabet Kali???");
	insert("A", "huruf pertama Alphabet Kali????");
	printAll();
	erase("A");
	printAll();
	search("GN");
	search("F");
	search("A");
}