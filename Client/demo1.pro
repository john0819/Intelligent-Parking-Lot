#-------------------------------------------------
#
# Project created by QtCreator 2022-07-16T19:28:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

Qt += xlsx

SOURCES += \
        main.cpp \
        widget.cpp\
    /opt/EasyPR/src/core/chars_identify.cpp \
    /opt/EasyPR/src/core/chars_recognise.cpp \
    /opt/EasyPR/src/core/chars_segment.cpp \
    /opt/EasyPR/src/core/core_func.cpp \
    /opt/EasyPR/src/core/feature.cpp \
    /opt/EasyPR/src/core/params.cpp \
    /opt/EasyPR/src/core/plate_detect.cpp \
    /opt/EasyPR/src/core/plate_judge.cpp \
    /opt/EasyPR/src/core/plate_locate.cpp \
    /opt/EasyPR/src/core/plate_recognize.cpp \
    /opt/EasyPR/src/train/ann_train.cpp \
    /opt/EasyPR/src/train/annCh_train.cpp \
    /opt/EasyPR/src/train/create_data.cpp \
    /opt/EasyPR/src/train/svm_train.cpp \
    /opt/EasyPR/src/train/train.cpp \
    /opt/EasyPR/src/util/kv.cpp \
    /opt/EasyPR/src/util/program_options.cpp \
    /opt/EasyPR/src/util/util.cpp \
    /opt/EasyPR/thirdparty/LBP/helper.cpp \
    /opt/EasyPR/thirdparty/LBP/lbp.cpp \
    /opt/EasyPR/thirdparty/mser/mser2.cpp \
    /opt/EasyPR/thirdparty/svm/corrected_svm.cpp \
    /opt/EasyPR/thirdparty/textDetect/erfilter.cpp \
    /opt/EasyPR/thirdparty/xmlParser/xmlParser.cpp \
    mythread.cpp \
    csetwin.cpp \
    cmanagewin.cpp \
    cregwin.cpp \
    centerwin.cpp \
    verificationcodelabel.cpp \
    cvideoplayer.cpp \
    videothread.cpp \
    csearchwin.cpp \
    mylineedit.cpp \
    ccarinwin.cpp \
    carenterthread.cpp \
    ccaroutwin.cpp \
    shareinfo.cpp \
    carleavethread.cpp \
    parkingvcrwin.cpp \
    parkingthread.cpp \
    vcrreviewwin.cpp \
    bigpicture.cpp \
    mainwindow.cpp \
    readthread.cpp \
    socketconnect.cpp \
    writethread.cpp \
    md5.cpp \
    onecarwin.cpp \
    picturethread.cpp

HEADERS += \
        widget.h\
/opt/EasyPR/include/easypr/core/character.hpp \
    /opt/EasyPR/include/easypr/core/chars_identify.h \
    /opt/EasyPR/include/easypr/core/chars_recognise.h \
    /opt/EasyPR/include/easypr/core/chars_segment.h \
    /opt/EasyPR/include/easypr/core/core_func.h \
    /opt/EasyPR/include/easypr/core/feature.h \
    /opt/EasyPR/include/easypr/core/params.h \
    /opt/EasyPR/include/easypr/core/plate.hpp \
    /opt/EasyPR/include/easypr/core/plate_detect.h \
    /opt/EasyPR/include/easypr/core/plate_judge.h \
    /opt/EasyPR/include/easypr/core/plate_locate.h \
    /opt/EasyPR/include/easypr/core/plate_recognize.h \
    /opt/EasyPR/include/easypr/train/ann_train.h \
    /opt/EasyPR/include/easypr/train/annCh_train.h \
    /opt/EasyPR/include/easypr/train/create_data.h \
    /opt/EasyPR/include/easypr/train/svm_train.h \
    /opt/EasyPR/include/easypr/train/train.h \
    /opt/EasyPR/include/easypr/util/kv.h \
    /opt/EasyPR/include/easypr/util/program_options.h \
    /opt/EasyPR/include/easypr/util/switch.hpp \
    /opt/EasyPR/include/easypr/util/util.h \
    /opt/EasyPR/include/easypr/api.hpp \
    /opt/EasyPR/include/easypr/config.h \
    /opt/EasyPR/include/easypr/version.h \
    /opt/EasyPR/include/easypr.h \
    /opt/EasyPR/test/accuracy.hpp \
    /opt/EasyPR/test/chars.hpp \
    /opt/EasyPR/test/config.hpp \
    /opt/EasyPR/test/plate.hpp \
    /opt/EasyPR/test/result.hpp \
    /opt/EasyPR/thirdparty/LBP/helper.hpp \
    /opt/EasyPR/thirdparty/LBP/lbp.hpp \
    /opt/EasyPR/thirdparty/mser/mser2.hpp \
    /opt/EasyPR/thirdparty/svm/precomp.hpp \
    /opt/EasyPR/thirdparty/textDetect/erfilter.hpp \
    /opt/EasyPR/thirdparty/xmlParser/xmlParser.h \
    mythread.h \
    csetwin.h \
    cmanagewin.h \
    cregwin.h \
    centerwin.h \
    verificationcodelabel.h \
    cvideoplayer.h \
    videothread.h \
    csearchwin.h \
    mylineedit.h \
    ccarinwin.h \
    carenterthread.h \
    ccaroutwin.h \
    shareinfo.h \
    carleavethread.h \
    parkingvcrwin.h \
    parkingthread.h \
    vcrreviewwin.h \
    bigpicture.h \
    mainwindow.h \
    protocol.h \
    readthread.h \
    socketconnect.h \
    writethread.h \
    md5.h \
    onecarwin.h \
    picturethread.h

FORMS += \
        widget.ui \
    csetwin.ui \
    cregwin.ui \
    centerwin.ui \
    cvideoplayer.ui \
    csearchwin.ui \
    ccarinwin.ui \
    ccaroutwin.ui \
    parkingvcrwin.ui \
    vcrreviewwin.ui \
    bigpicture.ui \
    mainwindow.ui \
    onecarwin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH +=/usr/local/include/

LIBS+=/usr/local/lib/libopencv_world.so

INCLUDEPATH += /opt/EasyPR/include/

DISTFILES += \
    model/ann_chinese.xml \
    model/ann.xml \
    model/annCh.xml \
    model/svm_hist.xml
