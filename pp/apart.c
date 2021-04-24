#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>
#include <stdio.h>
#include "tree.h"
#include "inputs.h"  
#include "menu.h"  

int file_tree(Tree* tree)
{
	FILE* fp = fopen("bintree.txt", "r");
	if (!fp) return 0;
	while (1)
	{
		char key[20];
		char el2[120];
		double el1;
		if (fscanf(fp, "%s%lf%s", &key, &el1, &el2) == -1)
		{
			fclose(fp);
			return 0;
		}
		tree_insert(tree, key, el1, el2);
	}
	return 1;
}
/// /// ///
int D_delete(Tree* tree)
{
	char* key = NULL;
	scanf("%*c");
	if (input_str(&key, "Enter key:\n") == 1)
		return 1;
	tree_delete(tree, key);
}
int D_add(Tree* tree)
{
	char* key = NULL;
	double el1 = 0; 
	char* el2 = NULL; 
	scanf("%*c");
	if (input_str(&key, "Enter key:\n") == 1)
		return 1;

	//printf("Enter information.");
	//printf("Element 1:\n");
	if (inputR(&el1,"Enter information.Element 1:\n") == 1)
	{
		free(key);
		return 1;
	}
	scanf("%*c");
	if (input_str(&el2, "Element2:\n") == 1)
	{
		free(key);
		return 1;
	}
	if (tree_insert(tree, key, el1, el2) == -1)
	{
		free(el2);
		free(key);
		return -1;
	}
	return 0;
}

int D_Rrint(Tree* tree)
{
	if (!tree)
		return 1;
	char* key = NULL;
	const char tmp = "";
	//printf("\n1.Simple print\n2.Print tree\n3.Reversed print (exceeding a given key)\n0.Exit\n ");
	int i;
	if (inputI(&i,"\n1.Simple print\n2.Print tree\n3.Reversed print (exceeding a given key)\n0.Exit\n " ) == 1)
	{
		return 1;
	}
	if (i == 1)
	{
		print(tree->root);
    }
	if (i == 2)
	{
		plot(tree->root, 0, 0);
	}
	if (i == 3)
	{
	
		scanf("%*c");
		if (input_str(&key, "Enter key:\n") == 1)
			return 1;
		if (strcmp(key, &tmp) == 0)
			print(tree->root);
		else
		reverse(tree->root, key);
		free(key);
	}
	if (i == 0) return 0;
}
int D_find(Tree* tree)
{
	if (!tree)
		return 1;
	char* key = NULL;
	//printf("\n1.Find by key\n2.Find element by largest key(not exceeding a given key)\n0.Exit\n ");
	int i;
	if (inputI(&i,"\n1.Find by key\n2.Find element by largest key(not exceeding a given key)\n0.Exit\n " ) == 1)
	{
		return 1;
	}
	if (i == 1)
	{
		scanf("%*c");
		if (input_str(&key, "Enter key:\n") == 1)
			return 1;
		Node* n = find(tree, key);
		print(n);
	}
	if(i==2)
	{
		scanf("%*c");
		if (input_str(&key, "Enter key:\n") == 1)
			return 1;
		Node* n = findlim(tree, key);
		print(n);
	}	
	if (i == 0) return 0;
}
int main()
{
	Tree* tree = tree_new();
	if (tree == NULL) return 1;
	int j;
		if (inputI(&j,"\nDo you want input from file? 1 - yes, 2 - no\n" ) == 1) return 1;
		switch (j)
		{
		case 1:
			file_tree(tree);
			break;
		case 2:
			break;
		}
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
    } while(i!=0);
	
	return 0;
}