#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<string.h>
typedef struct KhachHang{
    char name[255];
    char phone[255];
}KhachHang;

typedef struct HangHoa{
    int soluong;
    int tien;
}HangHoa;
typedef struct Node{
    KhachHang data;
    struct Node *next;
}Node;

Node *createNode(KhachHang data){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node *insertTop(Node *root, KhachHang data){
    Node *newNode = createNode(data);
    if(root == NULL){
        root = newNode;
    }else{
        newNode->next = root;
        root = newNode;
    } 
    return root;
}

Node *insertLast(Node *root, KhachHang data){
    Node *newNode = createNode(data);
    if(root == NULL){
        root = newNode;
    }else{
        Node *cur = root;
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = newNode;
    }
    return root;
}

Node *deleteNode(Node *root){
    Node *tmp = root;
    root = root->next;
    free(tmp);
    return root;
}
Node *inputFromFileUser(Node *root, char *filename){
    FILE *file = fopen(filename, "r");
    KhachHang khackHang;
    while(fscanf(file, "%s  %s", khackHang.name, khackHang.phone) != EOF){
        root = insertLast(root, khackHang);
    }
    fclose(file);
    return root;
}
void prinfList(Node *root){
    for(Node *cur = root; cur != NULL; cur = cur->next){
        printf("%s  %s\n", cur->data.name, cur->data.phone);
    }
}

KhachHang top(Node *root){
    return root->data;
}

void thongKe(char *filename){
    FILE *file = fopen(filename, "r");
    int check;
    int sum = 0;
    HangHoa daban[3];
    daban[0].tien = 10;
    daban[1].tien = 50;
    daban[2].tien = 80;
    daban[0].soluong = 0;
    daban[1].soluong = 0;
    daban[2].soluong = 0;
    int count = 0;
    int ngay = 1;
    while(fscanf(file, "%d", &check) != EOF){
        count++;
        if(count == 2) count = 0;
        if(check == -1){
            for(int i = 0; i < 3; i++){
                printf("so luong hang %d: %d\n", i + 1, daban[i].soluong);
                sum = sum + daban[i].tien * daban[i].soluong;
            }
            printf("Tong tien ngay %d : %d\n", ngay, sum);
            ngay+= 1;
            sum = 0;
        }else{
            daban[count].soluong = daban[count].soluong + check;
        }
        
    }
    
    fclose(file);
}


void writeFileBanHang(int array[], char *filename, int size){
    FILE *file = fopen(filename, "a");
    if(size == 0){
        fprintf(file,"%d\n", -1);
    }else{
        fprintf(file, "%d %d %d\n", array[0], array[1], array[2]);
    }
    fclose(file);
}

void writeFileDanhSach(Node *root, char *filename, char *filename_2){
    FILE *file = fopen(filename, "w");
    FILE *file_2 = fopen(filename_2, "a");
    for(Node *cur = root; cur != NULL; cur = cur->next){
        printf("%s  %s\n", cur->data.name, cur->data.phone);
        fprintf(file, "%s   %s\n", cur->data.name, cur->data.phone);
    }
    fprintf(file_2, "%d\n", -1);
    fclose(file);
    fclose(file_2);
}

void menu(){
    printf("1. Doc file danhsach.txt\n");
    printf("2. Them khach hang.txt\n");
    printf("3. Ban hang.txt\n");
    printf("4. Ghi thong tin 1 ngay.txt\n");
    printf("5. Thong ke thogn tin ban hang.txt\n");
    printf("6. Yeu cau dac biet\n");
}
int main(){
    Node *root = NULL;
    int array[3];
    prinfList(root);
    int select;

    while(44){
        KhachHang khachHang;
        menu();
        printf("Nhap lua chon: ");
        scanf("%d", &select);
        __fpurge(stdin);
        switch(select){
            case 1:
                root = inputFromFileUser(root, "./danhsach.txt");
                prinfList(root);
                break;
            case 2:
                khachHang;
                printf("Nhap ten khach hang: ");
                gets(khachHang.name);
                printf("Nhap phone khach hang: ");
                gets(khachHang.phone);
                root = insertLast(root, khachHang);
                break;
            case 3:
                khachHang = top(root);
                for(int i = 0; i < 3; i++){
                    while(44){
                        printf("Nhap so luong san pham %d :", i);
                        scanf("%d", &array[i]);
                        __fpurge(stdin);
                        if(array[i] >= 0)break;
                    }
                }
                writeFileBanHang(array, "./banhang.txt", 3);
                root = deleteNode(root);
                break;
            case 4:
                writeFileDanhSach(root, "./danhsach.txt", "./banhang.txt");
                break;
            case 5:
                thongKe("./banhang.txt");
                break;
            case 6:
                printf("Nhap ten khach hang: ");
                gets(khachHang.name);
                printf("Nhap phone khach hang: ");
                gets(khachHang.phone);
                root = insertTop(root, khachHang);
                break;
            default:
                printf("Nhap sai , hay nhap lai\n");
                break;

        }
    }
    return 0;
}
