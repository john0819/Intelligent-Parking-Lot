#include "parkingthread.h"

ParkingThread::ParkingThread(char *videopath)
{
    if(cap.open(videopath))
    {
        qDebug()<<"open video error";
    }
    qRegisterMetaType<Mat>("Mat");
    this->cascade.load("./Cascade/cars.xml");
}

void ParkingThread::run()
{
    while(cap.read(frame))
    {
        //emit process image
        this->resframe = this->detectCarDaw(frame,this->cascade,2);
        emit frameVideo(this->resframe);
        msleep(40);
    }
}

Mat ParkingThread::detectCarDaw(Mat frame, CascadeClassifier cascade, double scale)
{
    //灰度处理
            Mat gray;
            //需要克隆 避免frame相同被改变
            Mat output=frame.clone();

            cvtColor(output, gray, CV_RGB2GRAY);
            //灰度图缩小 根据scale
            Mat smalling(cvRound(output.rows/scale),cvRound(output.cols/scale),CV_8UC1);
            resize(gray, smalling, smalling.size(),0,0,INTER_LINEAR);

            //直方图均值化 : 缩小的灰度图进行黑白分明处理
            equalizeHist(smalling,smalling);

            //保存车辆的容器
            vector<Rect>cars;
            //级联分类器
            //根据算法（第五个参数） 对比学习特征（学习模型）比较的像素大小为（30 x 30） 把smalling中符合的放到cars
            //参数1：检测的图片（一般为灰度图），2：矩形框向量组，3：默认1.1，4：默认为2，5：算法
            cascade.detectMultiScale(smalling, cars, 1.1,2,0|CV_HAAR_SCALE_IMAGE,Size(30,30));

            //绘制车辆的矩形框 : 在frame上画图（原图）
            vector<Rect>::const_iterator iter;
            for(iter=cars.begin();iter!=cars.end();iter++)
            {
                //参数1：图像；2：起始坐标；3：末端坐标；4：颜色
                rectangle(output,
                          CvPoint(cvRound(iter->x*scale),cvRound(iter->y*scale)),
                          CvPoint(cvRound((iter->x+iter->width)*scale),cvRound((iter->y+iter->height)*scale)),
                          Scalar(0,255,0),2,8);
            }

            return output;
}
