#pragma once
#include "BaseTask.h"
#include<iostream>
#include<unistd.h>
#include "Frontserver.h"
#include"protocol.h"
using namespace std;
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
class ChildTask :
    public BaseTask
{
public:
    ChildTask(char* data,int type);
    ~ChildTask();
    void working();
private:
    int type;
    Frontserver* frontserver;
    char buf[3000];
    char buf1[3000];
    ACC acceptfd;
    FEEDBACK feedback;
    CARIN carin[4];
    REGISTER logreg;
    CARIN carin1;
    CAROUT carout;
    PARTINFO partinfo;
    INQUIRE inquire;
    VIDEOINFO videoinfo[4];
    VIDEOINFO videoinfo1;
    CAROUT carout1[4];
    PICTURE picture;
};

