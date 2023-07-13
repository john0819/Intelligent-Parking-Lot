#pragma once

//通信协议 TCP\UDP
//自定义通信协议：根据开发业务来制定通信协议
//通信协议最终体：定长协议头+不定长协议体

//协议头
typedef struct head
{
	int bussinesstype;//业务类型
	int bussinesslen;//协议体长度
	int CRC; //CRC校验
}HEAD;

typedef struct feedback
{
	int businesstype;
	int businesslen;
	int flag;
}FEEDBACK;
//注册结构体
typedef struct registers
{
	char username[20];//用户名
	char userid[20];//账号
	char userpwd[40];//密码
}REGISTER;

//登录结构体
typedef struct login
{
	char userid[20];//账号
	char userpwd[40];//密码	 
}LOGIN;
typedef struct acceptfd
{
	int acceptfd;
	int type;
}ACC;
//车辆入场结构体

typedef struct carin
{
	char carid[20];
	char intime[40];
	char location[20];
	int imgid;
	char imgpath[80];
}CARIN;
//车牌号修改结构体
typedef struct updatecar
{
	char oldcarid[20];
	char newcarid[20];
}UPDATE;
//懒加载结构体
typedef struct load
{
	int index;//按下"加载更多"按钮后+1
}LOAD;
//车辆出场结构体
typedef struct carout
{
	char carid[20];
	char intime[40];
	char outtime[40];
	char parktime[10];
	char inimagepath[80];
	char outimagepath[80];
	int money;
	int type;// 是 0 ，否 1

}CAROUT;
typedef struct partinfo
{
	int occupy;//已占用车位
	int leisure;//空闲车位
}PARTINFO;
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
typedef struct log
{
	char time[20];
	char useid[20];
	char type[20];
	char operate[40];

}LOG;
//按月或者按日查询结构体
typedef struct inquire
{
	int index;//索引，没有用到的业务就给 0
	char month[15]; 
	char date[15];
}INQUIRE;
//图片传输结构体
typedef struct picture
{
	int id;
	int oldsize;
	char name[20];
	int number;
	int newsize;
	char content[1024];

}PICTURE;

//查询车辆信息
typedef struct querycar
{
	int index;
	char carid[20];
	char carintime[40];
	char caroutime[40];
}QUERYCAR;
