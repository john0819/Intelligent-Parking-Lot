#include "Frontserver.h"
#include"protocol.h"
LOGIN login;
ACC acceptfd;
Frontserver* Frontserver::pTntence = nullptr;
//信号量创建
int sem_create(key_t key, int num_sems)
{
	int res = semget(key, num_sems, IPC_CREAT | 0777);
	if (res < 0)
	{
		perror("semget error");
	}
	return res;
}
//信号量赋初始值
int sem_setVal(int semid, int semnum, int val)
{
	union semun arg;
	arg.val = val;
	int res = semctl(semid, semnum, SETVAL, arg);
	if (res < 0)
	{
		perror("semctl error");
	}
	return res;
}
//信号量P操作 -1
int sem_p(int semid, int semindex)
{
	struct sembuf buf = { semindex,-1,SEM_UNDO };
	int res = semop(semid, &buf, 1);
	if (res < 0)
	{
		perror("semop error");
	}
	return res;
}
//信号量V操作 +1
int sem_v(int semid, int semindex)
{
	struct sembuf buf = { semindex,1,SEM_UNDO };
	int res = semop(semid, &buf, 1);
	if (res < 0)
	{
		perror("semop error");
	}
	return res;
}


Frontserver::Frontserver()
{
	semid = 0;//信号量1
	semid1 = 0;//信号量2
	shmid = 0;//共享内存1
	shmid1 = 0;//共享内存2
	msgid = 0;//消息队列1
	msgid1 = 0;//消息队列2
	arr[LENGTN] = 0;//共享内存1索引区
	arr1[LENGTN] = 0;//共享内存2索引区
	buf[1024] = 0;//数据
	buf1[1024] = 0;//数据
	int res = sharecreate();
	int res1 = messagecrete();

	if (res == 0 && res1 == 0)
	{
		Semaphorecreate();
	}

}

Frontserver* Frontserver::getIntence()
{
	//先判断这个唯一的对象是否已经创建
	if (Frontserver::pTntence == nullptr)//判断相等必须要==不能在这里出问题
	{
		//创建这个对象
		Frontserver::pTntence = new Frontserver();
	}
	//返回这个对象
	return Frontserver::pTntence;
}

Frontserver::~Frontserver()
{
}

int Frontserver::sharecreate()
{
	this->shmid = shmget((key_t)1001, sizeof(arr) + sizeof(buf) * LENGTN, IPC_CREAT | 0777);
	this->shmid1 = shmget((key_t)1004, sizeof(arr1) + sizeof(buf) * LENGTN, IPC_CREAT | 0777);
	
	if (shmid = -1 && shmid1 == -1)
	{
		cout << "create error" << endl;
		return -1;
	}
	else
	{
		return 0;
	}
	
}

int Frontserver::messagecrete()
{

	this->msgid = msgget((key_t)1002, IPC_CREAT | 0777);
	this->msgid1 = msgget((key_t)1005, IPC_CREAT | 0777);
	if (msgid = -1 && msgid1 == -1)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void Frontserver::Semaphorecreate()
{
	//信号量创建
	semid = sem_create((key_t)1003, 1);
	//信号量设置值
	sem_setVal(semid, 0, 1);
	//信号量创建
	semid1 = sem_create((key_t)1006, 1);
	//信号量设置值
	sem_setVal(semid1, 0, 1);
}

void Frontserver::writedata(char* data)
{
	int index = 0;
	void* shmaddr;
	MSGBUF sendbuf;	
	shmid = shmget((key_t)1001, sizeof(arr) + sizeof(buf) * LENGTN, IPC_CREAT | 0777);
	msgid = msgget((key_t)1002, IPC_CREAT | 0777);
	memcpy(buf, data, sizeof(buf));
	cout << "--------------------------准备工作完成，写数据开始-----------------------------" << endl;

	sem_p(semid, 0);
	shmaddr = shmat(shmid, NULL, 0);
	
	//读索引区
	memcpy(arr, shmaddr, sizeof(arr));
	for (int i = 0; i < LENGTN; i++)
	{
		if (arr[i] == 0)
		{
			index = i;
			break;
		}
	}
	cout << "可以写数据的索引区下标为index=" << index << endl;
	arr[index] = 1;
	//写索引区
	memcpy((void*)(shmaddr + (index * sizeof(int))), &arr[index], sizeof(int));
	//写数据区
	memcpy((void*)(shmaddr + sizeof(arr) + (index * sizeof(buf))), &buf, sizeof(buf));
	sendbuf.mtype = 1;
	sprintf(sendbuf.mtext, "%d", index);
	if (msgsnd(msgid, &sendbuf, sizeof(MSGBUF), 0) == -1)
	{
		perror("msgsnd error");
	}
	bzero(&sendbuf, sizeof(MSGBUF));
	bzero(&buf, sizeof(buf));
	cout << ">>>>>>>>>>>>>>写数据完成>>>>>>>>>>>>>" << endl;
	//断开共享内存
	shmdt(shmaddr);
	//进程解锁
	sem_v(semid, 0);
	cout << "写端进入sleep" << endl;
}

char* Frontserver::readata()
{
	int index = 0;
	void* shmaddr;
	MSGBUF rcvbuf;
	this->shmid1 = shmget((key_t)1004, sizeof(arr1) + sizeof(buf) * LENGTN, IPC_CREAT | 0777);
	this->msgid1 = msgget((key_t)1005, IPC_CREAT | 0777);
	if (msgrcv(msgid1, &rcvbuf, sizeof(rcvbuf), 1, 0) == -1)
	{
		perror("msgrcv error");
	}
	else
	{
		
		cout << "--------------------------准备工作完成，读数据开始-----------------------------" << endl;
		//进程加锁
		sem_p(semid1, 0);
		index = atoi(rcvbuf.mtext);
		cout << "读到消息队列中下标index=" << index << endl;
		//连接共享内存
		shmaddr = shmat(shmid1, NULL, 0);
		//读索引区
		memcpy(&arr1[index], (void*)(shmaddr + (index * sizeof(int))), sizeof(int));
		if (arr1[index] == 1)
		{
			//读数据区
			memcpy(&buf, (void*)(shmaddr + sizeof(arr) + (index * sizeof(buf))), sizeof(buf));
			
			//清空数据区
			memset((void*)(shmaddr + sizeof(arr) + (index * sizeof(buf))), 0, sizeof(buf));
			//修改索引区
			arr1[index] = 0;
			memcpy((void*)(shmaddr + (index * sizeof(int))), &arr1[index], sizeof(int));
			cout << "读数据完成" << endl;
		}
		//断开共享内存
		shmdt(shmaddr);
		//进程解锁
		sem_v(semid1, 0);
		cout << "读端进入sleep" << endl;
		
	}
	return buf;
}
