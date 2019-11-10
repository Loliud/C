#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node *next;
}Node;
void addNode(Node *root, int value){
    Node *new_Node = malloc(sizeof(Node));
    new_Node->data = value;
    for(Node *cur = root; cur != NULL; cur = cur->next){
        if(cur->next == NULL){
            cur->next = new_Node;
            break;
        }
    }
}
void addNodeHead(Node *root, int value){
    Node *new_Node = malloc(sizeof(Node));
    Node *head = root;
    head->next = NULL;
    new_Node->data = value;
    new_Node->next = head;
    root = new_Node;
}
int main(){

    Node *head = (Node *)malloc(sizeof(Node));
    head->data = 10;
    head->next = NULL;
    addNodeHead(head, 200);

    for(Node *cur = head; cur != NULL; cur = cur->next){
        printf("%d ", cur->data);
    }




    return 0;
}