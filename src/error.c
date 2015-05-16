#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void error(error_severity level, const char *fmt, ...){
        va_list args;
        
        switch(level){
                case ERROR_WARN:
                        fprintf(stderr, "Warning: ");
                        break;
                case ERROR_INFO:
                        fprintf(stderr, "Info: ");
                        break;
                case ERROR_FATAL:
                default:
                        fprintf(stderr, "Fatal error: ");
                        break;
        }

        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
        fprintf(stderr, "\n");
        
        if(level == ERROR_FATAL){
                exit(EXIT_FAILURE);
        }
}
