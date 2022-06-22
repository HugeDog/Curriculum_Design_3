#include "../include/network.h"
#include "./diff1.cpp"
#include"../include/en.h"
#include"../include/de.h"

char rcvss[MAX_LEN2];
char senss[MAX_LEN1];

void changes(unsigned char* chars, int num){
    if (!num) return;
    num --;
    chars[num] = '\0';
    return;
}

int echo_rcv(int sockfd) {
    int a = recv(sockfd, rcvss, MAX_LEN, 0);
    return a;
}
void echo_sen(int sockfd, char* snd) {
    send(sockfd, snd, strlen(snd), 0);
}

unsigned char* ctou(char* inputs, unsigned char* outputs){
    int flags = 0;
    while(inputs[flags]){
        outputs[flags] = (unsigned char)inputs[flags];
        ++flags;
    }
    // printf("----%d----",flags);
    outputs[flags] = '\0';
    return outputs;
}
char* utoc(unsigned char* inputs ,char* outputs){
    int flags = 0;
    while(inputs[flags]){
        outputs[flags] = (char)inputs[flags];
        ++flags;
    }
    outputs[flags] = '\0';
    return outputs;
}

int main() {
    int listen_socketfd, socketfd;
    struct sockaddr_in host_addr;
    time_t time_now;
    ret seds;

    int listen_port = PORTS; 
    listen_socketfd = socket(AF_INET, SOCK_STREAM, 0);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(listen_port);
    host_addr.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(listen_socketfd, (const struct sockaddr *)&host_addr, sizeof(host_addr)) == -1) {
        printf("bind error\n");
        exit(1);
    }

    if(listen(listen_socketfd, 10) == -1) {
        printf("listen error\n");
        exit(-1);
    }

    while(true) {
        printf("============= New Connect ============\n");
        unsigned char ciphertext[2048]; // 密文
        unsigned char iv[2048];  // 向量
        unsigned char decryptedtext[2048]; //明文
        unsigned char keyser[129]; //密钥

        char flagc; //密文大小标记位

        // 定义向量
        char *ivs = "A7EB19BC32CDBA9CF"; 

        // 标记，明文长度，密文长度
        int a, decryptedtext_len, ciphertext_len, err;

        // 客户种子，自己种子
        uint64_t clientseed, self1;
        // char ----> uchar
        ctou(ivs, iv);

        socketfd = accept(listen_socketfd, NULL, NULL);
        memset(rcvss,0,sizeof(rcvss));

        // 接收客户端的种子
        a = echo_rcv(socketfd);
        clientseed = strtoull(rcvss, NULL, 0);

        // 生成本服务器的种子
        seds =  test3();
        // printf("%llu\n\n\n",self1);
        snprintf(senss,sizeof(senss),"%ju",seds.b);

        // 计算密钥
        test4(clientseed, seds.a, keyser);
        // 消停一会
        sleep(1);

        // 种子发送给客户机
        echo_sen(socketfd,senss);
        memset(rcvss,0,sizeof(rcvss));

        a = echo_rcv(socketfd); // 接收密文
        ctou(rcvss,ciphertext); // 接收的字符串转换成无符号数字

        a = echo_rcv(socketfd); // 密文大小接收
        ciphertext_len = toint(rcvss); //转换成整数

        a = echo_rcv(socketfd); // 错误位接收
        err = toint(rcvss); //转换成整数
        // err = flagc; 

        // 还原 00
        changes(ciphertext, err);
        printf("MY-SECR:%llu\n",seds.a);
        printf("MY-SEED:%llu\n",seds.b);
        printf("CL-SEED:%llu\n",clientseed);
        printf("KEY>>>>>%s\n",keyser);
        printf("Ciphertext is %d bytes long:\n", ciphertext_len);

        // 解密
        const  char* t = reinterpret_cast<const  char *>( ciphertext ); 
        BIO_dump_fp(stdout, t, ciphertext_len);  
        decryptedtext_len = decrypts(ciphertext, ciphertext_len, keyser, iv,  
        decryptedtext); 
        decryptedtext[decryptedtext_len] = '\0'; 

        // 打印明文
        printf("Decrypted text is:\n");  
        printf("%s~\n", decryptedtext); 

        // 清除残余数据
        EVP_cleanup();  
        ERR_free_strings();

        close(socketfd);
        printf("\n============= Connect End ============\n");
    }

    return 0;
}