#include "trans2.h"
#include "common.h"
#include "cmdstruct.h"
#include "smb_commands.h"
#include "trans2_subcommand.h"
#include "readdir.h"
#include "myiconv.h"
int do_qfs_info(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    qfsinfo_para_req trans2_para;
    memcpy(&trans2_para,sess->_buf+para32->words.ParameterOffset,sizeof(qfsinfo_para_req));
    switch(trans2_para.InformationLevel)
    {
        case SMB_INFO_ALLOCATION:
            trans2_sub3_0x001(sess,para32,data32,para32r,data32r);
            break;
        case SMB_QUERY_FS_DEVICE_INFO://0x104
            trans2_sub3_0x104(sess,para32,data32,para32r,data32r);
            break;
        case SMB_QUERY_FS_ATTRIBUTE_INFO://0x105
            trans2_sub3_0x105(sess,para32,data32,para32r,data32r);
            break;
        case SMB_QUERY_FS_SIZE_INFO://0x103
            trans2_sub3_0x103(sess,para32,data32,para32r,data32r);
            break;
        case SMB_QUERY_CIFS_UNIX_INFO://0x200
            trans2_sub3_0x200(sess,para32,data32,para32r,data32r);
            break;
        case SMB_QUERY_POSIX_FS_INFO://0x201
            trans2_sub3_0x201(sess,para32,data32,para32r,data32r);
            break;
        default:
            break;
    }
    unsigned int rn = htonl(sess->_writelen);
    sess->relloc_writebuf();
    memcpy(sess->_writebuf,&rn,4);
    memcpy(sess->_writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    memcpy(sess->_writebuf+4+sizeof(smbhead_t),para32r,sizeof(*para32r));
    memcpy(sess->_writebuf+4+sizeof(smbhead_t)+sizeof(*para32r),data32r,2+data32r->bytecount);
    printf("do_qfs_info\n");
}
int do_sfs_info(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
//    sess->_writehead.Status.errorclass |=0x02;
//    sess->_writehead.Status.errorcode |=0xFFFF;
    sess->_writehead.Status = 0x0200ffff;
    sess->_writelen = 35;
    unsigned int rn = htonl(sess->_writelen);
    sess->relloc_writebuf();
    memcpy(sess->_writebuf,&rn,4);
    memcpy(sess->_writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    //memcpy(sess->_writebuf+4+sizeof(smbhead_t),para32r,sizeof(*para32r));
    //memcpy(sess->_writebuf+4+sizeof(smbhead_t)+sizeof(*para32r),data32r,2+data32r->bytecount);
    printf("do_sfs_info\n");
}
int do_gdfs_ref(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    char writebuf[1024];
    memcpy(writebuf,"\000\000\000#\377SMB2%\002\000\300\200\003\300\000\000\000\000\000\000\000\000\000\000\000\000\002\000\331Xd\000\034\000",
            sizeof("\000\000\000#\377SMB2%\002\000\300\200\003\300\000\000\000\000\000\000\000\000\000\000\000\000\002\000\331Xd\000\034\000"));
    smbhead_t smbtmp;
    sess->_writelen = 35;
    memcpy(&smbtmp,writebuf+4,sizeof(smbhead_t));
    sess->_writehead.Status = smbtmp.Status;
    sess->_writehead.Tid = 2;
    //CHK3(ret,write(cfd,writebuf,39),"sendResponse0x32");
    unsigned int rn = htonl(sess->_writelen);
    sess->relloc_writebuf();
    memcpy(sess->_writebuf,&rn,4);
    memcpy(sess->_writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    memcpy(sess->_writebuf+4+sizeof(smbhead_t),para32r,sizeof(*para32r));
    memcpy(sess->_writebuf+4+sizeof(smbhead_t)+sizeof(*para32r),data32r,2+data32r->bytecount);
    printf("do_gdfs_ref\n");
    return 1;
}
int do_qpath_info(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    struct Trans2_Parameters5 trans2_para5;
    ZERO(trans2_para5);
    memcpy(&trans2_para5,sess->_buf+(*para32).words.ParameterOffset,sizeof(trans2_para5));
    switch(trans2_para5.InformationLevel)
    {
        case SMB_QUERY_FILE_ALL_INFO:
            trans2_sub5_0x107(sess,para32,data32,para32r,data32r);
            break;
        case SMB_QUERY_FILE_UNIX_BASIC:
            trans2_sub5_0x200(sess,para32,data32,para32r,data32r);
            break;
        default:
            break;
    }
    unsigned int rn = htonl(sess->_writelen);
    sess->relloc_writebuf();
    memcpy(sess->_writebuf,&rn,4);
    memcpy(sess->_writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    if(para32r->wordcount>0)
        memcpy(sess->_writebuf+4+sizeof(smbhead_t),para32r,sizeof(*para32r));
    if(data32r->bytecount>0)
        memcpy(sess->_writebuf+4+sizeof(smbhead_t)+sizeof(*para32r),data32r,2+data32r->bytecount);
    printf("do_qpath_info\n");
}
int do_spath_info(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    struct Trans2_Parameters6 para6;
    ZERO(para6);
    memcpy(&para6,sess->_buf+para32->words.ParameterOffset,sizeof(para6));
    switch(para6.Informationlevel)
    {
        case SMB_POSIX_OPEN:
            trans2_sub6_0x209(sess,para32,data32,para32r,data32r);
            break;
        case SMB_POSIX_UNLINK:
            trans2_sub6_0x20a(sess,para32,data32,para32r,data32r);
            //oplock_breaking(cfd,40);
            break;
        default:
            break;
    }
    unsigned int rn = htonl(sess->_writelen);
    sess->relloc_writebuf();
    memcpy(sess->_writebuf,&rn,4);
    memcpy(sess->_writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    memcpy(sess->_writebuf+4+sizeof(smbhead_t),para32r,sizeof(*para32r));
    memcpy(sess->_writebuf+4+sizeof(smbhead_t)+sizeof(*para32r),data32r,2+data32r->bytecount);
    printf("do_spath_info\n");
}
int do_sfile_info(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    struct Trans2_Parameters8 para8;
    ZERO(para8);
    memcpy(&para8,sess->_buf+para32->words.ParameterOffset,sizeof(para8));
    switch(para8.InformationLevel)
    {
        case SMB_SET_FILE_UNIX_BASIC://0x200
        {
            trans2_sub8_0x200(sess,para32,data32,para32r,data32r);
        }
            break;
        case SMB_SET_FILE_END_OF_FILE_INFO2://0x3fc
        {
            struct file_end_of_file_info fend;
            ZERO(fend);
            memcpy(&fend,sess->_buf+para32->words.DataOffset,sizeof(fend));
            trans2_sub8_0x3fc(sess,para32,data32,para32r,data32r);
        }
            break;
            
        default:
            break;
            
    }
    unsigned int rn = htonl(sess->_writelen);
    sess->relloc_writebuf();
    memcpy(sess->_writebuf,&rn,4);
    memcpy(sess->_writebuf+4,&(sess->_writehead),sizeof(smbhead_t));
    memcpy(sess->_writebuf+4+sizeof(smbhead_t),para32r,sizeof(*para32r));
    memcpy(sess->_writebuf+4+sizeof(smbhead_t)+sizeof(*para32r),data32r,2+data32r->bytecount);
    printf("do_sfile_info\n");
}
int do_find_first(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    int ret;
    size_t inlen=100 ,outlen = 100;
    char longname[1024] = {0};
    strcpy(longname,sess->_path);
    char unicodename[200] = {0};
    char name[100] = {0};
    memcpy(unicodename,sess->_buf+para32->words.ParameterOffset+12,100);
    UnicodeToUtf8(unicodename,name,&inlen,&outlen);
    strcat(longname,name);
    longname[strlen(longname)-1] = 0;
    dir_file_info(sess,longname);   
    return 1;
}
int trans2(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r)
{
    memcpy(para32,sess->getbuf(),sizeof(*para32));
    int i;
    int size = sizeof(trans2cmds) / sizeof(trans2cmds[0]); //数组大小
    for (i=0; i<size; ++i)
    {
            if (trans2cmds[i].cmd==para32->words.Setup[0])
            {
                    if (trans2cmds[i].trans2_handler != NULL)
                    {
                            trans2cmds[i].trans2_handler(sess,para32,data32,para32r,data32r);
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
