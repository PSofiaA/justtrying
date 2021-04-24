#ifndef	__TREE_H
#define __TREE_H
/*���� ������ �������� ����, ��������� �� ������ � ����� ����������, 
��������� �� ��������� �/��� ���������� ���� (��� ����������� 
���������� ��������� �������� ������) 
� ��������� �� �������������� ���� (�.�. ����������� ������ ������ � ���������).*/

//� ������� �� ����� ��������� ������ � ����������� �������.
typedef struct Info //����� �� ���
{
	double el1;
	char* el2;
}Info;
typedef struct Node //������� ��������� ������ 
{
	char* key;
	struct Node* left;
	struct Node* right;
	struct Node* prev;
	Info* info;
}Node;
typedef struct Tree
{
	struct Node* root;
}Tree;

Tree* tree_new();

Node* node_new(char* key, double el1, char* el2);
void root_free(Node* node);
void info_free(Info* info);
Node* find(Tree* tree, char* key);
Node* findlim(Tree* tree, char* key);

int tree_insert(Tree* tree, char* key, double el1, char* el2);
Node* node_insert(Node* node, char* key, double el1, char* el2, int tmp);
void node_swap(Node* node, Node* tmp);

Node* minimum(Node* node);

void plot(Node* node, unsigned int offset, int turn);
int print(Node* root);
int reverse(Node* root, char* key);

void tree_delete(Tree* tree, char* key);
Node* delete(Node* root, char* key);
#endif