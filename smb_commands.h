/* 
 * File:   smb_commands.h
 * Author: root
 *
 * Created on 2014年12月19日, 上午11:28
 */
#ifndef SMB_COMMANDS_H
#define	SMB_COMMANDS_H
#define STATUS_SUCCESS 0x00000000
#include "common.h"
typedef struct smbcmd
{
	unsigned char cmd;	//smb指令
	void (*cmd_handler)(SESSION *sess);//该指令所对应的执行函数
} smbcmd_t;
void do_command_map(SESSION *sess);
void do_negotiate(SESSION *sess);
void do_sessionsetup(SESSION *sess);
void do_transcation2(SESSION *sess);
void do_treeconnect(SESSION *sess);
void do_NT_CREATE_ANDX(SESSION *sess);
void do_write_andx(SESSION *sess);
void do_read_andx(SESSION *sess);
void do_echo(SESSION *sess);
void do_close(SESSION *sess);
void do_rename(SESSION *sess);//0x07
static smbcmd_t smbcmds[] = {
	/* 访问控制命令 */
    {SMB_COM_NEGOTIATE,do_negotiate},
    {SMB_COM_SESSION_SETUP_ANDX,do_sessionsetup},
    {SMB_COM_TREE_CONNECT_ANDX,do_treeconnect},
    {SMB_COM_TRANSACTION2,do_transcation2},
    {SMB_COM_NT_CREATE_ANDX,do_NT_CREATE_ANDX},
    {SMB_COM_WRITE_ANDX,do_write_andx},
    {SMB_COM_READ_ANDX,do_read_andx},
    {SMB_COM_ECHO,do_echo},
    {SMB_COM_CLOSE,do_close},
    {SMB_COM_RENAME,do_rename}
};


#endif	/* SMB_COMMANDS_H */

