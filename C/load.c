#include <stdio.h>
#include <windows.h>

void load(int n);

int main(void){

    load(10);
    return 0;
}

void load(int n){
    printf("loading ");
    for(int i=0;i<=n;i++){
        printf("\b");
        printf("|");
        Sleep(100);

        printf("\b");
        printf("\\");
        Sleep(100);

        printf("\b");
        printf("-");
        Sleep(100);

        printf("\b");
        printf("/");
        Sleep(100);
    }
    printf("\b \ncomplete!\n");
}
