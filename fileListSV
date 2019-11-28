#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<string.h>

typedef struct SinhVien{
    char name[30];
    int age;
    char phone[30];
    char email[30];
}SV;
SV *listSinhVien;
int soLuong = 0;

int inputInfo(SV **listSinhVien){
    printf("Hay nhap so luong sv: ");
    scanf("%d", &soLuong);
    __fpurge(stdin);
    SV *list = (SV*)malloc(sizeof(SV) * soLuong);
    for(int i = 0; i < soLuong; i++){
        printf("Nhap ten sv: ");
        gets(list[i].name);
        __fpurge(stdin);
        printf("Nhap tuoi sv: ");
        scanf("%d", &list[i].age);
        __fpurge(stdin);
        printf("Nhap phone sv: ");
        gets(list[i].phone);
        __fpurge(stdin);
        printf("Nhap email sv: ");
        gets(list[i].email);
        __fpurge(stdin);   
    }
    *listSinhVien = list;
    return soLuong;
}
void writeFile(char *path){
    FILE *file = fopen(path, "wb");
    if(soLuong > 0){
        fwrite(listSinhVien, sizeof(SV), soLuong, file);
    }
    fclose(file);
}
void readFile(char *path){
    FILE *file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    soLuong = size / sizeof(SV);
    listSinhVien = malloc(sizeof(SV) * soLuong);
    fread(listSinhVien, sizeof(SV), soLuong, file);
    fclose(file);
}
int main(){
    
    //soLuong = inputInfo(&listSinhVien);
    //writeFile("./quanlysv.dat");
    readFile("./quanlysv.dat");
    
    for(int i = 0; i < soLuong; i++){
        printf("%s %d %s %s \n", listSinhVien[i].name, listSinhVien[i].age, listSinhVien[i].phone, listSinhVien[i].email);

    }



    return 0;
}
