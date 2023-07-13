#pragma once
#include "BaseTask.h"
#include<iostream>
#include<unistd.h>
#include "Behindserver.h"
#include"protocol.h"
#include"Cccontroller.h"
#include <ctime>
using namespace std;
#include<stdio.h>
#include<time.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include<string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include<string>
#include<math.h>
#include <errno.h>
#include <dirent.h>
using namespace std;
class ChildTask :
    public BaseTask
{
public:
    ChildTask(char* data,int type);
    ~ChildTask();
    void working();
private:
    int type;
    Behindserver* behindserver;
    char buf[3000];
    char buf1[3000];
    ACC acceptfd;
    LOGIN login;
    Cccontroller* ptrol;
    FEEDBACK feedback;
    REGISTER errol;
    REGISTER logre;//返回用户名
    CARIN carin[4];
    CARIN carin1;
    Cdatasqlite* ptr;
    UPDATE newcar;
    LOAD load;
    CAROUT carout;
    PARTINFO partinfo;
    VIDEOINFO videoinfo;
    VIDEOINFO videoinfo1[4];
    CAROUT carout1[4];
    PICTURE picture;
    LOG log;
    INQUIRE inquire;
    QUERYCAR querycar;
};

