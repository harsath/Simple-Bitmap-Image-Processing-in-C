#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#include<string.h>
#include<stdbool.h>
#include "bright_convert.c"
#include "negative_convert.c"

#define C_BUFFER_SIZE 50
#define ERROR (uint8_t)0x01
#define INFO (uint8_t)0x02
#define EXIT (uint8_t)0x04
#define ARR_SIZE(arr)(size_t)(sizeof(arr)/sizeof(arr[0]))

// TODO: Update usage print
void usage_binary(void){
    printf("Usage: ./bin --negative --bright --src [source image] --dest [output image path] \n");
}
//Placeholder struct for parsed arguments
typedef struct parse_args{
    // Negative conversion
    bool is_negative; 
    union{char *src_negative; bool no_negative;};
    char *dest_negative;

    // Bright conversion
    bool is_bright;
    union{char *src_bright; bool no_bright;};
    char *dest_bright;
}CLI_ARG;

int main(int argc, char* argv[]){
    CLI_ARG *current = (CLI_ARG*)malloc(sizeof(CLI_ARG));
    *current = (CLI_ARG){.is_negative=0, .is_bright=0};
    static struct option long_options[] ={
    {"negative", no_argument, NULL, 'n'},
    {"bright", no_argument, NULL, 'b'},
    {"src", required_argument, NULL, 's'},
    {"dest", required_argument, NULL, 'd'},
    {NULL, 0, NULL, 0}};
    char ch;
    char current_wd[C_BUFFER_SIZE];
    char full_path_dir[C_BUFFER_SIZE+20];
    void* source_buffer;
    void* destination_buffer;
    while ((ch = getopt_long(argc, argv, "n:b:s:d:", long_options, NULL)) != -1){
        switch(ch){
            case 'n':
                current->is_negative = 1;
                break;
            case 'b':
                current->is_bright = 1;
                break;
            case 's':
                current->src_negative = optarg;
                current->src_bright = optarg;
                break;
            case 'd':
                current->dest_bright = optarg;
                current->dest_negative = optarg;
                break;
            default:
                usage_binary();
                logger("Please specify options\n", INFO|EXIT, stdout);
        }

    }

    if(current->is_negative){
        negative(current->src_negative, current->dest_negative);
    }
    if(current->is_bright){
        bright(current->src_bright, current->dest_bright);
    }
    
    return EXIT_SUCCESS;
}





