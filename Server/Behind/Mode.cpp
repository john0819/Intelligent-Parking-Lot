#include "Mode.h"

cusermode* cusermode::model = nullptr;

cusermode::cusermode()
{
    //获取到唯一的数据库的单例对象
    ptr = Cdatasqlite::getIntence();
}
int cusermode::findcarnumber()
{
    char sql[1024] = {"select *from table_carin"};
    char** qres;
    int row = 0, col = 0;
    int res = ptr->getDataSql(sql, qres, row, col);
    if (res == 0)
    {
        
            return row;
        

    }
    else
    {
        return -1;
    }
}
int cusermode::videoinfoadd(VIDEOINFO& videoinfo)
{
    char sql[1024] = { 0 };
    //去数据库里面--用到我们的数据库单例
   
    sprintf(sql, "INSERT INTO table_video(videoname,framenumber,lastframenum,videopath,fristimgpath,month,data)values('%s',%d,%d,'%s','%s','%s','%s');", 
        videoinfo.videoname, videoinfo.video_count, videoinfo.video_num, videoinfo.video_path, videoinfo.picutre_path, videoinfo.month, videoinfo.date);

   // cout << sql << endl;
    int res = ptr->noResSql(sql);
    if (res == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
int cusermode::saveacceptfdAnduserid(int acceptfd, char* userid)
{
    char sql[1024] = { 0 };
    //去数据库里面--用到我们的数据库单例
    sprintf(sql, "INSERT INTO table_client(acceptfd,userid)values(%d,'%s');", acceptfd, userid);

    cout << sql << endl;
    int res = ptr->noResSql(sql);
    if (res == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }

}
int cusermode::logsave(int acceptfd,LOG &log)
{
   
    char sql1[1024] = { 0 };
    //去数据库里面--用到我们的数据库单例
    strcat(sql1, "select *from table_client where acceptfd='");
    sprintf(sql1, "%s%d", sql1, acceptfd);
    strcat(sql1, "';");
    char** qres;
    int row = 0, col = 0;
   // cout << sql1 << endl;
    int res1 = ptr->getDataSql(sql1, qres, row, col);
    if(res1==0)
    {
        char sql[1024] = { 0 };
        strcpy(log.useid, (qres[col + 1]));
        char operate[40] = { 0 };
        strcat(operate, log.useid);
        strcat(operate, log.type);
        strcpy(log.operate, operate);
        fstream fs;
        fs.open("./log.txt", ios::in | ios::out | ios::app);
        fs.seekg(0, ios::end);
        fs << log.useid << " " << log.time << " " << log.operate << endl;
        fs.close();
        //去数据库里面--用到我们的数据库单例
        sprintf(sql, "INSERT INTO table_log(time,userid,type,operate)values('%s','%s','%s','%s');", log.time, log.useid, log.type, log.operate);

       // cout << sql << endl;
        int res = ptr->noResSql(sql);
        if (res == 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
   

}
int cusermode::loginAndregisters(LOG& log)
{
    
    char sql[1024] = { 0 };
    fstream fs;
    fs.open("./log.txt", ios::in | ios::out | ios::app);
    fs.seekg(0, ios::end);
 
    fs << log.useid << " " << log.time << " " << log.operate  << endl;

  
    fs.close();
    //去数据库里面--用到我们的数据库单例
    sprintf(sql, "INSERT INTO table_log(time,userid,type,operate)values('%s','%s','%s','%s');", log.time, log.useid, log.type, log.operate);

   // cout << sql << endl;
    int res = ptr->noResSql(sql);
    if (res == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
    


}
int cusermode::revisevideoinfo(VIDEOINFO& videoinfo)
{
    char sql[1024] = { 0 };
    //去数据库里面--用到我们的数据库单例
    sprintf(sql, "%s%d%s%s%s", "Update table_video set lastframenum=", videoinfo.video_num, " where videoname='", videoinfo.videoname, "';");
 //   cout << sql << endl;
    int res = ptr->noResSql(sql);
    if (res == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
int cusermode::findUserByNameAndPwd(char* name, char* pwd)
{
    char sql[1024] = { 0 };;
    //去数据库里面--用到我们的数据库单例
    
    strcat(sql, "select *from table_user where user_id='");

    strcat(sql, name);
    strcat(sql, "'");
    strcat(sql,"and user_pwd='");
    strcat(sql,pwd);
    strcat(sql, "';");
    char** qres;
    int row = 0, col = 0;
    int res = ptr->getDataSql(sql, qres, row, col);
    if (res == 0)
    {
        if (row == 0)
        {
            return -1;
        }
        else
        {
            return 0;
        }

    }
    
}

int cusermode::userenroll(REGISTER& enroll)
{
    
    char sql[1024] = {0};
    //去数据库里面--用到我们的数据库单例

    strcat(sql, "INSERT INTO table_user values('");
    strcat(sql, enroll.userid);
    strcat(sql, "','");
    strcat(sql, enroll.username);
    strcat(sql, "','");
    strcat(sql, enroll.userpwd);
    strcat(sql, "');");
   // cout << sql << endl;
    int res = ptr->noResSql(sql);
    if (res == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int cusermode::carindeposit(CARIN& carin)
{

    char sql[1024] = { 0 };
    //去数据库里面--用到我们的数据库单例
    sprintf(sql,"INSERT INTO table_carin(carid,intime,location,imgpath)values('%s','%s','%s','%s');", carin.carid, carin.intime, carin.location, carin.imgpath) ;
    
   // cout << sql << endl;
    int res = ptr->noResSql(sql);
    if (res == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
int cusermode::addtocarout(CAROUT& carout)
{
    char sql[1024] = { 0 };
    //去数据库里面--用到我们的数据库单例
    sprintf(sql, "INSERT INTO table_carout(carid,intime,outtime,parktime,inimagepath,outimagepath,money,type)values('%s','%s','%s','%s','%s','%s','%d','%d');", carout.carid, carout.intime, carout.outtime, carout.parktime, carout.inimagepath, carout.outimagepath, carout.money, carout.type);

    cout << sql << endl;
    int res = ptr->noResSql(sql);
    if (res == 0)
    {
        char sql1[1024] = { 0 };
        //去数据库里面--用到我们的数据库单例
       
        strcat(sql1, "Delete from table_carin where carid='"); //222' where carid='2222';
        strcat(sql1, carout.carid);
        strcat(sql1, "';");
        cout << sql1 << endl;
        int res1 = ptr->noResSql(sql1);
        if (res1 == 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

int cusermode::carinrevise(UPDATE& newcar)
{

    char sql[1024] = { 0 };
    //去数据库里面--用到我们的数据库单例

    strcat(sql, "Update table_carin set carid='"); //222' where carid='2222';
    strcat(sql, newcar.newcarid);
    strcat(sql, "' where carid='");
    strcat(sql, newcar.oldcarid);
    strcat(sql, "';");
   // cout << sql << endl;
    int res = ptr->noResSql(sql);
    if (res == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
cusermode* cusermode::getSigModel()
{
    if (cusermode::model == nullptr)//判断相等必须要==不能在这里出问题
    {
        //创建这个对象
        cusermode::model = new cusermode();
    }
    return cusermode::model;

}

int cusermode::usersearch(char* name)
{
    char sql[1024] = { 0 };
    //去数据库里面--用到我们的数据库单例

    strcat(sql, "select *from table_user where user_id=");
    strcat(sql, "'");
    strcat(sql, name);
    strcat(sql, "';");
    char** qres;
    int row = 0, col = 0;
    int res = ptr->getDataSql(sql, qres, row, col);
    if (res == 0)
    {
        if (row == 0)
        {
            return -1;
        }
        else
        {
            return 0;
        }

    }
}
