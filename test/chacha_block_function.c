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
                0xe4e7f110, 0x15593bd1, 0x1fdd0f50, 0xc47120a3,
                0xc7f4d1c7, 0x0368c033, 0x9aaa2204, 0x4e6cd4c3,
                0x466482d2, 0x09aa9f07, 0x05d7c214, 0xa2028bd9,
                0xd19c12b5, 0xb94e16de, 0xe883d0cb, 0x4e3c50a2
        };
        
        chacha_state_setup(s, k, iv, c);
        chacha_block(s);
        
        for(i = 0; i < CHACHA_STATE_SIZE; i++){
                if(s[i] != t[i])
                        return 1;
        }
        
        return 0;
}
