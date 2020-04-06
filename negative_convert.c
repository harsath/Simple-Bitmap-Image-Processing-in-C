// make logger.o
// make neg
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<assert.h>
#include "logger.h"

#define ERROR (uint8_t)0x01
#define INFO (uint8_t)0x02
#define EXIT (uint8_t)0x04
#define ARR_SIZE(arr)(size_t)(sizeof(arr)/sizeof(arr[0]))
#define C_BUFFER_SIZE 50
//TODO: Make it as module passed by cli
//TODO: negative(const char *src, const char *dest) sprintf(dest,"%s/%s",(char*)system("pwd"),(char*)FILE_NAME);
int negative(const char *src, const char *dest){
    // Input image stream
    FILE *bmp_read = fopen(src,"rb");
    if(!bmp_read){
       logger("negative_convert.c:Cannot Open the source file", ERROR|EXIT, stdout);
    }
    // Output Binary(Bitmap Image)
    char destination_buffer[C_BUFFER_SIZE];
    static unsigned long long int count_image = 1;
    sprintf(destination_buffer,"%s/negative_%llu.bmp",dest, count_image);

    FILE *bmp_dump = fopen(destination_buffer,"wb");
    if(!bmp_dump){
        logger("negative_convert.c:Cannot Open the destination file", ERROR|EXIT, stdout);
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
        if(!fread(bmp_colorTable,sizeof(uint8_t),1024,bmp_read)){
            logger("negative_convert.c:Color table cannot be read", ERROR|EXIT, stdout);
        }
    }
    uint8_t img_buffer[bmp_height*bmp_width];
    if(!fread(img_buffer, sizeof(uint8_t), bmp_height*bmp_width, bmp_read)){
        logger("negative_convert.c:Image buffer cannot be read", ERROR|EXIT, stdout);
    }
    //Logging
    char* img_dim=malloc(sizeof(char)*50);
    assert(img_dim!=NULL);
    sprintf(img_dim,"Width:%d\tHeight:%d",bmp_width,bmp_height);
    logger(img_dim,INFO,stdout);
    if(!fwrite(bmp_header,sizeof(uint8_t),54, bmp_dump)){
        logger("negative_convert.c:Cannot write the image header", ERROR|EXIT, stdout);
    }
    //Writing the output bitmap file
    //Placeholder for negative image
    uint8_t *neg_image = (uint8_t*)malloc(bmp_height*bmp_width);
    if(bmp_bitDepth<=8){
        if(!fwrite(bmp_colorTable,sizeof(uint8_t),1024, bmp_dump)){
            logger("negative_convert.c:Cannot write color table on destination", ERROR|EXIT, stdout);
        }
    }
    for(size_t i=0; i<bmp_height; i++){
        for(size_t x=0; x<bmp_width; x++){
            neg_image[i*bmp_width+x] = 255-img_buffer[i*bmp_width+x];   // sub(255,ORG_VALUE)=NEG for 8 bit pat;
        }
    }
    if(!fwrite(neg_image,sizeof(uint8_t), bmp_height*bmp_width, bmp_dump)){
           logger("negative_convert.c:Cannot write to destination", ERROR|EXIT, stdout);
    }
    //Closing the File stream
    fclose(bmp_dump); fclose(bmp_read);
    count_image+=1;
    return 0;
}
