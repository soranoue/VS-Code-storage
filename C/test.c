#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int16_t input = -1832;
int16_t output = 0;
uint8_t Hbit = 0, Lbit = 0;

int main(){
    Lbit = (uint8_t)input;
    Hbit = (uint8_t)(input >> 8);
    output = (int16_t)Hbit << 8 | Lbit;
    printf("HELLO,WORLD!\n%d\n", output);
    return 0;
}