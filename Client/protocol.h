#ifndef PROTOCOL_H
#define PROTOCOL_H

/*
 *
业务类型bussinesstype
注册 1
登录 2
车辆入场 3
车辆出场 4
 */
//协议头
typedef struct head
{
    int bussinesstype;//业务类型
    int bussinesslen;//协议体长度
    int CRC; //CRC校验 0
}HEAD;

//服务器回复
typedef struct feedback
{
    int bussinesstype;//业务类型
    int bussinesslen;//协议体长度
    int flag;//结果  注册成功回复 0  失败回复 1
}FEEDBACK;

//注册结构体
typedef struct Register
{
    char username[20];
    char userid[20];
    char userpwd[40];
}REGISTER;

//登录结构体
typedef struct login
{
    char userid[20];
    char userpwd[40];

}LOGIN;

typedef struct carin
{
    char plate[20];
    char time[40];
    char site[20];
    int imageid;
    char filepath[80];
}CARIN;

//车牌号修改结构体
typedef struct updatecar
{
    char first[20];
    char second[20];

}UPDATE;


//车辆出场结构体
typedef struct carout
{
    char plate[20];
    char enter_time[40];
    char out_time[40];
    char duration_time[10];
    char enter_path[80];
    char out_path[80];
    int charge;
    int card; // 是 0 ，否 1

}CAROUT;

//懒加载结构体
typedef struct load
{
    int index;//按下"加载更多"按钮后+1

}LOAD;

typedef struct partinfo
{
    int occupy;//已占用车位
    int leisure;//空闲车位

}PARKINFO;


//视频信息结构体
typedef struct videoinfo
{
    char videoname[40];
    int video_count;
    int video_num;
    char video_path[80];
    char picutre_path[80];
    char month[15]; //视频保存月份(只有月份)
    char date[15]; //视频保存日期（月份和日期）

}VIDEOINFO;

typedef struct searchinfo
{
    int index;
    char month[15]; //视频保存月份(只有月份)
    char date[15]; //视频保存日期（月份和日期）

}SEARCH;


typedef struct picture
{
    int imageid;
    int size;
    char picture_name[20];
    int number;
    int one_size;
    char content[512];

}PICTURE;

typedef struct carsearch
{
    int index;
    char plate[20];
    char in_time[40];
    char out_time[40];
}CSEARCH;


typedef struct carinfo
{
    //序号
    char plate[20];
    char in_time[40];
    char out_time[40];
    char park_time[10];
    char in_path[80];
    char out_path[80];
    int charge;
    int type;
}CINFO;



#endif // PROTOCOL_H
