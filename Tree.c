#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node *right;
    struct Node *left;
}Node;
// khoi tao
Node *initTree(int value){
    Node *root = malloc(sizeof(Node));
    root->data = value;
    root->right = NULL;
    root->left = NULL;
    return root;
}
// tao Node
Node *createNode(int value){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// Them node vao cay
Node *insertNode(Node *root, int value){
    Node *newNode = createNode(value);
    if(root == NULL){
        root = newNode;
    }
    else if(value > root->data){
        root->right = insertNode(root->right, value);
    }else if(value < root->data){
        root->left = insertNode(root->left, value);
    }
    return root;
}
// in gia tri cac node theo thu ru left node right
void showNodeLNR(Node *root){ 
    if(root != NULL){  
        showNodeLNR(root->left);
        showNodeLNR(root->right);
        printf("%d ", root->data);
    }
}
// in cac node khong co con
void showNodeHasNoChild(Node *root){
    if(root != NULL){
        if(root->right == NULL && root->left == NULL){
            printf("%d ", root->data);
        }
        showNodeHasNoChild(root->left);
        showNodeHasNoChild(root->right);
    }
}
// in cac node co 1 con
void showNodeHasOneChild(Node *root){
    if(root != NULL){
        if(root->right == NULL && root->left != NULL){
            printf("%d ", root->data);
        }
        else if(root->right != NULL && root->left == NULL){
            printf("%d ", root->data);
        }
        showNodeHasOneChild(root->left);
        showNodeHasOneChild(root->right);
    }
}
// in cac node co 2 con
void showNodeHasTwoChild(Node *root){
    if(root != NULL){
        if(root->right != NULL && root->left != NULL){
            printf("%d ", root->data);
        }
        showNodeHasTwoChild(root->left);
        showNodeHasTwoChild(root->right);
    }
}
// tim max 
int max(Node *root){
    if(root->right == NULL){
        return root->data;
    }else{
        return max(root->right);
    }
}   
int main(){

    Node *root = initTree(10);
    root = insertNode(root, 2);
    root = insertNode(root, 30);
    root = insertNode(root, 90);
    root = insertNode(root, 15);
    root = insertNode(root, 1);
    //showNodeLNR(root);
    //printf("\n%d ",max(root));
    //showNodeHasNoChild(root);
    showNodeHasTwoChild(root);
    return 0;
}
