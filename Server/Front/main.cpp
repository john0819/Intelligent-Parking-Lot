#include<iostream>

using namespace std;
#include"CEpollServer.h"


int main()
{
	CEpollServer* tcp = new CEpollServer(10086);
	tcp->Start();
	return 0;
}