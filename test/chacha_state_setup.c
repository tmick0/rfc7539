#include <stdio.h>
#include "chacha.h"

int main(int argc, char **argv) {

        int i;

        chacha_state s;

        chacha_key k = {
                0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
                0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c
        };
        
        chacha_nonce iv = {
                0x09000000, 0x4a000000, 0x00000000
        };
        
        chacha_counter c = 1;
        
        chacha_state t = {
                0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
                0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
                0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
                0x00000001, 0x09000000, 0x4a000000, 0x00000000
        };
        
        chacha_state_setup(s, k, iv, c);
        
        for(i = 0; i < CHACHA_STATE_SIZE; i++){
                if(s[i] != t[i])
                        return 1;
        }
        
        return 0;
}
