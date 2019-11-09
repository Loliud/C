#include<stdio.h>
#define max 200
void nhap(int array[], int size){
    printf("\nNhap: ");
    for(int i = 0; i < size; i++){
        scanf("%d", &array[i]);
    }
}
void in(int array[], int size){
    printf("\nIn\n");
    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
}
void insert(int array[], int *size, int index, int value){ // 20 30 60   
                                                          //  0  1  2   size   
    // chen vao cuoi                                        // 
    if(index == *size){
        array[index] = value;
        *size++;
    }
    // dau hoac giua
    else if(index != *size){
        for(int i = *size; i >= index; i--){
            array[i] = array[i - 1];
            if(i == index){
                array[i] = value;
                
            }
            //array[i + 1] = array[i];  
        }
        *size = *size + 1;
    }
}
void delete(int array[], int *size, int index){
    for(int i = index; i < *size; i++){
        array[i] = array[i + 1];
    }
    *size = *size - 1;
}
int main(){

    int array[max];
    int size;
    printf("\nNhap size: ");
    scanf("%d", &size);
    nhap(array, size);
    in(array, size);
    delete(array, &size, 1);
    // insert(array, size, 1, 300);
    in(array, size);
   
    return 0;
}