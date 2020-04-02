#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "logger.h"

#define TS_BUFFER_L 30
#define ERROR (uint8_t)0x01
#define INFO (uint8_t)0x02
#define EXIT (uint8_t)0x04

// Logger function for stdout or file
void logger(const char* message, uint8_t tag, FILE *fd){
    // Date time object formatings
    char timestamp[TS_BUFFER_L]; char datestamp[TS_BUFFER_L];
    char MSG_EMBED[100];
    struct tm *timeInfo = localtime(&(time_t){time(NULL)});
    strftime(timestamp, TS_BUFFER_L, "Time: %H:%M:%S",timeInfo);
    strftime(datestamp, TS_BUFFER_L, "Date: %F (%a)",timeInfo);
    sprintf(MSG_EMBED, "%s\t%s",timestamp,datestamp);
    if(tag & ERROR){
        fprintf(fd, "ERROR: %s\n%s\n",MSG_EMBED,message);
    }
    if(tag & INFO){
        fprintf(fd, "INFO: %s\n%s\n",MSG_EMBED,message);
    }
    if(tag & EXIT){
        exit(1);
    }

}







