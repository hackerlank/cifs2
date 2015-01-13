/* 
 * File:   cmdstruct.h
 * Author: root
 *
 * Created on 2014年12月22日, 下午2:33
 */
#include <string>
#include <iostream>
#ifndef CMDSTRUCT_H
#define	CMDSTRUCT_H
#pragma pack(1)
typedef struct
{unsigned short SequnceNumber;} smb_pm_words_t;
typedef struct 
{
    unsigned char WordCount;
}rqpara72;//negotiate
typedef struct dw
{
    unsigned int dwLowDateTime;
    unsigned int dwHighDateTime;
    
}FILETIME;

typedef struct SMB_Parameter0x72r
{
    unsigned char WordCount;
    struct 
{
    unsigned short DialectIndex;
    unsigned char Securitymode;
    unsigned short MaxMpxCount;
    unsigned short MaxNumberVcs;
    unsigned int MaxBufferSize;
    unsigned int MaxRawSize;
    unsigned int SessionKey;
    unsigned int Capabilities;
    FILETIME SystemTime;
    short ServerTimeZone;
    unsigned char ChallengeLength;
}Words;
}rppara72;

typedef struct 
{
    unsigned char WordCount;
   struct
{
    unsigned char AndXCommand;
    unsigned char AndXReserved;
    unsigned short AndXoffset;
    unsigned short MaxBufferSize;
    unsigned short MaxMpxCount;
    unsigned short VcNumber;
    unsigned int SessionKey;
    unsigned short OEMPasswordLen;
    unsigned short UnicodePasswordLen;
    unsigned int Reserved;
    unsigned int Capabilities;
}Words;
}rqpara73;

typedef struct
{
    unsigned short ByteCount;
     struct
{
    unsigned char OEMPassword[24];
    unsigned char UnicodePassword[24];
    unsigned char AccountName[8];
    unsigned char PrimaryDomain[2];
    char NativeOS[72];
    char NativeLanMan[53];
}Bytes;
}rqdata73;


//response
typedef struct
{
    unsigned char WordCount;
   struct
{
    unsigned char AndXCommand;
    unsigned char AndXReserved;
    unsigned short AndXoffset;
    unsigned short Action;
}Words;
}rppara73;

typedef struct
{
    unsigned short ByteCount;
    struct
{
    char NativeOs[10];
    char NativeLanMan[44];
    char PrimaryDomain[17];
}Bytes;
}rpdata73;


//request of 0x75

typedef struct
{
    unsigned char wordcount;
    struct{
        unsigned char AndXCommand;
        unsigned char AndXReserved;
        unsigned short AndXOffset;
        unsigned short Flags;
        unsigned short PasswordLength;
    }words;
}rqpara75;

typedef struct
{
    unsigned short bytecount;
    struct
    {
        //unsigned char passwd[1];
        char path[41];
        char service[6];
    }bytes;
}rqdata75;

typedef struct
{
    unsigned char wordcount;
    struct
    {
        unsigned char  AndXCommand;
        unsigned char  AndXReserved;
        unsigned short AndXOffset;
        unsigned short OptionalSupport;
    }words;
}rppara75;

typedef struct
{
    unsigned short bytecount;
    struct
    {
        unsigned char s[13];
    }
    bytes;
}rpdata75;

//0x74
typedef struct
{
    unsigned char wordcount;
    struct
    {
        unsigned char AndXCommand;
        unsigned char AndXReserved;
        unsigned short AndXOffset;
    }words;
}rqpara74;

typedef struct
{
    unsigned short bytecount;
}rqdata74;

typedef rqpara74 rppara74;
typedef rqdata74 rpdata74;

//0x32
typedef struct
{
    unsigned char wordcount;
    struct
    {
        unsigned short TotalParameterCount;
        unsigned short TotalDataCount;
        unsigned short MaxParameterCount;
        unsigned short MaxDataCount;
        unsigned char  MaxSetupCount;
        unsigned char  Reserved1;
        unsigned short Flags;
        unsigned int  Timeout;
        unsigned short Reserved2;
        unsigned short ParameterCount;
        unsigned short ParameterOffset;
        unsigned short DataCount;
        unsigned short DataOffset;
        unsigned char  SetupCount;
        unsigned char  Reserved3;
        unsigned short Setup[1];
    }words;
}rqpara32;

typedef struct
{
    unsigned short bytecount;
    struct
    {
        unsigned char s[500];
    }bytes;
}rqdata32;

typedef struct
{
    unsigned char wordcount;
    struct
    {
        unsigned short TotalParameterCount;
        unsigned short TotalDataCount;
        unsigned short Reserved1;
        unsigned short ParameterCount;
        unsigned short ParameterOffset;
        unsigned short ParameterDisplacement;
        unsigned short DataCount;
        unsigned short DataOffset;
        unsigned short DataDisplacement;
        unsigned char SetupCount;
        unsigned char Reserved2;
    }words;
}rppara32;

typedef struct
{
    unsigned short bytecount;
    struct
    {
        char s[4000];
    }bytes;
}rpdata32;

typedef unsigned long LARGE_INTEGER;
typedef struct SMB_QUERY_FILE_STANDARD_INFO 
{
        LARGE_INTEGER AllocationSize;
        LARGE_INTEGER EndOfFile;
        unsigned int NumberOfLinks;
        unsigned char DeletePending;
        unsigned char Directory;
}SMB_QUERY_FILE_STANDARD_INFO;
//request 0xA2
typedef unsigned int SMB_EXT_FILE_ATTR;
typedef struct
{
    unsigned char wordcount;
    struct 
    {
        unsigned char AndXCommand;
        unsigned char AndXReserved;
        unsigned short AndXOffset;
        unsigned char  Reserved;
        unsigned short NameLength;
        unsigned int Flags;
        unsigned int RootDirectoryFID;
        unsigned int DesiredAccess;
        LARGE_INTEGER AllocationSize;
        SMB_EXT_FILE_ATTR ExtFileAttributes;
        unsigned int ShareAccess;
        unsigned int CreateDisposition;
        unsigned int CreateOptions;
        unsigned int ImpersonationLevel;
        unsigned char SecurityFlags;
    }words;
}rqparaA2;
typedef struct
{
    unsigned short bytecount;
    struct
    {
        char filename[200];
    }bytes;
}rqdataA2;
//response 0xA2
typedef unsigned short  SMB_NMPIPE_STATUS;
typedef struct
{
    unsigned char wordcount;
    struct
    {
        unsigned char AndXCommand; 
        unsigned char AndXReserved; 
        unsigned short AndXOffset; 
        unsigned char OpLockLevel; 
        unsigned short FID; 
        unsigned int CreateDisposition; 
        FILETIME CreateTime; 
        FILETIME LastAccessTime; 
        FILETIME LastWriteTime; 
        FILETIME LastChangeTime; 
        SMB_EXT_FILE_ATTR ExtFileAttributes; 
        LARGE_INTEGER AllocationSize; 
        LARGE_INTEGER EndOfFile; 
        unsigned short ResourceType; 
        SMB_NMPIPE_STATUS NMPipeStatus;
        unsigned char Directory;
    }words;
}rpparaA2;
typedef struct
{
    unsigned short bytecount;
}rpdataA2;
//request 0x04
typedef uint32_t UTIME;
typedef struct
{
    unsigned char wordcount;
    struct
    {
        unsigned short FID;
        UTIME LastTimeModified;
    }words;
}rqpara04;

typedef struct 
{
    unsigned short bytecount;
}rqdata04;
typedef struct
{
    unsigned char wordcount;
}rppara04;
typedef struct
{
    unsigned short bytecount;
}rpdata04;
//request SMB_COM_READ_ANDX (0x2E)
typedef struct
{
    unsigned char wordcount;//This field MUST be either 0x0A or 0x0C
    struct
    {
        unsigned char AndXCommand;
        unsigned char AndXReserved;
        unsigned short AndXOffset;
        unsigned short FID;
        unsigned int Offset;
        unsigned short MaxCountOfBytesToReturn;
        unsigned short MinCountOfBytesToReturn;
        unsigned int Timeout;
        unsigned short Remaining;
        //unsigned int OffsetHigh (optional);
        /*This field is optional. If WordCount is 0x0A this field is not included in the 
request. If WordCount is 0x0C this field represents the upper 32 bits of a 64-bit offset, measured 
in bytes, of where the read SHOULD start relative to the beginning of the file.*/
    }words;
}rqpara2E;
typedef struct
{
    unsigned short bytecount;
}rqdata2E;
//response SMB_COM_READ_ANDX (0x2E)
typedef struct
{
    unsigned char wordcount;
    struct
    {
        unsigned char AndXCommand;
        unsigned char AndXReserved;
        unsigned short AndXOffset;
        unsigned short Available;
        unsigned short DataCompactionMode;
        unsigned short Reserved1;
        unsigned short DataLength;
        unsigned short DataOffset;
        unsigned short Reserved2[5];
    }words;
}rppara2E;
typedef struct
{
    unsigned short ByteCount;
    struct
    {
        unsigned char s[4000];
    }bytes;
}rpdata2E;
//request 0x2F SMB_COM_WRITE_ANDX (0x2F)
typedef struct
{
    unsigned char wordcount;//This field MUST be either 0x0C or 0x0E
    struct 
    {
        unsigned char AndXCommand;
        unsigned char AndXReserved;
        unsigned short AndXOffset;
        unsigned short FID;
        unsigned int Offset;
        unsigned int Timeout;
        unsigned short WriteMode;
        unsigned short Remaining;
        unsigned short Reserved;
        unsigned short DataLength;
        unsigned short DataOffset;
        //unsigned int OffsetHigh ;
        /*OffsetHigh (4 bytes):  This field is optional. If WordCount is 0x0C, this field is not included in the 
request. If WordCount is 0x0E, this field represents the upper 32 bits of a 64-bit offset, measured 
in bytes, of where the write SHOULD start relative to the beginning of the file.
          */
    }words;
}rqpara2F;
typedef struct 
{
    unsigned short bytecount;
    struct
    {
        unsigned char Pad;
        unsigned char Data[100];
    }bytes;
}rqdata2F;
//response  0x2F SMB_COM_WRITE_ANDX (0x2F)
typedef struct
{
    unsigned char wordcount;//This field MUST be 0x06. The length in two-byte words of the remaining SMB_Parameters.
    struct
    {
        unsigned char AndXCommand;
        unsigned char AndXReserved;
        unsigned short AndXOffset;
        unsigned short Count;
        unsigned short Available;
        unsigned int Reserved;
    }words;
}rppara2F;
typedef struct
{
    unsigned short bytecount;
}rpdata2F;

//0x24
typedef struct
{
        unsigned char WordCount;
        struct
        {
        unsigned char AndXCommand;
        unsigned char AndXReserved;
        unsigned short AndXOffset;
        unsigned short FID;
        unsigned char TypeOfLock;
        unsigned char NewOpLockLevel;
        unsigned int Timeout;
        unsigned short NumberOfRequestedUnlocks;
        unsigned short NumberOfRequestedLocks;
        }words;
}rqpara24;
typedef struct
{
    unsigned short bytecount;
    struct
    {
        unsigned char s[20];
    }bytes;
}rqdata24;
//request 0x2B
typedef struct 
{
    unsigned char wordcount;
    struct
    {
        unsigned short EchoCount;
    }words;
}rqpara2B;
typedef struct 
{
    unsigned short ByteCount;
    struct
    {
        unsigned char Data[1];
    }shorts;
}rqdata2B;
//response 0x2B
typedef struct
{
    unsigned char wordcount;
    struct
    {
        unsigned short SequenceNumber;
    }words;
}rppara2B;
typedef struct
{
    unsigned short bytecount;
    struct
    {
        unsigned char Data[1];
    }bytes;
}rpdata2B;
typedef struct//0x07
{
    unsigned char wordcount;
    unsigned short searchattributes;
}rqpara07;
typedef struct//0x07
{
    unsigned short bytecount;
    unsigned char BufferFormate1;//0x04 ascill
    char oldfilename[1];
    unsigned char BufferFormate2;//0x04 ascill
    char newfilename[1];
}rqdata07;
#pragma pack()
#endif	/* CMDSTRUCT_H */

