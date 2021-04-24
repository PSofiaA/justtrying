#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

Tree* tree_new()
{
	Tree* tree = (Tree*)calloc(1, sizeof(Tree));
	if (!tree)
		return NULL;

	tree->root = NULL;
	return tree;
}
Node* node_new(char* key, double el1, char* el2)
{
	if (!key) return NULL;
	if (!el2) return NULL;
	Node* node = (Node*)calloc(1, sizeof(Node));
	if (!node) return NULL;

	Info* info = (Info*)calloc(1, sizeof(Info));
	if (!info) return NULL;
	info->el1 = el1;
	info->el2 = (char*)calloc((int)strlen(el2) + 1, sizeof(char));
	if (!info->el2)
	{
		free(info);
		free(node);
		return NULL;
	}
	strcpy(info->el2, el2);
	node->key = (char*)calloc((int)strlen(key) + 1, sizeof(char));
	if (!node->key) {
		free(info->el2);
		free(info);
		free(node);
		return NULL;
	}

	strcpy(node->key, key);
	node->info = info;
	return node;
}

void info_free(Info* info) {
	free(info->el2);
	free(info);
}
void root_free(Node* node) {
	free(node->key);
	info_free(node->info);
	free(node);
}
void node_swap(Node* node, Node* tmp)
{
	free(node->key);
	free(node->info->el2);

	node->key = (char*)calloc(strlen(tmp->key) + 1, sizeof(char));
	node->info->el2 = (char*)calloc(strlen(tmp->info->el2) + 1, sizeof(char));

	strcpy(node->key, tmp->key);
	strcpy(node->info->el2, tmp->info->el2);
	node->info->el1 = tmp->info->el1;
}
Node* find(Tree* tree, char* key) //поиск по ключу 
{
	if (!tree) return NULL;
	Node* tmp = tree->root;
	while (tmp)
	{
		if (strcmp(key, tmp->key) == 0)
			return tmp;
		else if (strcmp(key,tmp->key) < 0)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return NULL;
}
Node* findlim(Tree* tree, char* key)
{
	Node* tmp = tree->root;
	Node* max = NULL;
	while (tmp)
	{
		if (strcmp(key, tmp->key) < 0)
		{
			tmp = tmp->left;
		}
		else if (strcmp(key, tmp->key) >= 0)
		{
			max = tmp;
			tmp = tmp->right;
		}
		else break;
	}
	return max;
}

int tree_insert(Tree* tree, char* key, double el1, char* el2)
{
	int tmp = 0;
	tree->root = node_insert(tree->root, key, el1, el2, tmp);
	if (tmp == 1)
	{
		return -1;
	}
	return 0;
}
Node* node_insert(Node* node, char* key, double el1, char* el2, int tmp)
{
	if (!node)
		return node_new(key, el1, el2);
	if (strcmp(node->key, key) == 0)
	{
		printf("Try another key!\n");
		tmp = 1;
	}
	else if (strcmp(key,node->key)<0)
	{
		node->left = node_insert(node->left, key, el1, el2, tmp);
	}
	else
	{
		node->right = node_insert(node->right, key, el1, el2, tmp);
	}

	return(node);
}

Node* minimum(Node* node)
{
	if (!node)
		return NULL;
	while (node)
	{
		if (node->left)
			return node;
		node = node->left;	
	}
	return node;
}

int print(Node* root)
{
	if (!root) return 1;
	print(root->left);
	printf("  %s, info: %lf %s\n", root->key, root->info->el1, root->info->el2);
	print(root->right);
	return 0;
}
int reverse(Node* root, char* key)
{
	if (!root) return 1;
	reverse(root->left, key);
	reverse(root->right, key);
	if (strcmp(key, root->key) < 0)
	{
		printf("  %s, info: %lf %s\n", root->key, root->info->el1, root->info->el2);
	}
}
void plot(Node* node, unsigned int offset, int turn)
{
	if (!node)
		return;

	plot(node->right, offset + 8, 1);
	printf("\n");
	for (unsigned int i = 0; i < offset; ++i)
	{
		printf(" ");
	}
	if (turn == 1)
	{
		printf("  %s, info: %lf %s\n", node->key, node->info->el1, node->info->el2);

		for (unsigned int i = 0; i < offset; ++i)
		{
			printf(" ");
		}
		printf("/ ");
	}
	else if (turn == 2)
	{
		printf("\\ ");
		printf("\n");
		for (unsigned int i = 0; i < offset; ++i)
		{
			printf(" ");
		}
		printf("  %s, info: %lf %s\n", node->key, node->info->el1, node->info->el2);
	}
	else
		printf("  %s, info: %lf %s\n", node->key, node->info->el1, node->info->el2);
	plot(node->left, offset + 8, 2);
}

void tree_delete(Tree* tree, char* key)
{
	tree->root = delete(tree->root, key);
}
Node* delete(Node* root, char* key)
{
	if (root == NULL)
		return NULL;
	if (strcmp(key, root->key) < 0)
		root->left = delete(root->left, key);
	else if (strcmp(key, root->key) > 0)
		root->right = delete(root->right, key);
	else
	{
		if (!root->left && !root->right)
		{
			root_free(root);
			return NULL;
		}
		else if (!root->left || !root->right)
		{
			Node* tmp;
			if (!root->left)
				tmp = root->right;
			else
				tmp = root->left;
			root_free(root);
			return tmp;
		}
		else
		{
			Node* tmp = minimum(root->right);
			node_swap(root, tmp);
			root->right = delete(root->right, tmp->key);
		}
	}
	return root;
}
