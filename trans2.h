/* 
 * File:   trans2.h
 * Author: root
 *
 * Created on 2014年12月25日, 上午9:36
 */
#include "common.h"
#include "cmdstruct.h"
#ifndef TRANS2_H
#define	TRANS2_H

int do_qfs_info(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int do_sfs_info(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int do_qpath_info(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int do_spath_info(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int do_gdfs_ref(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int do_sfile_info(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int do_find_first(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int trans2(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
#pragma pack(1)
typedef struct trans2_cmd
{
	unsigned char cmd;	//smb_0x32_trans2指令
	int (*trans2_handler)(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);//该指令所对应的执行函数
} trans2cmd_t;
static trans2cmd_t trans2cmds[] = {
	/* 访问控制命令 */
    {TRANS2_QUERY_FS_INFORMATION,do_qfs_info},
    {TRANS2_QUERY_PATH_INFORMATION,do_qpath_info},
    {TRANS2_SET_FS_INFORMATION,do_sfs_info},
    {TRANS2_GET_DFS_REFERRAL,do_gdfs_ref},
    {TRANS2_SET_PATH_INFORMATION,do_spath_info},
    {TRANS2_SET_FILE_INFORMATION,do_sfile_info},
    {TRANS2_FIND_FIRST,do_find_first}
};
typedef struct //query_fs_info setup = 3;
{
    unsigned short InformationLevel;
}qfsinfo_para_req;
typedef unsigned long LARGE_INTEGER;
typedef struct 
{
LARGE_INTEGER TotalAllocationUnits;
LARGE_INTEGER TotalFreeAllocationUnits;
unsigned int SectorsPerAllocationUnit;
unsigned int BytesPerSector;
}FILE_SYSTEM_SIZE_INFO;
typedef struct 
{
    unsigned int idFileSystem;
    unsigned int cSectorUnit;
    unsigned int cUnit;
    unsigned int  cUnitAvailable;
    unsigned short cbSector;
}FILE_INFO_ALLOCATION ;
typedef struct unix_info
{
	unsigned short major_version;
	unsigned short minor_version;
	unsigned long capability;
}UNIX_INFO; 

//TRANS2_QUERY_PATH_INFORMATION (0x0005)
struct Trans2_Parameters5
{
        unsigned short InformationLevel;
        unsigned int Reserved;
        unsigned char FileName[100];
};

typedef struct
{
        FILETIME CreationTime;
        FILETIME LastAccessTime;
        FILETIME LastWriteTime;
        FILETIME LastChangeTime;
        unsigned int ExtFileAttributes;
        unsigned int Reserved1;
        unsigned long AllocationSize;
        unsigned long EndOfFile;
        unsigned int NumberOfLinks;
        unsigned char DeletePending;
        unsigned char Directory;
        unsigned short Reserved2;
        unsigned int EaSize;
        unsigned int FileNameLength;
        unsigned char FileName[20];
}fileallinfo;
struct FILEINFO_UNIX_BASIC{
			uint64_t end_of_file;
			uint64_t num_bytes;
			uint64_t status_change_time;
			uint64_t access_time;
			uint64_t change_time;
			uint64_t uid;
			uint64_t gid;
			uint32_t file_type;
			uint64_t dev_major;
			uint64_t dev_minor;
			uint64_t unique_id;
			uint64_t permissions;
			uint64_t nlink;
		} ;
struct Trans2_Parameters1
{
     unsigned short SID;
     unsigned short SearchCount;
     unsigned short EndOfSearch;
     unsigned short EaErrorOffset;
     unsigned short LastNameOffset;
};  //for 0x32 setup = 1 
struct Trans2_Parameters6//0x0006 request
 {
     unsigned short Informationlevel;
     unsigned int Reserved;
     char name[1];
 };
 //setup = 8
 struct Trans2_Parameters8//0x0008 request
 {
     unsigned short FID;
     unsigned short InformationLevel;
     unsigned short Reserved;
 };
 struct Trans2_Parameters6r//0x0006 response
 {
     unsigned short EaErrorOffset;
 };
struct posix_ace { /* access control entry (ACE) */
        __u8  cifs_e_tag;
        __u8  cifs_e_perm;
        __le64 cifs_uid; /* or gid */
} __attribute__((packed));

struct posix_acl { /* access conrol list  (ACL) */
        __le16  version;
        __le16  access_entry_count;  /* access ACL - count of entries */
        __le16  default_entry_count; /* default ACL - count of entries */
};
#pragma pack()
#endif	/* TRANS2_H */

