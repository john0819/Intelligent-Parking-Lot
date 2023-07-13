#include "vcrreviewwin.h"
#include "ui_vcrreviewwin.h"
#include <QDebug>
#include <QMessageBox>

VCRReviewWin::VCRReviewWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VCRReviewWin)
{
    ui->setupUi(this);
    //set listwidget
    QListWidgetItem *oneitem = new QListWidgetItem();
    QListWidgetItem *anoitem = new QListWidgetItem();

    qRegisterMetaType<QString>("QString");
    qRegisterMetaType<vector<SEARCH>>("vector<SEARCH>");
    qRegisterMetaType<vector<VIDEOINFO>>("vector<VIDEOINFO>");
    qRegisterMetaType<VIDEOINFO>("VIDEOINFO&");

    //init some
    this->shareinfo = ShareInfo::getInstance();

    this->ui->radioButton->setChecked(1);
    this->rt = ReadThread::getInstance();
    this->wt = WriteThread::getInstance();
    memset(buf,0,sizeof(this->buf));
    this->mORd_flag = 0;
    this->page=0;
    this->row_in_list2=0;

//    oneitem->setIcon(QIcon("./ParkImage/2022-07-26 00:49:00.png"));
//    anoitem->setIcon(QIcon("./Image/2022-07-19 01:56:56.png"));
//    oneitem->setText("2022-07-26 00:49:00");
    //oneitem->setTextAlignment(Qt::AlignBottom);
//    oneitem->setSizeHint(QSize(200,200));
    this->ui->listWidget->setIconSize(QSize(300,180)); //one picture size
    this->ui->listWidget->setSpacing(50); //space between
    this->ui->listWidget->setViewMode(QListWidget::IconMode);//mode
//    this->ui->listWidget->addItem(oneitem);
//    this->ui->listWidget->addItem(anoitem);
    /*
    this->ui->listWidget->setStyleSheet("QListWidget{border:none; color:black;outline:0px; }"
                                         "QListWidget::Item{padding-left:0px;padding-top:20px; padding-bottom:4px;color:black}"
                                         "QListWidget::Item:hover{background:lightgray; color:green;}"
                                         "QListWidget::item:selected{background:lightgray; color:green; }"
                                         );
    */
    //click double will show big picture and play video
    connect(this->ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(getBigImage(QListWidgetItem*)));
    //click one will show video
    //connect(this->ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(getVideoPlay(QListWidgetItem*)));4
    //the ratio of video
    this->player = new CVideoPlayer();


    this->ui->listWidget_2->setSpacing(20); //space

    connect(this->player,SIGNAL(sendRatio(int)),this, SLOT(GetRatio(int)));

    //get info
    connect(this->rt, SIGNAL(send2MonthSearch(int, vector<SEARCH>)), this, SLOT(getMonthData(int, vector<SEARCH>)));
    connect(this->rt, SIGNAL(send2DaySearch(int, vector<SEARCH>)), this, SLOT(getDayData(int, vector<SEARCH>)));

    //click data
    connect(this->ui->listWidget_2,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(changeItem(QListWidgetItem*)));

    //show data (video)
    connect(this->rt,SIGNAL(send2MonthData(int, vector<VIDEOINFO>)),this,SLOT(getMonthVideo(int, vector<VIDEOINFO>)));
    connect(this->rt,SIGNAL(send2DayData(int, vector<VIDEOINFO>)),this,SLOT(getDayVideo(int, vector<VIDEOINFO>)));

    //get one video
    connect(this->rt,SIGNAL(send2OneVideo(int,VIDEOINFO&)),this,SLOT(getOneVideo(int,VIDEOINFO&)));

    //add more
    connect(this->rt,SIGNAL(send2MoreMonth(int, vector<VIDEOINFO>)),this,SLOT(getMoreMonth(int, vector<VIDEOINFO>)));
    connect(this->rt,SIGNAL(send2MoreDay(int, vector<VIDEOINFO>)),this,SLOT(getDayMonth(int, vector<VIDEOINFO>)));

}

VCRReviewWin::~VCRReviewWin()
{
    delete ui;
}


//double click to big picture
void VCRReviewWin::getBigImage(QListWidgetItem *item) //type ==16
{
    QStringList str = item->text().split("|"); //2022-07-29
    QString video_name = str[0];
    qDebug()<<"video name = "<<video_name;
    this->select_video = video_name;

    memset(&this->video,0,sizeof(this->video));
    memcpy(this->video.videoname,video_name.toStdString().c_str(),sizeof(this->video.videoname));
    memset(&this->head,0,sizeof(this->head));
    this->head.bussinesstype=16;
    this->head.bussinesslen=sizeof(this->video);
    this->head.CRC=shareinfo->CalcCRCCode((unsigned char*)&this->video,sizeof(this->video));
    memset(this->buf,0,sizeof(this->buf));
    memcpy(this->buf,&(this->head),sizeof(this->head));
    memcpy(this->buf + sizeof(this->head), &(this->video), sizeof(this->video));
    this->wt->setData(this->buf,sizeof(this->head)+sizeof(this->video));
    qDebug()<<"send to server, type ==16";

    //big picture and video show
    /*
    qDebug()<<"big big";
    QRect rect = this->geometry(); //window size
    this->big = new BigPicture(item , QRect(rect.x(), rect.y()+rect.y()*1/4, rect.width(), rect.height()*2/3));
    //this->big = new BigPicture(item,QRect(100,100,100,100),this);
    this->big->show();

    //video name
    //item->text();
    //confirm whether to play video
    QMessageBox *box = new QMessageBox();
    box->setIcon(QMessageBox::Question);
    box->setWindowTitle(QString::fromLocal8Bit("Question"));
    box->setText(QString::fromLocal8Bit("Do you play video?"));
    this->okbtn = box->addButton("Yes",QMessageBox::AcceptRole);
    this->nobtn = box->addButton("no",QMessageBox::RejectRole);
    box->show();
    box->exec();

    if(this->okbtn == box->clickedButton()) //play video according to the name
    {
        qDebug()<<item->text();

        this->player->setVideoPath(item->text());
        this->player->show();
        qDebug()<<"ok";
    }
    else if(this->nobtn == box->clickedButton())
    {
        qDebug()<<"no";
    }
    */
}

//add ratio to video name
void VCRReviewWin::GetRatio(int num)
{
    qDebug()<<"GetRatio(int num) = "<<num;

    //qDebug()<<num;
    memset(&(this->video),0,sizeof(this->video));
    memcpy(this->video.videoname, this->select_video.toStdString().c_str(),sizeof(this->video.videoname));
    qDebug()<<"this->video.videoname = "<<this->video.videoname;
    this->video.video_num = num;
    memset(&(this->head),0,sizeof(this->head));
    this->head.bussinesstype=19;
    this->head.CRC=shareinfo->CalcCRCCode((unsigned char*)&this->video,sizeof(this->video));
    this->head.bussinesslen=sizeof(this->video);
    memset(this->buf,0,sizeof(this->buf));
    memcpy(this->buf,&(this->head),sizeof(this->head));
    memcpy(this->buf + sizeof(this->head), &(this->video), sizeof (this->video));
    this->wt->setData(this->buf,sizeof(this->head)+sizeof(this->video));
    qDebug()<<"write to server ok, type =19";
}

//month
void VCRReviewWin::on_radioButton_clicked() //type ==12
{
    this->mORd_flag = 0;
    this->page=0;
    qDebug()<<"month";
    char res[1024]={0};

    memset(&this->head,0,sizeof(this->head));
    this->head.bussinesstype = 12;
    this->head.bussinesslen = 0;
    this->head.CRC = shareinfo->CalcCRCCode((unsigned char*)res, 0);
    memset(this->buf,0,sizeof(this->buf));
    memcpy(this->buf,&(this->head),sizeof(this->head));
    this->wt->setData(this->buf,sizeof(this->head));
    qDebug()<<"write server ok, type ==12";

}

//day
void VCRReviewWin::on_radioButton_2_clicked() //type ==13
{
    this->mORd_flag =1;
    this->page=0;
    qDebug()<<"day";
    memset(&this->search,0,sizeof(this->search));
    memcpy(search.month,this->select_month.toStdString().c_str(),sizeof(search.month));
    qDebug()<<"this->select_month = "<<this->select_month;
    qDebug()<<"search.month = "<<search.month;
    /*
    char res[1024] ={0};
    memcpy(res, &this->search, sizeof(this->search));
    */
    memset(&this->head,0,sizeof(this->head));
    this->head.bussinesstype = 13;
    this->head.bussinesslen = 0;
    this->head.CRC = shareinfo->CalcCRCCode((unsigned char*)&this->search, sizeof(this->search));
    qDebug()<<"CRC = "<<head.CRC;
    memset(this->buf,0,sizeof(this->buf));
    memcpy(this->buf,&(this->head),sizeof(this->head));
    memcpy(this->buf + sizeof(this->head), &this->search, sizeof(this->search));
    this->wt->setData(this->buf,sizeof(this->head) + sizeof(this->search));
    qDebug()<<"write server ok, type ==13";

    /*
    //test
    this->ui->listWidget_2->addItem(new QListWidgetItem("2022-07-08"));
    this->ui->listWidget_2->addItem(new QListWidgetItem("2022-07-08"));
    this->ui->listWidget_2->addItem(new QListWidgetItem("2022-07-08"));
    this->ui->listWidget_2->addItem(new QListWidgetItem("2022-07-08"));
    */
}

//show left table
//month
void VCRReviewWin::getMonthData(int flag, vector<SEARCH> search) //type =14
{
    if(flag ==1)
    {
        this->ui->listWidget_2->clear();
        this->vec_search.clear();

        qDebug()<<"VCR search";
        for(int i =0; i < search.size(); i++)
        {
            this->vec_search.push_back(search[i]);
        }
        for(int i=0; i< this->vec_search.size(); i++)
        {
            if(QString(this->vec_search[i].month).isEmpty())
            {
                break;
            }

            qDebug()<<"this->vec_search[i].month = "<<this->vec_search[i].month;
            //add to list
            this->ui->listWidget_2->addItem(new QListWidgetItem(this->vec_search[i].month));
            //this->ui->listWidget_2->insertItem(i/2, new QListWidgetItem(this->vec_search[i].month));
        }
    }
    else if(flag ==0)
    {

    }
}

//day
void VCRReviewWin::getDayData(int flag, vector<SEARCH> search) //type = 15
{
    if(flag ==1)
    {
        this->ui->listWidget_2->clear();
        this->vec_search.clear();

        qDebug()<<"VCR search";
        for(int i =0; i < search.size(); i++)
        {
            this->vec_search.push_back(search[i]);
        }
        for(int i=0; i< this->vec_search.size(); i++)
        {
            if(QString(this->vec_search[i].date).isEmpty())
            {
                break;
            }

            qDebug()<<"this->vec_search[i].date = "<<this->vec_search[i].date;

            QString all_date;
            all_date = this->select_month + "-" + this->vec_search[i].date;

            qDebug()<<"all_date = "<<all_date;
            //add to list
            this->ui->listWidget_2->addItem(new QListWidgetItem(all_date));
        }

    }
    else if(flag ==0)
    {

    }
}

//show right table
//select date and send it to server
void VCRReviewWin::changeItem(QListWidgetItem *item)
{
    qDebug()<<item->text();
    this->select_date = item->text(); //save it
    this->select_month = item->text();
    if(this->mORd_flag ==0) //month type=14
    {
        memset(&this->search,0,sizeof(this->search));
        memcpy(this->search.month, item->text().toStdString().c_str(), sizeof(this->search.month));

        memset(&this->head,0,sizeof(this->head));
        this->head.bussinesstype=14;
        this->head.CRC=shareinfo->CalcCRCCode((unsigned char*)&this->search,sizeof(this->search));
        this->head.bussinesslen = sizeof(this->search);
        memset(this->buf,0,sizeof(this->buf));
        memcpy(this->buf,&(this->head),sizeof(this->head));
        memcpy(this->buf + sizeof(this->head), &(this->search), sizeof(this->search));
        this->wt->setData(this->buf,sizeof(this->head)+sizeof(this->search));
        qDebug()<<"write to server ok, type =14";
    }
    else if(this->mORd_flag ==1) //day type=15
    {
        QStringList str = item->text().split("-"); // 2022 07 29
        QString month = str[0] + "-" + str[1];
        QString day = str[2];

        memset(&this->search,0,sizeof(this->search));
        memcpy(this->search.month,month.toStdString().c_str(),sizeof(this->search.month));
        memcpy(this->search.date, day.toStdString().c_str(), sizeof(this->search.month));
        memset(&this->head,0,sizeof(this->head));
        this->head.bussinesstype=15;
        this->head.CRC=shareinfo->CalcCRCCode((unsigned char*)&this->search, sizeof(this->search));
        this->head.bussinesslen = sizeof(this->search);
        memset(this->buf,0,sizeof(this->buf));
        memcpy(this->buf,&(this->head),sizeof(this->head));
        memcpy(this->buf + sizeof(this->head), &(this->search), sizeof(this->search));
        this->wt->setData(this->buf,sizeof(this->head)+sizeof(this->search));
        qDebug()<<"write to server ok, type =15";
    }
}

//show month video
void VCRReviewWin::getMonthVideo(int flag, vector<VIDEOINFO> video)
{
    if(flag ==1)
    {
        this->ui->listWidget->clear();

        qDebug()<<"getMonthVideo ";
        //QListWidgetItem *item = new QListWidgetItem();
        QString str;
        QString final_name;
        int ratio=0;
        this->row_in_list2 = video.size()/3;
        this->ui->listWidget->clear();
        for(int i=0; i<video.size(); i++) //video.size()
        {

            if(QString(video[i].month).isEmpty())
            {
                break;
            }

            QListWidgetItem *item = new QListWidgetItem();
            qDebug()<<"i = "<<i;
            //ratio
            ratio = (video[i].video_num *100) / video[i].video_count;
            str = QString::number(ratio,10) + "%";
            //videoname
            qDebug()<<"video[i].videoname = "<<video[i].videoname;
            final_name = QString(video[i].videoname) + "|" + str;
            qDebug()<<"final_name = "<<final_name;

            item->setText(final_name);
            qDebug()<<"video[i].picutre_path = "<<video[i].picutre_path;

            item->setIcon(QIcon(video[i].picutre_path));

            item->setSizeHint(QSize(300,200));
            //this->ui->listWidget->insertItem((i/3),item); //012 / 345
            //this->ui->listWidget->addItem(item);
            this->ui->listWidget->insertItem(i/2, item);
            qDebug()<<"i/2 = "<<i/2;

        }
        qDebug()<<"get month data";
    }
}


//show day video
void VCRReviewWin::getDayVideo(int flag, vector<VIDEOINFO> video)
{
    if(flag ==1)
    {
        this->ui->listWidget->clear();

        //QListWidgetItem *item = new QListWidgetItem();
        QString str;
        QString final_name;
        int ratio=0;
        this->row_in_list2 = video.size()/3;
        this->ui->listWidget->clear();
        for(int i=0; i<video.size(); i++)
        {
            if(QString(video[i].date).isEmpty())
            {
                break;
            }

            QListWidgetItem *item = new QListWidgetItem();
            //ratio
            ratio = video[i].video_num / video[i].video_count;
            str = QString::number(ratio,10);
            //videoname
            final_name = QString(video[i].videoname) + "|" + str;
            item->setText(final_name);
            item->setIcon(QIcon(video[i].picutre_path));

            item->setSizeHint(QSize(200,200));
            //this->ui->listWidget->insertItem((i/3),item); //012 / 345
            this->ui->listWidget->addItem(item);
        }
        qDebug()<<"get day data";
    }
}

void VCRReviewWin::getOneVideo(int flag, VIDEOINFO& video)
{
    if(flag==1)
    {
        CVideoPlayer *playertest = new CVideoPlayer();

        connect(playertest,SIGNAL(sendRatio(int)),this, SLOT(GetRatio(int)));

        playertest->setValue(video.video_num);
        playertest->setVideoPath(video.video_path);
        playertest->show();

        //this->player->setValue(video.video_num);

        //this->player->setVideoPath(video.video_path);

        //this->player->show();
        qDebug()<<"video play";
    }
    else if(flag==0)
    {

    }
}

//more page
void VCRReviewWin::on_pushButton_2_clicked()
{
    this->page++;
    if(this->mORd_flag ==0) //month type=17
    {
        memset(&this->search,0,sizeof(this->search));
        this->search.index = this->page;
        memcpy(this->search.month,this->select_date.toStdString().c_str(),sizeof(this->search.month));
        memset(&this->head,0,sizeof(this->head));
        this->head.bussinesstype =17;
        this->head.bussinesslen = sizeof(this->search);
        this->head.CRC=shareinfo->CalcCRCCode((unsigned char*)&this->search,sizeof(this->search));
        memset(this->buf,0,sizeof(this->buf));
        memcpy(this->buf,&(this->head),sizeof(this->head));
        memcpy(this->buf + sizeof (this->head), &(this->search), sizeof(this->search));
        this->wt->setData(this->buf,sizeof(this->head)+sizeof(this->search));
        qDebug()<<"send to server ok, type =17";

    }
    else if(this->mORd_flag ==1) //day type=18
    {
        memset(&this->search,0,sizeof(this->search));
        this->search.index = this->page;
        memcpy(this->search.date,this->select_date.toStdString().c_str(),sizeof(this->search.month));
        memset(&this->head,0,sizeof(this->head));
        this->head.bussinesstype =17;
        this->head.bussinesslen = sizeof(this->search);
        this->head.CRC=shareinfo->CalcCRCCode((unsigned char*)&this->search, sizeof(this->search));
        memset(this->buf,0,sizeof(this->buf));
        memcpy(this->buf,&(this->head),sizeof(this->head));
        memcpy(this->buf + sizeof (this->head), &(this->search), sizeof(this->search));
        this->wt->setData(this->buf,sizeof(this->head)+sizeof(this->search));
        qDebug()<<"send to server ok, type =18";
    }

}

//month add
void VCRReviewWin::getMoreMonth(int flag, vector<VIDEOINFO> video)
{
    if(flag ==1)
    {

        QString str;
        QString final_name;
        int ratio=0;
        this->row_in_list2 = video.size()/3;
        //this->ui->listWidget->clear();
        for(int i=0; i<video.size(); i++)
        {
            if(QString(video[i].month).isEmpty())
            {
                break;
            }

            QListWidgetItem *item = new QListWidgetItem();
            //ratio
            ratio = video[i].video_num / video[i].video_count;
            str = QString::number(ratio,10);
            //videoname
            final_name = QString(video[i].videoname) + "|" + str;

            item->setText(final_name);
            //item->setIcon(QIcon(video[i].picutre_path));
            qDebug()<<"video[i].picutre_path = "<<video[i].picutre_path;
            item->setIcon(QIcon("./ParkImage/2022-08-03 03:40:49.png"));

            item->setSizeHint(QSize(200,200));
            //this->ui->listWidget->insertItem((this->row_in_list2 +(i/3)),item); //012 / 345
            this->ui->listWidget->addItem(item);
        }
        qDebug()<<"get more month data, type =17";
    }
    else if(flag==0)
    {
        QMessageBox::information(this,"hint","no else information!");
    }
}

//day add
void VCRReviewWin::getDayMonth(int flag, vector<VIDEOINFO> video)
{
    if(flag ==1)
    {

        QString str;
        QString final_name;
        int ratio=0;
        this->row_in_list2 = video.size()/3;
        //this->ui->listWidget->clear();
        for(int i=0; i<video.size(); i++)
        {
            if(QString(video[i].month).isEmpty())
            {
                break;
            }

            QListWidgetItem *item = new QListWidgetItem();
            //ratio
            ratio = video[i].video_num / video[i].video_count;
            str = QString::number(ratio,10);
            //videoname
            final_name = QString(video[i].videoname) + "|" + str;
            item->setText(final_name);
            item->setIcon(QIcon(video[i].picutre_path));


            item->setSizeHint(QSize(200,200));
            //this->ui->listWidget->insertItem((this->row_in_list2 +(i/3)),item); //012 / 345
            this->ui->listWidget->addItem(item);
        }
        qDebug()<<"get more day data,type=18";
    }
    else if(flag==0)
    {
        QMessageBox::information(this,"hint","no else information!");
    }
}
