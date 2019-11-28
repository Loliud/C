#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio_ext.h>

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

typedef struct _NODESTACK
{
	NODE* node[1024];
	int index;
}NODESTACK;

typedef struct _STACK
{
	char oper[1024];
	int index;
}STACK;

typedef struct _QUEUE
{
	float value[1024];
	int type[1024];
	int start;
	int stop;
}QUEUE;

void InitNodeStack(NODESTACK* stack)
{
	if (stack != NULL)
	{
		stack->index = -1;
	}
}

void InitStack(STACK* stack)
{
	if (stack != NULL)
	{
		stack->index = -1;
	}
}

int IsEmptyNodeStack(NODESTACK* stack)
{
	if (stack != NULL)
		return stack->index == -1;
	else 
		return 1;
}

int IsEmptyStack(STACK* stack)
{
	if (stack != NULL)
		return stack->index == -1;
	else 
		return 1;
}

void PushNode(NODESTACK* stack, NODE* oper)
{
	if (stack != NULL)
	{
		stack->node[++stack->index] = oper;
	}
}

void Push(STACK* stack, char oper)
{
	if (stack != NULL)
	{
		stack->oper[++stack->index] = oper;
	}
}

NODE* PopNode(NODESTACK* stack)
{
	if (stack != NULL && !IsEmptyNodeStack(stack))
		return stack->node[stack->index--];
	else
		return NULL;
}

int Pop(STACK* stack)
{
	if (stack != NULL && !IsEmptyStack(stack))
		return stack->oper[stack->index--];
	else
		return 0;
}

char Top(STACK* stack)
{
	if (stack != NULL && !IsEmptyStack(stack))
		return stack->oper[stack->index];
	else
		return 0;		
}

int Priority(char oper)
{
	switch (oper)
	{
		case '+':
		case '-':
			return 0;
		case '*':
		case '/':
			return 1;
		default:
			return -1;
	}
}

void InitQueue(QUEUE* queue)
{
	if (queue != NULL)	
	{
		queue->start = 0;
		queue->stop = -1;
	}
}

int IsEmptyQueue(QUEUE* queue)
{
	if (queue != NULL)
		return (queue->stop < queue->start);
	else
		return 1;
}

void QueueOper(QUEUE* queue, char oper)
{
	if (queue != NULL)
	{
		queue->value[++queue->stop] = (float)oper;
		queue->type[queue->stop] = OPER;
	}
}

void QueueValue(QUEUE* queue, float value)
{
	queue->value[++queue->stop] = value;
	queue->type[queue->stop] = VALUE;
}

int DeQueue(QUEUE* queue, float* v)
{
	int type = -1;
	if (queue != NULL && !IsEmptyQueue(queue))
	{
		type = queue->type[queue->start];
		*v = queue->value[queue->start++];
	}
	return type;
}

void PrintQueue(QUEUE* queue)
{
	float v = 0;
	while (queue != NULL && !IsEmptyQueue(queue))
	{
		int type = DeQueue(queue, &v);
		switch (type)
		{
			case OPER:
				printf("%c ", (int)v);
				break;
			case VALUE:
				printf("%.2f ", v);
				break;
		}
	}
	printf("\n");
}

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

char expr[1024];
char tmp[1024];
NODESTACK nodestack;
STACK stack;
QUEUE queue;
int pos = 0;
void main()
{
	memset(expr, 0, sizeof(expr));
	printf("Nhap bieu thuc: ");
	__fpurge(stdin);
	gets(expr);
	InitStack(&stack);
	InitQueue(&queue);
	while (pos < strlen(expr))
	{
		memset(tmp, 0, sizeof(tmp));
		sscanf(expr + pos, "%s", tmp);
		pos += strlen(tmp) + 1;
		if (strcmp(tmp,"+") == 0 || 
			strcmp(tmp,"-") == 0 ||
			strcmp(tmp,"*") == 0 || 
			strcmp(tmp,"/") == 0)
		{
			if (Priority(tmp[0]) > Priority(Top(&stack)))
			{
				Push(&stack, tmp[0]);
			}else
			{
				while (Priority(Top(&stack)) >= Priority(tmp[0]))
				{
					QueueOper(&queue, Pop(&stack));
				}
				Push(&stack, tmp[0]);
			}
		}else if (strcmp(tmp,"(") == 0)
		{
			Push(&stack, '(');
		}else if (strcmp(tmp,")") == 0)			
		{
			char oper = 0;
			do
			{
				oper = Pop(&stack);
				if (oper != '(')
				{
					QueueOper(&queue, oper);
				}
			}while (oper != '(');
		}else
		{
			float v = atof(tmp);
			QueueValue(&queue, v);
		}
	}
	
	while (!IsEmptyStack(&stack))
	{
		QueueOper(&queue, Pop(&stack));
	}
		
	InitNodeStack(&nodestack);
	while (!IsEmptyQueue(&queue))
	{
		float v = 0;
		int type = DeQueue(&queue, &v);
		NODE* node = (NODE*)calloc(1, sizeof(NODE));
		node->left = NULL;
		node->right = NULL;
		switch (type)
		{
			case VALUE:
				node->type = VALUE;
				node->value = v;
				PushNode(&nodestack, node);
			break;
			case OPER:
				node->type = OPER;
				switch ((int)v)
				{
					case '+':
						node->oper = ADD;
					break;
					case '-':
						node->oper = SUB;
					break;
					case '*':
						node->oper = MUL;
					break;
					case '/':
						node->oper = DIV;
					break;
				}
				node->left = PopNode(&nodestack);
				node->right = PopNode(&nodestack);
				PushNode(&nodestack, node);
			break;
		}
	}
	NODE* root = PopNode(&nodestack);
	float r = Eval(root);
	FreeTree(&root);
	root = NULL;
	printf("\n Ket qua: %.2f\n", r);
}
