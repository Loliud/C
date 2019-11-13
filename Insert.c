#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
	int data;
	struct Node *next;
}Node;

// Them vao giua list
void insertNode(Node *root, int value, int k){
	// k la vi tri muon chen vao
	// head bat dau tu vi tri so 0
	Node *cur;
	int x = 0; // vi tri hien tai con tro cur dang tro den
	Node *newNode = malloc(sizeof(Node));
	newNode->data = value;
	newNode->next = NULL;
	for(cur = root; cur != NULL; cur = cur->next){
		if(x + 1 == k){
			// x + 1 la vi tri Node ke tiep cua Node cur
			// phai thuc hien noi cac Node ngay luc nay neu khong se mat dia chi cua Node phia trc
			newNode->next = cur->next; // next cua Node moi tro den Node ke tiep Node cur
			cur->next = newNode; // next cua Node cur noi vao Node moi
			break; // thuc hien xong thi break de do ton ram
		}
		x++;
	}
}
int main(){
	Node *a = malloc(sizeof(Node));
	Node *b = malloc(sizeof(Node));
	Node *c = malloc(sizeof(Node));
	a->data = 20;
	b->data = 30;
	c->data = 40;
	a->next = b;
	b->next = c;
	c->next = NULL;
	Node *cur;
	// Danh sach luc chua chen Node
	for(cur = a; cur != NULL; cur = cur->next){
		printf("%d ", cur->data);
	}
	printf("\n"); // xuong dong
	
	// chen Node co gia tri = 300 vao vi tri so 1 trong danh sach (k == 1)
	insertNode(a, 300, 1);
	// Danh sach sau khi da them Node
	for(cur = a; cur != NULL; cur = cur->next){
		printf("%d ", cur->data);
	}
    return 0;
}
