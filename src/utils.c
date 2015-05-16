#include "utils.h"
#include "error.h"
#include <fcntl.h>
#include <unistd.h>

void rand_bytes(unsigned char *buf, size_t count){
        int rh = open("/dev/urandom", O_RDONLY);
        if(read(rh, buf, count) < 0){
                error(ERROR_FATAL, "Could not read from /dev/urandom");
        }
        close(rh);
}
