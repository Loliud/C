#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
typedef struct MonAn{
    int id;
    char name[255];
    int quantity;
    long price;
}MonAn;

typedef struct Request{
    int id;
    int order[7];
    long total;
    struct Request *next;
}Request;
void menu(){
    printf("1. DS mon hom nay\n");
    printf("2. Yeu cau dat mon\n");
    printf("3. Thong tin tat ca order\n");
    printf("4. Mon an ua chuong nhat\n");
    printf("5. Thoat\n");
}
void inputFromFile(MonAn array[], char *filename){
    FILE *file = fopen(filename, "r");
    MonAn monAn;
    int count = 0;
    while(fscanf(file,"%d %s %d %ld", &monAn.id, monAn.name, &monAn.quantity, &monAn.price) != EOF){
        if(count == 7) break;
        array[count].id = monAn.id;
        strcpy(array[count].name, monAn.name);
        array[count].quantity = monAn.quantity;
        array[count].price = monAn.price;
        count += 1;
    }
    fclose(file);
}
void menuMonAn(MonAn array[]){
    for(int i = 0; i < 7; i++){
        printf("%d %s %d %ld\n", array[i].id, array[i].name, array[i].quantity, array[i].price);
    }
    printf("-----------------------------------------------------------------------\n");
}
Request *push(Request *root, Request *newRequest){
    if(root == NULL){
        root = newRequest;
    }else{
        newRequest->next = root;
        root = newRequest;
    }
    return root;
}
void printfRequest(Request *root, MonAn array[], int number){
    int count = 1;
    Request *cur = NULL;
    for(cur = root; cur != NULL; cur = cur->next){
        printf("Don hang so %d -- %ld :\n", count, cur->total);
        for(int i = 0; i < 7; i++){
            if(cur->order[i] != 0){
                printf("Mon an da chon  So luong    Thanh tien\n");
                printf("%s          %d,         %ld\n", array[i].name, cur->order[i], cur->order[i] * array[i].price);
            }
            if(i == 7)break;
        }
        printf("Tong tien : %ld\n", cur->total);
        if(count == number)break;
        count += 1;
    }
}
void topFood(MonAn listMonAn[], int array[]){
    int max = 0;
    int index = 0;
    for(int i = 0; i < 7; i++){
        int used;
        used = array[i] - listMonAn[i].quantity;
        if(used > max){
             max = used;
             index = i;
             printf("%d\n", max);
        }
    }
    printf("Top food: %s - %d\n", listMonAn[index].name, max);
}
int main(){
    int number = 0;
    int sttMon = 1;
    MonAn listMonAn[7];
    int used[7];
    inputFromFile(listMonAn, "./data.txt");
    for(int i = 0; i < 7; i++){
        used[i] = listMonAn[i].quantity;
    }
    int select;
    int count = 0;
    long total = 0;
    Request *root = NULL;
    Request *newRequest = malloc(sizeof(Request));
    while(99){
        menu();
        printf("Nhap lua chon: ");
        scanf("%d", &select);
        __fpurge(stdin);
        switch(select){
            case 1:
                menuMonAn(listMonAn);
                break;
            case 2:
                while(99){
                    int soluong;  
                    printf("Nhap so luong muon mua cua mon thu %d: ", sttMon);
                    scanf("%d", &soluong);
                    __fpurge(stdin);
                    if(listMonAn[sttMon - 1].quantity >= soluong){
                        long price = listMonAn[sttMon -1].price;
                        newRequest->id = count;
                        newRequest->order[sttMon - 1] = soluong;
                        total = total + price * soluong;
                        newRequest->total = total;
                        printf("dat thanh cong\n");
                        listMonAn[sttMon - 1].quantity = listMonAn[sttMon - 1].quantity - soluong;
                        count += 1;
                        sttMon += 1;
                    }else{
                        printf("MOn an nay da het \n");
                        sttMon += 1;
                    }
                    if(count == 7){
                        count = 0;
                        total = 0;
                        break;
                    }
                }
                int status = 0;
                for(int i = 0; i < 7; i++){
                    if(newRequest->order[i] != -1){
                        status = 1;
                        break;
                    }
                }
                if(status == 1){
                    root = push(root, newRequest);
                    printf("Tong tien : %ld\n", root->total);
                    newRequest = malloc(sizeof(Request));
                    number += 1;
                    sttMon = 1;
                }else{
                    printf("Dat hang khong thanh cong, quy khac thong cam\n");
                    sttMon = 1;
                }    
                break;
            case 3:
                printfRequest(root, listMonAn, number);
                break;
            case 4:
                topFood(listMonAn, used);
                break;
            case 5:
                return 0;
            default:
                printf("Nhap sai, nhap lai\n");
        }

    }
    return 0;
}
