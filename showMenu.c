#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdio_ext.h>
void showMenu(){
    printf("Chon 1.\n");
    printf("Chon 2.\n");
    printf("Chon 3.\n");
    printf("Chon 4.\n");
    printf("Chon 5.\n");
}
int main(){
    int select;
    while(69){
        showMenu();
        printf("Hay nhap lua chon: ");
        scanf("%d", &select);
        __fpurge(stdin);
        switch(select){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                return 0;
                break;
            default:
                break;
        }
    }
    return 0;
}
	
