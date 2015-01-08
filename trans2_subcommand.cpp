#include "trans2_subcommand.h"
#include "common.h"
#include "cmdstruct.h"
#include "file_attr.h"
#include "trans2.h"
#include "myiconv.h"
#include "readdir.h"
int trans2_sub3_0x001(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    sess->_writelen = 74;
    (*para32r).wordcount = 10;
    (*para32r).words.DataCount = 18;
    (*para32r).words.TotalDataCount = 18;
    (*para32r).words.ParameterOffset = 56;
    (*para32r).words.DataOffset = 56;
    (*data32r).bytecount = 19;    
    memcpy((*data32r).bytes.s,"\000\002\375\000\000\002\000\000\000\310+\316\002\314\345|\002\000\002\000\000",
            sizeof("\000\002\375\000\000\002\000\000\000\310+\316\002\314\345|\002\000\002\000\000"));
    FILE_INFO_ALLOCATION info_allocation;
    memcpy(&info_allocation,(*data32r).bytes.s+(*para32r).words.DataOffset-55,sizeof(FILE_INFO_ALLOCATION));
    printf("0x32 setup = 3 0x001\n");
}
int trans2_sub3_0x103(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    sess->_writelen = 80;
    (*para32r).wordcount = 10;
    (*para32r).words.DataCount = 24;
    (*para32r).words.TotalDataCount = 24;
    (*para32r).words.ParameterOffset = 56;
    (*para32r).words.DataOffset = 56;
    (*data32r).bytecount = 25;    
    memcpy((*data32r).bytes.s,"\000\310+\316\002\000\000\000\000\314\345|\002\000\000\000\000\002\000\000\000\000\002\000\000\000",
            sizeof("\000\310+\316\002\000\000\000\000\314\345|\002\000\000\000\000\002\000\000\000\000\002\000\000\000"));
    FILE_SYSTEM_SIZE_INFO fs_size_info;
    memcpy(&fs_size_info,(*data32r).bytes.s+(*para32r).words.DataOffset-55,sizeof(FILE_SYSTEM_SIZE_INFO));
    //test
    printf("0x32 setup = 3 0x103\n");
}
int trans2_sub3_0x104(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{ 
    sess->_writelen = 64;
    (*para32r).wordcount = 10;
    (*para32r).words.DataCount = 8;
    (*para32r).words.DataOffset = 56;
    (*para32r).words.TotalDataCount = 8;
    (*para32r).words.ParameterOffset = 56;
    
    (*data32r).bytecount = 9;
    memcpy((*data32r).bytes.s , "\000\007\000\000\000 \000\000\000\000\000\000\000\000\000\000\000\000\000",sizeof("\000\007\000\000\000 \000\000\000\000\000\000\000\000\000\000\000\000\000"));
    FILE_SYSTEM_DEVICE_INFO device_info;
    memcpy(&device_info,data32r->bytes.s,sizeof(FILE_SYSTEM_DEVICE_INFO));
    printf("0x32 setup = 3 0x104\n");
}
int trans2_sub3_0x105(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    sess->_writelen = 76;
    sess->_writehead.MID=sess->_head.MID;
    (*para32r).wordcount = 10;
    (*para32r).words.DataCount = 20;
    (*para32r).words.TotalDataCount = 20;
    (*para32r).words.DataOffset = 56;
    (*para32r).words.ParameterOffset = 56;
    (*data32r).bytecount = 21;    
    memcpy((*data32r).bytes.s,"\000/\000\001\000\377\000\000\000\b\000\000\000N\000T\000F\000S",sizeof("\000/\000\001\000\377\000\000\000\b\000\000\000N\000T\000F\000S"));
    FILE_SYSTEM_ATTRIBUTE_INFO attr_file;
    memcpy(&attr_file,(*data32r).bytes.s,sizeof(attr_file));
    unsigned char *fsname = (unsigned char *)calloc(1,attr_file.FileSystemNameLen+1);
    memcpy(fsname,data32r->bytes.s+12,attr_file.FileSystemNameLen);
    printf("0x32 setup = 3 0x105\n");
}
int trans2_sub3_0x200(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    sess->_writelen = 68;
    (*para32r).wordcount = 10;
    (*para32r).words.DataCount = 12;
    (*para32r).words.DataOffset = 56;
    (*para32r).words.DataOffset = 56;
    (*para32r).words.TotalDataCount = 12;    
    (*data32r).bytecount = 13;
    memcpy((*data32r).bytes.s, "\000\001\000\000\000{\001\000\000\000\000\000\000\000\000\000\000\000\000",sizeof("\000\001\000\000\000{\001\000\000\000\000\000\000\000\000\000\000\000\000"));
/*
    	 TRANS2 RAW_QFS_UNIX_INFO interface 
	struct {
		enum smb_fsinfo_level level;

		struct {
			uint16_t major_version;
			uint16_t minor_version;
			uint64_t capability;
		} out;
	} unix_info;
*/
    UNIX_INFO uinfo={1,2,3};
    memcpy(&uinfo,"\001\000\000\000{\001\000\006\008\001\000\000\000\000\000\000\000\000",12);
    printf("0x32 setup = 3 0x200\n");
}
int trans2_sub3_0x201(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    sess->_writelen = 112;
    (*para32r).wordcount = 10;
    (*para32r).words.DataCount = 56;
    (*para32r).words.TotalDataCount = 56;
    (*para32r).words.ParameterOffset = 56;
    (*para32r).words.DataOffset = 56;
    (*data32r).bytecount = 57;    
    memcpy((*data32r).bytes.s,"\000\000\020\000\000\000\020\000\000\362\212\263\000\000\000\000\000@X\250\000\000\000\000\000t9\237\000\000\000\000\000\000\240-\000\000\000\000\000\304\\,\000\000\000\000\000\225?\246\027\301\351\331\312\000\000\000\000",
            sizeof("\000\000\020\000\000\000\020\000\000\362\212\263\000\000\000\000\000@X\250\000\000\000\000\000t9\237\000\000\000\000\000\000\240-\000\000\000\000\000\304\\,\000\000\000\000\000\225?\246\027\301\351\331\312\000\000\000\000"));
    FILE_SYSTEM_POSIX_INFO fs_posix_info;
    memcpy(&fs_posix_info,(*data32r).bytes.s+(*para32r).words.DataOffset-55,sizeof(fs_posix_info));
    printf("0x32 setup = 3 0x201\n");
}
int trans2_sub4(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
        //sess->_writehead.Status.errorclass |=0x02;
        //sess->_writehead.Status.errorcode |=0xFFFF;
    sess->_writehead.Status = 0x0200ffff;
        sess->_writelen = 35;
        printf("0x32 setup = 4\n");
}
int trans2_sub5_0x107(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
   unsigned char writebuf[2048];
   bzero(writebuf,2048);
   memcpy(writebuf,"\000\000\000\206\377SMB2\000\000\000\000\200\003\300\000\000\000\000\000\000\000\000\000\000\000\000\001\000\252fd\000Q\000\n\002\000J\000\000\000\002\000\070\000\000\000J\000<\000\000\000\000\000O\000\000\000\000\000\000\202\017\236\002P\363\317\001\202\017\236\002P\363\317\001\224\271\240\272\241\371\317\001\224\271\240\272\241\371\317\001\020\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\001\000\000\000\000\001\000\000\000\000\000\000\002\000\000\000\\\000\000\000\000\000\000\000\000\000\000",
           sizeof("\000\000\000\206\377SMB2\000\000\000\000\200\003\300\000\000\000\000\000\000\000\000\000\000\000\000\001\000\252fd\000Q\000\n\002\000J\000\000\000\002\000\070\000\000\000J\000<\000\000\000\000\000O\000\000\000\000\000\000\202\017\236\002P\363\317\001\202\017\236\002P\363\317\001\224\271\240\272\241\371\317\001\224\271\240\272\241\371\317\001\020\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\001\000\000\000\000\001\000\000\000\000\000\000\002\000\000\000\\\000\000\000\000\000\000\000\000\000\000"));
   memcpy(&(sess->_writehead),writebuf+4,sizeof(smbhead_t));
   sess->_writehead.MID = sess->_head.MID;
   fileallinfo finfo;
   ZERO(finfo);
   unsigned int rh;
   memcpy(&rh,writebuf,4);
   sess->_writelen = ntohl(rh);
   memcpy(para32r,writebuf+4+sizeof(smbhead_t),sizeof(*para32r));
   memcpy(data32r,writebuf+4+sizeof(smbhead_t)+sizeof(*para32r),sizeof(*data32r));
   memcpy(&finfo,writebuf+4+(*para32r).words.DataOffset,sizeof(finfo));
   printf("0x32 setup = 5 0x107\n");
   return 1;
}
int trans2_sub5_0x200(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    struct Trans2_Parameters5 trans2_para5;
    ZERO(trans2_para5);
    memcpy(&trans2_para5,sess->_buf+(*para32).words.ParameterOffset,sizeof(trans2_para5)); 
    //unsigned char name[100] = {0};
    char name[100] = {0};
    char longname2[1024] = "/home/lmx/test";
    memcpy(longname2,"/home/lmx/test",sizeof("/home/lmx/test"));
    //wcscpy(name,trans2_para5.FileName);
    size_t len = 100;
    size_t len2 = 100;
    char Filename[1024] = {0};
    UnicodeToUtf8((char*)trans2_para5.FileName,name,&len,&len2);
    strcat(longname2,name);
    struct FILEINFO_UNIX_BASIC basic = {0};
    if(-1==get_info_byname(longname2,&basic))
    {
        sess->_writehead.Status = STATUS_OBJECT_NOT_FOUND;
        return 0;
    }
    int ret;
    //test
    sess->_writelen = 160;
    para32r->wordcount =10;
    para32r->words.DataCount = 100;
    para32r->words.DataDisplacement = 0;
    para32r->words.DataOffset = 60;
    para32r->words.ParameterDisplacement = 0;
    para32r->words.ParameterCount = 2;
    para32r->words.ParameterOffset = 56;
    para32r->words.SetupCount = 0;
    para32r->words.TotalDataCount = 100;
    para32r->words.TotalParameterCount = 2;
    
    data32r->bytecount = 105;
    memcpy(data32r->bytes.s+5,&basic,sizeof(basic));
    printf("0x32 setup = 5 0x200\n");
    return 0;
}
int trans2_sub6_0x209(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)//setup = 6 0x209
{
    struct Trans2_Parameters6 para6;
    ZERO(para6);
    char unicodename[100] = {0};
    char name[100] = {0};
    char longname[1024] = "/home/lmx/test";
    size_t len = 100;
    size_t len2 = 100;
    char Filename[1024] = {0};
    memcpy(unicodename,sess->_buf+para32->words.ParameterOffset+6,100);
    UnicodeToUtf8(unicodename,name,&len,&len2);
    strcat(longname,name);
    memcpy(&para6,sess->_buf+para32->words.ParameterOffset,sizeof(para6));
   
    OPEN_PSX_REQ data6;
    ZERO(data6);
    memcpy(&data6,sess->_buf+para32->words.DataOffset,para32->words.DataCount);


    unsigned int rh;
    char writebuf[1024] = "\000\000\000\254\377SMB2\000\000\000\000\200\003\300\000\000\000\000\000\000\000\000\000\000\000\000\001\000\237Yd\000\b\000\n\002\000p\000\000\000\002\000\070\000\000\000p\000<\000\000\000\000\000u\000\000\000\000\000\000\001\000BE\001\000\000\000\000\002\000\000\006\000\000\000\000\000\000\000\000\020\000\000\000\000\000\000\217\346#\252\211\017\320\001\022\324\200\274\211\017\320\001\217\346#\252\211\017\320\001\364\001\000\000\000\000\000\000\364\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\245\000$\000\000\000\000\000\377\001\000\000\000\000\000\000\001\000\000\000\000\000";
    memcpy(&rh,writebuf,4);
    sess->_writelen = ntohl(rh);
//    memcpy(smbw,writebuf+4,sizeof(smbhead_t));
//    smbw->MID = smbr->MID;
//    smbw->PIDLow = smbr->PIDLow;
/*
    struct Trans2_Parameters6r para; //para
    OPEN_PSX_RSP data;   //data
    ZERO(para);
    ZERO(data);

    memcpy(para32r,writebuf+4+sizeof(smbhead_t),sizeof(*para32r));
    memcpy(data32r,writebuf+4+sizeof(smbhead_t)+sizeof(*para32r),sizeof(*data32r));   
    memcpy(&para,writebuf+4+para32r->words.ParameterOffset,para32r->words.ParameterCount);
    memcpy(&data,writebuf+4+para32r->words.DataOffset,para32r->words.DataCount);
*/


    OPEN_PSX_RSP data;
    ZERO(data);
    bzero(para32r,sizeof(*para32r));
    bzero(data32r,sizeof(*data32r));
    struct FILEINFO_UNIX_BASIC basic = {0};
    umask((mode_t)data6.Permissions);
    int a=data6.Permissions&0x1FF;
    int fid = open(longname,O_RDWR|O_CREAT);
    chmod(longname,a);
    get_info_byname(longname,&basic);
    para32r->wordcount = 10;
    para32r->words.DataCount = 112;
    para32r->words.DataOffset = 60;
    para32r->words.ParameterCount = 2;
    para32r->words.ParameterOffset = 56;
    para32r->words.TotalDataCount = 112;
    para32r->words.TotalParameterCount = 2;
    
    data32r->bytecount = 117;
    data.CreateAction = 1;
    data.Fid = fid;
    data.OplockFlags = 1;
    memcpy((data32r->bytes.s)+5,&data,sizeof(data));
    memcpy((data32r->bytes.s)+5+sizeof(data),&basic,sizeof(basic));//bytecount 后面是u16_t的reserved
    printf("0x32 setup = 6 0x209\n"); //open
}
int trans2_sub6_0x20a(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)//setup = 6 0x20a
{
    int ret = 0;
    unsigned int rh;
    char unicodename[100] = {0};
    char name[100] = {0};
    char longname[1024] = "/home/lmx/test";
    size_t len = 100;
    size_t len2 = 100;
    unsigned char Filename[1024] = {0};
    memcpy(unicodename,sess->_buf+para32->words.ParameterOffset+6,100);
    UnicodeToUtf8(unicodename,name,&len,&len2);
    strcat(longname,name);
    struct stat buf;
    CHK3(ret,lstat(longname,&buf),"lstat in 0x20a ");
    remove(longname);
    char writebuf[1024] = "\000\000\000:\377SMB2\000\000\000\000\200\003\300\000\000\000\000\000\000\000\000\000\000\000\000\001\000\356\207d\000\022\000\n\002\000\000\000\000\000\002\000\070\000\000\000\000\000\000\000\000\000\000\000\003\000\000\000";
    memcpy(&rh,writebuf,4);
    sess->_writelen = ntohl(rh);
    memcpy(para32r,writebuf+4+sizeof(smbhead_t),sizeof(*para32r));
    memcpy(data32r,writebuf+4+sizeof(smbhead_t)+sizeof(*para32r),sizeof(*data32r));
    printf("0x32 setup = 6 0x20a\n");
}

int trans2_sub8_0x3fc(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)//setup = 8 0x200
{    
    char writebuf[1024] = "\000\000\000:\377SMB2\000\000\000\000\200\003\300\000\000\000\000\000\000\000\000\000\000\000\000\001\000\374\311d\000\t\000\n\002\000\000\000\000\000\002\000\070\000\000\000\000\000\000\000\000\000\000\000\003\000\000\000\000\000";
    unsigned int rh;
    memcpy(&rh,writebuf,4);
    sess->_writelen = ntohl(rh);
    memcpy(para32r,writebuf+4+sizeof(smbhead_t),sizeof(*para32r));
    memcpy(data32r,writebuf+4+sizeof(smbhead_t)+sizeof(*para32r),sizeof(*data32r));
    printf("0x32 setup = 8 0x3fc\n");
}
int trans2_sub8_0x200(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)//setup = 8 0x209
{   
    unsigned int rh;
    struct FILEINFO_UNIX_BASIC basic;
    ZERO(basic);
    struct Trans2_Parameters8 transpara;
    ZERO(transpara);
    memcpy(&transpara,sess->_buf+para32->words.ParameterOffset,para32->words.DataCount);
    memcpy(&basic,sess->_buf+para32->words.DataOffset,sizeof(basic));
    char writebuf[1024] = "\000\000\000:\377SMB2\000\000\000\000\200\003\300\000\000\000\000\000\000\000\000\000\000\000\000\001\000vzd\000\v\000\n\002\000\000\000\000\000\002\000\070\000\000\000\000\000\000\000\000\000\000\000\003\000";
    memcpy(&rh,writebuf,4);
    sess->_writelen = ntohl(rh);
    memcpy(para32r,writebuf+4+sizeof(smbhead_t),sizeof(*para32r));
    memcpy(data32r,writebuf+4+sizeof(smbhead_t)+sizeof(*para32r),sizeof(*data32r));
    printf("0x32 setup = 8 0x200\n");
}