#include "chacha.h"

#include <string.h>

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
