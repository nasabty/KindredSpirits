// Nicholas Asbaty  |   5591

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"


typedef struct stack
{
	// array
	int *array;

	// how big is my stack
	int capacity;

	// how many items are in the stack
	int size;

}stack;

stack *create_stack(int capacity)
{
	stack *s;

	// if memory allocation fails
	if ((s = malloc(sizeof(stack))) == NULL)
	{
		return NULL;
	}

	// if memory allocation fails
	if ((s->array = malloc(sizeof(int) * capacity)) == NULL)
	{
		free(s);
		return NULL;
	}

	s->size = 0;
	s->capacity = capacity;

	return s;
}

stack *destroy_stack(stack *s)
{
	if(s == NULL)
		return NULL;

	free(s->array);
	free(s);

	return NULL;
}

// return 1 if stack is empty, o otherwise
int isEmpty(stack *s)
{
	return (s == NULL || s->size == 0);
}

// return 1 if full, 0 otherwise
int isFull(stack *s)
{
	return (s->capacity == s->size && s != NULL);
}

// push a new element into stack
void push(stack *s, int data)
{
	if (isFull(s))
        return;

	s->array[s->size++] = data;
}

// pop top element from stack
int pop(stack *s)
{
	if (isEmpty(s))
		return NULL;

	return s->array[--s->size];
}

node *BST_insert(node *root, int data)
{

	//insert in the left subtree
	if (data < root->data)
        root->left = BST_insert(root->left, data);

	//insert in the right subtree
	else if (data > root->data)
        root->right = BST_insert(root->right, data);

	//disallow insert duplicates
	else
			;

	return root;
}

void preorder(node *root, stack *s)
{
	if (root == NULL)
		return;

	push(s, root->data);
	preorder(root->left, s);
	preorder(root->right, s);
}

void inorder(node *root, stack *s)
{
    if (root == NULL)
		return;

    inorder(root->left, s);
    push(s, root->data);
	inorder(root->right, s);
}

void reverse_inorder(node *root, stack *s)
{
	if (root == NULL)
		return;

	reverse_inorder(root->right, s);
	push(s, root->data);
	reverse_inorder(root->left, s);
}

void postorder(node *root, stack *s)
{
	if (root == NULL)
		return;

	postorder(root->left, s);
	postorder(root->right, s);
	push(s, root->data);
}

node *copy_tree(node *root)
{
	if (root == NULL)
		return;

    node *temp = (node *)malloc(sizeof(node));
    temp->data = root->data;
    temp->left = copy_tree(root->left);
    temp->right = copy_tree(root->right);
    return temp;
}

void reflect(node *root)
{
    if (root == NULL)
        return;

    node *temp;

    reflect(root->left);
    reflect(root->right);

    temp = root->left;
    root->left = root->right;
    root->right = temp;
}

int countNodes(node *root)
{
	return (root == NULL) ? 0 : 1 + countNodes(root->left) + countNodes(root->right);
}

int isReflection(node *a, node *b)
{
    int aSize = countNodes(a), bSize = countNodes(b);
    int i;

    //create stacks
    stack *sA, *sB;
    sA = create_stack(aSize);
    sB = create_stack(bSize);

    if (aSize != bSize)
        return 0;

    //preform traversals
    inorder(a, sA);
    reverse_inorder(b, sB);

    //compare traversals
    for (i = 0; i < aSize; i++)
    {
        if (pop(sA) != pop(sB))
            return 0;
    }

    return 1;
}

node *makeReflection(node *root)
{
    if (root == NULL)
        return NULL;

    //create tree
    node *reflection = copy_tree(root);

    //reflect tree
    reflect(reflection);

    return reflection;
}

int kindredSpirits(node *a, node *b)
{
	int aSize = countNodes(a), bSize = countNodes(b);
    int i, n1 = 0, n2 = 0;

    //create stack for each traversal
    stack *sApre, *sApost, *sBpre, *sBpost;
    sApre = create_stack(aSize);
    sApost = create_stack(aSize);
    sBpre = create_stack(bSize);
    sBpost = create_stack(bSize);

    //preform traversal methods
    preorder(a, sApre);
    preorder(b, sBpre);
    postorder(a, sApost);
    postorder(b, sBpost);

    //compare traversals
    for (i = 0; i < aSize; i++)
    {
        if (pop(sApre) != pop(sBpost))
            n1 = 1;

        if (pop(sApost) != pop(sBpre))
            n2 = 1;
    }

    if (n1 == 1 && n2 == 1)
    {
        return 0;
    }

    return 1;
}

double difficultyRating(void)
{
    return 3.0;
}

double hoursSpent(void)
{
    return 10.0;
}

