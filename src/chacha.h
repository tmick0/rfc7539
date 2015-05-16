#ifndef _chacha_h_
#define _chacha_h_

#include <stdint.h>
#include <string.h>

#define ROTL_32(x, n) x = (x << n) | (x >> (32 - n))

/* sizes in 32-bit words */
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
void chacha_encrypt(uint32_t counter, const unsigned char key[32], const unsigned char iv[12], const unsigned char *input, unsigned char *output, size_t len);

#endif
