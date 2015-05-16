#include <stdio.h>
#include "chacha.h"

int main(int argc, char **argv) {

        int i;

        chacha_round_def d = {2, 7, 8, 13};

        chacha_state s = {
                0x879531e0, 0xc5ecf37d, 0x516461b1, 0xc9a62f8a,
                0x44c20ef3, 0x3390af7f, 0xd9fc690b, 0x2a5f714c,
                0x53372767, 0xb00a5631, 0x974c541a, 0x359e9963,
                0x5c971061, 0x3d631689, 0x2098d9d6, 0x91dbd320,
        };
        
        chacha_state t = {
                0x879531e0, 0xc5ecf37d, 0xbdb886dc, 0xc9a62f8a,
                0x44c20ef3, 0x3390af7f, 0xd9fc690b, 0xcfacafd2,
                0xe46bea80, 0xb00a5631, 0x974c541a, 0x359e9963,
                0x5c971061, 0xccc07c79, 0x2098d9d6, 0x91dbd320
        };
        
        chacha_quarter_round(s, d);
        
        for(i = 0; i < 16; i++){
                if(s[i] != t[i])
                        return 1;
        }
        
        return 0;
}
