#pragma once
#include <sys/epoll.h>
#include <iostream>
#include "CTcpServer.h"
#include<string.h>
#include"protocol.h"
#include "ThreadPool.h"
#include "BaseTask.h"
#include "ChildTask.h"
using namespace std;
#include "Frontserver.h"
#include<map>;
#include<unistd.h>
#include<stdio.h>
#include<time.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include<string>
#include<math.h>
#define EPOLL_SIZE 5
class CEpollServer
{
public:
	CEpollServer(unsigned short port);
	~CEpollServer();
	void Start();

private:
	int epollfd;
	int epollwaitefd;
	int acceptFd;
	char buf[3000]; //存放客户端发来的消息
	char buf1[3000];//存放fd和需要发送给后端的数据
	struct epoll_event epollEvent;
	struct epoll_event epollEventArray[5];
	CTcpServer* tcp;//TCP类
	HEAD h;
	FEEDBACK feedback;
	REGISTER enroll;
	LOGIN login;
	ThreadPool* pool;
	Frontserver* frontserver;
	CARIN carin;
	ACC acceptfd;
	UPDATE newcar;
	LOAD load;
	CAROUT carout;
	VIDEOINFO videoinfo;
	INQUIRE inquire;
	PICTURE picture;
	QUERYCAR querycar;
	
	//CARIN
};

