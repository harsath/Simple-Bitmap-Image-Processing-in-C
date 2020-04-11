#include<stdint.h>
#ifndef LOGGER_H
#define LOGGER_H
void logger(const char message[static 1], uint8_t tag, FILE *fd);
#endif