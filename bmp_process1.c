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
    // Output Binary(Bitmap Image)
    FILE *bmp_dump = fopen("test_img/res/test1.bmp","wb");
    // Input image stream
    FILE *bmp_read = fopen("test_img/lena512.bmp","r");

    if(bmp_read==NULL){
       logger("Cannot Open the File", ERROR|EXIT, stdout);
    }
    // Image Metadata
    uint8_t bmp_header[54];
    uint8_t bmp_colorTable[1024];
    for(size_t i=1; i<=ARR_SIZE(bmp_header);i++){
        bmp_header[i-1] = (uint8_t)getc(bmp_read);
    }
    //Reading the original Image
    int bmp_width = *(int*)&bmp_header[18];
    int bmp_height = *(int*)&bmp_header[22];
    int bmp_bitDepth = *(int*)&bmp_header[28];
    if(bmp_bitDepth<=8){
        fread(bmp_colorTable,sizeof(uint8_t),1024,bmp_read);
    }
    uint8_t img_buffer[bmp_height*bmp_width];
    fread(img_buffer, sizeof(uint8_t), (uint8_t){bmp_height*bmp_width}, bmp_read);
    //Logging
    char* img_dim=malloc(sizeof(char)*50);
    sprintf(img_dim,"Width:%d\tHeight:%d",bmp_width,bmp_height);
    logger(img_dim,INFO,stdout);
    fwrite(bmp_header,sizeof(uint8_t),54, bmp_dump);
    //Writing the output bitmap file
    if(bmp_bitDepth<=8){
        fwrite(bmp_colorTable,sizeof(uint8_t),1024, bmp_dump);
    }
    fwrite(img_buffer,sizeof(uint8_t), (uint8_t){bmp_height*bmp_width}, bmp_dump);
    //Closing the File stream
    fclose(bmp_dump); fclose(bmp_read);
    return 0;
}













