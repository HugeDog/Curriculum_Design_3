#ifndef _DE_H  
#define _DE_H  
#include "ende.h"

int decrypts(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,  
  unsigned char *iv, unsigned char *plaintext);  

#endif  