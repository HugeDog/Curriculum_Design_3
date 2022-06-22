#include "../include/diff1.h"

typedef struct res{
    uint64_t a;
    uint64_t b;
}ret;

ret test1() {
    uint64_t a = randomint64();
    uint64_t A = powmodp(G, a);
    uint64_t b = randomint64();
    uint64_t B = powmodp(G, b);
    ret result;
    result.a = b;
    result.b = B;
    return result;
}

ret test3() {
    sleep(1.1);
    srand(time(NULL));
    uint64_t a = randomint64();
    uint64_t A = powmodp(G, a);
    uint64_t b = randomint64();
    uint64_t B = powmodp(G, b);
    ret result;
    result.a = a;
    result.b = A;
    return result;
}


void test4(uint64_t f,uint64_t l, unsigned char* k) {
    uint64_t secret1 = powmodp(f,l);
    keysinit(secret1, k);
    return ;
}


void test2(uint64_t f,uint64_t l, unsigned char* k) {
    uint64_t secret2 = powmodp(f,l);
    memset(keys,0,sizeof(keys));
    keysinit(secret2, k);
    return ;
}

void tostr(int num, char *str){
    int temp, i = 1;
    temp = num % 10;
     // 48
    str[0] = 48 + temp;
    while(i < 8){
        num = num / 10;
        temp = num % 10;
        str[i] = 48 + temp;
        ++ i;
    }
    str[8] = '\0';
    return;
}

int toint(char *str){
    int sum = 0, flag = 1, i = 0;
    while(i < 8){
        sum += (str[i] - 48) * flag;
        flag *= 10;
        ++ i;
    }
    return sum;

}