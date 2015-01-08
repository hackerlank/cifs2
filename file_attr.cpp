#include "file_attr.h"
#include <stdint.h>
unsigned long
  cifs_UnixTimeToNT(struct timespec t)
  {
          /* Convert to 100ns intervals and then add the NTFS time offset. */
          return (unsigned long) t.tv_sec * 10000000 + t.tv_nsec/100 + NTFS_TIME_OFFSET;
  }
struct timespec
  cifs_NTtimeToUnix(unsigned long ntutc)
  {
          struct timespec ts;
          // BB what about the timezone? BB 
  
          // Subtract the NTFS time offset, then convert to 1s intervals. 
          uint64_t t;
  
          t = ntutc - NTFS_TIME_OFFSET;
          //ts.tv_nsec = do_div(t, 10000000) * 100
          //ts.tv_sec = t;
          ts.tv_sec = t/10000000;
          ts.tv_nsec = (t%10000000)*100;
          return ts;
  }
unsigned int getfiletype(mode_t mode)
{
    unsigned int type;
         if (S_ISREG(mode))
                 type = UNIX_FILE;
         else if (S_ISDIR(mode))
                 type = UNIX_DIR;
         else if (S_ISLNK(mode))
                 type = UNIX_SYMLINK;
         else if (S_ISCHR(mode))
                 type = UNIX_CHARDEV;
         else if (S_ISBLK(mode))
                 type = UNIX_BLOCKDEV;
         else if (S_ISFIFO(mode))
                 type = UNIX_FIFO;
         else if (S_ISSOCK(mode))
                 type = UNIX_SOCKET;
         return type;
 }
