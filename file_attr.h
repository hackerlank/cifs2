/* 
 * File:   file_attr.h
 * Author: root
 *
 * Created on 2014年12月11日, 上午11:12
 */

#ifndef FILE_ATTR_H
#define	FILE_ATTR_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <time.h>
#include <sys/stat.h>
#include <linux/kdev_t.h>
#define UNIX_FILE      0
#define UNIX_DIR       1
#define UNIX_SYMLINK   2
#define UNIX_CHARDEV   3
#define UNIX_BLOCKDEV  4
#define UNIX_FIFO      5
#define UNIX_SOCKET    6

#define NTFS_TIME_OFFSET ((unsigned long)(369*365 + 89) * 24 * 3600 * 10000000)
unsigned long
  cifs_UnixTimeToNT(struct timespec t);
struct timespec
  cifs_NTtimeToUnix(unsigned long ntutc);
unsigned int getfiletype(mode_t mode);
#ifdef	__cplusplus
}
#endif

#endif	/* NT_UNIX_TIME_H */

