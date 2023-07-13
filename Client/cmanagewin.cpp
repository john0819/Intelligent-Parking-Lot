#include "cmanagewin.h"

CManageWin *CManageWin::cmanager = nullptr;

CManageWin *CManageWin::getInstance()
{
    if(CManageWin::cmanager == nullptr)
    {
        CManageWin::cmanager = new CManageWin();
    }
    return CManageWin::cmanager;
}
/*
CSetWin *CManageWin::setwin()
{
    return this->setinWin;
}

Widget *CManageWin::widwin()
{
    return this->widinWin;
}

CEnterWin *CManageWin::enterwin()
{
    return this->enterinWin;
}

CRegWin *CManageWin::regwin()
{
    return this->reginWin;
}
*/
CVideoPlayer *CManageWin::videoplayer()
{
    return this->videoWin;
}

CSearchWin *CManageWin::searchwin()
{
    return this->searchinWin;
}

CCarInWin *CManageWin::carinwin()
{
    return this->carinWin;
}

CCarOutWin *CManageWin::caroutwin()
{
    return this->caroutWin;
}

ParkingVCRWin *CManageWin::vcrwin()
{
    return this->vcrinWin;
}

VCRReviewWin *CManageWin::reviewwin()
{
    return this->reviewinWin;
}

CManageWin::CManageWin()
{
//    this->widinWin = new Widget();
//    this->setinWin = new CSetWin();
//    this->enterinWin = new CEnterWin();
//    this->reginWin = new CRegWin();
    this->videoWin = new CVideoPlayer();
    this->searchinWin = new CSearchWin();
    this->carinWin = new CCarInWin();
    this->caroutWin = new CCarOutWin();
    this->vcrinWin = new ParkingVCRWin();
    this->reviewinWin = new VCRReviewWin();
}
