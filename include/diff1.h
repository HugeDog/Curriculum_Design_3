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
#include <unistd.h>

typedef struct res{
    uint64_t a;
    uint64_t b;
}ret;

unsigned inline char keys[128] = {'\0'};

inline int prime[45] = { 593, 607, 653, 733, 947, 977, 1103, 1123, 1187, 1223, 1367, 1511, 1747, 1753, 1907, 2287, 2417, 2677, 29, 41, 47, 53, 59, 71, 83, 89, 101, 107, 113, 131, \
       137, 149, 167, 173, 179, 191, 197, 227, 233, 239, 251, 257, 263};

static inline uint64_t mul_mod_p(uint64_t a, uint64_t b);

static inline uint64_t pow_mod_p(uint64_t a, uint64_t b);

inline uint64_t powmodp(uint64_t a, uint64_t b);

inline char getchk(int a);

inline uint64_t randomint64() ;

inline void keysinit(uint64_t ini, unsigned char* k);

inline ret test1();

inline ret test3() ;

inline void test4(uint64_t f,uint64_t l, unsigned char* k) ;

inline void test2(uint64_t f,uint64_t l, unsigned char* k);

inline void tostr(int num, char *str);

inline int toint(char *str);

inline void divided(char* source,char* dst1,char* dst2);

inline void my_system(const char *cmd, char *result);

#endif  