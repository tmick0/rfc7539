#include "chacha.h"

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

void chacha_quarter_round(chacha_state s, chacha_round_def d){
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
