#include "stdio.h"
#include "stdint.h"

void sbus_encode(uint8_t *packet, int16_t *output){
    ;
    packet[0] = 0x0F; //Header

    packet[1] = (uint8_t) (output[0] & 0x07FF);
    packet[2] = (uint8_t) ((output[0] & 0x07FF)>>8 | (output[1] & 0x07FF)<<3);
    packet[3] = (uint8_t) ((output[1] & 0x07FF)>>5 | (output[2] & 0x07FF)<<6);
    packet[4] = (uint8_t) ((output[2] & 0x07FF)>>2);
    packet[5] = (uint8_t) ((output[2] & 0x07FF)>>10 | (output[3] & 0x07FF)<<1);
    packet[6] = (uint8_t) ((output[3] & 0x07FF)>>7 | (output[4] & 0x07FF)<<4);
    packet[7] = (uint8_t) ((output[4] & 0x07FF)>>4 | (output[5] & 0x07FF)<<7);
    packet[8] = (uint8_t) ((output[5] & 0x07FF)>>1);
    packet[9] = (uint8_t) ((output[5] & 0x07FF)>>9 | (output[6] & 0x07FF)<<2);
    packet[10] = (uint8_t) ((output[6] & 0x07FF)>>6 | (output[7] & 0x07FF)<<5);
    packet[11] = (uint8_t) ((output[7] & 0x07FF)>>3);
    packet[12] = (uint8_t) ((output[8] & 0x07FF));
    packet[13] = (uint8_t) ((output[8] & 0x07FF)>>8 | (output[9] & 0x07FF)<<3);
    packet[14] = (uint8_t) ((output[9] & 0x07FF)>>5 | (output[10] & 0x07FF)<<6);  
    packet[15] = (uint8_t) ((output[10] & 0x07FF)>>2);
    packet[16] = (uint8_t) ((output[10] & 0x07FF)>>10 | (output[11] & 0x07FF)<<1);
    packet[17] = (uint8_t) ((output[11] & 0x07FF)>>7 | (output[12] & 0x07FF)<<4);
    packet[18] = (uint8_t) ((output[12] & 0x07FF)>>4 | (output[13] & 0x07FF)<<7);
    packet[19] = (uint8_t) ((output[13] & 0x07FF)>>1);
    packet[20] = (uint8_t) ((output[13] & 0x07FF)>>9 | (output[14] & 0x07FF)<<2);
    packet[21] = (uint8_t) ((output[14] & 0x07FF)>>6 | (output[15] & 0x07FF)<<5);
    packet[22] = (uint8_t) ((output[15] & 0x07FF)>>3);

    packet[23] = 0x00; //Flags byte
    packet[24] = 0x00; //Footer
}

void sbus_decode(uint8_t *sbus_original_data, int16_t *sbus_ch){
    ;
	sbus_ch[ 0] = ((int16_t)sbus_original_data[ 1] >> 0 | ((int16_t)sbus_original_data[ 2] << 8 )) & 0x07FF;
	sbus_ch[ 1] = ((int16_t)sbus_original_data[ 2] >> 3 | ((int16_t)sbus_original_data[ 3] << 5 )) & 0x07FF;
	sbus_ch[ 2] = ((int16_t)sbus_original_data[ 3] >> 6 | ((int16_t)sbus_original_data[ 4] << 2 )  | (int16_t)sbus_original_data[ 5] << 10 ) & 0x07FF;
	sbus_ch[ 3] = ((int16_t)sbus_original_data[ 5] >> 1 | ((int16_t)sbus_original_data[ 6] << 7 )) & 0x07FF;
	sbus_ch[ 4] = ((int16_t)sbus_original_data[ 6] >> 4 | ((int16_t)sbus_original_data[ 7] << 4 )) & 0x07FF;
	sbus_ch[ 5] = ((int16_t)sbus_original_data[ 7] >> 7 | ((int16_t)sbus_original_data[ 8] << 1 )  | (int16_t)sbus_original_data[ 9] <<  9 ) & 0x07FF;
	sbus_ch[ 6] = ((int16_t)sbus_original_data[ 9] >> 2 | ((int16_t)sbus_original_data[10] << 6 )) & 0x07FF;
	sbus_ch[ 7] = ((int16_t)sbus_original_data[10] >> 5 | ((int16_t)sbus_original_data[11] << 3 )) & 0x07FF;
	
	sbus_ch[ 8] = ((int16_t)sbus_original_data[12] << 0 | ((int16_t)sbus_original_data[13] << 8 )) & 0x07FF;
	sbus_ch[ 9] = ((int16_t)sbus_original_data[13] >> 3 | ((int16_t)sbus_original_data[14] << 5 )) & 0x07FF;
	sbus_ch[10] = ((int16_t)sbus_original_data[14] >> 6 | ((int16_t)sbus_original_data[15] << 2 )  | (int16_t)sbus_original_data[16] << 10 ) & 0x07FF;
	sbus_ch[11] = ((int16_t)sbus_original_data[16] >> 1 | ((int16_t)sbus_original_data[17] << 7 )) & 0x07FF;
	sbus_ch[12] = ((int16_t)sbus_original_data[17] >> 4 | ((int16_t)sbus_original_data[18] << 4 )) & 0x07FF;
	sbus_ch[13] = ((int16_t)sbus_original_data[18] >> 7 | ((int16_t)sbus_original_data[19] << 1 )  | (int16_t)sbus_original_data[20] <<  9 ) & 0x07FF;
	sbus_ch[14] = ((int16_t)sbus_original_data[20] >> 2 | ((int16_t)sbus_original_data[21] << 6 )) & 0x07FF;
	sbus_ch[15] = ((int16_t)sbus_original_data[21] >> 5 | ((int16_t)sbus_original_data[22] << 3 )) & 0x07FF;
}

int16_t map_range(int16_t lista, int16_t amin, int16_t amax, int16_t bmin, int16_t bmax){
    return (int16_t)(((float)(lista - amin) / (float)(amax - amin)) * (bmax - bmin) + bmin);
}

int main(){
    ;
    uint8_t packet[25] = {0};
    int16_t output[16] = {0};
    uint8_t sbus_original_data[25] = {0};
    int16_t sbus_ch[16] = {0};
    uint8_t flag = 1;

    for(uint8_t i = 0; i < 16; i++){
        output[i] = map_range(1500, 1000, 2000, 173, 1811);
        //printf("output[%d] = %d\n", i, output[i]);
    }

    sbus_encode(packet, output);

    for(uint8_t i = 0; i < 25; i++){
        sbus_original_data[i] = packet[i];
    }

    sbus_decode(sbus_original_data, sbus_ch);

    for(uint8_t i = 0; i < 16; i++){
        if(map_range(sbus_ch[i], 173, 1811, 1000, 2000) != 1500) flag = 0;
    }

    if(flag) printf("Success!\n");
    else printf("Fail!\n");

    return 0;
}
