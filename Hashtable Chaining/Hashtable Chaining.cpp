#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int size = 4;
struct node
{
	char value[1001];
	char desc[1001];
	struct node* next;
	struct node* prev;
};
struct node* head[size];
struct node* tail[size];
void init()
{
	for(int i=0;i<size;i++)
	{
		head[i] = NULL;
		tail[i] = NULL;
	}
}
int hash(char value[])
{
	int len = strlen(value);
	int idx = 0;
	for(int i=0;i<len;i++)
	{
		idx += value[i];
		idx = idx%size;
	}
	return idx;
}
struct node* createNewNode(char value[], char desc[])
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->next = NULL;
	newNode->prev = NULL;
	strcpy(newNode->value, value);
	strcpy(newNode->desc,desc);
	return newNode;
}
void insert(char value[], char desc[])
{
	int idx = hash(value);
	struct node* newNode = createNewNode(value,desc);
	if(head[idx] == NULL)
	{
		
		head[idx] = tail[idx] = newNode;
		return;
	}
	//Push Tail
	tail[idx]->next = newNode;
	newNode->prev = tail[idx];
	tail[idx] = newNode;
}
struct node* search(char value[])
{
	int idx = hash(value);
	struct node* temp = head[idx];
	while(temp!=NULL)
	{
		if(strcmp(value,temp->value)==0)
		{
			printf("Description: %s\n",temp->desc);
			return temp;
		}
		temp=temp->next;
	}
	printf("Definition for %s is Not Found!\n",value);
}
void erase(char value[])
{
	int idx = hash(value);
	if(head[idx]==NULL)
	{
		printf("%s is Not Found In Hash Table!\n",value);
		return;
	}
	if(head[idx]==tail[idx])
	{
		if(strcmp(head[idx]->value,value)==0)
		{
			free(head[idx]);
			head[idx]=tail[idx]=NULL;
		}
		printf("%s is Not Found In Hash Table!\n",value);
		return;
	}
	if(strcmp(head[idx]->value, value)==0)
	{
		head[idx] = head[idx]->next;
		free(head[idx]->prev);
		head[idx]->prev = NULL;
		return;
	}
	else if(strcmp(tail[idx]->value,value)==0)
	{
		tail[idx] = tail[idx]->prev;
		free(tail[idx]->next);
		tail[idx]->next = NULL;
		return;
	}
	else
	{
		struct node* temp = head[idx];
		while(temp!=NULL)
		{
			if(strcmp(value, temp->value))
			{
				struct node* tempNext = temp->next;
				struct node* tempPrev = temp->prev;
				tempNext->prev = tempPrev;
				tempPrev->next = tempNext;
				free(temp);
				temp = NULL;
				return;
			}
		}
		printf("%s is Not Found In Hash Table!\n",value);
	}
	
}
void printAll()
{
	for(int i=0;i<size;i++)
	{
		printf("Index %d:\n",i);
		struct node* temp = head[i];
		while(temp!=NULL)
		{
			printf("%s->",temp->value);
			temp=temp->next;
		}
		printf("NULL\n");
	}
	printf("============\n");
}
int main()
{
	init();
	insert("Sapi", "Hewan Mamalia Berkaki 4");
	insert("Ayam", "Bahan Baku KFC");
	insert("Kursi","Tempat Manusia Duduk");
	insert("Meja","Tempat Meletakkan Barang");
	search("Kursi");
	printAll();
	erase("Sapi");
	erase("Test");
	printAll();
}