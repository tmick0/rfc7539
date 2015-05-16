#ifndef _error_h_
#define _error_h_

typedef enum {
        ERROR_FATAL,
        ERROR_WARN,
        ERROR_INFO
} error_severity;

void error(error_severity level, const char *fmt, ...);

#endif
