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
Node *addNodeHead(Node *root, int value){
    Node *new_Node = malloc(sizeof(Node));
    new_Node->data = value;
    new_Node->next = root;
    root->next = NULL;
    return new_Node;
}
int main(){

    Node *head = (Node *)malloc(sizeof(Node));
    head->data = 10;
    head->next = NULL;
    head = addNodeHead(head, 200);

    for(Node *cur = head; cur != NULL; cur = cur->next){
        printf("%d ", cur->data);
    }




    return 0;
}