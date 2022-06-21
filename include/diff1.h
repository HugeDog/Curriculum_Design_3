#ifndef _DIFF1_H  
#define _DIFF1_H 
#define P 0xfffffffffffffcc5ull
#define G 7
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned char keys[128] = {'\0'};
int prime[45] = { 593, 607, 653, 733, 947, 977, 1103, 1123, 1187, 1223, 1367, 1511, 1747, 1753, 1907, 2287, 2417, 2677, 29, 41, 47, 53, 59, 71, 83, 89, 101, 107, 113, 131, \
       137, 149, 167, 173, 179, 191, 197, 227, 233, 239, 251, 257, 263};
static inline uint64_t mul_mod_p(uint64_t a, uint64_t b) {
    uint64_t m = 0;
    while(b) {
        if(b&1) {
            uint64_t t = P-a;
            if ( m >= t) {
                m -= t;
            } else {
                m += a;
            }
        }
        if (a >= P - a) {
            a = a * 2 - P;
        } else {
            a = a * 2;
        }
        b>>=1;
    }
    return m;
}
static inline uint64_t pow_mod_p(uint64_t a, uint64_t b) {
    if (b==1) {
        return a;
    }
    uint64_t t = pow_mod_p(a, b>>1);
    t = mul_mod_p(t,t);
    if (b % 2) {
        t = mul_mod_p(t, a);
    }
    return t;
}
uint64_t powmodp(uint64_t a, uint64_t b) {
    if (a > P)
        a%=P;
    return pow_mod_p(a,b);
}

char getchk(int a){
    int flag = a % 16 ;
    switch(flag) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13:return 'D';
        case 14: return 'E';
        case 15: return 'F';
    }
}

uint64_t randomint64() {
    srand(time(NULL));
    uint64_t a = rand();
    srand(3 * time(NULL) + 57564323);
    uint64_t b = rand();
    srand(7 * time(NULL) + 57564323);
    uint64_t c = rand();
    srand(13 * time(NULL) + 57564323);
    uint64_t d = rand();
    return a << 48 | b << 32 | c << 16 | d;
}

void keysinit(uint64_t ini, unsigned char* k){
    uint64_t test = ini;
    int i;
    for (i = 0; i <32; ++i){
        if((i + 1)%3 == 0){
            test = test * 7;
        }
        srand(test >> 4 + test / 13);
        int temp = (rand() * rand() / 31 + test >> 7 )% 16;
        k[i] = getchk(temp);
        test = test >> 1;
    }
    k[i] = '\0';
    return ;
}

// void keysinit(uint64_t ini, unsigned char* k){
//     uint64_t test = ini;
//     int i;
//     for (i = 0; i <32; ++i){
//         if((i + 1)%3 == 0){
//             test = test * 7;
//         }
//         srand(test >> 4 + test / 13);
//         int temp = (test * prime[i+1] + test >> 7 )% 16;
//         k[i] = getchk(temp);
//         test = test >> 1;
//     }
//     k[i] = '\0';
//     return ;
// }

#endif  