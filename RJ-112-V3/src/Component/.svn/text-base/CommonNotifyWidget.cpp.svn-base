#include "CommonNotifyWidget.h"
#include <QTimerEvent>
#include <QDebug>
#include <QVBoxLayout>

CommonNotifyWidget::CommonNotifyWidget(QWidget *parent) :
    QWidget(parent)
  , _mainLayout(NULL)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setFocusPolicy(Qt::NoFocus);
    setAttribute(Qt::WA_LayoutUsesWidgetRect);


    initUI();

    _selfTimerId = startTimer(1500);
//    qDebug()<<"width"<<width()<<"height"<<height();
}
void CommonNotifyWidget::initUI(){
    setWindowOpacity(0.5);
    setAutoFillBackground(false);
    setMaximumHeight(50);
    setMaximumWidth(200);
    setStyleSheet("QWidget{border-radius:25px;background-color:rgba(0,0,0,50%);}");
    setAttribute(Qt::WA_TranslucentBackground,true);

    _titleLable.setMinimumHeight(14);
    _titleLable.setWordWrap(true);
    _titleLable.setVisible(false);
    _titleLable.setStyleSheet("font-size:18px;color:white");
    _titleLable.setAlignment(Qt::AlignHCenter | Qt::AlignHCenter);

    _noticeLable.setMinimumHeight(30);
    _noticeLable.setMaximumWidth(200);
    _noticeLable.setWordWrap(true);
    _noticeLable.setVisible(false);
    _noticeLable.setStyleSheet("font-size:18px;color:white");
    _noticeLable.setAlignment(Qt::AlignHCenter | Qt::AlignHCenter);

    _mainLayout = new QVBoxLayout();
    _mainLayout->setSpacing(0);
    _mainLayout->setMargin(0);
    _mainLayout->setContentsMargins(3, 3, 3, 3);

    _mainLayout->addWidget(&_titleLable);
    _mainLayout->addWidget(&_noticeLable);

    setLayout(_mainLayout);
}

CommonNotifyWidget::~CommonNotifyWidget(){
    qDebug()<<"~CommonNotifyWidget()";
    if(_mainLayout != NULL){
        _mainLayout->deleteLater();
    }
}

QSize CommonNotifyWidget::sizeHint() const{
    return QSize(200 ,50);
}

QString CommonNotifyWidget::getTitle() const{
    return _titleLable.text();
}

void CommonNotifyWidget::setTitle(const QString &value){
    if(!value.isEmpty()){
        _titleLable.setText(value);
        _titleLable.setVisible(true);
    }else{
        _titleLable.setVisible(false);
    }
}

QString CommonNotifyWidget::getNotice() const{
    return _noticeLable.text();
}

void CommonNotifyWidget::setNotice(const QString &value){
    if(!value.isEmpty()){
        _noticeLable.setText(value);
        _noticeLable.setVisible(true);
    }else{
        _noticeLable.setVisible(false);
    }
}

void CommonNotifyWidget::timerEvent(QTimerEvent *event){
    if(event->timerId() == _selfTimerId){
        event->accept();
        emit timeOut();
    }
}

void CommonNotifyWidget::enterEvent(QEvent *){
    int tid = _selfTimerId;
    _selfTimerId = -1;
    if(tid != -1){
        killTimer(tid);
    }
}

void CommonNotifyWidget::leaveEvent(QEvent *){
    if(_selfTimerId != -1){
        return;
    }
    _selfTimerId = startTimer(1500);
}


