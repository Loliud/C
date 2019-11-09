#include<stdio.h>
// struct SinhVien{
//     char name[30];
//     int age;
// };
// typedef struct SinhVien SV;

typedef struct SinhVien{
    char name[30];
    int age;
}SV;

void insert(SV list[], int *size, SV value){
    
}
int main(){
    SV sv_01 = {"Ken", 20};
    SV sv_02 = {"Minh", 40};
    SV sv_03 = {"Ky Anh", 20};
    SV list[3];
    list[0] = sv_01;
    list[1] = sv_02;
    list[2] = sv_03;

    for(int i = 0; i < 3; i++){
        printf("%s %d\n", list[i].name, list[i].age);
    }


   
    

    return 0;
}