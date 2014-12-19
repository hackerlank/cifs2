/* 
 * File:   common.h
 * Author: root
 *
 * Created on 2014年12月19日, 上午9:38
 */

#ifndef COMMON_H
#define	COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <linux/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <iconv.h>
#include <sys/time.h>
#include <stdint.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <wchar.h>
#include <math.h>
//#include "transcation2_sub.h"
//#include "oplock.h"
#include "cifspdu.h"
#include "smb_commands.h"
#define CHK(eval) if(eval < 0){perror("eval"); exit(-1);}
#define CHK2(res, eval) if((res = eval) < 0){perror("eval"); exit(-1);}
#define CHK3(res,eval,error) if((res=eval)<0){perror(error); exit(-1);}
#define EPOLL_SIZE 100
#define EPOLL_RUNTIME_OUT -1
#define ZERO(x) bzero(&x,sizeof(x))
class SESSION
{
public:
    int _cfd;
    unsigned int _len;
    unsigned char *_buf;
    unsigned int _sess_key;
    SESSION(int cfd)
    :_cfd(cfd),
    _len(0),
    _buf(NULL),
    _sess_key(0)
    {
        
    }
    int relloc_buf(unsigned int len)
    {
        _len  = len;
        _buf = (unsigned char*)realloc(1,len);
    }
    ~SESSION()
    {
        free(_buf);
        _buf = NULL;
    }
};

typedef struct smbcmd
{
	const unsigned char cmd;	//smb指令
	void (*cmd_handler)(SESSION *sess);//该指令所对应的执行函数
} smbcmd_t;
#endif	/* COMMON_H */

