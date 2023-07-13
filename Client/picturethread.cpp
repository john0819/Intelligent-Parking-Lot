#include "picturethread.h"
#include <QDebug>
#include <unistd.h>

PictureThread::PictureThread(QObject *parent)
{
    this->picture_num = 0;
    this->picture_size=0;
    this->wt = WriteThread::getInstance();
    this->shareinfo = ShareInfo::getInstance();
}

//break picture
void PictureThread::breakpicture(QString filepath, QString directname)
{
    int readfd=0;
    int writefd=0;
    int res1=0;
    int res2=0;
    //content
    char buf[512]={0};
    //int num=0;
    char res[20]={0};
    QString tempname;
    umask(0);
    //file size (count size)
    struct stat statbuf;
    stat(filepath.toStdString().c_str(), &statbuf);
    size_t filesize = statbuf.st_size;
    this->picture_size = (int)filesize;
    qDebug()<<filesize;

    //read picture
    readfd = open(filepath.toStdString().c_str(),O_RDONLY,0777);
    //judge
    if(readfd<0 || writefd<0)
    {
        perror("cannt open file");
    }
    else
    {

        while((res1 = read(readfd, buf, sizeof(buf)))>0)
        {
            sprintf(res, "%d", this->picture_num);
            tempname =directname + "/" + QString(res) + ".temp";
            qDebug()<<tempname;
            writefd = open(tempname.toStdString().c_str(), O_CREAT | O_WRONLY, 0777);
            qDebug()<<"res1 = "<<res1;
            res2 = write(writefd, buf, res1);
            if(res2 >0)
            {
                close(writefd);
                tempname = "";
                this->picture_num++;
                bzero(buf,sizeof(buf));
            }
        }
    }
    close(readfd);
}

//save all
void PictureThread::sendFile(QString filepath, vector<QString> &files)
{
    struct dirent *ptr;
    DIR *dir;
    dir=opendir(filepath.toStdString().c_str());
    printf("文件列表:\n");
    while((ptr=readdir(dir))!=NULL)
    {

    //跳过'.'和'..'两个目录
        if(ptr->d_name[0] == '.')
        {
            continue;
        }
        files.push_back(ptr->d_name);
            //printf("%s\n",ptr->d_name);
    }
    closedir(dir);
}

void PictureThread::setFilename(QString filename)
{
    this->filepath = filename;
}

void PictureThread::setDirname(QString dir)
{
    this->directname = dir;
}

void PictureThread::setPictureName(QString picturename)
{
    this->picture_name = picturename;
}

//delete file
void PictureThread::Getfilepath(const char *path, const char *filename, char *filepath)
{
    strcpy(filepath, path);
    if(filepath[strlen(path) - 1] != '/')
        strcat(filepath, "/");
    strcat(filepath, filename);
//    printf("path is = %s\n",filepath);
}

bool PictureThread::DeleteFile(const char *path)
{
    DIR *dir;
    struct dirent *dirinfo;
    struct stat statbuf;
    char filepath[256] = {0};
    lstat(path, &statbuf);

    if (S_ISREG(statbuf.st_mode))//判断是否是常规文件
    {
        remove(path);
    }
    else if (S_ISDIR(statbuf.st_mode))//判断是否是目录
    {
        if ((dir = opendir(path)) == NULL)
            return 1;
        while ((dirinfo = readdir(dir)) != NULL)
        {
            Getfilepath(path, dirinfo->d_name, filepath);
            if (strcmp(dirinfo->d_name, ".") == 0 || strcmp(dirinfo->d_name, "..") == 0)//判断是否是特殊目录
            continue;
            DeleteFile(filepath);
            rmdir(filepath);
        }
        closedir(dir);
    }
    return 0;
}



int PictureThread::splite_file(const char fileUrl[], const char dirUrl[])
{
        char buf[3000] = { 0 };
        char rcv[1024] = { 0 };
        int index;//序号
        int sumSize = 3211264;//总大小
        char videoName[20];//视频原名称(Warcraft3.avi)
        int num;//视频拆分个数(63)
        int pieceSize;//碎片大小(<=512000)
        char fileContent[512]; //碎片文件内容(51200)

        struct stat statbuf;
        stat(fileUrl, &statbuf);
        size_t filesize = statbuf.st_size;
        this->picture_size = (int)filesize;
        qDebug()<<this->picture_size;

        int readFd = 0, writeFd = 0;
        int readRes = 0;
        int fileNumber = 1;
        umask(0);
        readFd = open(fileUrl, O_RDONLY, 0777);//打开母文件
        char bufs[512] = { 0 };//4*25600=100kb
    //	int bufs[128] = { 0 };
        if (readFd < 0)
        {
            perror("open file error");//打开母文件失败
            return 0;
        }
        else
        {
            while ((readRes = read(readFd, bufs, sizeof(bufs))) > 0)//以100kb为单位分割父文件
            {
                char childFileName[255] = { 0 };//存放分割后的子文件名
                sprintf(childFileName, "%s%d%s", dirUrl, fileNumber, ".temp");//子文件绝对路径拼接
                //qDebug()<<"childFileName = "<<childFileName;
                writeFd = open(childFileName, O_CREAT | O_WRONLY, 0777);//创建子文件
                if (writeFd < 0)
                {
                    perror("open file error");
                }
                else
                {
                    write(writeFd, bufs, readRes);//子文件写入数据
                    //cout << childFileName << " 分割成功！" << endl;
                    close(writeFd);//关闭子文件

                    FEEDBACK feedback;
                    HEAD head;
                    memset(&feedback, 0, sizeof(feedback));
                    memset(&head, 0, sizeof(head));

                    PICTURE picture;
                    memset(&picture, 0, sizeof(picture));

                    picture.imageid = fileNumber;//序号
                    picture.size = this->picture_size;//总大小
                    memcpy(picture.picture_name, this->picture_name.toStdString().c_str(), sizeof(picture.picture_name));
                    picture.number = picture.size/sizeof(picture.content)+1;//视频拆分个数
                    if (picture.imageid != picture.number)
                    {
                        picture.one_size = 512;
                    }
                    else if( (picture.size % sizeof(picture.content) != 0) && (picture.imageid= picture.number))
                    {
                        picture.one_size = picture.size % sizeof(picture.content);
                    }
                    //cout << "filetrain.pieceSize:" << picture.one_size << endl;
                    memcpy(picture.content, bufs, sizeof(bufs));


                    head.bussinesslen = sizeof(picture);
                    char res[sizeof(picture)]={0};
                    memcpy(res, &picture, sizeof(picture));
                    //head.CRC = shareinfo->CalcCRCCode((unsigned char*)res, sizeof(picture));
                    head.CRC = shareinfo->CalcCRCCode((unsigned char*)&picture, sizeof(picture));
                    //head.CRC =0;
                    qDebug()<<" sizeof(picture) = "<<sizeof(picture);
                    qDebug()<<" CRC = "<<head.CRC;
                    head.bussinesstype = 20;


                    memcpy(buf, &head, sizeof(head));//记得每次都要写

                    memcpy(buf + sizeof(head), &picture, sizeof(picture));
                    //int writeSize = write(socketfd, buf, sizeof(head) + sizeof(filetrain));//发送头+体
                    this->wt->setData(buf, sizeof(head) + sizeof(this->picture));
                    fileNumber++;
                    close(writeFd);//关闭子文件
                    usleep(100000);
                    if (picture.imageid == picture.number)
                    {
                        break;
                    }
                }
                //清空数组
                bzero(buf, sizeof(buf));
                bzero(bufs, sizeof(bufs));
                bzero(childFileName, sizeof(childFileName));

                usleep(60000);
            }
            close(readFd);//关闭母文件
    //		//开文件
    //		int totalwfd = open("girltotal.jpg", O_CREAT | O_WRONLY, 0777);
    //		if (totalwfd < 0)
    //		{
    //			perror("open file error");
    //		}
    //		//拼接
    //		for (int i = 1; i <= fileNumber-1; i++)
    //		{
    //
    //			lseek(totalwfd, 0, SEEK_END);
    //			write(totalwfd, bufs, 512);
    //			//cout << "FileMap[filetrain.videoName][i]:" << FileMap[filetrain.videoName][i] << endl;
    //		}
    //		cout << "拼接成功" << endl;
    //		close(totalwfd);//关闭母文件
            return 1;
        }
        return 0;
}

//sort
bool vct_compare(QString a, QString b)
{
    return stoi(a.toStdString()) < stoi(b.toStdString());
}



void PictureThread::run()
{
    qDebug()<<"this->filepath = "<<this->filepath;
    qDebug()<<"this->directname = "<<this->directname;
    qDebug()<<"this->picture_name = "<<this->picture_name;

    DeleteFile(this->directname.toStdString().c_str());

    this->splite_file(this->filepath.toStdString().c_str(), this->directname.toStdString().c_str());

    emit send2PictureOk(1);

/*
    //clear file (dir)
    DeleteFile(this->directname.toStdString().c_str());

    //break picture
    this->breakpicture(this->filepath,this->directname);
    //save all picture name (.temp) ->files


    this->files.clear();
    this->sendFile(this->directname, this->files);
    sort(this->files.begin(), this->files.end(),vct_compare);//sort


    //send to server
    int readfd=0;
    int writefd=0;
    int res1=0;
    int res2=0;
    char buf[512]={0};
    int num = 1;
    QString file_all_name = "";
    //read all files
    for(int i=0;i<this->files.size();i++)
    {
        file_all_name = this->directname + "/" +this->files[i];
        //open
        readfd = open(file_all_name.toStdString().c_str(),O_RDONLY,0777);
        //read content
        res1 = read(readfd, buf, sizeof(buf));
        //send it to server
        memset(&this->picture,0,sizeof(this->picture));
        this->picture.imageid = num;
        this->picture.size = this->picture_size;
        memcpy(this->picture.picture_name, this->picture_name.toStdString().c_str(),sizeof(this->picture.picture_name));
        this->picture.number = this->picture_num;
        this->picture.one_size = res1;
        memcpy(this->picture.content, buf, sizeof(this->picture.content));
        //set head
        memset(&(this->head),0,sizeof(this->head));
        this->head.bussinesstype=20;
        this->head.CRC=0;
        this->head.bussinesslen = sizeof(this->picture);
        //send to server
        memset(this->buf,0,sizeof(this->buf));
        memcpy(this->buf,&this->head,sizeof(this->head));
        memcpy(this->buf + sizeof(this->head), &(this->picture),sizeof(this->picture));
        this->wt->setData(this->buf, sizeof(this->head)+sizeof(this->picture));
        qDebug()<<"send to sever ok, type =20";
        //close and num++
        num++;
        close(readfd);
        usleep(60000);
    }

    qDebug()<<"clear all";

    emit send2PictureOk(1);
*/
}
