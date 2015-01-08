#include <vector>
#include "common.h"
#include "smb_commands.h"
#include "mem.h"
#include "trans2.h"
using namespace std;
void do_command_map(SESSION *sess)
{
	int i;
	int size = sizeof(smbcmds) / sizeof(smbcmds[0]); //数组大小
	for (i=0; i<size; ++i)
	{
		if (smbcmds[i].cmd==sess->_head.Command)
		{
			if (smbcmds[i].cmd_handler != NULL)
			{
				smbcmds[i].cmd_handler(sess);
			}
			else
			{
				//该命令没有实现
			}

			break;
		}
	}

	if (i == size)
	{
		//未识别的命令
	}
}
void do_close(SESSION *sess)
{
    int ret = 0;
    rqpara04 para04;
    rqdata04 data04;
    rppara04 para04r;
    rpdata04 data04r;
    memcpy(&para04,sess->getbuf(),sizeof(para04));
    close(para04.words.FID);
    memcpy(&data04,sess->getbuf()+sizeof(para04),sizeof(data04));
    
    sess->_writehead.MID = sess->_head.MID;
    sess->_writehead.Tid = sess->_head.Tid;
    sess->_writehead.Command = sess->_head.Command;
    sess->_writehead.PIDLow = getpid();
    char writebuf[39] = {0};
    unsigned int rh = htonl(35);
    memcpy(writebuf,&rh,4);
    memcpy(writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    CHK3(ret,write(sess->_cfd,writebuf,39),"write in do_close");
    printf("do_close FID:%d\n",para04.words.FID);
}
void do_negotiate(SESSION *sess)
{
    rqpara72 para72;
    unsigned short bytecount;
    memcpy(&para72,sess->getbuf(),sizeof(rqpara72));
    sess->_offset+=sizeof(rqpara72);
    memcpy(&bytecount,sess->getbuf(),2);
    sess->_offset+=2;
    unsigned short i=0;
    unsigned int len;
    char d[100]={0};
    char *tmp =(char*) sess->getbuf();
    while(len=strlen((char*)tmp))
    {
        
        if(strcmp(tmp,"\002NT LM 0.12")==0)
        {
            sess->_dialect = i;
            break;
        }
        i++;
        tmp+=len+1;
    }
    
    
    unsigned char writebuf[2048]={0};
    int ret;
    sess->_writehead.Protocol[0]=0xff;
    sess->_writehead.Protocol[1]='S';
    sess->_writehead.Protocol[2]='M';
    sess->_writehead.Protocol[3]='B';
    //bzero(&sess->_writehead.Status,sizeof(sess->_writehead));
    sess->_writehead.Command =0x72;
    sess->_writehead.Flags = 128;//0x88;
    sess->_writehead.Flags2 = 49155;//0xc843;
    sess->_writehead.PIDHigh = 0;
    sess->_writehead.Reserved = 0;
    sess->_writehead.Tid = 0;
    sess->_writehead.PIDLow = getpid();//smb_head.PIDLow;
    sess->_writehead.UID = 0;
    sess->_writehead.MID = sess->_head.MID;
    memcpy(writebuf+4,&(sess->_writehead),32);
    rppara72 para72r;
    bzero(&para72r,sizeof(para72r));
    para72r.WordCount = 17;
    
    para72r.Words.Capabilities = 8451069;//0x8080fcfd;//0x80000000 CAP_EXTENDED_SECURITY
    para72r.Words.ChallengeLength = 8;
    para72r.Words.MaxMpxCount = 50;
    para72r.Words.DialectIndex =sess->_dialect;
    para72r.Words.MaxBufferSize = 16644;
    para72r.Words.SystemTime.dwHighDateTime=30408667;
    para72r.Words.SystemTime.dwLowDateTime=4159977650;
    para72r.Words.MaxNumberVcs=1;
    para72r.Words.MaxRawSize=65536;
    para72r.Words.ServerTimeZone=-480;
    para72r.Words.SessionKey = 17207;
    para72r.Words.Securitymode =3;
    memcpy(writebuf+4+sizeof(smbhead_t),&para72r,sizeof(para72r));
    unsigned char DomainName[16]={0};
    unsigned char challenge[8] = {0};
    challenge[0]=140;
    challenge[1]=73;
    challenge[2] =209;
    challenge[3]=40;
    challenge[4]=253;
    challenge[5]=71;
    challenge[6]=219;
    challenge[7]=204;  
    DomainName[0]=0;  
    DomainName[1]='M';
    DomainName[2]=0;  
    DomainName[3]='Y';  
    DomainName[4]=0;  
    DomainName[5]='G';
    DomainName[6]=0;  
    DomainName[7]='R';  
    DomainName[8]=0;  
    DomainName[9]='O';
    DomainName[10]=0;  
    DomainName[11]='U';  
    DomainName[12]=0;  
    DomainName[13]='P';
    DomainName[14]=0;  
    DomainName[15]=0;  
    bytecount = 24;
    memcpy(writebuf+4+sizeof(smbhead_t)+sizeof(para72r),&bytecount,2);
    memcpy(writebuf+4+sizeof(smbhead_t)+sizeof(para72r)+2,challenge,8);
    memcpy(writebuf+4+sizeof(smbhead_t)+sizeof(para72r)+2+8,DomainName,16);
    unsigned int rh = htonl(93);
    memcpy(writebuf,&rh,4);
    ret = write(sess->_cfd,writebuf,97);
    unsigned char buf[1024]; 
    printf("sendResponse0x72,writebytes:%d\n",ret);
}
void do_sessionsetup(SESSION *sess)
{
    rqpara73 para73;
    unsigned short bytecount;
    memcpy(&para73,sess->getbuf(),sizeof(rqpara73));
    sess->_offset+=sizeof(rqpara73);
    memcpy(&bytecount,sess->getbuf(),2);
    sess->_offset+=2;
    unsigned char *oempassword = (unsigned char *)calloc(1,para73.Words.OEMPasswordLen+1);
    unsigned char *unicodepassword = (unsigned char *)calloc(1,para73.Words.UnicodePasswordLen+1);
    
    int ret;
    unsigned int len73r=htonl(112);
    bzero(&(sess->_writehead),sizeof(smbhead_t));
    rppara73 para73r;
    rpdata73 data73r;
    bzero(&para73r,sizeof(rppara73));
    bzero(&data73r,sizeof(rpdata73));
    sess->_writehead.Command =0x73;
    sess->_writehead.Flags = 128;
    sess->_writehead.Flags2 = 49155;
    sess->_writehead.MID = sess->_head.MID;
    sess->_writehead.PIDLow = getpid();
    sess->_writehead.Protocol[0] = 0xFF;
    sess->_writehead.Protocol[1] = 'S';
    sess->_writehead.Protocol[2] = 'M';
    sess->_writehead.Protocol[3] = 'B';
    sess->_writehead.UID = 100;
    
    para73r.WordCount = 3;
    para73r.Words.Action = 0;
    para73r.Words.AndXCommand = 0xFF;
    
    data73r.ByteCount = 71;
    memcpy(data73r.Bytes.NativeOs,"\000U\000n\000i\000x\000",sizeof("\000U\000n\000i\000x\000"));
    memcpy(data73r.Bytes.NativeLanMan,"\000S\000a\000m\000b\000a\000 \000\063\000.\000\066\000.\000\071\000-\000\061\000\066\000\071\000.\000e\000l\000\066\000_\000\065\000",sizeof("\000S\000a\000m\000b\000a\000 \000\063\000.\000\066\000.\000\071\000-\000\061\000\066\000\071\000.\000e\000l\000\066\000_\000\065\000"));
    memcpy(data73r.Bytes.PrimaryDomain,"\000M\000Y\000G\000R\000O\000U\000P\000",sizeof("\000M\000Y\000G\000R\000O\000U\000P\000"));
    
    char writebuf73[2048] = {0};
    memcpy(writebuf73,&len73r,sizeof(len73r));
    memcpy(writebuf73+4,&(sess->_writehead),sizeof(smbhead_t));
    memcpy(writebuf73+4+sizeof(smbhead_t),&para73r,sizeof(para73r));
    memcpy(writebuf73+4+sizeof(smbhead_t)+sizeof(para73r),&data73r,sizeof(data73r));
    
    int a=4+sizeof(smbhead_t)+sizeof(para73r)+sizeof(data73r);
    CHK3(ret,write(sess->_cfd,writebuf73,a),"sendResponse0x73");
    printf("sendResponse0x73,writebytes:%d\n",ret);
}
void do_treeconnect(SESSION *sess)
{
    int ret;
    rqpara75 para75;
    rqdata75 data75;
    rppara75 para75r;
    rpdata75 data75r;
    ZERO(para75);
    ZERO(data75);
    ZERO(para75r);
    ZERO(data75r);
    memcpy(&para75,sess->getbuf(),sizeof(para75));
    sess->_offset+=sizeof(para75);
    memcpy(&data75,sess->getbuf(),sizeof(data75));
    char writebuf[2048];
    if (!memchr(&data75,'$',sizeof(data75)))
    {
    sess->_writehead.Command = 0x75;
    sess->_writehead.Tid = 1;
    sess->_writehead.MID = sess->_head.MID;
    
    unsigned int rn = htonl(54);
    para75r.wordcount = 3;
    para75r.words.AndXCommand=0xff;
    para75r.words.OptionalSupport =1;
    data75r.bytecount=13;
    memcpy(&data75r.bytes.s,"A:\000N\000T\000F\000S\000",sizeof("A:\000N\000T\000F\000S\000"));
    bzero(writebuf,2048);
    memcpy(writebuf,&rn,4);
    memcpy(writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    memcpy(writebuf+4+sizeof(smbhead_t),&para75r,sizeof(para75r));
    memcpy(writebuf+4+sizeof(smbhead_t)+sizeof(para75r),&data75r,sizeof(data75r));
    CHK3(ret,write(sess->_cfd,writebuf,58),"sendResponse0x75");
    printf("sendResponse0x75,writebytes:%d\n",54);
    }
    else
    {
        unsigned int rn;
    rn = htonl(48);
    sess->_writehead.Command = 0x75;
    sess->_writehead.Tid = 2;
    sess->_writehead.MID = sess->_head.MID;
    para75r.wordcount = 3;
    para75r.words.AndXCommand=0xff;
    para75r.words.OptionalSupport =1;
    data75r.bytecount = 7;
    bzero(data75r.bytes.s,sizeof((data75r).bytes.s));
    memcpy(data75r.bytes.s,"IPC",sizeof("IPC"));
    bzero(writebuf,2048);
    memcpy(writebuf,&rn,4);
    memcpy(writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    memcpy(writebuf+4+sizeof(smbhead_t),&para75r,sizeof(para75r));
    memcpy(writebuf+4+sizeof(smbhead_t)+sizeof(para75r),&data75r,sizeof(data75r));
    CHK3(ret,write(sess->_cfd,writebuf,52),"sendResponse0x75_IPC");
    printf("sendResponse0x75_IPC,writebytes:%d\n",ret);
    }
}

void do_transcation2(SESSION *sess)
{
    int ret;
    rqpara32 para32;
    rqdata32 data32;
    rppara32 para32r;
    rpdata32 data32r;
    ZERO(para32);
    ZERO(data32);
    ZERO(para32r);
    ZERO(data32r);
    
    sess->_writehead.Command = 0x32;
    sess->_writehead.MID = sess->_head.MID;
    sess->_writehead.Flags = 128;
    sess->_writehead.Flags2 = 49155;
    sess->_writehead.PIDLow = getpid();
    sess->_writehead.Protocol[0] = 0xff;
    sess->_writehead.Protocol[1] = 'S';
    sess->_writehead.Protocol[2] = 'M';
    sess->_writehead.Protocol[3] = 'B';
    bzero(&(sess->_writehead.Status),sizeof(smb_error_t));
    sess->_writehead.Tid = sess->_head.Tid;
    sess->_writehead.UID = sess->_head.UID;
    unsigned char writebuf[2048];
    bzero(writebuf,2048);
    bzero(&para32r,sizeof(rppara32));
    bzero(&data32r,sizeof(rpdata32));
    trans2(sess,&para32,&data32,&para32r,&data32r);
/*
    unsigned int rn = htonl(sess->_writelen);
    memcpy(writebuf,&rn,4);
    memcpy(writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    memcpy(writebuf+4+sizeof(smbhead_t),&para32r,sizeof(para32r));
    memcpy(writebuf+4+sizeof(smbhead_t)+sizeof(para32r),&data32r,sizeof(data32r));
*/
     CHK3(ret,write(sess->_cfd,sess->_writebuf,sess->_writelen+4),"trans2");
    printf("do_trans2\n");
}
void do_NT_CREATE_ANDX(SESSION *sess)//0xA2
{
    rqparaA2 paraA2;
    rqdataA2 dataA2;
    rpparaA2 paraA2r;
    rpdataA2 dataA2r;
    unsigned int rh;
    int ret;
    bzero(&paraA2,sizeof(paraA2));
    bzero(&dataA2,sizeof(dataA2));
    memcpy(&paraA2,sess->getbuf(),sizeof(paraA2));
    memcpy(&dataA2,sess->getbuf()+sizeof(paraA2),sizeof(dataA2));
    size_t len = paraA2.words.NameLength;
    size_t len2 = paraA2.words.NameLength/2;
    char name[100] = {0};
    char longname[200] = {0};
    int fid = 0;//the file fid
    UnicodeToUtf8(dataA2.bytes.filename,name,&len,&len2);
    /*RootDirectoryFID (4 bytes):  If nonzero, this value is the File ID of an opened root directory, and 
the FileName field MUST be handled as relative to the directory specified by this RootDirectoryFID. If 
this value is 0x00000000, the FileName field MUST be handled as relative to the root of the share 
(the TID). The RootDirectoryFID MUST have been acquired in a previous message exchange.*/
    if(paraA2.words.RootDirectoryFID)
    {
        strcpy(longname,sess->filelink[paraA2.words.RootDirectoryFID].c_str());
        strcat(longname,name);
        map<int,string>::iterator it;
        for(it = sess->filelink.begin();it!=sess->filelink.end();it++)
        {
            if(0==strcmp(it->second.c_str(),longname))
            {
                fid = it->first;
                break;
            }
        }
        if(it==sess->filelink.end())
        {
            fid = open(longname,paraA2.words.DesiredAccess|O_CREAT);
            sess->filelink[fid] == string(longname);
        }
    }
    else
    {
        strcpy(longname,sess->_path);
        strcat(longname,name);
        map<int,string>::iterator it;
        for(it = sess->filelink.begin();it!=sess->filelink.end();it++)
        {
            if(0==strcmp(it->second.c_str(),longname))
            {
                fid = it->first;
                break;
            }
        }
        if(it==sess->filelink.end())
        {
            fid = open(longname,paraA2.words.DesiredAccess|O_CREAT);
            sess->filelink[fid] == string(longname);
        }
    }
    
    char writebuf[2048] = "\000\000\000g\377SMB\242\000\000\000\000\200\003\300\000\000\000\000\000\000\000\000\000\000\000\000\001\000\366\326d\000\b\000\042\377\000\000\000\001jF\003\000\000\000x\376rnC\r\320\001bBUpC\r\320\001x\376rnC\r\320\001x\376rnC\r\320\001 \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\063\377SMB$\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\001\000\377\377\000\000\377\377\b\377\000\000\000jF\002\000\000\000";
    memcpy(&(sess->_writehead),writebuf+4,sizeof(smbhead_t));
    sess->_writehead.MID = sess->_head.MID;
    sess->_writehead.PIDLow = getpid();
    memcpy(writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    memcpy(&rh,writebuf,4);
    sess->_writelen = ntohl(rh);
    memcpy(&paraA2r,writebuf+4+sizeof(smbhead_t),sizeof(paraA2r));
    paraA2r.words.FID = fid;
    memcpy(writebuf+4+sizeof(smbhead_t),&paraA2r,sizeof(paraA2r));
    memcpy(&dataA2r,writebuf+4+sizeof(smbhead_t)+sizeof(paraA2r),sizeof(dataA2r));
    CHK3(ret,write(sess->_cfd,writebuf,sess->_writelen+4),"sendResponse0xA2");
    printf("do_NT_CREATE_ANDX\n");
}
void do_write_andx(SESSION *sess)//0x2F
{
    rqpara2F para2F;
    rqdata2F data2F;
    rppara2F para2Fr;
    rpdata2F data2Fr;
    unsigned int rh;
    int ret = 0;
    bzero(&para2F,sizeof(para2F));
    bzero(&data2F,sizeof(data2F));
    memcpy(&para2F,sess->getbuf(),sizeof(para2F));
    unsigned int OffsetHigh=0;//optional
    if(para2F.wordcount==0x0E)
    {
        memcpy(&OffsetHigh,sess->getbuf()+sizeof(para2F),sizeof(OffsetHigh));
        //memcpy(data2F,readbuf+4+32+sizeof(*para2F)+4,para2F->words.DataLength+10);
        memcpy(data2F.bytes.Data,sess->_buf+para2F.words.DataOffset,sizeof(data2F));
    }
    else
        memcpy(data2F.bytes.Data,sess->_buf+para2F.words.DataOffset,sizeof(data2F));
    write(para2F.words.FID,data2F.bytes.Data,para2F.words.DataLength);
    printf("getRequest0x2F,readbytes:%d\n",sess->_writelen);
    
    char writebuf[100] = "\000\000\000/\377SMB/\000\000\000\000\200\003\300\000\000\000\000\000\000\000\000\000\000\000\000\001\000(8d\000\f\000\006\377\000\000\000\006\000\000\000\000\000\000\000\000\000\000\000\000\063\377SMB$\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\001\000\377\377\000\000\377\377\b\377\000\000\000\200!\002\000";
    memcpy(&(sess->_writehead),writebuf+4,sizeof(smbhead_t));
    sess->_writehead.MID = sess->_head.MID;
    sess->_writehead.PIDLow = getpid();
    memcpy(writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    memcpy(&rh,writebuf,4);
    sess->_writelen = ntohl(rh);
    memcpy(&para2Fr,writebuf+4+sizeof(smbhead_t),sizeof(para2Fr));
    memcpy(&data2Fr,writebuf+4+sizeof(smbhead_t)+sizeof(para2Fr),sizeof(data2Fr));
    CHK3(ret,write(sess->_cfd,writebuf,ntohl(rh)+4),"sendResponse0x2F");
    printf("sendResponse0x2F,writebytes:%d\n",ret);

}
void do_read_andx(SESSION *sess)//0x2E
{
    rqpara2E para2E;
    rqdata2E data2E;
    rppara2E para2Er;
    rpdata2E data2Er;
    bzero(&para2E,sizeof(para2E));
    bzero(&data2E,sizeof(data2E));
    memcpy(&para2E,sess->getbuf(),sizeof(para2E));
    unsigned int OffsetHigh=0;//optional
    if(para2E.wordcount==0x0C)
    {
        memcpy(&OffsetHigh,sess->getbuf()+sizeof(para2E),sizeof(OffsetHigh));
        memcpy(&data2E,sess->getbuf()+sizeof(para2E)+4,sizeof(data2E));
    }
    else
        memcpy(&data2E,sess->getbuf()+sizeof(para2E),sizeof(data2E));
    printf("getRequest0x2E,readbytes:%d\n",sess->_len);
    
    int ret;
    unsigned int rh;
    char writebuf[4096] = "\000\000\000A\377SMB.\000\000\000\000\200\003\300\000\000\000\000\000\000\000\000\000\000\000\000\001\000\334\067d\000\021\000\f\377\000\000\000\377\377\000\000\000\000\006\000;\000\000\000\000\000\000\000\000\000\006\000\006\000wollo\n\000\000";
    memcpy(&(sess->_writehead),writebuf+4,sizeof(smbhead_t));
    memcpy(&rh,writebuf,4);
    rh = ntohl(rh);
    sess->_writehead.MID = sess->_head.MID;
    sess->_writehead.PIDLow = getpid();
    memcpy(writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    memcpy(&para2Er,writebuf+4+32,sizeof(para2Er));
    memcpy(&data2Er,writebuf+4+32+sizeof(para2Er),sizeof(data2Er));
    CHK3(ret,read(para2E.words.FID,data2Er.bytes.s,4096),"read para2Er");
    para2Er.words.DataLength = ret;
    data2Er.ByteCount = ret;
    memcpy(writebuf+4+32,&para2Er,sizeof(para2Er));
    memcpy(writebuf+4+32+sizeof(para2Er),&data2Er,sizeof(data2Er));
    rh = 32+sizeof(para2Er)+2+data2Er.ByteCount;
    unsigned int rn = htonl(rh);
    memcpy(writebuf,&rn,4);
    CHK3(ret,write(sess->_cfd,writebuf,rh+4),"sendResponse0x2E");
    printf("sendResponse0x2E,writebytes:%d\n",ret);
}
void do_echo(SESSION *sess)//0x2b
{
    rqpara2B para2b;
    rqdata2B data2b;
    rppara2B para2br;
    rpdata2B data2br;
    bzero(&para2b,sizeof(para2b));
    bzero(&data2b,sizeof(data2b));
    memcpy(&para2b,sess->getbuf(),sizeof(para2b));
    memcpy(&data2b,sess->getbuf()+sizeof(para2b),2);
    unsigned char *data = (unsigned char*)calloc(1,data2b.ByteCount);
    memcpy(data,sess->getbuf()+sizeof(para2b)+2,data2b.ByteCount);
    
    int ret;
    unsigned int rh,rn;
    unsigned char writebuf[2048];
    sess->_writehead.Command = sess->_head.Command;
    sess->_writehead.Flags = 128;
    sess->_writehead.Flags2 = 16387;
    sess->_writehead.Tid = sess->_head.Tid;
    sess->_writehead.MID = sess->_head.MID;
    sess->_writehead.UID = sess->_head.UID;
    para2br.wordcount = 0x01;
    static unsigned short seqnumber = 1;
    para2br.words.SequenceNumber = seqnumber++;
    data2br.bytecount = data2b.ByteCount;
    rh = 32+sizeof(para2br)+2+data2br.bytecount;
    rn = htonl(rh);
    memcpy(writebuf,&rn,4);
    memcpy(writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    memcpy(writebuf+36,&para2br,sizeof(para2br));
    memcpy(writebuf+36+sizeof(para2br),&data2br,2);
    memcpy(writebuf+38+sizeof(para2br),data,data2br.bytecount);
    CHK3(ret,write(sess->_cfd,writebuf,rh+4),"sendResponse0x2E");
    printf("sendResponse0x2B,writebytes:%d\n",ret);
}