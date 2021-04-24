#include <stdio.h>
#include <malloc.h>

typedef struct Info
{
	int el1;
	int el2;
	char* el3;
struct Info* next;
}Info;
typedef struct Node
{
	unsigned int key;
	struct Node* left;
	struct Node* right;
	Info* info;
	int height;
}Node;
typedef struct Tree
{
	struct Node* root;
}Tree;

Tree* tree_new();
Node* node_new(unsigned int key, Info* info);
void info_free(Info* info);
void root_free(Node* node);

Node* insert(Node* node, unsigned int key, int el1, int el2, char* el3);
Node* find(Node* node, unsigned int key);
int getBalance(Node* N);
Node* leftTurn(Node* x);
Node* rightTurn(Node* node);
int maximum(int a, int b);
int get_height(Node* node);
int tree_insert(Tree* tree, unsigned int key, int el1, int el2, char* el3);


Node* findlim(Tree* tree);
void print(Node* root);

Tree* tree_new()
{
	Tree* tree = (Tree*)calloc(1, sizeof(Tree));
	if (!tree)
		return NULL;

	tree->root = NULL;
	return tree;
}
Node* node_new(unsigned int key, Info* info)
{
	Node* node = (Node*)calloc(1, sizeof(Node));
	if (!node) return NULL;
	
	node->key = key;
	node->info = info;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return node;
}
Info* info_new(int el1, int el2, char* el3) 
{
Info* info = (Info*)calloc(1, sizeof(Info));
	if (!info) return NULL;
	info->el1 = el1;
	info->el2 = el2;
	info->el3 = (char*)calloc((int)strlen(el3) + 1, sizeof(char));
	if (!info->el3)
	{
		free(info);
		return NULL;
	}
	strcpy(info->el3, el3);
return info;
}
void info_free(Info* info) {
	free(info->el3);
	free(info);
}
void root_free(Node* node) {
	info_free(node->info);
	free(node);
}

int get_height(Node* node)
{
	if (node == NULL)
		return 0;
	return node->height;
}
int maximum(int a, int b)
{
	return (a > b) ? a : b;
}
Node* rightTurn(Node* node)
{
	Node* x = node->left;
	Node* T2 = x->right;

	x->right = node;
	node->left = T2;

	node->height = maximum(get_height(node->left),
		get_height(node->right)) + 1;
	x->height = maximum(get_height(x->left),
		get_height(x->right)) + 1;

	return x;
}

Node* leftTurn(Node* x)
{
	Node* y = x->right;
	Node* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = maximum(get_height(x->left),
		get_height(x->right)) + 1;
	y->height = maximum(get_height(y->left),
		get_height(y->right)) + 1;

	return y;
}

int getBalance(Node* N)
{
	if (N == NULL)
		return 0;
	return (get_height(N->left) - get_height(N->right));
}
Node* find(Node* node, unsigned int key)
{
if (!node) return NULL;

	while (node) {
		if (key < node->key)
			node = node->left;
		else if (key > node->key)
			node = node->right;
		else break;
	}
	return node;
}

Node* findlim(Tree* tree)
{
	if (!tree) return NULL;

	Node* tmp = tree->root;
	return tmp->left ? findlim(tmp->left) : tmp;

	//if (tmp->left == NULL)
	//	return tmp;
	//else return findlim(tmp->left);
}
void node_push_front(Node *node, Info *info) 
{
info->next = node->info;
	node->info = info;

}
Node* insert(Node* node, unsigned int key, int el1, int el2, char* el3)
{
Info* info = info_new(el1, el2, el3) ;
	if (node == NULL)
		return(node_new(key, info));

	if (key < node->key)
		node->left = insert(node->left, key, el1, el2,  el3);
	else if (key > node->key)
		node->right = insert(node->right, key, el1, el2, el3);
	else
	{
		Node* nnode = find(node, key);
 node_push_front(nnode,info);
		return node;
	}

	node->height = 1 + maximum(get_height(node->left),
		get_height(node->right));

	int balance = getBalance(node);

	if (balance > 1 && key < node->left->key)
		return rightTurn(node);

	if (balance < -1 && key > node->right->key)
		return leftTurn(node);

	if (balance > 1 && key > node->left->key)
	{
		node->left = leftTurn(node->left);
		return rightTurn(node);
	}

	if (balance < -1 && key < node->right->key)
	{
		node->right = rightTurn(node->right);
		return leftTurn(node);
	}

	return node;
}
void print(Node* root)
{
	if (root != NULL)
	{
		print(root->left);
		printf("KEY: %d INFO: %d %d %s\n", root->key, root->info->el1, root->info->el2, root->info->el3);

if(root->info->next) printf("KEY: %d INFO: %d %d %s\n", root->key, root->info->next->el1, root->info->next->el2, root->info->next->el3);		
		print(root->right);
	}
}

int tree_insert(Tree* tree, unsigned int key, int el1, int el2, char* el3)
{
	tree->root = insert(tree->root, key, el1, el2, el3);
	return 0;
}
int getInt(int* a)
{
    int A;
    do
    {

        A = scanf("%d", a);
        if (A < 0)
        {
            return 0;
        }
        if (A == 0)
        {
            printf("Try again:\n");
            scanf("%*s");
        }

    } while (A == 0);
    return 1;
}
int getReal(double* p)
{
    double B;
    do
    {

        B = scanf("%10lf", p);
        if (B < 0)
        {
            return 0;
        }
        if (B == 0)
        {
            printf("Try again!\n");
            scanf("%*s");
        }

    } while (B == 0);
    return 1;
}
char* get_str()
{
    char buf[101] = { 0 };
    char* p = NULL;
    int n = 0;
    int len = 0;
    do
    {
        n = scanf("%100[^\n]", buf);
        if (n < 0)
        {
            if (!p)
            {
                printf("\nEnd of file occured!\n");
                return NULL;
            }
        }
        else if (n > 0)
        {
            char* tmp = p;
            p = (char*)realloc(p, len + strlen(buf) + 1);
            if (!p)
            {
                free(tmp);
                return NULL;
            }
            memcpy(p + len, buf, strlen(buf));
            len += strlen(buf);
        }
        else
        {
            scanf("%*c");
        }

    } while (n > 0);

    if (len > 0)
    {
        p[len] = '\0';
    }
    else
    {
        p = (char*)calloc(1, sizeof(char));
    }
    return p;
}
int input_str(char** str, const char* msg)
{
    const char* pr = "";
    do
    {
        printf("%s\n%s ", pr, msg);
        *str = get_str();
        if (!*str)
            return 1;
        pr = "Error! Try again!";
    } while (!str);
    return 0;
}
int inputI(int* turn, const char* msg)
{
    const char* t = " ";
    do
    {
        printf("%s\n%s ", t, msg);
        t = "Out of range!";
        if (getInt(turn) == 0)
        {
            return 1;
        }

    } while (turn < 0);
    return 0;
}
int inputR(double* turn, const char* msg)
{
    const char* t = " ";
    do
    {
        printf("%s\n%s ", t, msg);
        t = "Out of range!";
        if (getReal(turn) == 0)
        {
            return 1;
        }

    } while (turn < 0);
    return 0;
}
int getU(unsigned int* k)
{
    int tmp;
    int val;
    do
    {
        tmp = scanf("%d", &val);
        if (tmp < 0)
        {
            printf("\nEnd of file occured!\n");
            return 1;
        }
        else if (tmp == 0 || val < 0)
        {
            printf("\nError! Try again!\n");
            scanf("%*c");
        }
        else
            *k = (unsigned int)val;
    } while (tmp == 0 || val < 0);
    return 0;
}
int inputU(unsigned int* k, const char* msg)
{
    const char* t = " ";
    do
    {
        printf("%s\n%s ", t, msg);
        //printf("Here: ");
        t = "Out of range!";
        if (getU(k) == 1)
        {
            return 1;
        }

    } while (k < 0);
    return 0;
}

int D_delete(Tree* tree)
{
	unsigned int key;
	if (inputU(&key, "Enter key:\n") == 1)
		return 1;
	//tree_delete(tree, key);
}
int D_add(Tree* tree)
{
	unsigned int key;
	int el1, el2;
	char* el3 = NULL;
	if (inputU(&key, "Enter key:\n") == 1)
		return 1;

	if (inputI(&el1, "Enter information.Element 1:\n") == 1)
	{
		free(key);
		return 1;
	}
	if (inputI(&el2, "Element2:\n") == 1)
	{
		free(key);
		return 1;
	}
	scanf("%*c");
	if (input_str(&el3, "Element3:\n") == 1)
		return 1;
	tree_insert(tree, key, el1, el2, el3);
	return 0;
}

int D_Rrint(Tree* tree)
{
	if (!tree)
		return 1;
	const char tmp = "";
	//printf("\n1.Simple print\n2.Print tree\n3.Reversed print (exceeding a given key)\n0.Exit\n ");
	int i;
	if (inputI(&i, "\n1.Simple print\n0.Exit\n ") == 1)
	{
		return 1;
	}
	if (i == 1)
	{
		print(tree->root);
	}
	if (i == 0) return 0;
}
int D_find(Tree* tree)
{
	if (!tree)
		return 1;
	unsigned int key;
	//printf("\n1.Find by key\n2.Find element by largest key(not exceeding a given key)\n0.Exit\n ");
	int i;
	if (inputI(&i, "\n1.Find by key\n2.Find minimal key\n0.Exit\n ") == 1)
	{
		return 1;
	}
	if (i == 1)
	{
		if (inputU(&key, "Enter key:\n") == 1)
			return 1;
		Node* n = find(tree, key);	
		print(n);
	}
	if (i == 2)
	{
		Node* n = findlim(tree);
		//print(n);
		printf("KEY: %d INFO: %d %d %s\n", n->key, n->info->el1, n->info->el2, n->info->el3);
	}
	if (i == 0) return 0;
}

int main()
{
	Tree* tree = tree_new();
	if (tree == NULL) return 1;
	int i;
	do
	{
		//printf("\n1. Add\n2. Find\n3. Print\n4. Delete\n0. Exit\n ");
		if (inputI(&i, "\n1. Add\n2. Find\n3. Print\n4. Delete\n0. Exit\n ") == 1)
		{
			return 1;
		}
		switch (i)
		{
		case 1:
			D_add(tree);
			break;
		case 2:
			D_find(tree);
			break;
		case 3:
			D_Rrint(tree);
			break;
		case 4:
			D_delete(tree);
			break;
		case 0:
			break;
		default:
			printf("Input 0, 1, 2, 3 or 4\n");
			break;
		}
	} while (i != 0);

	return 0;
}
