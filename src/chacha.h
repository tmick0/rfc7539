#ifndef _chacha_h_
#define _chacha_h_

#include <stdint.h>

#define ROTL_32(x, n) x = (x << n) | (x >> (32 - n))

typedef uint32_t chacha_state[16]; 
typedef uint8_t chacha_round_def[4];

void chacha_quarter_round(chacha_state s, chacha_round_def d);

#endif
