#include "../include/network.h"
#include "./diff1.cpp"
#include"../include/en.h"
#include"../include/de.h"

// CCCC  --L-- ????? ---R--- SSSSS

char rcvssl[MAX_LEN2];
char senssl[MAX_LEN1];
char rcvssr[MAX_LEN2];
char senssr[MAX_LEN1];
unsigned char key111[129];
unsigned char key222[129];

void changes(unsigned char* chars, int num){
    if (num == 0) return;
    num --;
    chars[num] = '\0';
    return;
}

int echo_rcvl(int sockfd) {
    int a = recv(sockfd, rcvssl, MAX_LEN, 0);
    return a;
}
void echo_senl(int sockfd, char* snd) {
    send(sockfd, snd, strlen(snd), 0);
}

void echo_senr(int sockfd, char* snd) {
    unsigned char buffs[MAX_LEN] = {'1','2','3','4','5','6','7','8','9'};
    // utoc(buffs);
    send(sockfd, snd, strlen(snd), 0);
}

int echo_rcvr(int sockfd) {
    int a = recv(sockfd, rcvssr, MAX_LEN, 0);
    return a;
}


int getpos(unsigned char* test, int length){
    int pos = 0;
    for(; pos < length + 1; pos ++){
        if (test[pos] == '\0'){
            test[pos] = '\1';
            return pos + 1;
        }
    }
    return 0;
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

// int getsize(unsigned char* inputs ){
//     int flags = 0;
//     while(inputs[flags]){
//         ++flags;
//     }
//     return flags + 1;
// }


int main(int argc, char** args) {
    // if (!args[1]){
    //     printf("Error Input!\n");
    //     exit(-1);
    // }
    int listen_socketfdl, socketfdl;
    struct sockaddr_in host_addrl;
    time_t time_now;

    int listen_portl = PORTSL; 
    listen_socketfdl = socket(AF_INET, SOCK_STREAM, 0);

    host_addrl.sin_family = AF_INET;
    host_addrl.sin_port = htons(listen_portl);
    host_addrl.sin_addr.s_addr = INADDR_ANY;
    ////////////////////////////////////////////////////////////////
    int socketfdr, nr, ar, errr;// 标记变量
    int decryptedtext_lenr, ciphertext_lenr;  //明文密文长度

    // 服务器种子，本机客户机种子
    uint64_t serverseedr;
    uint64_t selfr;

    // 明文 密文 向量 密钥
    unsigned char plaintextr[2048];
    unsigned char ciphertextr[2048]; 
    unsigned char ivr[2048];
    unsigned char* keyclir;

    // 密文字符串 接收载荷 接收长度的标记字符
    char ciphertext1r[2048], useless[2048];
    char flag_sr[10] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    char flagcr;
    ////////////////////////////////////////////////////////////////
    
    if(bind(listen_socketfdl, (const struct sockaddr *)&host_addrl, sizeof(host_addrl)) == -1) {
        printf("bind error\n");
        exit(1);
    }

    if(listen(listen_socketfdl, 10) == -1) {
        printf("listen error\n");
        exit(-1);
    }

    while(true) {
        // unsigned char* key111
        struct sockaddr_in target_addrr;
        int target_portr = PORTSR; 
        char target_ipr[16] = "127.0.0.1"; 

        if ((socketfdr = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("socket error\n");
            exit(1);
        }

        bzero(&target_addrr, sizeof(target_addrr));
        target_addrr.sin_family = AF_INET;
        target_addrr.sin_port = htons(target_portr);

        if ((nr = inet_pton(AF_INET, target_ipr, &target_addrr.sin_addr)) < 0) {
            printf("inet_pton error\n");
            exit(1);
        }

        if(connect(socketfdr, (const struct sockaddr *)&target_addrr, sizeof(struct sockaddr)) < 0) {
            printf("connect error\n");
            exit(1);
        }
        printf("=================== New Connect ==================\n");
        unsigned char ciphertextl[2048]; // 密文
        unsigned char iv[2048];  // 向量
        unsigned char decryptedtextl[2048]; //明文
        unsigned char* keyserl; //密钥

        char flagcl; //密文大小标记位

        // 定义向量
        char *ivs = "A7EB19BC32CDBA9CF"; 
        ctou(ivs, iv);
        

        // 标记，明文长度，密文长度
        int al, decryptedtext_lenl, ciphertext_lenl, errl;

        // 客户种子，自己种子
        uint64_t clientseedl, selfl;
        // char ----> uchar
        ret seds1, seds2;

        socketfdl = accept(listen_socketfdl, NULL, NULL);
        memset(rcvssl,0,sizeof(rcvssl));

        // 接收客户端的种子
        al = echo_rcvl(socketfdl);
        clientseedl = strtoull(rcvssl, NULL, 0);
        // 生成本服务器的种子
        seds1 =  test3();
        snprintf(senssl,sizeof(senssl),"%ju",seds1.b);

        // 计算密钥
        test4(clientseedl,seds1.a, key111);
        // printf("---------%s-----------",key111);
        // 消停一会
        sleep(1);

        // 种子发送给客户机
        echo_senl(socketfdl,senssl);
        memset(rcvssl,0,sizeof(rcvssl));

        // 模拟客户机给服务器发送种子
        seds2 = test1();
        // printf("%llu////\n",seds2.b);
        // 转换成字符串并发送
        snprintf(senssr,sizeof(senssr),"%ju",seds2.b);
        echo_senr(socketfdr,senssr);

        // 清空缓冲区，等待接收服务器的种子
        memset(rcvssr,0,sizeof(rcvssr));

        // 接受了服务器的种子
        ar = echo_rcvr(socketfdr);
        serverseedr = strtoull(rcvssr, NULL, 0);
        
        // 生成密钥
        test2(serverseedr, seds2.a, key222);// 密钥
        // printf("---------%s-----------",key111);
        printf("MY_TO_CLI-SECR:%llu\n",seds1.a);
        printf("MY_TO_CLI-SEED:%llu\n",seds1.b);
        printf("CL-SEED:%llu\n",clientseedl);
        printf("==================================================\n");
        printf("MY_TO_SER-SECR:%llu\n",seds2.a);
        printf("MY_TO_SER-SEED:%llu\n",seds2.b);
        printf("SER-SEED:%llu\n",serverseedr);
        printf("==================================================\n");
        printf("KEY-C>>>%s\n",key111);
        printf("KEY-S>>>%s\n",key222);
        printf("==================================================\n");

        al = echo_rcvl(socketfdl); // 接收密文
        ctou(rcvssl,ciphertextl); // 接收的字符串转换成无符号数字

        al = echo_rcvl(socketfdl); // 密文大小接收
        // flagcl = rcvssl[0]; 
        ciphertext_lenl = toint(rcvssl); //转换成整数
        // ciphertext_lenl = flagcl; 

        al = echo_rcvl(socketfdl); // 错误位接收
        errl = toint(rcvssl);  //转换成整数
        // flagcl = rcvssl[0]; 
        // errl = flagcl;
        changes(ciphertextl, errl);
        // printf("Ciphertext is %d bytes long:\n", ciphertext_lenl);
        
        // 解密
        const  char* t = reinterpret_cast<const  char *>( ciphertextl ); 
        BIO_dump_fp(stdout, t, ciphertext_lenl);  
        printf("=================== FROM CLIENT ==================\n");
        decryptedtext_lenl = decrypts(ciphertextl, ciphertext_lenl, key111, iv,  
        decryptedtextl); 
        decryptedtextl[decryptedtext_lenl] = '\0'; 

        // 打印明文
        // printf("==================================================\n");
        // printf("Decrypted text is:\n");  
        // printf("%s~\n", decryptedtextl); 
        // printf("==================================================\n");
        utoc(decryptedtextl,useless);

        ciphertext_lenr = encrypts(decryptedtextl, strlen(useless)+1, key222, iv,  ciphertextr);  
        const char* tr = reinterpret_cast<const  char *>( ciphertextr );
        printf("======================= TO SERVER ================\n");
        BIO_dump_fp(stdout, tr, ciphertext_lenr); 
        printf("==================================================\n");
        printf("Decrypted text is:\n");  
        printf("%s~\n", decryptedtextl); 
        printf("==================================================\n");
        // errr = 0;
        errr = getpos(ciphertextr, ciphertext_lenr);
        
        sleep(2);
        // 发送密文
        utoc(ciphertextr,ciphertext1r);
        echo_senr(socketfdr,ciphertext1r);
        sleep(0.5);

        // 发送密文长度信息
        // flagcr = ciphertext_lenr;
        // flag_sr[0] = flagcr;
        tostr(ciphertext_lenr, flag_sr);
        echo_senr(socketfdr,flag_sr);
        sleep(0.5);

        //发送错误位
        // flagcr = errr;
        // flag_sr[0] = flagcr;
        tostr(errr, flag_sr);
        echo_senr(socketfdr,flag_sr);

        close(socketfdl);
        close(socketfdr);
        printf("\n=================== Connect End ==================\n"); 
    }
    return 0;
}