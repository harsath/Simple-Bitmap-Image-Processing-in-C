// make logger.o
// make bright
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<assert.h>
#include "logger.h"

#define ERROR (uint8_t)0x01
#define INFO (uint8_t)0x02
#define EXIT (uint8_t)0x04
#define ARR_SIZE(arr)(size_t)(sizeof(arr)/sizeof(arr[0]))
#define BRIGHTNESS_FACTOR 27
#define MAX_COLOR_G 255 // Grayscale 2^8-1 
//TODO: Make it as module passed by cli
//TODO: bright(const char *src, const char *dest) -> sprintf(dest,"%s/%s",(char*)system("pwd"),(char*)FILE_NAME);
int main(){
    // Input image stream
    FILE *bmp_read = fopen("test_img/lena512.bmp","rb");

    if(bmp_read==NULL){
       logger("Cannot Open the File", ERROR|EXIT, stdout);
    }
    // Output Binary(Bitmap Image)
    FILE *bmp_dump = fopen("test_img/res/bright.bmp","wb");

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
    fread(img_buffer, sizeof(uint8_t), bmp_height*bmp_width, bmp_read);
    //Logging
    char* img_dim=malloc(sizeof(char)*50);
    sprintf(img_dim,"Width:%d\tHeight:%d",bmp_width,bmp_height);
    logger(img_dim,INFO,stdout);
    fwrite(bmp_header,sizeof(uint8_t),54, bmp_dump);
    //Writing the output bitmap file
    //Placeholder for negative image
    uint8_t *bright_img = (uint8_t*)malloc(sizeof(bmp_height*bmp_width));
    uint8_t temp_buffer;
    if(bmp_bitDepth<=8){
        fwrite(bmp_colorTable,sizeof(uint8_t),1024, bmp_dump);
    }
    //Incrementing the value of color palette by factor of BRIGHTNESS_FACTOR
    for(size_t i=0; i<bmp_height; i++){
        for(size_t x=0; x<bmp_width; x++){
            temp_buffer = img_buffer[i*bmp_width+x] + BRIGHTNESS_FACTOR;
            bright_img[i*bmp_width+x]=(temp_buffer>MAX_COLOR_G)?MAX_COLOR_G:temp_buffer;
        }
    }

    fwrite(bright_img,sizeof(uint8_t), bmp_height*bmp_width, bmp_dump);
    //Closing the File stream
    //TODO: Macro to freeup malloc() allocated memory
    fclose(bmp_dump); fclose(bmp_read);
    return 0;
}
