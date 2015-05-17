#include "chacha.h"

#include <string.h>
#include <endian.h>
#include <stdio.h>

static const chacha_round_def CHACHA_ROUND_DEFS[8] = {
        {0, 4,  8, 12},
        {1, 5,  9, 13},
        {2, 6, 10, 14},
        {3, 7, 11, 15},
        {0, 5, 10, 15},
        {1, 6, 11, 12},
        {2, 7,  8, 13},
        {3, 4,  9, 14}
};

static const uint32_t CHACHA_MAGIC_NUMBERS[4] = {
        0x61707865, 0x3320646e, 0x79622d32, 0x6b206574
};

void chacha_quarter_round(chacha_state s, const chacha_round_def d){
        s[d[0]] += s[d[1]];
        s[d[3]] ^= s[d[0]];
        ROTL_32(s[d[3]], 16);
        
        s[d[2]] += s[d[3]];
        s[d[1]] ^= s[d[2]];
        ROTL_32(s[d[1]], 12);
        
        s[d[0]] += s[d[1]];
        s[d[3]] ^= s[d[0]];
        ROTL_32(s[d[3]], 8);
        
        s[d[2]] += s[d[3]];
        s[d[1]] ^= s[d[2]];
        ROTL_32(s[d[1]], 7);
}

void chacha_state_setup(chacha_state s, chacha_key k, chacha_nonce iv, chacha_counter c){      
        s[0]  = CHACHA_MAGIC_NUMBERS[0];
        s[1]  = CHACHA_MAGIC_NUMBERS[1];
        s[2]  = CHACHA_MAGIC_NUMBERS[2];
        s[3]  = CHACHA_MAGIC_NUMBERS[3];
        s[4]  = k[0];
        s[5]  = k[1];
        s[6]  = k[2];
        s[7]  = k[3];
        s[8]  = k[4];
        s[9]  = k[5];
        s[10] = k[6];
        s[11] = k[7];
        s[12] = c;
        s[13] = iv[0];
        s[14] = iv[1];
        s[15] = iv[2];
}

void chacha_block(chacha_state s){
        unsigned char i, j;
       
        chacha_state t;
        memcpy(t, s, CHACHA_STATE_SIZE * sizeof(uint32_t));
        
        for(i = 0; i < 10; i++){
                for(j = 0; j < 8; j++){
                        chacha_quarter_round(t, CHACHA_ROUND_DEFS[j]);
                }
        }
        
        for(i = 0; i < CHACHA_STATE_SIZE; i++){
                s[i] += t[i];
        }

}

void chacha_encrypt(uint32_t counter, const unsigned char key[32], const unsigned char iv[12], const unsigned char *input, unsigned char *output, size_t len){
        uint32_t i, j;
        chacha_key key_32;
        chacha_nonce iv_32;
        
        /* fix endianness of input key */
        for(i = 0; i < 8; i++){
                key_32[i] = htole32(((const uint32_t *) key)[i]);
        }
        
        /* fix endianness of input iv */
        for(i = 0; i < 3; i++){
                iv_32[i] = htole32(((const uint32_t *) iv)[i]);
        }
        
        /* process each block */
        for(i = 0; i < len; i+=64){
                uint32_t b_len = (i/64 == len/64) ? (len - i) : 64;
                uint32_t keystream[16];
                
                /* generate keystream */
                chacha_state s;
                chacha_state_setup(s, key_32, iv_32, counter + i/64);
                chacha_block(s);
                
                /* fix endianness of keystream */
                for(j = 0; j < b_len; j+=4){
                        keystream[j/4] = le32toh(s[j/4]);
                }
                
                /* xor keystream with input */
                for(j = 0; j < b_len; j++){
                        output[i+j] = input[i+j] ^ ((unsigned char *)keystream)[j];
                }
        }       
}
