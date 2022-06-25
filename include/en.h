#ifndef _EN_H  
#define _EN_H  
#include "ende.h"

int getpos(unsigned char* test, int length);

int encrypts(unsigned char *plaintext, int plaintext_len, unsigned char *key,  
  unsigned char *iv, unsigned char *ciphertext) ;

#endif  