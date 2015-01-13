/* 
 * File:   trans2_subcommand.h
 * Author: root
 *
 * Created on 2014年12月25日, 下午1:18
 */
#include "common.h"
#include "cmdstruct.h"
#ifndef TRANS2_SUBCOMMAND_H
#define	TRANS2_SUBCOMMAND_H
int trans2_sub3_0x001(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int trans2_sub3_0x103(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int trans2_sub3_0x104(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int trans2_sub3_0x105(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int trans2_sub3_0x200(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int trans2_sub3_0x201(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int trans2_sub5_0x107(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int trans2_sub5_0x200(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);
int trans2_sub5_0x204(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);//SMB_QUERY_POSIX_ACL
int trans2_sub6_0x209(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);//setup = 6 0x209
int trans2_sub6_0x20a(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);//setup = 6 0x20a
int trans2_sub8_0x3fc(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);//setup = 8 0x200
int trans2_sub8_0x200(SESSION *sess,rqpara32 *para32,rqdata32 *data32,rppara32 *para32r,rpdata32 *data32r);//setup = 8 0x209
#endif	/* TRANS2_SUBCOMMAND_H */

