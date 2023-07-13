#include "CEpollServer.h"
//==================================================
//函数名称：uByte CalcCRCCode（uByte *Array， uByte Len）
//输入参数：需要计算 CRC 的数据首地址、数据个数
//输出参数：对应数据的 CRC 校验码
//函数功能：计算数据的 CRC 校验码
//==================================================
unsigned int CalcCRCCode(unsigned char* Array, unsigned int Len)
{
	unsigned int i = 0;
	unsigned int j = 0;
	const unsigned short CalcConst = 0xFFFF;
	unsigned int TempOut = 0;
	for (i = 0; i < Len; i++)
	{
		TempOut = CalcConst ^ Array[i];
		for (j = 0; j < 8; j++)
		{
			if (TempOut & 0x0001)
			{
				TempOut = TempOut >> 1;
				TempOut ^= 0xA001;
			}
			else {
				TempOut = TempOut >> 1;
			}
		}
	}
	return(TempOut);
}

CEpollServer::CEpollServer(unsigned short port)
{
	//初始化 TcpServer类
	this->tcp = new CTcpServer(port);
	this->tcp->Start();
	cout << "socketFd = " << this->tcp->getSocketfd() << endl;

	//初始化数据成员
	this->epollfd = 0;
	this->epollwaitefd = 0;
	this->acceptFd = 0;
	bzero(this->buf, sizeof(this, buf));
	bzero(this->buf1, sizeof(this, buf1));
	//事件结构体初始化
	bzero(&(this->epollEvent), sizeof(this->epollEvent));
	//绑定当前准备好的sockedfd（可用网络对象）
	this->epollEvent.data.fd = this->tcp->getSocketfd();
	//绑定事件为客户端接入事件
	this->epollEvent.events = EPOLLIN;
	//创建epoll
	this->epollfd = epoll_create(EPOLL_SIZE);
	//将已经准备好的网络描述符添加到epoll事件队列中
	epoll_ctl(this->epollfd, EPOLL_CTL_ADD, this->tcp->getSocketfd(), &(this->epollEvent));
	pool = new ThreadPool(20);
	frontserver = Frontserver::getIntence();
}

CEpollServer::~CEpollServer()
{

}

void CEpollServer::Start()
{
	while (1)
	{
		cout << "epoll wait client........" << endl;
		this->epollwaitefd = epoll_wait(this->epollfd, epollEventArray, EPOLL_SIZE, -1);
		if (this->epollwaitefd < 0)
		{
			perror("epoll wait error");
		}
		for (int i = 0; i < this->epollwaitefd; i++)
		{
			
			//判断是否有客户端上线
			if (epollEventArray[i].data.fd == this->tcp->getSocketfd())
			{
				cout << "网络开始工作，等待客户端上线" << endl;
				this->acceptFd = accept(this->tcp->getSocketfd(), NULL, NULL);
				cout << "acceptfd = " << this->acceptFd << endl;

				//上线的客户端描述符是acceptfd 绑定事件添加到epoll
				epollEvent.data.fd = this->acceptFd;
				epollEvent.events = EPOLLIN; //EPOLLIN表示对应的文件描述符可以读
				epoll_ctl(this->epollfd, EPOLL_CTL_ADD, this->acceptFd, &epollEvent);
			}
			else if (epollEventArray[i].events & EPOLLIN)
			{
				bzero(this->buf, sizeof(this->buf));
				int res = read(epollEventArray[i].data.fd, this->buf, sizeof(this->buf));
				if (res > 0)
				{
					
					memcpy(&h,buf, sizeof(HEAD));
					
					unsigned char buf2[h.bussinesslen];
					memcpy(buf2, buf + sizeof(HEAD), h.bussinesslen);
					int CRC = CalcCRCCode( buf2, h.bussinesslen);
					if (CRC == h.CRC)
					{
						cout << "--------CRC校验成功--------" << endl;
						cout << "CRC=" << h.CRC << endl;
						if (h.bussinesstype == 2)
						{
							cout << "登录" << endl;
							memcpy(&login, buf + sizeof(HEAD), sizeof(LOGIN));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &login, sizeof(LOGIN));			
							BaseTask* task = new ChildTask(buf1, 0);

							pool->pushTask(task);


						}
						else if (h.bussinesstype == 1)
						{
							cout << "注册" << endl;
							memcpy(&enroll, buf + sizeof(HEAD), sizeof(REGISTER));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &enroll, sizeof(REGISTER));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);


						}
						else if (h.bussinesstype == 3)
						{
							cout << "进入入场主界面" << endl;
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 4)
						{
							cout << "添加入场车辆" << endl;
							memcpy(&carin, buf + sizeof(HEAD), sizeof(CARIN));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &carin, sizeof(CARIN));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);


						}
						else if (h.bussinesstype == 5)
						{
							cout << "修改矫正车牌信息" << endl;
							memcpy(&newcar, buf + sizeof(HEAD), sizeof(UPDATE));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &newcar, sizeof(UPDATE));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);


						}
						else if (h.bussinesstype == 6)
						{
							cout << "懒加载" << endl;
							memcpy(&load, buf + sizeof(HEAD), sizeof(LOAD));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &load, sizeof(LOAD));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);


						}
						else if (h.bussinesstype == 7)
						{
							cout << "双击" << endl;
							memcpy(&carin, buf + sizeof(HEAD), sizeof(CARIN));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &carin, sizeof(CARIN));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);


						}
						else if (h.bussinesstype == 8)
						{
							cout << "抓拍到出场车牌" << endl;
							memcpy(&carout, buf + sizeof(HEAD), sizeof(CAROUT));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &carout, sizeof(CAROUT));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 9)
						{
							cout << "抓拍到出场车牌" << endl;
							memcpy(&carout, buf + sizeof(HEAD), sizeof(CAROUT));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &carout, sizeof(CAROUT));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 10)//
						{
							cout << "获取停车场信息" << endl;
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 11)//
						{
							cout << "获取视频信息" << endl;
							memcpy(&videoinfo, buf + sizeof(HEAD), sizeof(VIDEOINFO));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &videoinfo, sizeof(VIDEOINFO));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 12)
						{
							cout << "获取视频的月份" << endl;
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 13)//按日查询
						{

							cout << "获取视频的日期" << endl;
							memcpy(&inquire, buf + sizeof(HEAD), sizeof(INQUIRE));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &inquire, sizeof(INQUIRE));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 14)//按月查询
						{

							cout << "按月查询" << endl;
							memcpy(&inquire, buf + sizeof(HEAD), sizeof(INQUIRE));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &inquire, sizeof(INQUIRE));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 15)//按日查询
						{

							cout << "按日查询" << endl;
							memcpy(&inquire, buf + sizeof(HEAD), sizeof(INQUIRE));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &inquire, sizeof(INQUIRE));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 16)//打开视频
						{

							cout << "按日查询" << endl;
							memcpy(&videoinfo, buf + sizeof(HEAD), sizeof(VIDEOINFO));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &videoinfo, sizeof(VIDEOINFO));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 17)//按月翻页
						{

							cout << "按月翻页" << endl;
							memcpy(&inquire, buf + sizeof(HEAD), sizeof(INQUIRE));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &inquire, sizeof(INQUIRE));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 18)//按日翻页
						{

							cout << "按日翻页" << endl;
							memcpy(&inquire, buf + sizeof(HEAD), sizeof(INQUIRE));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &inquire, sizeof(INQUIRE));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 19)//打开视频
						{

							cout << "按日查询" << endl;
							memcpy(&videoinfo, buf + sizeof(HEAD), sizeof(VIDEOINFO));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &videoinfo, sizeof(VIDEOINFO));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 20)//打开视频
						{

							cout << "接受碎片文件" << endl;
							memcpy(&picture, buf + sizeof(HEAD), sizeof(PICTURE));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &picture, sizeof(PICTURE));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 21)//打开视频
						{
							cout << "查询车辆信息" << endl;
							memcpy(&querycar, buf + sizeof(HEAD), sizeof(QUERYCAR));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &querycar, sizeof(QUERYCAR));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 22)//打开视频
						{
							cout << "懒加载" << endl;
							memcpy(&querycar, buf + sizeof(HEAD), sizeof(QUERYCAR));
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							memcpy(buf1 + sizeof(acceptfd), &querycar, sizeof(QUERYCAR));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
						}
						else if (h.bussinesstype == 23)//打开视频
						{
							cout << "客户端 fd = " << epollEventArray[i].data.fd << " 掉线……" << endl;
							acceptfd.acceptfd = epollEventArray[i].data.fd;
							acceptfd.type = h.bussinesstype;
							bzero(&buf1, sizeof(buf1));
							memcpy(buf1, &acceptfd, sizeof(acceptfd));
							BaseTask* task = new ChildTask(buf1, 0);
							pool->pushTask(task);
							close(epollEventArray[i].data.fd);
							//从epoll中删除客户端描述符
							epollEvent.data.fd = epollEvent.data.fd;
							epollEvent.events = EPOLLIN;
							epoll_ctl(this->epollfd, EPOLL_CTL_DEL, epollEventArray[i].data.fd, &epollEvent);


						}
					}
					else
					{
						cout << "--------CRC校验失败--------" << endl;
						cout << "CRC=" << CRC << endl;
						feedback.flag = 0;
						feedback.businesslen = h.bussinesslen;
						feedback.businesstype = h.bussinesstype;
						write(epollEventArray[i].data.fd, &feedback, sizeof(FEEDBACK));
					}
				}
				else if (res <= 0)
				{
					cout << "客户端 fd = " << epollEventArray[i].data.fd << " 掉线……" << endl;
					acceptfd.acceptfd = epollEventArray[i].data.fd;
					acceptfd.type = 23;
					bzero(&buf1, sizeof(buf1));
					memcpy(buf1, &acceptfd, sizeof(acceptfd));
					BaseTask* task = new ChildTask(buf1, 0);
					pool->pushTask(task);
					close(epollEventArray[i].data.fd);
					//从epoll中删除客户端描述符
					epollEvent.data.fd = epollEvent.data.fd;
					epollEvent.events = EPOLLIN;
					epoll_ctl(this->epollfd, EPOLL_CTL_DEL, epollEventArray[i].data.fd, &epollEvent);
					
				}
			}
			BaseTask* task1 = new ChildTask(buf1, 1);
			pool->pushTask(task1);
		}
			
	}
}