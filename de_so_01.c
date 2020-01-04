#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<string.h>
// kieu sv
typedef struct SinhVien{
    char username[30];
    char password[30];
    float point;
}SV;
// kieu node
typedef struct Node{
    SV data;
    struct Node *left;
    struct Node *right;
}Node;

Node *createNode(SV data){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
}

Node *insertNode(Node *root, SV data){
    Node *newNode = createNode(data);
    if(root == NULL) root = newNode;
    else
    {
        if(strcmp(data.username, root->data.username) > 0){
            root->right = insertNode(root->right, data);
        }else if(strcmp(data.username, root->data.username) < 0){
            root->left = insertNode(root->left, data);
        }
    }
    return root;
}

void printList(Node *root){
    if(root != NULL){
        printList(root->left);
        if(strcmp(root->data.username, "Admin") != 0){
            printf("%s - %s - %.2f\n", root->data.username,root->data.password,root->data.point);
        }
        printList(root->right);
    }
}
void duyetNodeVaGhiFile(Node *root, FILE *file){
    if(root != NULL){
        duyetNodeVaGhiFile(root->left, file);
        fprintf(file, "%s   %s   %f\n", root->data.username, root->data.password, root->data.point);
        duyetNodeVaGhiFile(root->right, file);
    }
}

Node *inputFromFile(Node *root, char *filename){
    FILE *file = fopen(filename, "r");
    if(!file){
        printf("Khong doc dc file\n");
    }
    SV sv;
    while(fscanf(file, "%s  %s  %f", sv.username, sv.password, &sv.point) != EOF){
        root = insertNode(root, sv);
    }
    fclose(file);
    return root;
}
void writeFile(Node *root, char *filename){
    FILE *file = fopen(filename, "w");
    duyetNodeVaGhiFile(root, file);
    fclose(file);
}

Node *search(Node *root, char *username, char *password){
    if (root == NULL || strcmp(root->data.username, username) == 0 && strcmp(root->data.password, password) == 0){
        return root;
    } 
    if (strcmp(root->data.username, username) < 0) 
        return search(root->right, username, password); 

    return search(root->left, username, password); 
}

Node * minValueNode(Node *node) 
{ 
    Node *minNode = node; 
    while (minNode && minNode->left != NULL){
        minNode = minNode->left; 
    }
    return minNode; 
}

Node *deleteNode(Node *root, char *username){
    if (root == NULL) return root; 

    if (strcmp(username, root->data.username) < 0){
        root->left = deleteNode(root->left, username); 
    } 
    else if (strcmp(username, root->data.username) > 0) 
        root->right = deleteNode(root->right, username); 
    else
    { 
        if (root->left == NULL) 
        { 
            Node *temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            Node *temp = root->left; 
            free(root); 
            return temp; 
        } 
        Node *temp = minValueNode(root->right); 
        root->data = temp->data; 
        root->right = deleteNode(root->right, temp->data.username); 
    } 
    return root; 
}
void menuBegin(){
    printf("1. Dang nhap\n");
    printf("2. Thaot\n");
}
void menuSV(){
    printf("1. Xem diem\n");
    printf("2. Reset pass\n");
    printf("3. Ghi len file\n");
}
void menuAdmin(){
    printf("1. Them sv\n");
    printf("2. In ra ds\n");
    printf("3. Xoa sv\n");
    printf("4. Ghi len file\n");
}
int main(){
    Node *root = NULL;
    SV sv;
    root = inputFromFile(root, "./data.txt");
    int select;
    
    while(68){
        menuBegin();
        printf("Nhap lua chon: ");
        scanf("%d", &select);
        __fpurge(stdin);
        if(select == 1){
            int count = 0;
            while(22){
            printf("Nhap ten: ");
            gets(sv.username);
            __fpurge(stdin);
            printf("Nhap mat khau: ");
            gets(sv.password);
            __fpurge(stdin);
            Node *node = NULL;
            node  = search(root, sv.username, sv.password);
            if(node != NULL){
                if(strcmp(node->data.username, "Admin") == 0){
                    int status;
                    while(89){
                        menuAdmin();
                        printf("Select: ");
                        scanf("%d", &select);
                        __fpurge(stdin);
                        switch(select){
                            case 1:
                                printf("Nhap ten: ");
                                gets(sv.username);
                                __fpurge(stdin);
                                printf("Nhap mat khau: ");
                                gets(sv.password);
                                __fpurge(stdin);
                                printf("Nhap diem: ");
                                scanf("%f", &sv.point);
                                __fpurge(stdin);
                                root = insertNode(root, sv);
                                break;
                            case 2:
                                printList(root);
                                break;
                            case 3:
                                __fpurge(stdin);
                                printf("Nhap username muon xoa: ");
                                gets(sv.username);
                                __fpurge(stdin);
                                root = deleteNode(root, sv.username);
                                break;
                            case 4:
                                writeFile(root, "./data.txt");
                                status = 1;
                                break;
                        }
                        if(status == 1){
                            count = 4;
                            break;
                        }
                    }     
                }else{
                    int status;
                    while(44){
                        menuSV();
                        printf("Nhap select: ");
                        scanf("%d", &select);
                        switch(select){
                            case 1:
                                printf("Diem cua sinh vien: %f\n", node->data.point);
                                break;
                            case 2:
                                printf("Nhap mk moi: ");
                                char newPass[30];
                                char confirmNewPass[30];
                                __fpurge(stdin);
                                gets(newPass);
                                __fpurge(stdin);
                                printf("Confirm mk moi: ");
                                gets(confirmNewPass);
                                __fpurge(stdin);
                                if(strcmp(confirmNewPass, newPass) == 0){
                                    printf("THanh cong\n");
                                    strcpy(node->data.password, newPass);
                                    printList(root);
                                }else{
                                    printf("Khogn thanh cong\n");
                                }
                                break;
                            case 3:
                                writeFile(root, "./data.txt");
                                status = 1;
                                break;
                        }
                        if(status == 1){
                            count = 4;
                            break;
                        }
                        
                    }                    
                }
            }else{
                printf("Sai , hay nhap lai\n");
                count += 1;
            }
            if(count == 3){
                return 0;
            }
            if(count == 4){
                break;
            }
            }
        }else if(select == 2){
            return 0;
        }
    }
    return 0;
}
