#pragma once
#include<queue>
#include<list>
using namespace std;//写容器必须要这个不然容器不能用
#include<pthread.h>
#include"BaseTask.h"
#include<algorithm>//find 函数的头文件
#include<iostream>
#define MIN_NUM 10
class ThreadPool
{
public:
	ThreadPool(const int num = MIN_NUM);
	~ThreadPool();
	//判断任务队列是否为空                                                     
	bool QueueIsEmpty();
	//线程互斥量加锁解锁
	void Lock();
	void Unlock();
	//线程条件变量等待和唤醒
	void WakeUp();
	void Wait();
	//添加任务到任务队列
	void pushTask(BaseTask* task);
	//从任务队列移除任务
	BaseTask* popTask(BaseTask* task);
	//线程执行函数
	static void* RunTime(void* vo);
	//从忙碌回到空闲  工作结束
	void MoveToIdle(pthread_t id);
	//从空闲到忙碌  工作开始
	void MoveToBusy(pthread_t id);
private:
	int threadMinNum;
	int threadMaxNum;
	queue<BaseTask*>taskQueue;
	list<pthread_t>busyList;//线程忙碌列表
	list<pthread_t>idleList;//线程空闲列表
	pthread_mutex_t mutex;//互斥量:做锁
	pthread_cond_t cond;//条件变量：让现场等待或者唤醒
};