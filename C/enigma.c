#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define VER "0.1"
#define YY 2023
#define MM 9
#define DD 5
#define auther "soranoue"


int main(void){
    int Rot1[26] = { 10, 14, 1, 15, 9, 23, 20, 4, 21, 8, 7, 24, 18, 5, 25, 6, 17, 16, 11, 13, 2, 3, 19, 26, 22, 12};
    int Rot2[26] = { 19, 11, 12, 23, 10, 3, 13, 14, 6, 2, 1, 15, 25, 26, 5, 20, 22, 17, 8, 16, 9, 7, 18, 24, 21, 4};
    int Rot3[26] = { 16, 15, 4, 19, 6, 12, 1, 24, 3, 2, 17, 14, 25, 10, 13, 22, 21, 20, 23, 5, 26, 7, 18, 9, 8, 11};
    int Rot4[26] = { 25, 24, 19, 16, 13, 23, 8, 26, 10, 1, 21, 2, 7, 14, 20, 6, 3, 9, 22, 11, 17, 18, 12, 5, 4, 15};
    int Refl[26] = { 21, 23, 15, 19, 16, 20, 10, 18, 13, 17, 1, 7, 26, 25, 4, 9, 22, 12, 3, 5, 11, 8, 2, 24, 14, 6};

    printf("ENIGMA Ver %s\n%d-%d-%d By %s\n",VER,YY,MM,DD,auther);

    for(int i = 0;i < 26;i++){
        printf("%d,",Rot1[i]);
        printf("%d,",Rot2[i]);
        printf("%d,",Rot3[i]);
        printf("%d,",Rot4[i]);
        printf("%d,",Refl[i]);
    }
    return 0;
}