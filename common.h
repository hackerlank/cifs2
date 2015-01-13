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
#include <string>
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
#include <map>
#include "cmdstruct.h"
//#include "transcation2_sub.h"
//#include "oplock.h"
#include "cifspdu.h"
#define CHK(eval) if(eval < 0){perror("eval"); exit(-1);}
#define CHK2(res, eval) if((res = eval) < 0){perror("eval"); exit(-1);}
#define CHK3(res,eval,error) if((res=eval)<0){perror(error); exit(-1);}
#define EPOLL_SIZE 100
#define EPOLL_RUNTIME_OUT -1
#define ZERO(x) bzero(&x,sizeof(x))
#pragma pack (1)
#define STATUS_OBJECT_NOT_FOUND 0xc0000034
typedef struct SMB_ERROR
{
    unsigned char errorclass;
    unsigned char reserved;
    unsigned short errorcode;
}smb_error_t;
typedef struct 
{
    unsigned char Protocol[4];
    unsigned char Command;
    unsigned int Status;
    unsigned char Flags;
    unsigned short Flags2;
    unsigned short PIDHigh;
    unsigned char SecurityFeatures[8];
    unsigned short Reserved;
    unsigned short Tid;
    unsigned short PIDLow;
    unsigned short UID;
    unsigned short MID;
    
}smbhead_t;
class SESSION
{
public:
    int _cfd;
    unsigned int _len;
    unsigned int _writelen;
    unsigned int _offset;
    unsigned int _writeoffset;
    unsigned short _dialect;
    char *_buf;
    char *_writebuf;
    char _path[200];
    unsigned int _sess_key;
    smbhead_t _head;
    smbhead_t _writehead;
    std::map<int,std::string > filelink;
    SESSION()
    {}
    SESSION(int cfd)
    :_cfd(cfd),
    _len(0),
    _writelen(0),
    _offset(0),
    _writeoffset(0),
    _dialect(0),
    _buf(NULL),
    _writebuf(NULL)
    {
        bzero(_path,200);
        strcpy(_path,"/home/lmx/test");
        bzero(&_head,sizeof(smbhead_t));
        bzero(&_writehead,sizeof(smbhead_t));
    }
    void* relloc_buf()
    {
        _offset = 0;
//        if(_buf!=NULL)
//        {
//            free(_buf);
//            _buf = NULL;
//        }
        _buf = (char*)realloc(_buf,this->_len);
        bzero(_buf,this->_len);
        return _buf;
    }
    void* relloc_writebuf()
    {
        _writeoffset = 0;
        _writebuf = (char*)realloc(_writebuf,this->_writelen+4);
        bzero(_writebuf,this->_writelen+4);
        return _writebuf;
    }
    void fill_head()
    {
        
        memcpy(&_head,_buf+_offset,32);
        _offset+=32;
    }
    char *getbuf()
    {
        return _buf+_offset;
    }
    ~SESSION()
    {
         free(_buf);
         free(_writebuf);
        _buf = NULL;
        _writebuf = NULL;
    }
};

#pragma pack()
#endif	/* COMMON_H */

