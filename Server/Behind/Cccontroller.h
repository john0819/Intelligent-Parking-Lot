
#include<string.h>
#include"Mode.h"
#include"protocol.h"


//控制器相当于一个中转站：类似于我们的代理商  腾讯qq端服务器
class Cccontroller
{
public:
    Cccontroller();
    //接收登录那边用户的查询请求
    int searchUserByNameAndPwd(char* name, char* pwd);
    int userenroll(REGISTER &enroll);
    int usersearch(char* name);
    int carindeposit(CARIN &carin);
    int carinrevise(UPDATE& newcar);
    int addtocarout(CAROUT& carout);
    int videoinfoadd(VIDEOINFO& videoinfo);
    int findcarnumber();
    int saveacceptfdAnduserid(int acceptfd, char* userid);
    int logsave(int acceptfd, LOG& log);
    int loginAndregisters(LOG& log);
    //因为模型是要通过控制器委托来处理事情的
    int revisevideoinfo(VIDEOINFO& videoinfo);
private:
    cusermode* model;
};

