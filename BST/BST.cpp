#include <stdio.h>
#include <stdlib.h>
struct node
{
	int value;
	struct node* left;
	struct node* right;	
};
struct node* root = NULL;
struct node* createNewNode(int value)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->value = value;
	return newNode;
}
struct node* insert(struct node* root,int value)
{
	struct node* newNode = createNewNode(value);
	if(root == NULL)
	{
		root = newNode;
		return root;
	}
	else if(value < root->value)
	{
		root->left = insert(root->left, value);
	}
	else
	{
		root->right = insert(root->right,value);
	}
	return root;
}
struct node* mostLeft(struct node* root)
{
	//We Will Find The Smallest Element 
	//Greater Than The Deleted Node
	//So We Found A Substitute That is 
	//More than Left Node and Less than Right Node
	struct node* temp = root;
	while(temp->left!=NULL)
	{
		temp = temp->left;
	}
	return temp;
}
struct node* erase(struct node* root,int value)
{
	if(root == NULL)
	{
		printf("Value Not Found!\n");
		return NULL;
	}
	if(value < root->value)
	{
		root->left = erase(root->left, value);
	}
	else if(value > root->value)
	{
		root->right = erase(root->right, value);
	}
	else
	{
		//4 Condition: 
		//a. Have No Child
		//b. Have one Left Child
		//c. Have one Right Child
		//d. Have two Child
		if(root->left == NULL && root->right == NULL)
		{
			free(root);
			root = NULL;	
		}
		else if(root->left == NULL)
		{
			//If Both Child is Not Empty But The Left Child is Empty
			//That means It Have One Right Child
			// We Need to Join the Right Child to The Parent of the Node
			struct node* rightChild = root->right;
			free(root);
			root = NULL;
			return rightChild;
		}
		else if(root->right == NULL)
		{
			//If Both Child is Not Empty But The Right Child is Empty
			//That means It Have One Left Child
			// We Need to Join the Left Child to The Parent of the Node
			struct node* leftChild = root->left;
			free(root);
			root = NULL;
			return leftChild;
		}
		else
		{
			//Two Child Condition
			struct node* subs = mostLeft(root->right);
			root->value = subs->value;
			root->right = erase(root->right, subs->value);
		}
	}
	return root;
}
void inorder(struct node* root)
{
	if(root == NULL)
	{
		return;
	}
	inorder(root->left);
	printf("%d ", root->value);
	inorder(root->right);
}
int main()
{
	root = insert(root,10);
	root = insert(root,5);
	root = insert(root,15);
	root = insert(root,3);
	root = insert(root,7);
	root = insert(root,12);
	root = insert(root,1);
	root = erase(root,1);
	root = erase(root,2);
	root = erase(root,10);
	inorder(root);	
}