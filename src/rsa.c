#include <stdio.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

//using namespace std;

unsigned char* ctou(char* inputs, unsigned char* outputs){
    int flags = 0;
    while(inputs[flags]){
        outputs[flags] = (unsigned char)inputs[flags];
        ++flags;
    }
    printf("----%d----",flags);
    outputs[flags] = '\0';
    return outputs;
}

//公钥认证
int my_verify(const char *input, int input_len,  unsigned char *signret, unsigned int signlen, const char *pub_key_fn)
{
    RSA  *p_rsa = NULL;
    BIGNUM *signnum;
    unsigned char data[2][512+1];
    FILE *file = NULL;
    int nid;
    int ret = 0;

    signnum = BN_new();
    if((file = fopen(pub_key_fn, "rb")) == NULL)
    {
        ret = -1;
        return ret;
    }
    if((p_rsa = PEM_read_RSA_PUBKEY(file, NULL,NULL,NULL )) == NULL)
    {
        ret = -2;
        fclose(file);
        return ret;
    }
    fclose(file);
    
    //const char* t1 = reinterpret_cast<const char*>( signret );
    BN_hex2bn(&signnum, signret);

    BN_bn2bin(signnum, data[0]);

    nid = NID_md5;

    //const unsigned char* t2 = reinterpret_cast<const char*>( input );
    ret = RSA_verify(nid, input, input_len, data[0], signlen, p_rsa);
    if(ret != 1)  
    {
        ret = -3;
        printf("RSA签名验证有误!\n");
        RSA_free(p_rsa);
        BN_free(signnum);
        return ret;
    }
    printf("RSA签名验证成功!\n");
    RSA_free(p_rsa);
    BN_free(signnum);
}

//私钥签名
int my_sign(const char *input, int input_len, BIGNUM *signret, const char *pri_key_fn, char *datax)//,unsigned char *datax
{
    RSA  *p_rsa = NULL;
    FILE *file = NULL;
    unsigned char data[2][512+1];
    int nid;
    unsigned int signlen;
    int i = 0;
    int ret = 0;

    nid = NID_md5;
    file = fopen(pri_key_fn, "rb");
    if(!file)
    {
        ret = -1;
        printf("noopen\n");
        return ret;
    }
    
    OpenSSL_add_all_algorithms();
    OpenSSL_add_all_ciphers();
    ERR_load_crypto_strings();

    if((p_rsa = PEM_read_RSAPrivateKey(file, NULL,NULL,NULL )) == NULL)
    {
        ret = -2;
        fclose(file);
        printf("noread");
        return ret;
    }

    fclose(file);

    ret = RSA_sign(nid, input, input_len, data[0], &signlen, p_rsa);
    if(ret != 1)
    {
        ret = -3;
        printf("签名失败!\n");
        return ret;
    }

    RSA_free(p_rsa);

    //printf("signlen=[%d]\n", signlen*2+1);

    for(i=0; i<signlen; i++)
    {
         
        sprintf(data[1]+i*2, "%02x", data[0][i]);
    }

    data[1][2*i] = 0x00;

    strcpy(datax,data[1]);
    //printf("%s\n", data[1]);
    BN_hex2bn(&signret, data[1]);

    return 0;
}

int main(int argc, char**argv)
{
        BIGNUM *dst = BN_new();
        char src[2048+1];
        char dst_str[512+1];
        char datax[2048+1];
        int src_len;
        int ret;
       

        memset(src, 0x00, sizeof(src));
        memset(dst, 0x00, sizeof(dst));

        if(argv[1][0] == 's')
        {
                FILE *f;
                FILE *fp;
                fp=fopen("../pem/seedcli.txt","r");//读取
                FILE *fp2;
                fp2=fopen("../pem/signcli.txt","w");//写签名
                if(!fp)
                {
                  printf("文件打开失败\n");
                  return 0;
                }
                fseek( fp , 0 , SEEK_END );
                int file_size;
                file_size = ftell( fp );
                //printf( "%d" , file_size );
                char *tmp;
                fseek( fp , 0 , SEEK_SET);
                tmp =  (char *)malloc( file_size * sizeof( char ) );
                fread( tmp , file_size , sizeof(char) , fp);
                strcpy(src,tmp);
                //printf("%ssrcname\n",src);
                //strcpy(src, "aedewderdfercfrtvgfrtfgrtgfrtgvtrgtrvgtyebtybytbnybyuyubndrybrfgswdhyewhde");
                src_len = strlen(src);

                ret = my_sign(src, src_len, dst, argv[2], datax);
                fprintf(fp2,"%s",datax);
                fclose(fp2);
                //assert(ret == NULL);
                if(ret)
                {
                        fprintf(stderr, "%d\n",ret);
                        fprintf(stderr, "Error1\n");
                }
                fclose(fp);
        }
        else if (argv[1][0] == 'n')
        {
                FILE *f;
                FILE *fp;
                fp=fopen("../pem/seedser.txt","r");//读取
                FILE *fp2;
                fp2=fopen("../pem/signser.txt","w");//写签名
                if(!fp)
                {
                  printf("文件打开失败\n");
                  return 0;
                }
                fseek( fp , 0 , SEEK_END );
                int file_size;
                file_size = ftell( fp );
                //printf( "%d" , file_size );
                char *tmp;
                fseek( fp , 0 , SEEK_SET);
                tmp =  (char *)malloc( file_size * sizeof( char ) );
                fread( tmp , file_size , sizeof(char) , fp);
                strcpy(src,tmp);
                //printf("%ssrcname\n",src);
                //strcpy(src, "aedewderdfercfrtvgfrtfgrtgfrtgvtrgtrvgtyebtybytbnybyuyubndrybrfgswdhyewhde");
                src_len = strlen(src);

                ret = my_sign(src, src_len, dst, argv[2], datax);
                fprintf(fp2,"%s",datax);
                fclose(fp2);
                //assert(ret == NULL);
                if(ret)
                {
                        fprintf(stderr, "%d\n",ret);
                        fprintf(stderr, "Error1\n");
                }
                fclose(fp);
        }
        else
        {
                //printf()
                strcpy(src, argv[3]);
                strncpy(dst_str, argv[2], 512);
                src_len = strlen(src);

                ret = my_verify(src, src_len, dst_str, 256, argv[1]);
                // exit(20);
                return 99;
                if(ret)
                {
                        fprintf(stderr, "Error2\n");
                }
        }

        BN_free(dst);
      

        return 99;
}