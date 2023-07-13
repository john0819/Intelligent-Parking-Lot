#include "ChildTask.h"
#include<string.h>
#include<vector>

int get_file_num(char* root)
{
	int total = 0;
	DIR* dir = NULL;
	// 打开目录
	dir = opendir(root);
	// 循环从目录中读文件

	char path[1024];
	// 定义记录指针
	struct dirent* ptr = NULL;
	while ((ptr = readdir(dir)) != NULL)
	{
		// 跳过. 和 ..
		if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
		{
			continue;
		}
		// 判断是不是目录
		if (ptr->d_type == DT_DIR)
		{
			sprintf(path, "%s/%s", root, ptr->d_name);
			// 递归读目录
			total += get_file_num(path);
		}
		// 如果是普通文件
		if (ptr->d_type == DT_REG)
		{
			total++;
		}
	}
	closedir(dir);

	return total;
}



void error_quit(const char* msg)
{
	perror(msg);
	exit(-1);
}
void change_path(const char* path)
{
	printf("Leave %s Successed . . .\n", getcwd(NULL, 0));
	if (chdir(path) == -1)
		error_quit("chdir");
	printf("Entry %s Successed . . .\n", getcwd(NULL, 0));
}
void rm_dir(const char* path)
{
	DIR* dir;
	struct dirent* dirp;
	struct stat  buf;
	char* p = getcwd(NULL, 0);
	if ((dir = opendir(path)) == NULL)
		error_quit("OpenDir");
	change_path(path);
	while (dirp = readdir(dir))
	{
		if ((strcmp(dirp->d_name, ".") == 0) || (strcmp(dirp->d_name, "..") == 0))
			continue;
		if (stat(dirp->d_name, &buf) == -1)
			error_quit("stat");
		if (S_ISDIR(buf.st_mode))
		{
			rm_dir(dirp->d_name);
			/*if(rmdir(dirp->d_name)==-1)
			 *  error_quit("rmdir");
			 * printf("rm %s Successed . . .\n",dirp->d_name);*/
			continue;
		}
		if (remove(dirp->d_name) == -1)
			error_quit("remove");
		//printf("rm %s Successed . . .\n", dirp->d_name);
	}
	closedir(dir);
	change_path(p);
	if (rmdir(path) == -1)
		error_quit("rmdir");
	//printf("rm %s Successed . . .\n", path);
}

ChildTask::ChildTask(char* data,int type) :BaseTask(data)
{
	this->type = type;
	behindserver = Behindserver::getIntence();
	bzero(&buf, sizeof(buf));
	ptrol = new Cccontroller();
	this->type = type;
	ptr = Cdatasqlite::getIntence();
}

ChildTask::~ChildTask()
{
}

void ChildTask::working()
{
	time_t nowtime;
	//首先创建一个time_t 类型的变量nowtime
	struct tm* p;
	//然后创建一个新时间结构体指针 p 
	time(&nowtime);
	//使用该函数就可得到当前系统时间，使用该函数需要将传入time_t类型变量nowtime的地址值。
	p = localtime(&nowtime);
	char time[20];
	sprintf(time,"%d-%02d-%02d-%02d-%02d",p->tm_year+1900,p->tm_mon+1,  p->tm_mday,p->tm_hour, p->tm_min);
	//登录
	if (type == 2)
	{
		cout << "用户登录" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&login, data + sizeof(acceptfd), sizeof(login));
		int res = ptrol->searchUserByNameAndPwd(login.userid, login.userpwd);

		if (res == -1)
		{
			cout << "查询失败" << endl;
			feedback.businesstype = 2;
			feedback.businesslen = 0;
			feedback.flag = 0;
			bzero(&buf1, sizeof(buf1));
			memcpy(buf1, &acceptfd, sizeof(acceptfd));
			memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		}
		else
		{

			int res2 = ptrol->saveacceptfdAnduserid(acceptfd.acceptfd,login.userid);
			if (res2 == -1)
			{
				feedback.businesstype = 2;
				feedback.businesslen = 0;
				feedback.flag = 0;
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &acceptfd, sizeof(acceptfd));
				memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
			}
			else
			{
				cout << "查询成功" << endl;
				char operate[40];
				strcat(operate, login.userid);
				strcat(operate, "登录");
				

				strcpy(log.useid, login.userid);
				strcpy(log.time, time);
				strcpy(log.type, "登录");
				strcpy(log.operate, operate);
				int res3 = ptrol->loginAndregisters(log);
				if (res3 == 0)
				{
					char sql[1024] = { 0 };
					//去数据库里面--用到我们的数据库单例
					strcat(sql, "select *from table_user where user_id='");
					strcat(sql, login.userid);
					strcat(sql, "'");
					strcat(sql, "and user_pwd='");
					strcat(sql, login.userpwd);
					strcat(sql, "';");
					char** qres;
					int row = 0, col = 0;
					//cout << sql << endl;
					int res = ptr->getDataSql(sql, qres, row, col);
					strcpy(logre.userid, (qres[col + 0]));
					strcpy(logre.username, (qres[col + 1]));
					strcpy(logre.userpwd, (qres[col + 2]));
					char sql1[1024] = ("select * from table_carin order by imgid desc limit 0,4;");
					//CARIN carin[4] = { 0 };
					row = 0, col = 0;
					res = ptr->getDataSql(sql1, qres, row, col);
					if (res == 0)
					{
						if (row == 0)
						{
							feedback.businesstype = 2;
							feedback.businesslen = sizeof(REGISTER);
							feedback.flag = 1;
						}
						else
						{
							for (int j = 1; j <= row; j++)
							{
								int i = j - 1;
								carin[i].imgid = atoi((qres[j * col + 0]));

								strcpy(carin[i].carid, (qres[j * col + 1]));
								strcpy(carin[i].intime, (qres[j * col + 2]));
								strcpy(carin[i].location, (qres[j * col + 3]));
								strcpy(carin[i].imgpath, (qres[j * col + 4]));
								feedback.businesstype = 2;
								feedback.businesslen = sizeof(CARIN) * 4 + sizeof(REGISTER);
								feedback.flag = 1;

							}
						}
					}
				}
				else
				{
					feedback.businesstype = 2;
					feedback.businesslen = 0;
					feedback.flag = 0;
					bzero(&buf1, sizeof(buf1));
					memcpy(buf1, &acceptfd, sizeof(acceptfd));
					memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
				}
				cout << "做任务" << endl;
				cout << carin[0].carid << endl;
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &acceptfd, sizeof(acceptfd));
				memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &logre, sizeof(REGISTER));
				memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK) + sizeof(REGISTER), &carin, sizeof(CARIN) * 4);
			}
			
		}

		
		behindserver->writedata(this->buf1);

	}
	else if (type == 1)//注册
	{
		cout << "用户注册" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&errol, data + sizeof(acceptfd), sizeof(REGISTER));
		char operate[40] = { 0 };
		strcat(operate, errol.userid);
		strcat(operate, "注册");
		strcpy(log.useid, errol.userid);
		strcpy(log.time, time);
		strcpy(log.type, "注册");
		strcpy(log.operate, operate);
		int res1 = ptrol->loginAndregisters(log);
		if (res1 == 0)
		{
			int res = ptrol->userenroll(errol);
			if (res == -1)
			{
				perror("insert fail");
				feedback.businesstype = 1;
				feedback.businesslen = 0;
				feedback.flag = 0;
			}
			else
			{

				feedback.businesstype = 1;
				feedback.businesslen = 0;
				feedback.flag = 1;
			}
			
		}
		else
		{
			feedback.businesstype = 1;
			feedback.businesslen = 0;
			feedback.flag = 0;
		}
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		behindserver->writedata(this->buf1);
	}
	else if (type == 3)//进入入场主界面的得到最后的四份数据
	{
		cout << "得到最新的四份入场车辆信息" << endl;
		bzero(&carin, sizeof(carin));
		memcpy(&acceptfd, data, sizeof(acceptfd));
		strcpy(log.time, time);
		strcpy(log.type, "得到最后的四份数据");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql1[1024] = ("select * from table_carin order by imgid desc limit 0,4;");
			//CARIN carin[4] = { 0 };
			int row = 0, col = 0;
			char** qres;
			int res = ptr->getDataSql(sql1, qres, row, col);
			if (res == 0)
			{
				if (row == 0)
				{
					feedback.businesstype = 3;
					feedback.businesslen = 0;
					feedback.flag = 1;
				}
				else
				{
					feedback.businesstype = 3;
					feedback.businesslen = sizeof(CARIN) * 4;
					feedback.flag = 1;
					for (int j = 1; j <= row; j++)
					{
						int i = j - 1;
						carin[i].imgid = atoi((qres[j * col + 0]));

						strcpy(carin[i].carid, (qres[j * col + 1]));
						strcpy(carin[i].intime, (qres[j * col + 2]));
						strcpy(carin[i].location, (qres[j * col + 3]));
						strcpy(carin[i].imgpath, (qres[j * col + 4]));

					}


				}
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &acceptfd, sizeof(acceptfd));
				memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &carin, sizeof(CARIN) * 4);
			}
			else
			{
				feedback.businesstype = 3;
				feedback.businesslen = 0;
				feedback.flag = 0;
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &acceptfd, sizeof(acceptfd));
				memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
			}
		}
		else
		{
			feedback.businesstype = 3;
			feedback.businesslen = 0;
			feedback.flag = 0;
			bzero(&buf1, sizeof(buf1));
			memcpy(buf1, &acceptfd, sizeof(acceptfd));
			memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		}
		behindserver->writedata(this->buf1);
	}
	else if (type == 4)//拍照
	{
		cout << "抓拍入场车牌" << endl;
		bzero(&carin, sizeof(carin));
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&carin1, data + sizeof(acceptfd), sizeof(CARIN));
		strcpy(log.time, time);
		strcpy(log.type, "抓拍入场车牌");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			int res = ptrol->carindeposit(carin1);
			if (res == -1)
			{
				perror("insert fail");
				feedback.businesstype = 4;
				feedback.businesslen = 0;
				feedback.flag = 0;
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &acceptfd, sizeof(acceptfd));
				memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
			}
			else
			{
				char sql1[1024] = ("select * from table_carin order by imgid desc limit 0,4;");
				//CARIN carin[4] = { 0 };
				int row = 0, col = 0;
				char** qres;
				int res = ptr->getDataSql(sql1, qres, row, col);
				if (res == 0)
				{
					feedback.businesstype = 4;
					feedback.businesslen = sizeof(CARIN) * 4;
					feedback.flag = 1;
					for (int j = 1; j <= row; j++)
					{
						int i = j - 1;
						carin[i].imgid = atoi((qres[j * col + 0]));

						strcpy(carin[i].carid, (qres[j * col + 1]));
						strcpy(carin[i].intime, (qres[j * col + 2]));
						strcpy(carin[i].location, (qres[j * col + 3]));
						strcpy(carin[i].imgpath, (qres[j * col + 4]));

					}
					bzero(&buf1, sizeof(buf1));
					memcpy(buf1, &acceptfd, sizeof(acceptfd));
					memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
					memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &carin, sizeof(CARIN) * 4);
				}

			}
		}
		else
		{
			feedback.businesstype = 4;
			feedback.businesslen = 0;
			feedback.flag = 0;
			bzero(&buf1, sizeof(buf1));
			memcpy(buf1, &acceptfd, sizeof(acceptfd));
			memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		}

		
		behindserver->writedata(this->buf1);

	}
	else if (type == 5)
	{
		cout << "修改入场车牌" << endl;
		bzero(&carin, sizeof(carin));
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&newcar, data + sizeof(acceptfd), sizeof(UPDATE));
		strcpy(log.time, time);
		strcpy(log.type, "修改入场车牌号");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			int res = ptrol->carinrevise(newcar);
			if (res == -1)
			{
				perror("Update fail");
				feedback.businesstype = 5;
				feedback.businesslen = 0;
				feedback.flag = 0;
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &acceptfd, sizeof(acceptfd));
				memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
			}
			else
			{
				char sql1[1024] = ("select * from table_carin order by imgid desc limit 0,4;");
				//CARIN carin[4] = { 0 };
				int row = 0, col = 0;
				char** qres;
				int res = ptr->getDataSql(sql1, qres, row, col);
				if (res == 0)
				{
					feedback.businesstype = 5;
					feedback.businesslen = sizeof(CARIN) * 4;
					feedback.flag = 1;
					for (int j = 1; j <= row; j++)
					{
						int i = j - 1;
						carin[i].imgid = atoi((qres[j * col + 0]));

						strcpy(carin[i].carid, (qres[j * col + 1]));
						strcpy(carin[i].intime, (qres[j * col + 2]));
						strcpy(carin[i].location, (qres[j * col + 3]));
						strcpy(carin[i].imgpath, (qres[j * col + 4]));

					}
					bzero(&buf1, sizeof(buf1));
					memcpy(buf1, &acceptfd, sizeof(acceptfd));
					memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
					memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &carin, sizeof(CARIN) * 4);
				}
			}
		}
		else
		{
			feedback.businesstype = 5;
			feedback.businesslen = 0;
			feedback.flag = 0;
			bzero(&buf1, sizeof(buf1));
			memcpy(buf1, &acceptfd, sizeof(acceptfd));
			memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		}
		behindserver->writedata(this->buf1);
	}
	else if (type == 6)
	{
		cout << "入场车辆信息懒加载" << endl;
		bzero(&carin, sizeof(carin));
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&load, data + sizeof(acceptfd), sizeof(LOAD));
		strcpy(log.time, time);
		strcpy(log.type, "懒记载");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql[1024] = { 0 };
			strcat(sql, "select * from table_carin order by imgid desc limit ");
			sprintf(sql, "%s%d", sql, load.index * 4);
			//strcat(sql, (itoa)(load.index * 4));
			strcat(sql, ",4;");
			//cout << sql << endl;
			int row = 0, col = 0;
			char** qres;
			int res = ptr->getDataSql(sql, qres, row, col);
			if (res == 0)
			{
				if (row == 0)
				{
					feedback.businesstype = 6;
					feedback.businesslen = 0;
					feedback.flag = 1;

				}
				else
				{
					feedback.businesstype = 6;
					feedback.businesslen = sizeof(CARIN) * 4;
					feedback.flag = 1;
					for (int j = 1; j <= row; j++)
					{
						int i = j - 1;
						carin[i].imgid = atoi((qres[j * col + 0]));

						strcpy(carin[i].carid, (qres[j * col + 1]));
						strcpy(carin[i].intime, (qres[j * col + 2]));
						strcpy(carin[i].location, (qres[j * col + 3]));
						strcpy(carin[i].imgpath, (qres[j * col + 4]));

					}
				}
				
			}
			else
			{
				feedback.businesstype = 6;
				feedback.businesslen = 0;
				feedback.flag = 0;
			}
		}
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &carin, sizeof(CARIN) * 4);
		
		behindserver->writedata(this->buf1);
	}
	else if (type == 7)
	{
		cout << "查看入场车辆具体信息" << endl;
		bzero(&carin, sizeof(carin));
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&carin1, data + sizeof(acceptfd), sizeof(CARIN));
		strcpy(log.time, time);
		strcpy(log.type, "查看入场车辆具体信息");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql[1024] = { 0 };
			//去数据库里面--用到我们的数据库单例

			strcat(sql, "select *from table_carin where carid=");
			strcat(sql, "'");
			strcat(sql, carin1.carid);
			strcat(sql, "';");
			char** qres;
			int row = 0, col = 0;
			int res = ptr->getDataSql(sql, qres, row, col);
			if (res == 0)
			{
				carin1.imgid = atoi((qres[col + 0]));
				strcpy(carin1.carid, (qres[col + 1]));
				strcpy(carin1.intime, (qres[col + 2]));
				strcpy(carin1.location, (qres[col + 3]));
				strcpy(carin1.imgpath, (qres[col + 4]));
				feedback.businesstype = 7;
				feedback.businesslen = sizeof(CARIN);
				feedback.flag = 1;
			}
		}
		else
		{
			feedback.businesstype = 7;
			feedback.businesslen = 0;
			feedback.flag = 0;
		}
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &carin1, sizeof(CARIN));
		behindserver->writedata(this->buf1);
	}
	else if (type == 8)
	{
		cout << "抓拍出场车牌" << endl;
		cout << "抓拍出场车牌" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&carout, data + sizeof(acceptfd), sizeof(CAROUT));
		strcpy(log.time, time);
		strcpy(log.type, "抓拍出场车牌");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql[1024] = { 0 };
			//去数据库里面--用到我们的数据库单例

			strcat(sql, "select *from table_carin where carid=");
			strcat(sql, "'");
			strcat(sql, carout.carid);
			strcat(sql, "';");
			char** qres;
			int row = 0, col = 0;
			int res = ptr->getDataSql(sql, qres, row, col);
			if (res == 0)
			{
				if (row == 0)
				{
					feedback.businesstype = 8;
					feedback.businesslen = 0;
					feedback.flag = 0;
					bzero(&buf1, sizeof(buf1));
					memcpy(buf1, &acceptfd, sizeof(acceptfd));
					memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
				}
				else
				{
					strcpy(carout.carid, (qres[col + 1]));
					strcpy(carout.intime, (qres[col + 2]));
					strcpy(carout.inimagepath, (qres[col + 4]));
					feedback.businesstype = 8;
					feedback.businesslen = sizeof(CAROUT);
					feedback.flag = 1;
					bzero(&buf1, sizeof(buf1));
					memcpy(buf1, &acceptfd, sizeof(acceptfd));
					memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
					memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &carout, sizeof(CAROUT));
					behindserver->writedata(this->buf1);
				}
				

			}
		}
		else
		{
			feedback.businesstype = 8;
			feedback.businesslen = 0;
			feedback.flag = 0;
			bzero(&buf1, sizeof(buf1));
			memcpy(buf1, &acceptfd, sizeof(acceptfd));
			memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		}
		
	}
	else if (type == 9)
	{
		cout << "放行车辆" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&carout, data + sizeof(acceptfd), sizeof(CAROUT));
		strcpy(log.time, time);
		strcpy(log.type, "放行车辆");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			int res = ptrol->addtocarout(carout);
			if (res == -1)
			{
				perror("insert fail");
				feedback.businesstype = 9;
				feedback.businesslen = 0;
				feedback.flag = 0;

			}
			else
			{
				feedback.businesstype = 9;
				feedback.businesslen = sizeof(carout);
				feedback.flag = 1;
			}
			

		}
		else
		{
			feedback.businesstype = 9;
			feedback.businesslen = 0;
			feedback.flag = 0;
			
		}
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		behindserver->writedata(this->buf1);
	}
	else if (type == 10)
	{
		cout << "获取停车场信息" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		strcpy(log.time, time);
		strcpy(log.type, "获取停车场信息");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			int res = ptrol->findcarnumber();
			if (res == -1)
			{
				perror("insert fail");
				feedback.businesstype = 10;
				feedback.businesslen = 0;
				feedback.flag = 0;
			}
			else
			{
				feedback.businesstype = 10;
				feedback.businesslen = sizeof(partinfo);
				feedback.flag = 1;
				partinfo.occupy = res;
				partinfo.leisure = 1000 - res;

			}
			
		}
		else
		{
			feedback.businesstype = 10;
			feedback.businesslen = 0;
			feedback.flag = 0;
			
		}
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		memcpy(buf1 + sizeof(acceptfd) + sizeof(feedback), &partinfo, sizeof(PARTINFO));
		behindserver->writedata(this->buf1);
	}
	else if (type == 11)//视频信息获取
	{
		cout << "保存视频信息" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&videoinfo, data + sizeof(acceptfd), sizeof(VIDEOINFO));
		strcpy(log.time, time);
		strcpy(log.type, "保存视频信息");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			int res1 = ptrol->videoinfoadd(videoinfo);
			if (res1 == -1)
			{
				perror("insert fail");
				feedback.businesstype = 11;
				feedback.businesslen = 0;
				feedback.flag = 0;
			}
			else
			{
				feedback.businesstype = 11;
				feedback.businesslen = sizeof(VIDEOINFO);
				feedback.flag = 1;
			}
		}
		else
		{
			feedback.businesstype = 11;
			feedback.businesslen = 0;
			feedback.flag = 0;
		}
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		behindserver->writedata(this->buf1);
	}
	else if (type == 12)//获取月
	{
		cout << "获取月份" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		strcpy(log.time, time);
		strcpy(log.type, "获取已有视频的时间（月）");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			
			char sql[1024] = ("select distinct month from table_video;");
			
			char **qres;
			int row,col = 0;
			int res = ptr->getDataSql(sql, qres, row, col);
			INQUIRE inquire[row];
			if (res == 0)
			{
				if (row == 0)
				{
					feedback.businesstype = 12;
					feedback.businesslen = 0;
					feedback.flag = 1;
					bzero(&buf1, sizeof(buf1));
					memcpy(buf1, &acceptfd, sizeof(acceptfd));
					memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
					memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &inquire, sizeof(inquire) * row);
					
				}
				else
				{
					for (int j = 1; j <= row; j++)
					{
						int i = j - 1;


						strcpy(inquire[i].month, (qres[j * col ]));

						feedback.businesstype = 12;
						feedback.businesslen = row * sizeof(inquire);
						feedback.flag = 1;
						
					}
				}
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &acceptfd, sizeof(acceptfd));
				memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &inquire, sizeof(inquire)* row);
			}
		}
		else
		{
			feedback.businesstype = 12;
			feedback.businesslen = 0;
			feedback.flag = 0;
			bzero(&buf1, sizeof(buf1));
			memcpy(buf1, &acceptfd, sizeof(acceptfd));
			memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		}
		behindserver->writedata(this->buf1);
	}
	else if (type == 13)//获取日期
	{
		cout << "获取具体日期" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&inquire, data + sizeof(acceptfd), sizeof(INQUIRE));
		strcpy(log.time, time);
		strcpy(log.type, "获取已有视频的时间（具体日）");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql[1024] = { 0 };
			//cout << "前置发来的月数是" << inquire.month << endl;
			sprintf(sql, "%s%s%s", "select distinct data from table_video where month='", inquire.month ,"';");
			//cout << sql << endl;
			char** qres;
			int row, col = 0;
			int res = ptr->getDataSql(sql, qres, row, col);
			INQUIRE inquire[row];
			if (res == 0)
			{
				if (row == 0)
				{
					feedback.businesstype = 13;
					feedback.businesslen = 0;
					feedback.flag = 1;
					bzero(&buf1, sizeof(buf1));
					memcpy(buf1, &acceptfd, sizeof(acceptfd));
					memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
					memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &inquire, sizeof(INQUIRE) * row);

				}
				else
				{
					for (int j = 1; j <= row; j++)
					{
						int i = j - 1;
						strcpy(inquire[i].date, (qres[j * col ]));
						feedback.businesstype = 13;
						feedback.businesslen = row * sizeof(inquire);
						feedback.flag = 1;
						
					}
				}
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &acceptfd, sizeof(acceptfd));
				memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &inquire, sizeof(INQUIRE)* row);
			}
		}
		else
		{
			feedback.businesstype = 13;
			feedback.businesslen = 0;
			feedback.flag = 0;
			bzero(&buf1, sizeof(buf1));
			memcpy(buf1, &acceptfd, sizeof(acceptfd));
			memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		}
		behindserver->writedata(this->buf1);
	}
	else if (type == 14)//按月查询
	{
		cout << "按月份查询" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&inquire, data + sizeof(acceptfd), sizeof(INQUIRE));
		strcpy(log.time, time);
		strcpy(log.type, "按月份查询");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql[1024] = { 0 };
			sprintf(sql, "%s%s%s", "select *from table_video where month='", inquire.month, "' order by videoid desc limit 0, 4;");
		//	cout << sql << endl;
			char** qres;
			int row, col = 0;
			int res = ptr->getDataSql(sql, qres, row, col);
			INQUIRE inquire[row];
			if (res == 0)
			{
				if (row == 0)
				{
					feedback.businesstype = 14;
					feedback.businesslen = 0;
					feedback.flag = 1;
					

				}
				else
				{
					for (int j = 1; j <= row; j++)
					{
						int i = j - 1;
						strcpy(videoinfo1[i].videoname, (qres[j * col+1]));
						videoinfo1[i].video_count = strtol((qres[j * col + 2]), NULL, 10);
						videoinfo1[i].video_num = strtol((qres[j * col + 3]), NULL, 10);
						strcpy(videoinfo1[i].video_path, (qres[j * col+4]));
						strcpy(videoinfo1[i].picutre_path, (qres[j * col+5]));
						strcpy(videoinfo1[i].month, (qres[j * col+6]));
						strcpy(videoinfo1[i].date, (qres[j * col+7]));

						feedback.businesstype = 14;
						feedback.businesslen = 4 * sizeof(VIDEOINFO);
						feedback.flag = 1;
						
					}
				}
			}
		}
		else
		{
			feedback.businesstype = 14;
			feedback.businesslen = 0;
			feedback.flag = 0;
			
		}
		
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &videoinfo1, sizeof(VIDEOINFO) * 4);

		behindserver->writedata(this->buf1);
	}
	else if (type == 15)//按日查询
	{
		cout << "按日期查询" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&inquire, data + sizeof(acceptfd), sizeof(INQUIRE));
		strcpy(log.time, time);
		strcpy(log.type, "按日期查询");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql[1024] = { 0 };
			sprintf(sql, "%s%s%s%s%s", "select *from table_video where month='", inquire.month, "' and data='",inquire.date,"' order by videoid desc limit 0,4;");
		//	cout << sql << endl;
			char** qres;
			int row, col = 0;
			int res = ptr->getDataSql(sql, qres, row, col);
			INQUIRE inquire[row];
			if (res == 0)
			{
				if (row == 0)
				{
					feedback.businesstype = 15;
					feedback.businesslen = 0;
					feedback.flag = 1;
					

				}
				else
				{
					for (int j = 1; j <= row; j++)
					{
						int i = j - 1;
						strcpy(videoinfo1[i].videoname, (qres[j * col + 1]));
						videoinfo1[i].video_count = strtol((qres[j * col + 2]), NULL, 10);
						videoinfo1[i].video_num = strtol((qres[j * col + 3]), NULL, 10);
						strcpy(videoinfo1[i].video_path, (qres[j * col + 4]));
						strcpy(videoinfo1[i].picutre_path, (qres[j * col + 5]));
						strcpy(videoinfo1[i].month, (qres[j * col + 6]));
						strcpy(videoinfo1[i].date, (qres[j * col + 7]));

						feedback.businesstype = 15;
						feedback.businesslen = 4 * sizeof(VIDEOINFO);
						feedback.flag = 1;
						
					}
				}
			}
		}
		else
		{
			feedback.businesstype = 15;
			feedback.businesslen = 0;
			feedback.flag = 0;
			
		}
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &videoinfo1, sizeof(VIDEOINFO) * 4);
		behindserver->writedata(this->buf1);
	}
	else if (type == 16)//打开视频
	{
		cout << "获取需打开视频的信息" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&videoinfo, data + sizeof(acceptfd), sizeof(VIDEOINFO));
		strcpy(log.time, time);
		strcpy(log.type, "打开视频");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql[1024] = { 0 };
			//char sql[1024] = ("select distinct data from table_video where month='");
			sprintf(sql, "%s%s%s", "select *from table_video where videoname='", videoinfo.videoname, "';");
		//	cout << sql << endl;
			char** qres;
			int row, col = 0;
			int res = ptr->getDataSql(sql, qres, row, col);
			INQUIRE inquire[row];
			if (res == 0)
			{
				if (row == 0)
				{
					feedback.businesstype = 16;
					feedback.businesslen = 0;
					feedback.flag = 1;
					

				}
				else
				{

					strcpy(videoinfo.videoname, (qres[ col+1]));
					videoinfo.video_count = strtol((qres[col + 2]), NULL, 10);
					videoinfo.video_num = strtol((qres[ col + 3]), NULL, 10);
					strcpy(videoinfo.video_path, (qres[ col + 4]));
					strcpy(videoinfo.picutre_path, (qres[ col + 5]));
					strcpy(videoinfo.month, (qres[ col + 6]));
					strcpy(videoinfo.date, (qres[ col + 7]));

					feedback.businesstype = 16;
					feedback.businesslen =  sizeof(VIDEOINFO);
					feedback.flag = 1;
					
				}
			}
		}
		else
		{
			feedback.businesstype = 16;
			feedback.businesslen = 0;
			feedback.flag = 0;
			
		}

		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &videoinfo, sizeof(VIDEOINFO));
		behindserver->writedata(this->buf1);
	}
	else if (type == 17)//按月翻页
	{
		cout << "按月份查询的翻页" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&inquire, data + sizeof(acceptfd), sizeof(INQUIRE));
		strcpy(log.time, time);
		strcpy(log.type, "按月翻页");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql[1024] = { 0 };
			//char sql[1024] = ("select distinct data from table_video where month='");//
			sprintf(sql, "%s%s%s%d%s", "select *from table_video where month='", inquire.month, "' order by videoid desc limit ",4*(inquire.index),", 4; ");
		//	cout << sql << endl;
			char** qres;
			int row, col = 0;
			int res = ptr->getDataSql(sql, qres, row, col);
			INQUIRE inquire[row];
			if (res == 0)
			{
				if (row == 0)
				{
					feedback.businesstype = 17;
					feedback.businesslen = 0;
					feedback.flag = 1;
					

				}
				else
				{
					for (int j = 1; j <= row; j++)
					{
						int i = j - 1;
						strcpy(videoinfo1[i].videoname, (qres[j * col + 1]));
						videoinfo1[i].video_count = strtol((qres[j * col + 2]), NULL, 10);
						videoinfo1[i].video_num = strtol((qres[j * col + 3]), NULL, 10);
						strcpy(videoinfo1[i].video_path, (qres[j * col + 4]));
						strcpy(videoinfo1[i].picutre_path, (qres[j * col + 5]));
						strcpy(videoinfo1[i].month, (qres[j * col + 6]));
						strcpy(videoinfo1[i].date, (qres[j * col + 7]));

						feedback.businesstype = 17;
						feedback.businesslen = 4 * sizeof(VIDEOINFO);
						feedback.flag = 1;
						
					}
				}
			}
		}
		else
		{
			feedback.businesstype = 17;
			feedback.businesslen = 0;
			feedback.flag = 0;
			
		}

		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &videoinfo1, sizeof(VIDEOINFO) * 4);
		behindserver->writedata(this->buf1);
	}
	else if (type == 18)//按日翻页
	{
		cout << "按日期查询的翻页" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&inquire, data + sizeof(acceptfd), sizeof(INQUIRE));
		strcpy(log.time, time);
		strcpy(log.type, "按日翻页");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql[1024] = { 0 };
			//char sql[1024] = ("select distinct data from table_video where month='");
			sprintf(sql, "%s%s%s%s%s%s%d%s", "select *from table_video where month='", inquire.month, "' and data='", inquire.date, "' order by videoid desc limit ", 4 * (inquire.index), ", 4; ");
		//	cout << sql << endl;
			char** qres;
			int row, col = 0;
			int res = ptr->getDataSql(sql, qres, row, col);
			INQUIRE inquire[row];
			if (res == 0)
			{
				if (row == 0)
				{
					feedback.businesstype = 18;
					feedback.businesslen = 0;
					feedback.flag = 1;
					

				}
				else
				{
					for (int j = 1; j <= row; j++)
					{
						int i = j - 1;
						strcpy(videoinfo1[i].videoname, (qres[j * col+1]));
						videoinfo1[i].video_count = strtol((qres[j * col + 2]), NULL, 10);
						videoinfo1[i].video_num = strtol((qres[j * col + 3]), NULL, 10);
						strcpy(videoinfo1[i].video_path, (qres[j * col + 4]));
						strcpy(videoinfo1[i].picutre_path, (qres[j * col + 5]));
						strcpy(videoinfo1[i].month, (qres[j * col + 6]));
						strcpy(videoinfo1[i].date, (qres[j * col + 7]));

						feedback.businesstype = 18;
						feedback.businesslen = 4 * sizeof(VIDEOINFO);
						feedback.flag = 1;
						
					}
				}
			}
		}
		else
		{
			feedback.businesstype = 18;
			feedback.businesslen = 0;
			feedback.flag = 0;
			
		}
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &videoinfo1, sizeof(VIDEOINFO) * 4);
		behindserver->writedata(this->buf1);
	}
	else if (type == 19)//
	{
		cout << "获取上次视频播放帧数" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&videoinfo, data + sizeof(acceptfd), sizeof(VIDEOINFO));
		strcpy(log.time, time);
		strcpy(log.type, "视频播放到一半关闭");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
	//	cout << videoinfo.videoname << endl;
		if (res1 == 0)
		{
			int res1 = ptrol->revisevideoinfo(videoinfo);
			if (res1 == -1)
			{
				perror("insert fail");
				feedback.businesstype = 19;
				feedback.businesslen = 0;
				feedback.flag = 0;
			}
			else
			{
				feedback.businesstype = 19;
				feedback.businesslen = 0;
				feedback.flag = 1;
			}
		}
		else
		{
			feedback.businesstype = 19;
			feedback.businesslen = 0;
			feedback.flag = 0;
		}
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		behindserver->writedata(this->buf1);
	}
	else if (type == 20)
	{
		cout << "文件传输" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&picture, data + sizeof(acceptfd), sizeof(PICTURE));
		char folderpath[20] = {0};
		string folderPath =picture.name;
		string command;
		command = "mkdir -p " + folderPath;
		system(command.c_str());
		strcpy(folderpath, folderPath.c_str());
		int num = get_file_num(folderpath);
		string name = "./picture/" + folderPath +".jpg";
		char str[40] = { 0 };
		sprintf(str, "%s%s%s%d%s", "./",folderpath, "/", picture.id, ".temp");
		//cout << str<<"----------" << endl;
		umask(0);//权限掩码  默认022
		int wfd = 0;
		int res = 0;
		
		wfd = open(str,O_CREAT | O_WRONLY, 0777);//读取的时候就不需要创建只需要使用O_RDONLY
		//fd=3是因为0,1,2都是标准输入，输出，错误，自己写的就会是3
		if (wfd < 0)
		{
			perror("open file error");
			feedback.businesstype = 20;
			feedback.businesslen = 0;
			feedback.flag = 0;
		}
		else
		{
			write(wfd, picture.content, picture.newsize);
			close(wfd);
			feedback.businesstype = 20;
			feedback.businesslen = 0;
			feedback.flag = 1;
		}
		cout << "文件个数" << num << endl;
		cout << "破碎文件总个数" << picture.number << endl;
		cout << "当前文件id" << picture.id << endl;
		if (num == picture.number-1 && picture.id == picture.number)
		{
			cout << "复制完全成功" << endl;
			cout << name << endl;
			cout << folderPath << endl;
			string name1 = "./" + folderPath;
			int fd = 0;
			int res = 0;
			fd = open(name.c_str(), O_CREAT | O_WRONLY, 0777);
			DIR* dir = NULL;
			int status = 0;
			struct dirent* pdir = NULL;
			int count = 0;
			int i = 0;
			char path[20] = { 0 };
			strcpy(path, name1.c_str());
			while (1)
			{
				if (i < picture.number)
				{
					
					char str[40] = { 0 };
					
					sprintf(str, "%s%s%d%s", path, +"/", ++i , ".temp");
					cout << str << endl;
					struct stat   buffer;
					//读取的时候就不需要创建只需要使用O_RDONLY
					char buf[20] = { 0 };
					umask(0);//权限掩码  默认022
					int wfd = 0;
					int res = 0;
					wfd = open(str, O_RDONLY, 0777);//读取的时候就不需要创建只需要使用O_RDONLY
					//fd=3是因为0,1,2都是标准输入，输出，错误，自己写的就会是3
					if (fd != -1)
					{
						while ((res = read(wfd, buf, sizeof(buf))) != 0)
						{
							//cout << "res=" << res << endl;
							write(fd, buf, res);
							
						}
						
						close(wfd);
						
					}
					else
					{
						perror("open error");
					}


				}
				else
				{
					break;
				}

			}
			close(fd);
			char str1[40] = { 0 };
			sprintf(str1, "%s%s", path, +"/");
			rm_dir(str1);

		}
		if (picture.id == picture.number)
		{
			if (num == picture.number - 1)
			{
				feedback.businesstype = 20;
				feedback.businesslen = 0;
				feedback.flag = 1;
			}
			else
			{
				feedback.businesstype = 20;
				feedback.businesslen = 0;
				feedback.flag = 0;
			}
		}
		
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		behindserver->writedata(this->buf1);
	}
	else if (type == 21)//查询
	{
		cout << "车辆信息查询" << endl;
		bzero(carout1, sizeof(CAROUT) * 4); 
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&querycar, data + sizeof(acceptfd), sizeof(QUERYCAR));
		strcpy(log.time, time);
		strcpy(log.type, "车辆信息查询");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql[1024] = { 0 };
			if (strlen(querycar.carid) != 0 )
			{
				if (strlen(querycar.carintime) != 0 )
				{
					if (strlen(querycar.caroutime) != 0)
					{
						sprintf(sql, "%s%s%s%s%s%s%s", "select *from table_carout where carid='", querycar.carid, "' and intime>='", querycar.carintime, "' and outtime<='", querycar.caroutime, "' limit 0,4;");
					}
					else if (strlen(querycar.caroutime) == 0)
					{
						sprintf(sql, "%s%s%s%s%s", "select *from table_carout where carid='", querycar.carid, "' and intime>='", querycar.carintime, "' limit 0,4;");

					}
				}
				else if(strlen(querycar.carintime) == 0)
				{
					if (strlen(querycar.caroutime) != 0)
					{
						sprintf(sql, "%s%s%s%s%s", "select *from table_carout where carid='", querycar.carid, "' and outtime<='", querycar.caroutime, "' limit 0,4;");
					}
					else if (strlen(querycar.caroutime) == 0)
					{
						sprintf(sql, "%s%s%s", "select *from table_carout where carid='", querycar.carid, "' limit 0,4;");

					}
				}
			}
			if (strlen(querycar.carid) == 0)
			{
				if (strlen(querycar.carintime) != 0)
				{
					if (strlen(querycar.caroutime) != 0)
					{
						sprintf(sql, "%s%s%s%s%s", "select *from table_carout where intime>='", querycar.carintime, "' and outtime<='", querycar.caroutime, "' limit 0,4;");
					}
					else if (strlen(querycar.caroutime) == 0)
					{
						sprintf(sql, "%s%s%s", "select *from table_carout where intime>='", querycar.carintime, "' limit 0,4;");

					}
				}
				else if (strlen(querycar.carintime) == 0)
				{
					if (strlen(querycar.caroutime) != 0)
					{
						sprintf(sql, "%s%s%s", "select *from table_carout where outtime<='", querycar.caroutime, "' limit 0,4;");
					}
					else if (strlen(querycar.caroutime) == 0)
					{
						sprintf(sql, "%s", "select *from table_carout order by videoid desc limit 0,4;");

					}
				}
			}
			
		//	cout << sql << endl;
			char** qres;
			int row, col = 0;
			int res = ptr->getDataSql(sql, qres, row, col);
			INQUIRE inquire[row];
			if (res == 0)
			{
				if (row == 0)
				{
					feedback.businesstype = 21;
					feedback.businesslen = 0;
					feedback.flag = 1;
					

				}
				else
				{
					for (int j = 1; j <=row; j++)
					{
						int i = j - 1;
						strcpy(carout1[i].carid, (qres[j * col]));
						
						strcpy(carout1[i].intime, (qres[j * col + 1]));
						strcpy(carout1[i].outtime, (qres[j * col + 2]));
						strcpy(carout1[i].parktime, (qres[j * col + 3]));
						strcpy(carout1[i].inimagepath, (qres[j * col +4]));
						strcpy(carout1[i].outimagepath, (qres[j * col + 5]));
						carout1[i].money = strtol((qres[j * col + 6]), NULL, 10);
						carout1[i].type = strtol((qres[j * col + 7]), NULL, 10);
						feedback.businesstype = 21;
						feedback.businesslen = 4 * sizeof(CAROUT);
						feedback.flag = 1;
						
					}
				}
			}
		}
		else
		{
			feedback.businesstype = 21;
			feedback.businesslen = 0;
			feedback.flag = 0;
			
		}
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &carout1, sizeof(CAROUT) * 4);
		behindserver->writedata(this->buf1);
	}
	else if (type == 22)//查询
	{
		cout << "车辆信息翻页" << endl;
		bzero(carout1, sizeof(CAROUT) * 4);
		memcpy(&acceptfd, data, sizeof(acceptfd));
		memcpy(&querycar, data + sizeof(acceptfd), sizeof(QUERYCAR));
		strcpy(log.time, time);
		strcpy(log.type, "视频懒加载");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql[1024] = { 0 };
			if (strlen(querycar.carid) != 0)
			{
				if (strlen(querycar.carintime) != 0)
				{
					if (strlen(querycar.caroutime) != 0)
					{
						sprintf(sql, "%s%s%s%s%s%s%s%d%s", "select *from table_carout where carid='", querycar.carid, "' and intime>='", querycar.carintime, "' and outtime<='", querycar.caroutime, "' limit ", 4 * (querycar.index), ", 4; ");
					}
					else if (strlen(querycar.caroutime) == 0)
					{
						sprintf(sql, "%s%s%s%s%s%d%s", "select *from table_carout where carid='", querycar.carid, "' and intime>='", querycar.carintime, "' limit ", 4 * (querycar.index), ", 4; ");

					}
				}
				else if (strlen(querycar.carintime) == 0)
				{
					if (strlen(querycar.caroutime) != 0)
					{
						sprintf(sql, "%s%s%s%s%s%d%s", "select *from table_carout where carid='", querycar.carid, "' and outtime<='", querycar.caroutime, "' limit ", 4 * (querycar.index), ", 4; ");
					}
					else if (strlen(querycar.caroutime) == 0)
					{
						sprintf(sql, "%s%s%s%d%s", "select *from table_carout where carid='", querycar.carid, "' limit ", 4 * (querycar.index), ", 4; ");

					}
				}
			}
			if (strlen(querycar.carid) == 0)
			{
				if (strlen(querycar.carintime) != 0)
				{
					if (strlen(querycar.caroutime) != 0)
					{
						sprintf(sql, "%s%s%s%s%s%s%s", "select *from table_carout where intime>='", querycar.carintime, "' and outtime<='", querycar.caroutime, "' limit ", 4 * (querycar.index), ", 4; ");
					}
					else if (strlen(querycar.caroutime) == 0)
					{
						sprintf(sql, "%s%s%s%s%s%s%s", "select *from table_carout where intime>='", querycar.carintime, "' limit ", 4 * (querycar.index), ", 4; ");

					}
				}
				else if (strlen(querycar.carintime) == 0)
				{
					if (strlen(querycar.caroutime) != 0)
					{
						sprintf(sql, "%s%s%s%s%s%s%s", "select *from table_carout where outtime<='", querycar.caroutime, "' limit ", 4 * (querycar.index), ", 4; ");
					}
					else if (strlen(querycar.caroutime) == 0)
					{
						sprintf(sql, "%s%s%s%s%s%s%s", "select *from table_carout limit ", 4 * (querycar.index), ", 4; ");

					}
				}
			}
			
		//	cout << sql << endl;
			char** qres;
			int row, col = 0;
			int res = ptr->getDataSql(sql, qres, row, col);
			INQUIRE inquire[row];
			if (res == 0)
			{
				if (row == 0)
				{
					feedback.businesstype = 22;
					feedback.businesslen = 0;
					feedback.flag = 1;
					

				}
				else
				{
					for (int j = 1; j <= row; j++)
					{
						int i = j - 1;
						strcpy(carout1[i].carid, (qres[j * col]));

						strcpy(carout1[i].intime, (qres[j * col + 1]));
						strcpy(carout1[i].outtime, (qres[j * col + 2]));
						strcpy(carout1[i].parktime, (qres[j * col + 3]));
						strcpy(carout1[i].inimagepath, (qres[j * col + 4]));
						strcpy(carout1[i].outimagepath, (qres[j * col + 5]));
						carout1[i].money = strtol((qres[j * col + 6]), NULL, 10);
						carout1[i].type = strtol((qres[j * col + 7]), NULL, 10);

						feedback.businesstype = 22;
						feedback.businesslen = 4 * sizeof(CAROUT);
						feedback.flag = 1;
						
					}
				}
			}
		}
		else
		{
			feedback.businesstype = 22;
			feedback.businesslen = 0;
			feedback.flag = 0;
			
		}
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		memcpy(buf1 + sizeof(acceptfd) + sizeof(FEEDBACK), &carout1, sizeof(CAROUT) * 4);
		behindserver->writedata(this->buf1);
	}
	else if(type==23)
	{
		cout << "客户端下线" << endl;
		memcpy(&acceptfd, data, sizeof(acceptfd));
		strcpy(log.time, time);
		strcpy(log.type, "用户下线");
		int res1 = ptrol->logsave(acceptfd.acceptfd, log);
		if (res1 == 0)
		{
			char sql1[1024] = { 0 };
			//去数据库里面--用到我们的数据库单例
			sprintf(sql1, "%s%d%s", "Delete from table_client where acceptfd=", acceptfd.acceptfd, ";");
			cout << sql1 << endl;
			int res = ptr->noResSql(sql1);
			if (res == 0)
			{
				feedback.businesstype = 23;
				feedback.businesslen = 0;
				feedback.flag = 1;
			}
			else
			{
				feedback.businesstype = 23;
				feedback.businesslen = 0;
				feedback.flag = 0;
			}
		}
		else
		{
			feedback.businesstype = 23;
			feedback.businesslen = 0;
			feedback.flag = 0;
		}
		bzero(&buf1, sizeof(buf1));
		memcpy(buf1, &acceptfd, sizeof(acceptfd));
		memcpy(buf1 + sizeof(acceptfd), &feedback, sizeof(FEEDBACK));
		behindserver->writedata(this->buf1);
	}
}


