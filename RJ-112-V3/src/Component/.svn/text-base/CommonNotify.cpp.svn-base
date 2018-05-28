#include "CommonNotify.h"
#include <QRect>
#include <QPoint>
#include <QTimer>
#include <QDebug>
#include "../MainWidget.h"
#include "CommonNotifyWidget.h"

CommonNotify *CommonNotify::_instance = NULL;

QList<CommonNotifyWidget*> CommonNotify::_noticeList;

CommonNotify *CommonNotify::instance(){
    if(_instance == NULL){
        _instance = new CommonNotify();
    }
    return _instance;
}

CommonNotify::~CommonNotify(){
    while (!_noticeList.isEmpty()) {
        _noticeList.first()->setVisible(true);
        _noticeList.first()->deleteLater();
        _noticeList.removeFirst();
    }
}

CommonNotify::CommonNotify(QObject *parent) :
    QObject(parent)
{
    if(MainWidget::instance() != NULL){
        connect(MainWidget::instance(), SIGNAL(positionChanged()), this, SLOT(adjustNoticePosition()));
    }
    if(_instance == NULL){
        _instance = this;
    }
}

void CommonNotify::messageBox(QString text)
{
    Q_UNUSED(text)
}

void CommonNotify::messageBox(QString title, QString text){
    if(MainWidget::instance() == NULL){
        return;
    }

    CommonNotifyWidget* box = new CommonNotifyWidget();
    connect(box, SIGNAL(timeOut()), instance(), SLOT(recycleNotice()));

    box->setTitle(title);
    box->setNotice(text);

    QRect mainRect = MainWidget::instance()->geometry();
    QRect rect((mainRect.x() + mainRect.width())/2 + 550, mainRect.y() + 280 + 55 * _noticeList.size(), 200, 50);

    box->setGeometry(rect);
    box->show();

//    _noticeList.append(box);
}

void CommonNotify::recycleNotice(){
    QWidget *o = (QWidget*)sender();
    if(o != NULL){
        o->setVisible(false);
        o->deleteLater();
        if(!_noticeList.isEmpty()){
            _noticeList.removeFirst();
            adjustNoticePosition();
        }
    }
}

void CommonNotify::adjustNoticePosition(){
    if(MainWidget::instance() == NULL){
        return;
    }

    QRect mainRect = MainWidget::instance()->geometry();
    for(int i=0; i<_noticeList.size(); i++){
        QPoint pos(mainRect.x() + mainRect.width() - 203, mainRect.y() + 49 + 55 * i);
        _noticeList[i]->move(pos);
    }
}

bool CommonNotify::exists(){
    if(_instance == NULL || _noticeList.size() == 0){
        return false;
    }
    return true;
}
