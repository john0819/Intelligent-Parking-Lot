#include "ChildTask.h"
#include"protocol.h"

ChildTask::ChildTask(char* data, int type) :BaseTask(data)
{
	this->type = type;
	frontserver = Frontserver::getIntence();
	bzero(&buf, sizeof(buf));
}

ChildTask::~ChildTask()
{
}

void ChildTask::working()
{
	LOGIN login;
	ACC acceptfd;
	
	if (type == 0)
	{
		
		frontserver->writedata(data);
		
	}
	else if (type == 1)
	{
		bzero(&buf, sizeof(buf));
		memcpy(buf, (frontserver->readata()), sizeof(buf));
		memcpy(&acceptfd, buf, sizeof(acceptfd));
		if (acceptfd.type == 2)
		{

			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{
				memcpy(&logreg, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(REGISTER));
				memcpy(&carin, buf + sizeof(acceptfd) + sizeof(FEEDBACK) + sizeof(REGISTER), sizeof(CARIN) * 4);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK), &logreg, sizeof(REGISTER));
				memcpy(buf1 + sizeof(FEEDBACK) + sizeof(REGISTER), &carin, sizeof(CARIN) * 4);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}


		}
		else if (acceptfd.type == 1)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
		}
		else if (acceptfd.type == 3)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{
				memcpy(&carin, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(CARIN) * 4);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK), &carin, sizeof(CARIN) * 4);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 4)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{
				memcpy(&carin, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(CARIN) * 4);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));

				memcpy(buf1 + sizeof(FEEDBACK), &carin, sizeof(CARIN) * 4);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 5)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{
				memcpy(&carin, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(CARIN) * 4);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));

				memcpy(buf1 + sizeof(FEEDBACK), &carin, sizeof(CARIN) * 4);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 6)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{
				memcpy(&carin, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(CARIN) * 4);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK), &carin, sizeof(CARIN) * 4);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 7)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{
				memcpy(&carin1, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(CARIN));
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK), &carin1, sizeof(CARIN));
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 8)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{
				memcpy(&carout, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(CAROUT));
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));

				memcpy(buf1 + sizeof(FEEDBACK), &carout, sizeof(CAROUT));
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 9)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
		}
		else if (acceptfd.type == 10)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{
				memcpy(&partinfo, buf + sizeof(acceptfd) + sizeof(feedback), sizeof(PARTINFO));
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));

				memcpy(buf1 + sizeof(FEEDBACK), &partinfo, sizeof(PARTINFO));
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 11)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
		}
		else if (acceptfd.type == 12)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{
				int len = (feedback.businesslen) / sizeof(inquire);
				INQUIRE inquire1[len];
				memcpy(&inquire1, buf + sizeof(acceptfd) + sizeof(FEEDBACK) , sizeof(INQUIRE) * len);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK) , &inquire1, sizeof(INQUIRE) * len);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 13)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{
				int len = (feedback.businesslen) / sizeof(inquire);
				INQUIRE inquire1[len];
				memcpy(&inquire1, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(INQUIRE) * len);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK), &inquire1, sizeof(INQUIRE) * len);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 14)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{

				memcpy(&videoinfo, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(VIDEOINFO) * 4);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK), &videoinfo, sizeof(VIDEOINFO) * 4);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 15)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{

				memcpy(&videoinfo, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(VIDEOINFO) * 4);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK), &videoinfo, sizeof(VIDEOINFO) * 4);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 16)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{

				memcpy(&videoinfo1, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(VIDEOINFO));
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK), &videoinfo1, sizeof(VIDEOINFO) );
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 17)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{

				memcpy(&videoinfo, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(VIDEOINFO) * 4);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK), &videoinfo, sizeof(VIDEOINFO) * 4);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 18)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{
				memcpy(&videoinfo, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(VIDEOINFO) * 4);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK), &videoinfo, sizeof(VIDEOINFO) * 4);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 19)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
		}
		else if (acceptfd.type == 20)
		{
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
		}
		else if (acceptfd.type == 21)
		{
			bzero(carout1, sizeof(CAROUT) * 4);
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{

				memcpy(&carout1, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(CAROUT) * 4);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK), &carout1, sizeof(CAROUT) * 4);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
		else if (acceptfd.type == 22)
		{
			bzero(carout1, sizeof(CAROUT) * 4);
			memcpy(&feedback, buf + sizeof(acceptfd), sizeof(feedback));
			if (feedback.flag == 0)
			{
				write(acceptfd.acceptfd, &feedback, sizeof(FEEDBACK));
			}
			else if (feedback.flag == 1)
			{
				memcpy(&carout1, buf + sizeof(acceptfd) + sizeof(FEEDBACK), sizeof(CAROUT) * 4);
				bzero(&buf1, sizeof(buf1));
				memcpy(buf1, &feedback, sizeof(FEEDBACK));
				memcpy(buf1 + sizeof(FEEDBACK), &carout1, sizeof(CAROUT) * 4);
				write(acceptfd.acceptfd, buf1, sizeof(buf1));
			}
		}
	}
}
