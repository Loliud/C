#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* sample_words[] = {"hello","okay","cancel","good","bad"};
char* sample_meanings[] = {"xin chao","chap nhan","huy bo","tot","toi te"};

typedef struct _NODE
{
	char* word;
	char* meaning;
	struct _NODE* left;
	struct _NODE* right;
}NODE;

NODE* root = NULL;

NODE* InsertNode(NODE* root, char* word, char* meaning)
{
	if (root == NULL)
	{
		NODE* tmp = (NODE*)calloc(1, sizeof(NODE));
		tmp->word = (char*)calloc(1, strlen(word) + 1);
		strcpy(tmp->word, word);
		tmp->meaning = (char*)calloc(1, strlen(meaning) + 1);
		strcpy(tmp->meaning, meaning);
		tmp->left = NULL;
		tmp->right = NULL;
		return tmp;
	}else
	{
		if (strcmp(root->word, word) < 0)
		{
			root->right = InsertNode(root->right, word, meaning);
		}else if (strcmp(root->word, word) > 0)
		{
			root->left = InsertNode(root->left, word, meaning);
		}
		return root;
	}
}

NODE* CreateBST(char** words, char** meanings, int count)
{
	NODE* tmp = NULL;
	int i = 0;
	for (i = 0;i < count;i++)
	{
		tmp = InsertNode(tmp, words[i], meanings[i]);
	}
	return tmp;
}

void PrintBST(NODE* root)
{
	if (root != NULL)
	{
		PrintBST(root->left);
		printf("%s\n",root->word);
		PrintBST(root->right);
	}
}

void main()
{
	root = CreateBST(sample_words, sample_meanings);
	PrintBST(root);
}
