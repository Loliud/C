#include<stdio.h>
int change(int x){
    x = x + 20;
    return x;
}
int main(){

    int a = 10;
    
    a = change(a); // 30
    printf("\n%d\n", a);

    return 0;
}