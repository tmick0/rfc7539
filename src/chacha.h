#ifndef _chacha_h_
#define _chacha_h_

#include <stdint.h>

#define ROTL_32(x, n) x = (x << n) | (x >> (32 - n))

#define CHACHA_STATE_SIZE (16)
#define CHACHA_KEY_SIZE    (8)
#define CHACHA_NONCE_SIZE  (3)

typedef uint32_t chacha_state[CHACHA_STATE_SIZE]; 
typedef uint8_t chacha_round_def[4];

typedef uint32_t chacha_key[CHACHA_KEY_SIZE];
typedef uint32_t chacha_nonce[CHACHA_NONCE_SIZE];
typedef uint32_t chacha_counter;

void chacha_quarter_round(chacha_state s, const chacha_round_def d);
void chacha_state_setup(chacha_state s, chacha_key k, chacha_nonce iv, chacha_counter c);
void chacha_block(chacha_state s);
#endif
