/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on 2014年12月19日, 上午9:35
 */

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "mem.h"
#include "common.h"
#include "smb_commands.h"
#include "myiconv.h"
using namespace std;

/*
 * 
 */
vector<SESSION> ses;
int server_fd;
struct epoll_event ev,events[EPOLL_SIZE];
void *client_get_message(void *arg);
void *handle_message(SESSION *sess);
void *epoll_listen(void *arg)
{
    printf("aaaaaaa\n");
    pthread_detach(pthread_self());
    int epfd = *(int *)arg;
    int ep_count=0,i,res;
    if(-1==epfd)
        perror("epoll_fd");
    while(1)
    {
        ep_count = epoll_wait(epfd,events,EPOLL_SIZE,EPOLL_RUNTIME_OUT);
        for(i=0;i<ep_count;i++)
        {
            if(events[i].data.fd==server_fd)
            {
                int clientfd = accept(server_fd,NULL,NULL);
                if(-1==clientfd)
                    perror("accept");
                //setnonblocking(clientfd); 
                //printf("ew")
                ev.data.fd = clientfd;
                ev.events = EPOLLIN;
                CHK(epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &ev));
                SESSION sess(clientfd);
                //sess._cfd = clientfd;
                ses.push_back(sess);
                cout<<"a new client come in,the fd is"<<sess._cfd<<endl;
            }
            else{
                for(int j=0;j<ses.size();j++)
                {
                    if(ses[j]._cfd=events[i].data.fd)
                    {
                        handle_message(&ses[j]);
                        break;
                    }
                //CHK2(res,handle_message(events[i].data.fd))
                }
            }
        }
    }
    close(server_fd);
    close(epfd);
}
void sswswswswswsswswws()
{
    char s[100] = {0};
    char d[100] = "0200000032000000a4810000000000000002";
    sscanf(d,"%2x",&s[0]);
    getchar();
}
int main(int argc, char** argv) {
    //sswswswswswsswswws();
    char s[100]="0200000032000000a4810000000000000002",d[100] = {0};
    itostr(s,d);
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd<0)
        perror("socket");
    struct sockaddr_in servaddr;
    servaddr.sin_family=AF_INET;
    servaddr.sin_port = htons(445);
    servaddr.sin_addr.s_addr = inet_addr("172.16.10.24");
    //servaddr.sin_addr.s_addr = INADDR_ANY;
    struct sockaddr clientaddr;
    int on=1;
    if(-1==setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))
        perror("setsockopt");
    if(-1==bind(server_fd,(struct sockaddr *)&servaddr,sizeof(servaddr)))
        perror("bind");
    listen(server_fd,5);
    
    int epfd = epoll_create(EPOLL_SIZE);
    if(-1 == epfd)
        perror("epoll_create!");
    bzero(&ev,sizeof(struct epoll_event));
    bzero(&events,EPOLL_SIZE*sizeof(struct epoll_event));
    ev.data.fd = server_fd;
    ev.events = EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,server_fd,&ev);
    //建立一个线程用来监听
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,epoll_listen,&epfd); 
    while(1);
    return 0;
}
void *client_get_message(void *arg)
{
    int ret;
    SESSION *sess = (SESSION*)arg;
    handle_message(sess);
}
void *handle_message(SESSION *sess)
{
    unsigned int head;
    int ret;
    CHK3(ret,read(sess->_cfd,&head,4),"read in client_get_message_head!");
    sess->_len = ntohl(head);
    sess->relloc_buf();
    CHK3(ret,read(sess->_cfd,sess->_buf,sess->_len),"read in client_get_message_message!");
    sess->fill_head();
    do_command_map(sess);
}


