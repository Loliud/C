#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define OPER 0
#define VALUE 1

#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3

typedef struct _NODE
{
	int type;
	int oper;
	float value;
	struct _NODE* left;
	struct _NODE* right;
}NODE;

void FreeTree(NODE** root)
{
	if (root != NULL)
	{
		NODE* node = *root;
		if (node != NULL)
		{
			if (node->left != NULL)
			{
				FreeTree(&node->left);
			}
			if (node->right != NULL)
			{
				FreeTree(&node->right);
			}
			if (node->type == OPER)
			{
				switch (node->oper)
				{
					case ADD: printf("+\n");break;
					case SUB: printf("-\n");break;
					case MUL: printf("*\n");break;
					case DIV: printf("/\n");break;
				}
				
			}else{
				printf("%.2f\n", node->value);
			}
			free(node);
			node = NULL;
		}
	}
}

float Eval(NODE* root)
{
	float left = 0;
	float right = 0;
	if (root == NULL)
		return 0;
	else
	{
		if (root->type == VALUE)
			return root->value;
		else
		{
			left = Eval(root->left);
			right = Eval(root->right);
			switch (root->oper)
			{
				case SUB: return left - right; break;
				case ADD: return left + right; break;
				case MUL: return left * right; break;
				case DIV: return left / right; break;
			}
		}
	}
}

NODE* root = NULL;
NODE* l1 = NULL;
NODE* l2 = NULL;
NODE* l3 = NULL;
NODE* r1 = NULL;
NODE* r2 = NULL;
NODE* r3 = NULL;
void main()
{
	//2 + 3 * (5 - 1)
	//                           (root)+
	//                      (l1) 2           * (r1)
	//                               (l2)3       - (r2)
	//                                     (l3)5    1 (r3)
	root = (NODE*)calloc(1, sizeof(NODE));
	root->type = OPER;
	root->oper = ADD;
	l1 = (NODE*)calloc(1, sizeof(NODE));
	l1->type = VALUE;
	l1->value = 2;
	root->left = l1;
	l3 = (NODE*)calloc(1, sizeof(NODE));
	l3->type = VALUE;
	l3->value = 5;
	r3 = (NODE*)calloc(1, sizeof(NODE));
	r3->type = VALUE;
	r3->value = 1;
	r2 = (NODE*)calloc(1, sizeof(NODE));
	r2->type = OPER;
	r2->oper = SUB;
	r2->left = l3;
	r2->right = r3;
	l2 = (NODE*)calloc(1, sizeof(NODE));
	l2->type = VALUE;
	l2->value = 3;
	r1 = (NODE*)calloc(1, sizeof(NODE));
	r1->type = OPER;
	r1->oper = MUL;
	r1->left = l2;
	r1->right = r2;
	root->right = r1;
	printf("%.2f\n",Eval(root));
	FreeTree(&root);
}
