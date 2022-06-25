#include "en.h"

int encrypts(unsigned char *plaintext, int plaintext_len, unsigned char *key,  
  unsigned char *iv, unsigned char *ciphertext)  
{  
  EVP_CIPHER_CTX *ctx; 

  int len;
    
  int ciphertext_len;  
  
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();  
  
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))  
    handleErrors();  
  
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))  
    handleErrors();  
  ciphertext_len = len;  
  
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();  
  ciphertext_len += len;  
   
  EVP_CIPHER_CTX_free(ctx);  
  
  return ciphertext_len;  
}  