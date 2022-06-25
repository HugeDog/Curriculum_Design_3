#include "diff1.h"

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

inline uint64_t powmodp(uint64_t a, uint64_t b) {
    if (a > P)
        a%=P;
    return pow_mod_p(a,b);
}

inline char getchk(int a){
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

inline uint64_t randomint64() {
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

inline void keysinit(uint64_t ini, unsigned char* k){
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

inline ret test1() {
    uint64_t a = randomint64();
    uint64_t A = powmodp(G, a);
    uint64_t b = randomint64();
    uint64_t B = powmodp(G, b);
    ret result;
    result.a = b;
    result.b = B;
    return result;
}

inline ret test3() {
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


inline void test4(uint64_t f,uint64_t l, unsigned char* k) {
    uint64_t secret1 = powmodp(f,l);
    keysinit(secret1, k);
    return ;
}


inline void test2(uint64_t f,uint64_t l, unsigned char* k) {
    uint64_t secret2 = powmodp(f,l);
    memset(keys,0,sizeof(keys));
    keysinit(secret2, k);
    return ;
}

inline void tostr(int num, char *str){
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

inline int toint(char *str){
    int sum = 0, flag = 1, i = 0;
    while(i < 8){
        sum += (str[i] - 48) * flag;
        flag *= 10;
        ++ i;
    }
    return sum;

}

inline void divided(char* source,char* dst1,char* dst2){
  int pos = 0;
  int j = 0;
  while(source[pos] != '\1') ++pos;
  for (int i = 0; i < pos; ++i){
      dst1[i] = source[i];
  }
  dst1[pos] = '\0';
  for (int i = pos + 3; source[i]; ++i, ++j){
    dst2[j] = source[i];
  } 
  dst2[j] = '\0';
  return;
}


inline void my_system(const char *cmd, char *result)
{
	  char buf[1024];
    int flag = 0;
    memset( buf, '\0', sizeof(buf) );
    FILE *fp = NULL;

    if( (fp = popen(cmd, "r")) == NULL ) {
        printf("popen error!\n");
        return;
    }
    memset( buf, '\0', sizeof(buf) );
    while (fgets(buf, sizeof(buf), fp)) {
        flag++;
        if(flag >= 1)
        strcat(result, buf);
    }
    
    pclose(fp);

}
