#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<assert.h>
#include "logger.h"

#define ERROR (uint8_t)0x01
#define INFO (uint8_t)0x02
#define EXIT (uint8_t)0x04
#define ARR_SIZE(arr)(size_t)(sizeof(arr)/sizeof(arr[0]))

int main(){
    // Input file stream
    // FILE *bmp_read = fopen("test_img/lena512.bmp","r");
    // if(bmp_read==NULL){
    //     printf("Cannot open the file\n");
    //     exit(0);
    // }
    // // Image Metadata
    // uint8_t bmp_header[54];
    // uint8_t bmp_colorTable[1024];
    // for(size_t i=1; i<=ARR_SIZE(bmp_header);i++){
    //     bmp_header[i-1] = (uint8_t)getc(bmp_read);
    // }
    // int bmp_width = *(int*)&bmp_header[18];
    // int bmp_height = *(int*)&bmp_header[22];
    // int bmp_bitDepth = *(int*)&bmp_header[28];
    logger("Test message!", INFO|, stdout);


    return 0;
}













