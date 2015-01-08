#include "common.h"
#include <math.h> 
#include "smb_commands.h"
#include "file_attr.h"
#include "trans2.h"
#include "myiconv.h"
int dir_file_info(SESSION *sess,char *dirname)
{
        FILE_UNIX_INFO fileinfo;
        unsigned int lastoffset=0;
        unsigned char writebuf[2048];
        unsigned int rn = 0;
        int i=0;
        int writeoffset = 72;//4+32
        int unicode_len;
        struct Trans2_Parameters1 para2 = {0};
        rppara32 p32r = {0};
        rpdata32 d32r = {0};
        static int sid=0;
        sid++;
        struct stat buf;		//man lstat可以看到此结构
	char name[100];	
	DIR *dir;		//类似打开文件的fd描述符
	struct dirent *pdr;		//man readdir可以看到此结构
        int lflag = 1;
        int aflag = 1;
        //char w[100] = "/home/lmx/test";
	if(lstat(dirname,&buf)<0)		//获取文件/目录属性并赋值给buf，该函数和lstat一样，只是当w为链接时，指代他本身，并不存在文件
	{
		fprintf(stderr,"stat error:%s\n",strerror(errno));
		return -1;
	}
	if(S_ISDIR(buf.st_mode))	//判断是否为目录，是返回真
	{
		dir = opendir(dirname);		//打开目录
                while ((pdr = readdir(dir))!=NULL)	//读/遍历目录
		{
                    unicode_len = strlen(pdr->d_name)*2+2;
			if(aflag==0)	//如果不带a参数，越过以.开头的所有文件/目录
			{ 
				if(pdr->d_name[0]=='.')
					continue;
				memset(name,0,100);		
				strcpy(name,dirname);			//拷贝
				strcat(name,"/");		//追加
				strcat(name,pdr->d_name);
				//do_ls(name,pdr->d_name,lflag);
			}else		//有a参数显示所有
			{
				memset(name,0,100);
				strcpy(name,dirname);
				strcat(name,"/");
				strcat(name,pdr->d_name);
				//do_ls(name,pdr->d_name,lflag);
			}
                        	int n;
                        struct stat buf;
                        //char out[100];
                        struct passwd *pw;
                        struct group *gr;
                        struct tm *t;
                        lstat(name,&buf);
                        fileinfo.ResumeKey = 0;
                        fileinfo.basic.LastAccessTime = cifs_UnixTimeToNT(buf.st_atim);
                        fileinfo.basic.LastStatusChange = cifs_UnixTimeToNT(buf.st_ctim);
                        fileinfo.basic.LastModificationTime = cifs_UnixTimeToNT(buf.st_mtim);
                        fileinfo.basic.DevMajor = MAJOR(buf.st_rdev);
                        fileinfo.basic.DevMinor = MINOR(buf.st_rdev);
                        fileinfo.basic.EndOfFile = buf.st_size;
                        fileinfo.basic.Type = getfiletype(buf.st_mode);
                        fileinfo.basic.Gid = buf.st_gid;
                        fileinfo.basic.Nlinks = buf.st_nlink;
                        fileinfo.basic.NumOfBytes = buf.st_blksize;
                        fileinfo.basic.Permissions = (buf.st_mode&0x1FF);
                        fileinfo.basic.Uid = buf.st_uid;
                        fileinfo.basic.UniqueId = buf.st_ino;
                        fileinfo.NextEntryOffset = 108+unicode_len;
                        if(pdr->d_name[1]=='.')
                        {
                            fileinfo.basic.EndOfFile = 0;
                            fileinfo.basic.NumOfBytes = 0;
                                if(strcmp(pdr->d_name,"..")==0)
                                {
                                    unicode_len+=2;
                                    fileinfo.NextEntryOffset =108 + unicode_len;                                    
                                }                                    
                        }
                        char *writename = (char*)calloc(1,unicode_len+2);
                        size_t in = strlen(pdr->d_name)+1;
                        size_t out = unicode_len+2;
                        Utf8ToUnicode(pdr->d_name,writename, &in,&out);//name to unicode
                        memcpy(writebuf+writeoffset,&fileinfo,108);
                        writeoffset+=108;
                        memcpy(writebuf+writeoffset,writename+2,unicode_len);
                        writeoffset+=unicode_len;
                        p32r.words.TotalDataCount +=fileinfo.NextEntryOffset;
                        printf("%d\n",fileinfo.NextEntryOffset);
                        lastoffset = fileinfo.NextEntryOffset;
                        i++;
		}
                p32r.wordcount = 10;
                p32r.words.DataCount  = p32r.words.TotalDataCount;
                p32r.words.DataOffset = 68;
                p32r.words.ParameterOffset = 56;
                p32r.words.TotalParameterCount = 10;
                p32r.words.ParameterCount = 10;
                memcpy(writebuf+4+32,&p32r,sizeof(p32r));
                para2.EaErrorOffset = 0;
                para2.EndOfSearch = 1;
                para2.LastNameOffset = p32r.words.DataCount - lastoffset;
                para2.SID = sid++;
                para2.SearchCount = i;
                
                d32r.bytecount = p32r.words.DataCount + p32r.words.ParameterCount + 3;
		memcpy(writebuf+4+32+sizeof(p32r),&d32r,2);
                memcpy(writebuf+4+p32r.words.ParameterOffset,&para2,sizeof(para2));
                sess->_writelen=32+sizeof(p32r)+d32r.bytecount+2;
                rn = htonl(sess->_writelen);
                memcpy(writebuf,&rn,4);
                memcpy(writebuf+4,&(sess->_writehead),32);
                sess->relloc_writebuf();
                memcpy(sess->_writebuf,writebuf,sess->_writelen+4);
                closedir(dir);
	}else	//为文件则直接显示
	{
		//do_ls(w,w,lflag);
	}
        return i;
        //test ls end
}
int get_info_byname(char *w,struct FILEINFO_UNIX_BASIC *basic)
{
    struct stat buf;
    char name[100];	
    DIR *dir;		//类似打开文件的fd描述符
    struct dirent *pdr;		//man readdir可以看到此结构
    int lflag = 1;
    int aflag = 1;
    //char w[100] = "/home/lmx/test";
    if(lstat(w,&buf)<0)
    {
    	fprintf(stderr,"stat error:%s\n",strerror(errno));
    	return -1;
    }
    basic->access_time = cifs_UnixTimeToNT(buf.st_atim);
    basic->change_time = cifs_UnixTimeToNT(buf.st_ctim);
    basic->status_change_time = cifs_UnixTimeToNT(buf.st_mtim);
    basic->dev_major = MAJOR(buf.st_rdev);
    basic->dev_minor = MINOR(buf.st_rdev);
    basic->end_of_file = buf.st_size;
    basic->file_type = getfiletype(buf.st_mode);
    basic->gid = buf.st_gid;
    basic->nlink = buf.st_nlink;
    basic->num_bytes = buf.st_blksize;
    basic->permissions = (buf.st_mode&0x1FF);
    basic->uid = buf.st_uid;
    basic->unique_id = buf.st_ino;
    return 0;
}

