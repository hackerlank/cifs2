/* 
 * File:   readdir.h
 * Author: root
 *
 * Created on 2014年12月26日, 下午2:15
 */
#include "common.h"
#include "cifspdu.h"
#ifndef READDIR_H
#define	READDIR_H
int dir_file_info(SESSION *sess,char *dirname);
int get_info_byname(char *w,struct FILEINFO_UNIX_BASIC *basic);

#endif	/* READDIR_H */

