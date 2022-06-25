#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <openssl/bio.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <sys/socket.h>
#include <openssl/rand.h> 
#include <openssl/err.h>

#ifndef _ENDE_H  
#define _ENDE_H  

inline void handleErrors(void)  
{  
  ERR_print_errors_fp(stderr);  
  abort();  
} 
  
#endif  
