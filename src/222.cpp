#include "../include/network.h"
#include "./diff1.cpp"
#include"../include/en.h"
#include"../include/de.h"

char rcvss[MAX_LEN2];
char senss[MAX_LEN1];

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

void echo_sen(int sockfd, char* snd) {
    unsigned char buffs[MAX_LEN] = {'1','2','3','4','5','6','7','8','9'};
    // utoc(buffs);
    send(sockfd, snd, strlen(snd) + 1, 0);
}

int echo_rcv(int sockfd) {
    int a = recv(sockfd, rcvss, MAX_LEN, 0);
    // ctou(rcvss);
    // printf("\n");
    // printf("%s",outputs);
    return a;
}

char* utoc1(unsigned char* inputs ,char* outputs){
    int flags = 0;
    while(inputs[flags]){
        outputs[flags] = (char)inputs[flags];
        ++flags;
    }
    outputs[flags] = '\0';
    return outputs;
}

unsigned char* ctou1(char* inputs, unsigned char* outputs){
    int flags = 0;
    while(inputs[flags]){
        outputs[flags] = (unsigned char)inputs[flags];
        ++flags;
    }
    // printf("----%d----",flags);
    outputs[flags] = '\0';
    return outputs;
}


int main(int argc, char **argv) {
    int socketfd, n, a, err;// 标记变量
    int decryptedtext_len, ciphertext_len;  //明文密文长度
    FILE *files;
    files = fopen("./seedcli.txt","w");//my-seed保存

    // 服务器种子，本机客户机种子
    uint64_t serverseed;
    uint64_t self1;
    uint64_t sscd[2];
    ret seds;

    // 明文 密文 向量 密钥
    unsigned char plaintext[2048];
    unsigned char ciphertext[2048]; 
    unsigned char iv[2048];
    unsigned char keycli[129];

    // 密文字符串 接收载荷 接收长度的标记字符
    char ciphertext1[2048];
    char flag_s [10] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    char flagc;
    // 设置向量，并转换成uc格式
    char *ivs = "A7EB19BC32CDBA9CF"; 
    ctou1(ivs, iv);

    struct sockaddr_in target_addr;
    int target_port = PORTS; 
    char target_ip[16] = "127.0.0.1";      

    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket error\n");
        exit(1);
    }

    bzero(&target_addr, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(target_port);

    if ((n = inet_pton(AF_INET, target_ip, &target_addr.sin_addr)) < 0) {
        printf("inet_pton error\n");
        exit(1);
    }

    if(connect(socketfd, (const struct sockaddr *)&target_addr, sizeof(struct sockaddr)) < 0) {
        printf("connect error\n");
        exit(1);
    }

    // 生成客户机自己的种
    
    seds =  test1();
    // printf("%llu\n\n\n",self1);
    // 转换成字符串并发送
    snprintf(senss,sizeof(senss),"%ju",seds.b);
    fprintf(files,"%s",senss);
    //system("./rsa1 s clientpri.pem");
    echo_sen(socketfd,senss);

    // 清空缓冲区，等待接收服务器的种子
    memset(rcvss,0,sizeof(rcvss));
    sleep(1);

    // 接受了服务器的种子
    a = echo_rcv(socketfd);
    serverseed = strtoull(rcvss, NULL, 0);
    
    // 生成密钥
    test2(serverseed,seds.a, keycli);// 密钥

    ///////明文 明文 明文 明文 明文 明文 明文 明文 明文 明文 明文 明文 明文//////////////////////////////////////
    char *plaintext1 = "What are you barking at?"; 
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // 明文转换成uc
    ctou1(plaintext1, plaintext);

    // 加密！！！！ 
    ciphertext_len = encrypts(plaintext, strlen(plaintext1), keycli, iv,  
    ciphertext);  
    const char* t = reinterpret_cast<const  char *>( ciphertext ); 

    // 打印
    printf("MY-SECR:%llu\n",seds.a);
    printf("MY-SEED:%llu\n",seds.b);
    printf("SE-SEED:%llu\n",serverseed);
    printf("KEY>>>>>%s\n",keycli);
    printf("Plaintext is:\n%s~\n", plaintext); 
    printf("Ciphertext is %d bytes long:\n", ciphertext_len); 
    BIO_dump_fp(stdout, t, ciphertext_len);  
    
    // 监测 0 并修改为 1
    err = getpos(ciphertext, ciphertext_len);
    // err = 0; // 没必要，不触发

    // 发送密文
    utoc1(ciphertext,ciphertext1);
    echo_sen(socketfd,ciphertext1);
    sleep(0.5);

    // 发送密文长度信息
    // flagc = ciphertext_len;
    // flag_s[0] = flagc;
    tostr(ciphertext_len, flag_s);
    echo_sen(socketfd,flag_s);
    sleep(0.5);

    //发送错误位
    tostr(err, flag_s);
    echo_sen(socketfd,flag_s);
    
    // USELESS!!!!
    EVP_cleanup();  
    ERR_free_strings();

    close(socketfd);   
    return 0;
}