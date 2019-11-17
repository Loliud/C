#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node*next;
}Node;
typedef struct Queue{
    Node *front;
    Node *rear;
}Queue;
// khoi tao queue
Queue *initQueue(){
    Queue *q = malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}
// tao 1 node moi
Node *createNode(int value){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}
// them node vao cuoi queue
void enQueue(Queue *q, int value){
    Node *newNode = createNode(value);
    if(q->front == NULL){
        q->front = q->rear = newNode;
    }else{
        q->rear->next = newNode;
        q->rear = newNode;
    }  
}
int isEmpty(Queue *q){
    if(q->front == NULL){
        return 1;
    }else{
        return 0;
    }
}
// ham dequeue
int dequeue(Queue *q){
    if(isEmpty(q) == 1){
        printf("queue dang rong!\n");
        return -932333;
    }else{
        Node *tmp = q->front;
        int value = tmp->data;
        q->front = q->front->next;
        free(tmp);
        if(q->front == NULL){
            q->rear = NULL;
        }
        printf("\nDequeue value:  %d", value);
        return value;
    }
}
int main(){
    Queue *q = initQueue();
    enQueue(q, 200);
    enQueue(q, 400);
    enQueue(q, 1000);
    enQueue(q, 5000);
    for(Node *cur = q->front; cur != NULL; cur = cur->next){
        printf("%d ", cur->data);
    }
    dequeue(q);
    printf("\n");
    for(Node *cur = q->front; cur != NULL; cur = cur->next){
        printf("%d ", cur->data);
    }
    return 0;
}
