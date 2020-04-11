#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<stdbool.h>

#include "logger.h"

#define TS_BUFFER_L 30
#define LOG_MSG_SIZE 100
#define ERROR (uint8_t)0x01
#define INFO (uint8_t)0x02
#define EXIT (uint8_t)0x04

// Logger function for stdout or file
void logger(const char message[static 1], uint8_t tag, FILE *fd){
    _Bool is_error = tag & ERROR;
    _Bool is_info = tag & INFO;
    assert(!(is_error && is_info));
    
    // Date time object formatings
    char timestamp[TS_BUFFER_L]; char datestamp[TS_BUFFER_L];
    char MSG_EMBED[LOG_MSG_SIZE];
    struct tm *timeInfo = localtime(&(time_t){time(NULL)});
    strftime(timestamp, TS_BUFFER_L, "Time: %H:%M:%S",timeInfo);
    strftime(datestamp, TS_BUFFER_L, "Date: %F (%a)",timeInfo);
    sprintf(MSG_EMBED, "%s\t%s",timestamp,datestamp);
    //Logical And for Conditional jumps
    if(tag & ERROR){
        snprintf(MSG_EMBED,LOG_MSG_SIZE,"ERROR: %s\n%s\n",MSG_EMBED,message);
        perror(MSG_EMBED);
    }
    if(tag & INFO){
        fprintf(fd, "INFO: %s\n%s\n",MSG_EMBED,message);
    }
    if(tag & EXIT){
        exit(EXIT_FAILURE);
    }

}







