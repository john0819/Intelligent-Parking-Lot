#include<iostream>
using namespace std;
#include"Behindserver.h"
#include"ThreadPool.h"
#include"ChildTask.h"
#include <stdio.h>
#include <sqlite3.h>
#include"Behindserver.h"
#include"protocol.h"

int main()
{
	ACC acceptfd;
	LOGIN login;
	REGISTER errol;
	CARIN carin;
	UPDATE newcar;
	LOAD load;
	CAROUT carout;
	VIDEOINFO videoinfo;
	INQUIRE inquire;
	PICTURE picture;
	QUERYCAR querycar;
	char buf[1024] = { 0 };
	ThreadPool* pool = new ThreadPool(20);
	
	Behindserver *behindserver = Behindserver::getIntence();
	while (true)
	{
		memcpy(buf, (behindserver->readata()), sizeof(buf));
		memcpy(&acceptfd, buf,  sizeof(acceptfd));
		if (sizeof(buf) > 0)
		{
			BaseTask* task = new ChildTask(buf, acceptfd.type);
			pool->pushTask(task);
		}
		bzero(&buf, sizeof(buf));
	}
	
	
	
	return 0;
	
}