#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
	int value;
	struct node* next;
	struct node* prev;
};
struct masterNode
{
	char group[1001];
	struct node* head;
	struct node* tail;
	struct masterNode* next;
	struct masterNode* prev;
};
struct masterNode* head = NULL;
struct masterNode* tail = NULL;
struct masterNode* createNewMasterNode(char group[])
{
	struct masterNode* newNode = (struct masterNode*)malloc(sizeof(struct masterNode));
	newNode->head = NULL;
	newNode->tail = NULL;
	newNode->next = NULL;
	newNode->prev = NULL;
	strcpy(newNode->group, group);
}
struct node* createNewNode(int value)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->value = value;
}
void createGroup(char group[])
{
	//Push Tail for Each Master Node
	struct masterNode* newMasterNode = createNewMasterNode(group);
	if(head == NULL)
	{
		head = tail = newMasterNode;
		return;
	}
	tail->next = newMasterNode;
	newMasterNode->prev = tail;
	tail = newMasterNode;
}
void pushNode(int value, char group[])
{
	//Search for Spesific Group
	struct masterNode* temp = head;
	while(temp!=NULL)
	{
		if(strcmp(temp->group, group) == 0)
		{
			break;
		}
		temp = temp->next;
	}
	if(temp!=NULL)
	{
		struct node* newNode = createNewNode(value);
		//Push Mid New Node At Temp
		if(temp->head == NULL)
		{
			temp->head = temp->tail = newNode; 
			return;
		}
		if(value < temp->head->value)
		{
			//Push Head
			newNode->next = temp->head;
			temp->head->prev = newNode;
			temp->head = newNode;
		}
		else if(value >= temp->tail->value)
		{
			//Push Tail
			newNode->prev = temp->tail;
			temp->tail->next = newNode;
			temp->tail = newNode;
		}
		else
		{
			//Push Mid
			struct node* temp1 = temp->head;
			//Stop When we find temp value > value
			while(temp1!=NULL&&temp1->value <= value)
			{
				temp1 = temp1->next;
			}
			temp1->prev->next = newNode;
			newNode->next = temp1;
			newNode->prev = temp1->prev;
			temp1->prev = newNode; 
		}
	}
	else
	{
		printf("Can't Add %d Since Group %s Doesn't Exist!\n",value, group);
	}
}
void erase(int value, char group[])
{
	struct masterNode* masterTemp = head;
	while(masterTemp->next!=NULL)
	{
		if(strcmp(masterTemp->group,group)==0)
		{
			break;
		}
		masterTemp = masterTemp->next;
	}
	//Empty Validation
	if(masterTemp->head==NULL)
	{
		return;
	}
	//One Validation
	if(masterTemp->head == masterTemp->tail)
	{
		free(masterTemp->head);
		masterTemp->head = masterTemp->tail = NULL;
	}
	//Pop Head
	if(value == masterTemp->head->value)
	{
		masterTemp->head = masterTemp->head->next;
		free(masterTemp->head->prev);
		masterTemp->head->prev = NULL;
	}
	//Pop Tail
	else if(value == masterTemp->tail->value)
	{
		masterTemp->tail = masterTemp->tail->prev;
		free(masterTemp->tail->next);
		masterTemp->tail->next = NULL;
	}
	//Pop Mid
	else
	{
		struct node* temp = masterTemp->head;
		while(temp!=NULL)
		{
			if(value == temp->value)
			{
				struct node* tempNext = temp->next;
				struct node* tempPrev = temp->prev;
				tempNext->prev = tempPrev;
				tempPrev->next = tempNext;
				free(temp);
				temp = NULL;
				return;
			}
			temp = temp->next;
		}
		printf("Value not Found!");
	}
}
void printAll()
{
	struct masterNode* masterTemp = head;
	while(masterTemp!=NULL)
	{
		printf("Group: %s\n",masterTemp->group);
		struct node* temp = masterTemp->head;
		while(temp!=NULL)
		{
			printf("%d ",temp->value);
			temp = temp->next;
		}
		printf("\n");
		masterTemp = masterTemp->next;
	}
	printf("======================\n");
}
int main()
{
	createGroup("A");
	pushNode(3,"A");
	pushNode(1,"A");
	pushNode(2,"A");
	createGroup("B");
	pushNode(4,"B");
	pushNode(3,"B");
	pushNode(2,"A");
	printAll();
	erase(2,"A");
	erase(2,"A");
	erase(1,"A");
	erase(3,"B");
	printAll();
}