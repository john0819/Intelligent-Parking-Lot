#include "BaseTask.h"

BaseTask::BaseTask(char* data)
{
	bzero(this->data, sizeof(this->data));
	memcpy(this->data, data, sizeof(this->data));
}

BaseTask::~BaseTask()
{
	delete this->data;
}
