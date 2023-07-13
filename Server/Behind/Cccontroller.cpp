#include "Cccontroller.h"

Cccontroller::Cccontroller()
{
    model = cusermode::getSigModel();
}

int Cccontroller::searchUserByNameAndPwd(char* name, char* pwd)
{
    //委托
    return model->findUserByNameAndPwd(name, pwd);
}

int Cccontroller::userenroll(REGISTER& enroll)
{
    return model->userenroll(enroll);
}

int Cccontroller::usersearch(char* name)
{
    return model->usersearch(name);
}

int Cccontroller::carindeposit(CARIN& carin)
{
    return model->carindeposit(carin);
}

int Cccontroller::carinrevise(UPDATE& newcar)
{
    return model->carinrevise(newcar);
}

int Cccontroller::addtocarout(CAROUT& carout)
{
    return model->addtocarout(carout);
}

int Cccontroller::videoinfoadd(VIDEOINFO& videoinfo)
{
    return model->videoinfoadd(videoinfo);
}



int Cccontroller::findcarnumber()
{
    return model->findcarnumber();
}

int Cccontroller::saveacceptfdAnduserid(int acceptfd, char* userid)
{
    return model->saveacceptfdAnduserid(acceptfd, userid);
}

int Cccontroller::logsave(int acceptfd, LOG& log)
{
    return model->logsave(acceptfd, log);
}

int Cccontroller::loginAndregisters(LOG& log)
{
    return model->loginAndregisters(log);
}

int Cccontroller::revisevideoinfo(VIDEOINFO& videoinfo)
{
    return model->revisevideoinfo(videoinfo);
}

