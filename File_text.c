#include<stdio.h>
#include<stdlib.h>
void readAndWriteFile(FILE *file_01, FILE *file_02){
    int c;
    while((c = fgetc(file_01)) != EOF){
        printf("%c", (char)c);
        fputc(c, file_02);
    }
    fclose(file_01);
    fclose(file_02);
}
int main(){

    // mo file
    FILE *file_01;
    FILE *file_02;
    file_01 = fopen("./info_01.txt", "r");
    file_02 = fopen("./info_02.txt", "w");
    readAndWriteFile(file_01, file_02);
   








    return 0;
}