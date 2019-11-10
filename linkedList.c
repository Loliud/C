#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node *next;
}Node;
Node *concatList(Node *list_01, Node *list_02){
    Node *tmp;
    tmp = list_01->next;
    list_01->next = list_02->next;
    list_02->next = tmp;

    return tmp;
}
 
int main(){
    // bt: cho 2 ds lien ket list_01 va list_02
    // gs moi ds co 3 phan tu
    // noi list_02 vao sau list_01
    // De bai chi cho biet 2 node cuoi cung 2 ds
    

    // list 1:
    Node *a = (Node *)malloc(sizeof(Node));
    Node *b = (Node *)malloc(sizeof(Node));
    Node *c = (Node *)malloc(sizeof(Node));
    a->data = 10;
    a->next = b;
    b->data = 20;
    b->next = c;
    c->data = 30;
    c->next = a; // AAA --> a

    // list 2:
    Node *e = (Node *)malloc(sizeof(Node)); 
    Node *f = (Node *)malloc(sizeof(Node));
    Node *g = (Node *)malloc(sizeof(Node));
    e->data = 200;
    e->next = f;
    f->data = 500;
    f->next = g;
    g->data = 800;
    g->next = e;

    // coi chi su dung c, g->
    // Node *tmp;
    // tmp = c->next;
    // c->next = g->next;
    // g->next = tmp;
    Node *head = concatList(c, g);
    Node *cur;
    for(cur = head; cur != NULL; cur = cur->next){
        printf("%d ", cur->data);
        if(cur->next == head){
            break;
        }
    }


    return 0;
}