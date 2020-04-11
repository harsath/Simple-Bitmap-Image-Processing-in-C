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
#define C_BUFFER_SIZE 50
//For pointer deferencing on the following lines
static_assert(sizeof(int)==4, "Size of int is not 4 bytes, This code is not compadable");

int bright(const char src[static 1], const char dest[static 1]){  // sprintf(dest,"%s/%s",(char*)system("pwd"),(char*)FILE_NAME);
    // Input image stream
    FILE *bmp_read = fopen(src,"rb");

    if(bmp_read==NULL){
       logger("bright_convert.c:Cannot Open the File", ERROR|EXIT, stderr);
    }
    // Output Binary(Bitmap Image)
    char destination_buffer[C_BUFFER_SIZE];
    static unsigned long long int count_image = 1;
    snprintf(destination_buffer,C_BUFFER_SIZE,"%s/bright_%llu.bmp",dest, count_image);

    FILE *bmp_dump = fopen(destination_buffer,"wb");
    if(!bmp_dump){
        logger("bright_convert.c:Cannot write to File", ERROR|EXIT, stderr);
    }
    // Image Metadata
    uint8_t bmp_header[54];
    uint8_t bmp_colorTable[1024];
    for(size_t i=0; i<ARR_SIZE(bmp_header);i++){
        bmp_header[i] = (uint8_t)getc(bmp_read);
    }
    //Reading the original Image
    int bmp_width = *(int*)&bmp_header[18];
    int bmp_height = *(int*)&bmp_header[22];
    int bmp_bitDepth = *(int*)&bmp_header[28];
    printf("width=%d height=%d bitDepth=%d\n", bmp_width, bmp_height, bmp_bitDepth);
    if(bmp_bitDepth<=8){
        if(!fread(bmp_colorTable,sizeof(uint8_t),1024,bmp_read)){
            logger("bright_convert.c:Cannot read image table", ERROR|EXIT, stderr);
        }
    }
    uint8_t *img_buffer = (uint8_t*)malloc(bmp_height*bmp_width);
    if(!img_buffer){
        logger("bright_convert.c:Cannot allocate memory for Image Buffer", ERROR|EXIT, stderr);
    }
    fread(img_buffer, sizeof(uint8_t), bmp_height*bmp_width, bmp_read);
    //Logging
    char* img_dim=malloc(sizeof(char)*C_BUFFER_SIZE);
    if(!img_dim){
        logger("bright_convert.c:Memory Error", ERROR|EXIT, stderr);
    }
    snprintf(img_dim,C_BUFFER_SIZE,"Width:%d\tHeight:%d",bmp_width,bmp_height);
    logger(img_dim,INFO,stdout);
    if(!fwrite(bmp_header,sizeof(uint8_t),54, bmp_dump)){
        logger("bright_convert.c:Write Error", ERROR|EXIT, stderr);
    }
    //Writing the output bitmap file
    //Placeholder for bright image
    uint8_t *bright_img = (uint8_t*)malloc(bmp_height*bmp_width);
    if(!bright_img){
        logger("bright_convert.c:Cannot allocate memory for Image Buffer", ERROR|EXIT, stderr);
    }
    int temp_buffer;
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
    if(!fwrite(bright_img,sizeof(uint8_t), bmp_height*bmp_width, bmp_dump)){
        logger("bright_convert.c:Write Error", ERROR|EXIT, stderr);
    }
    //Closing the File stream
    //TODO: Macro to freeup malloc() allocated memory
    fclose(bmp_dump); fclose(bmp_read);
    count_image+=1;
    return 0;
}
