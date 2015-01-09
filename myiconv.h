/* 
 * File:   myiconv.h
 * Author: root
 *
 * Created on 2014年10月28日, 下午1:35
 */
#ifndef MYICONV_H
#define	MYICONV_H
int Utf8ToUnicode(char * inbuff,char *outbuff, size_t *inlen, size_t *outlen);
int UnicodeToUtf8(char * inbuff,char *outbuff, size_t *inlen, size_t *outlen);
int itostr(char *value,char *str);
#endif	/* MYICONV_H */

