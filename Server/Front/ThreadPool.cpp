#include "ThreadPool.h"

ThreadPool::ThreadPool(const int num)
{
	this->threadMinNum = num;
	//条件变量、互斥量初始化
	pthread_mutex_init(&this->mutex, NULL);
	pthread_cond_init(&this->cond, NULL);
	pthread_t id;
	//num条线程的创建
	for (int i = 0; i < this->threadMinNum; i++)
	{
		pthread_create(&id, NULL, RunTime, this);
		this->idleList.push_back(id);
	}

}

ThreadPool::~ThreadPool()
{
	if (this->taskQueue.size() == 0 && this->idleList.size() == this->threadMinNum)
	{
		list<pthread_t>::iterator iter;
		while (iter != idleList.end())
		{
			pthread_cancel(*iter);
			iter++;
		}
	}
	else if (this->busyList.size() > 0)
	{
		list<pthread_t>::iterator iter;
		while (iter != idleList.end())
		{
			//通知系统，线程可以结束
			pthread_cancel(*iter);
			pthread_join(*iter, NULL);
			iter++;
		}
	}
	//所有线程停止后执行销毁，互斥量  条件变量
	pthread_mutex_destroy(&this->mutex);
	pthread_cond_destroy(&this->cond);
}
//任务队列是否为空
bool ThreadPool::QueueIsEmpty()
{
	return this->taskQueue.empty();
}
//线程加锁
void ThreadPool::Lock()
{
	pthread_mutex_lock(&this->mutex);
}
//线程解锁
void ThreadPool::Unlock()
{
	pthread_mutex_unlock(&this->mutex);
}
//线程唤醒
void ThreadPool::WakeUp()
{
	pthread_cond_signal(&this->cond);
}
//线程等待
void ThreadPool::Wait()
{
	pthread_cond_wait(&this->cond, &this->mutex);
}
//添加任务到任务队列
void ThreadPool::pushTask(BaseTask* task)
{
	Lock();
	taskQueue.push(task);
	Unlock();
	WakeUp();

}
//从任务队列移除任务
BaseTask* ThreadPool::popTask(BaseTask* task)
{
	task = this->taskQueue.front();//从队列头取
	this->taskQueue.pop();
	return task;
}
//从忙碌回到空闲  工作结束
void ThreadPool::MoveToIdle(pthread_t id)
{
	list<pthread_t>::iterator iter;
	iter = find(busyList.begin(), busyList.end(), id);
	if (iter != busyList.end())
	{
		this->busyList.erase(iter);
		this->idleList.push_back(*iter);//也可以写成this->idleList.push_back(*iter); this->idleList.push_back(id);
	}
}
//从空闲到忙碌  工作开始
void ThreadPool::MoveToBusy(pthread_t id)
{
	list<pthread_t>::iterator iter;
	iter = find(idleList.begin(), idleList.end(), id);
	if (iter != idleList.end())
	{
		this->idleList.erase(iter);
		this->idleList.push_back(*iter); //也可以写成this->idleList.push_back(*iter);this->busyList.push_back(id);
	}
}
void* ThreadPool::RunTime(void* vo)
{
	//1.取任务
	//2.做任务
	//线程从空闲到忙碌
	//线程从忙碌到空闲
	//拿到执行线程自己的id  因为后面要处理忙碌和空闲的情况
	pthread_t id = pthread_self();
	//确保主线程和子线程分离，子线程结束后，资源自动回收
	//分离的目的是为了声明这个线程不会阻塞主线程
	//pthread_detach不会终止线程
	pthread_detach(id);

	//线程参数获取
	ThreadPool* argThis = (ThreadPool*)vo;
	while (true)
	{
		argThis->Lock();
		//如果任务队列为空  线程则一直等待 直到任务队列不为空为止则会被pushtask函数唤醒线程
		while (argThis->QueueIsEmpty())
		{
			argThis->Wait();
		}
		argThis->MoveToBusy(id);
		cout << "工作前 任务数" << argThis->taskQueue.size() << endl;
		cout << "工作前 忙碌数" << argThis->busyList.size() << endl;
		cout << "工作前 空闲数" << argThis->idleList.size() << endl;
		cout << "----------------------------------------" << endl;
		//取任务
		BaseTask* task;
		task = argThis->popTask(task);
		argThis->Unlock();
		//任务工作
		task->working();
		//工作结束 
		argThis->Lock();
		argThis->MoveToIdle(id);
		argThis->Unlock();
		cout << "工作完 任务数" << argThis->taskQueue.size() << endl;
		cout << "工作完 忙碌数" << argThis->busyList.size() << endl;
		cout << "工作完 空闲数" << argThis->idleList.size() << endl;
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	}
}

