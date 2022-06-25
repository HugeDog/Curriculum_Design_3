#include "de.h"

int decrypts(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,  
  unsigned char *iv, unsigned char *plaintext)  
{  
  EVP_CIPHER_CTX *ctx;  
  
  int len;  
  
  int plaintext_len;  
  
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();  
  
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))  
    handleErrors();  

  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))  
    handleErrors();  
  plaintext_len = len;  

  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();  
  plaintext_len += len;  
  
  EVP_CIPHER_CTX_free(ctx);  
  
  return plaintext_len;  
}  