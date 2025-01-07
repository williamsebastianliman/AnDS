#include <stdio.h>
#include <stdlib.h>
struct Node
{
	int value;
	struct Node* left;
	struct Node* right;
	int height;
};
struct Node* root = NULL;
struct Node* createNewNode(int value)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 1;
}
int getHeight(struct Node* root)
{
	if(root == NULL)
	{
		return 0;
	}
	return root->height;
}
int max(int a, int b)
{
	if(a>b)
	{
		return a;
	}
	return b;
}
struct Node* rightRotate(struct Node* x)
{
	struct Node* y = x->left;
	struct Node* z = y->right;
	y->right = x;
	x->left = z;
	x->height = 1 + max(getHeight(x->left), getHeight(x->right));
	y->height = 1 + max(getHeight(y->left), getHeight(y->right));
	return y;
}
struct Node* leftRotate(struct Node* x)
{
	struct Node* y = x->right;
	struct Node* z = y->left;
	y->left = x;
	x->right = z;
	x->height = 1 + max(getHeight(x->left), getHeight(x->right));
	y->height = 1 + max(getHeight(y->left), getHeight(y->right));
	return y;
}
struct Node* insert(struct Node* root, int value)
{
	struct Node* newNode = createNewNode(value);
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
		root->right = insert(root->right, value);
	}
	//Update Height
	root->height = 1+max(getHeight(root->left), getHeight(root->right));
	int balance = getHeight(root->left) - getHeight(root->right);
	//LL --> Right Rotate
	if(balance > 1 && value < root->left->value)
	{
		root = rightRotate(root);
	}
	//RR --> Left Rotate
	else if(balance < -1 && value > root->right->value)
	{
		root = leftRotate(root);
	}
	//LR --> Left Rotate, Right Rotate
	else if(balance > 1 && value > root->left->value)
	{
		root->left = leftRotate(root->left);
		root = rightRotate(root);
		
	}
	//RL --> Right Rotate, Left Rotate
	else if(balance < -1)
	{
		root->right = rightRotate(root->right);
		root = leftRotate(root);
	}
	return root;
}
void inorder(struct Node* root)
{
	if(root == NULL)
	{
		return;
	}
	inorder(root->left);
	printf("Value: %d ; Height: %d\n",root->value, root->height);
	inorder(root->right);
}
int main()
{
	root = insert(root,1);
	root = insert(root,2);
	root = insert(root,3);
	root = insert(root,4);
	root = insert(root, 5);
	root = insert(root,6);
	root = insert(root,7);
	root = insert(root,8);
	root = insert(root,9);
	root = insert(root,10);
	inorder(root);
}