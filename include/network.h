#ifndef NETWORK

#define NETWORK 1

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
#include <ctime>

#define MAX_LEN 102400
#define MAX_LEN1 2048
#define MAX_LEN2 2048

#define PORTS 6666
#define PORTSL 7653
#define PORTSR 9802



int my_recv(int sockfd, char *buf);
int recvline(int sockfd, char *buf, unsigned int maxlen);
int recvn(int sockfd, char *buf, unsigned int fixedlen);
int recvvl(int sockfd, char *buf, unsigned int buflen);
int sendvl(int sockfd, char *buf, unsigned int buflen);
unsigned char* ctou(char* inputs);
char* utoc(unsigned char* inputs);
#endif /* networklab.h */