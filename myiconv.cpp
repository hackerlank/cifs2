


#include "common.h"
#include "myiconv.h"
int Utf8ToUnicode(char * inbuff,char *outbuff, size_t *inlen, size_t *outlen)
{
    iconv_t cd;
    char ** pin = &inbuff;
    char ** pout = &outbuff; 
    
    
    
    cd = iconv_open("UNICODE", "UTF-8");
    if ((iconv_t)0 == cd)
    {
        perror("open");
        return -1;
    }
    
    int ret = -1;
    ret = iconv(cd, pin, inlen, pout, outlen);
    if (-1 == ret)
    {
        perror("iconv");
        return -1;
    }
    
    iconv_close(cd);
    return 0;
    
}

int UnicodeToUtf8(char * inbuff,char *outbuff, size_t *inlen, size_t *outlen)
{
    iconv_t cd;
    char ** pin = &inbuff;
    char ** pout = &outbuff; 
    
    
    
    cd = iconv_open("UTF-8","UNICODE");
    if ((iconv_t)0 == cd)
    {
        perror("open");
        return -1;
    }
    
    int ret = -1;
    ret = iconv(cd, pin, inlen, pout, outlen);
    if (-1 == ret)
    {
        perror("iconv");
        return -1;
    }
    
    iconv_close(cd);
    return 0;
    
}

