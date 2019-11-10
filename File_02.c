#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void readAndWriteFile(FILE *file_01, FILE *file_02){
    char text[2000];
    char sentence[300];
    while(fgets(sentence, 500, file_01)){
        strcat(text, sentence);
    }
    // printf("%s", text);

    //
    for(int i = 0; i < strlen(text); i++){
        for(int j = i; j < strlen(text); j++){
            if(text[i] < text[j]){
                char c = text[i];
                text[i] = text[j];
                text[j] = c;
            }
        }
    }
    printf("%s", text);
    for(int i = 0; i < strlen(text); i++){
        int count = 0;
        if(('a' <= text[i] && 'z' >= text[i]) || ('A' <= text[i] && 'Z' >= text[i])){
            for(int j = i; j < strlen(text); j++){
                if(text[i] == text[j]){
                    count += 1;
                }else{
                    printf("%c : %d\n", text[i], count);
                    fprintf(file_02, "%c : %d\n", text[i], count);
                    count = 0;
                    i = j - 1;
                    break; // uuuuu 
                }
            }
        }
    }
    fclose(file_01);
    fclose(file_02);
}
int main(){

    FILE *file_01;
    FILE *file_02;
    file_01 = fopen("./info_01.txt", "r");
    file_02 = fopen("./info_02.txt", "w");
    readAndWriteFile(file_01, file_02);






    return 0;
}