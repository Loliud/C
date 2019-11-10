#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;
void addNode(Node * root, int data){
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    for(Node *cur = root; cur != NULL; cur = cur->next){
        if(cur->next == NULL){
            cur->next = new_node;
            break;
        }
    }
}
int main(){
    Node *head = malloc(sizeof(Node));
    head->data = 100;
    head->next = NULL;
    addNode(head, 200);
    addNode(head, 500);
    addNode(head, 400);
    addNode(head, 200);
    for(Node *cur = head; cur != NULL; cur = cur->next){
        printf("%d ", cur->data);
    }
    return 0;
}