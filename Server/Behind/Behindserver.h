#pragma once
#include<iostream>
#include<stdlib.h>
	using namespace std;
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/msg.h>
#include<stdio.h>
#include<string.h>
#define LENGTN 100
typedef struct student
{
	char stuid[20];
	char stuname[20];
	char age[20];
}STU;
typedef struct sendmsgbuf
{
	long mtype;
	char mtext[2];
}MSGBUF;
union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds* buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short* array;  /* Array for GETALL, SETALL */
	struct seminfo* __buf;  /* Buffer for IPC_INFO
								(Linux-specific) */
};

class Behindserver
{
public:
	static Behindserver* getIntence();
	static Behindserver* pTntence;
	~Behindserver();
	int sharecreate();//共享内存创建
	int messagecrete();//消息队列创建
	void Semaphorecreate();//信号量创建
	char* readata();//读操作
	void writedata(char* data);//写操作
private:
	Behindserver();
	int semid;//信号量1
	int semid1;//信号量2
	int shmid;//共享内存1
	int shmid1;//共享内存2
	int msgid;//消息队列1
	int msgid1;//消息队列2

	int arr[LENGTN];//共享内存1索引区
	int arr1[LENGTN];//共享内存2索引区
	char buf[3000];//数据
};