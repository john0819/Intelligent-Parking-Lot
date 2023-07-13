#pragma once
#include<string.h>
class BaseTask
{
public:
	BaseTask(char* data);
	virtual ~BaseTask();
	char data[1024];
	virtual void working() = 0;
};

