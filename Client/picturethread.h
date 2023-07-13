#ifndef PICTURETHREAD_H
#define PICTURETHREAD_H
#include <QThread>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <dirent.h>
#include<algorithm>

#include "writethread.h"
#include "shareinfo.h"

using namespace std;

class PictureThread : public QThread
{
    Q_OBJECT
public:
    explicit PictureThread(QObject *parent = nullptr);

    void breakpicture(QString filepath, QString directname);
    void sendFile(QString filepath, vector<QString>& files);

    void setFilename(QString filename);
    void setDirname(QString dir);
    void setPictureName(QString picturename);

    void Getfilepath(const char *path, const char *filename,  char *filepath);
    bool DeleteFile(const char* path);

    int splite_file(const char fileUrl[], const char dirUrl[]);


protected:
    void run();

private:
    QString filepath;
    QString directname;
    QString picture_name;
    vector<QString> files;

    WriteThread *wt;
    PICTURE picture;
    HEAD head;


    int picture_num;

    int picture_size;

    char buf[1024];

    ShareInfo *shareinfo;

signals:
    void send2PictureOk(int flag);
};

#endif // PICTURETHREAD_H
