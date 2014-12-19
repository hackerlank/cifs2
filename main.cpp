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
#include "mem.h"
#include "common.h"
using namespace std;

/*
 * 
 */
vector<SESSION> ses;
int server_fd;
struct epoll_event ev,events[EPOLL_SIZE];

int handle_message(SESSION *sess);
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
            }
            else{
                pid_t tid;
                SESSION sess;
                sess._cfd = events[i].data.fd;
                ses.push_back(sess);
                pthread_create(&tid,NULL,client_get_message,&sess);
                //CHK2(res,handle_message(events[i].data.fd))
            }
        }
    }
    close(server_fd);
    close(epfd);
}
int main(int argc, char** argv) {

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
int client_get_message(void *arg)
{
    int ret;
    SESSION *sess = (SESSION*)arg;
    cout<<"a new client come in,the fd is"<<sess->_cfd<<endl;
    unsigned int head;
    CHK2(ret,read(sess->_cfd,&head,4),);
    sess->relloc_buf(ntohl(head));
    
}
int handle_message(SESSION *sess)
{
    
    //memcpy()
}


