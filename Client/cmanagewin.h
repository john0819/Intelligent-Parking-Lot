#ifndef CMANAGEWIN_H
#define CMANAGEWIN_H

//#include <csetwin.h>
//#include <widget.h>
//#include "centerwin.h"
//#include "cregwin.h"
#include "cvideoplayer.h"
#include "csearchwin.h"
#include "ccarinwin.h"
#include "ccaroutwin.h"
#include "parkingvcrwin.h"
#include "vcrreviewwin.h"

//manage all window

class CManageWin
{
public:
    static CManageWin* getInstance();
    static CManageWin* cmanager;
//    CSetWin *setwin();
//    Widget *widwin();
//    CEnterWin *enterwin();
//    CRegWin *regwin();
    CVideoPlayer *videoplayer();
    CSearchWin *searchwin();
    CCarInWin *carinwin();
    CCarOutWin *caroutwin();
    ParkingVCRWin *vcrwin();
    VCRReviewWin *reviewwin();

private:
    CManageWin();

//    CSetWin *setinWin;
//    Widget *widinWin;
//    CEnterWin *enterinWin;
//    CRegWin *reginWin;
    CVideoPlayer *videoWin;
    CSearchWin *searchinWin;
    CCarInWin *carinWin;
    CCarOutWin *caroutWin;
    ParkingVCRWin *vcrinWin;
    VCRReviewWin *reviewinWin;
};

#endif // CMANAGEWIN_H
