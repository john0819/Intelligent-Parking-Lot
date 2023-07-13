
#include<string.h>
#include "Cdatasqlite.h"
#include"protocol.h"
#include <stdio.h>
#include<fstream>
//单例：在项目中创建一个用户模型就够了

class cusermode
{
public:

    //提供一个方法去查询用户表，找到对应的用户信息
    int findUserByNameAndPwd(char* name, char* pwd);
    int userenroll(REGISTER& enroll);
    int usersearch(char* name);
    static cusermode* getSigModel();
    int carindeposit(CARIN& carin);
    int findcarnumber();
    int addtocarout(CAROUT& carout);
    
    int carinrevise(UPDATE& newcar);
    int videoinfoadd(VIDEOINFO& videoinfo);
    int saveacceptfdAnduserid(int acceptfd, char* userid);
    int logsave(int acceptfd, LOG& log);
    int loginAndregisters(LOG& log);
    int revisevideoinfo(VIDEOINFO& videoinfo);
private:
    Cdatasqlite* ptr;
    cusermode();
    static cusermode* model;
};


