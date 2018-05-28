#include "NavigationNode.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include <QMouseEvent>
#include <qmath.h>
#include <QPropertyAnimation>
#include "../DataHeaderDefine.h"
static int Rectwidth = 250;
static int Rectheight = 28;//y=x/11+8
static int ArcSpace = (Rectheight-4*2)/2;
NavigationNode::NavigationNode(QWidget *parent) : QWidget(parent)
  , m_size(Rectwidth,Rectheight)
  , m_clickflag(1)
{
    setFixedSize(m_size);
    installEventFilter(this);
    changeClickFlag(0);
}

NavigationNode::~NavigationNode()
{
    qDebug()<<"NavigationNode::~NavigationNode()";
}

void NavigationNode::setClickPoint(QPoint point)
{
    m_point = point;
    qDebug()<<"point = "<<point;
    changeNode();
}

QPoint NavigationNode::getClickPoint() const
{
    return m_point;
}

void NavigationNode::changeClickFlag(int bit)
{
    if(bit >= 0  && bit < 7){
        m_clickflag = 0;
        setbit(m_clickflag,bit);
        emit NodeClicked(getClickedFlag());
        update();
    }
}

int NavigationNode::getClickedFlag() const
{
    int bit = -1;
    switch(m_clickflag){
    case 0x01:
        bit = 0;
        break;
    case 0x02:
        bit = 1;
        break;
    case 0x04:
        bit = 2;
        break;
    case 0x08:
        bit = 3;
        break;
    case 0x10:
        bit = 4;
        break;
    case 0x20:
        bit = 5;
        break;
    case 0x40:
        bit = 6;
        break;
    default:
        break;
    }
    return bit;
}

void NavigationNode::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//启用反走样以得到平滑的边缘

    painter.save();
    painter.setOpacity(0.5);

    painter.setPen(QColor("#848484"));
    painter.setBrush(QColor("#848484"));
    painter.drawRoundedRect(rect(), Rectheight/2,Rectheight/2);

    painter.setPen(QColor("#474747"));
    painter.setBrush(QColor("#474747"));

    if(m_clickflag & 0x01){
        painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+0*((Rectheight-4*2)+ArcSpace),4,
                                       Rectheight-4*2+20,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);

        for(int i=1;i<((Rectwidth-2*(Rectheight-4*2)+3*ArcSpace)/((Rectheight-4*2)+ArcSpace))-1;i++){
            painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2+5+i*((Rectheight-4*2)+ArcSpace),4,
                                           Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);
        }
    }else if(m_clickflag & 0x02){
        painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+0*((Rectheight-4*2)+ArcSpace),4,
                                       Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);

        painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+1*((Rectheight-4*2)+ArcSpace),4,
                                       Rectheight-4*2+20,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);

        for(int i=2;i<((Rectwidth-2*(Rectheight-4*2)+3*ArcSpace)/((Rectheight-4*2)+ArcSpace))-1;i++){
            painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2+5+i*((Rectheight-4*2)+ArcSpace),4,
                                           Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);
        }
    }else if(m_clickflag & 0x04){
        for(int i=0;i<2;i++){
            painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+i*((Rectheight-4*2)+ArcSpace),4,
                                           Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);
        }

        painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+2*((Rectheight-4*2)+ArcSpace),4,
                                       Rectheight-4*2+20,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);

        for(int i=3;i<((Rectwidth-2*(Rectheight-4*2)+3*ArcSpace)/((Rectheight-4*2)+ArcSpace))-1;i++){
            painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2+5+i*((Rectheight-4*2)+ArcSpace),4,
                                           Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);
        }
    }else if(m_clickflag & 0x08){
        for(int i=0;i<3;i++){
            painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+i*((Rectheight-4*2)+ArcSpace),4,
                                           Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);
        }

        painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+3*((Rectheight-4*2)+ArcSpace),4,
                                       Rectheight-4*2+20,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);

        for(int i=4;i<((Rectwidth-2*(Rectheight-4*2)+3*ArcSpace)/((Rectheight-4*2)+ArcSpace))-1;i++){
            painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2+5+i*((Rectheight-4*2)+ArcSpace),4,
                                           Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);
        }
    }else if(m_clickflag & 0x10){
        for(int i=0;i<4;i++){
            painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+i*((Rectheight-4*2)+ArcSpace),4,
                                           Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);
        }

        painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+4*((Rectheight-4*2)+ArcSpace),4,
                                       Rectheight-4*2+20,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);

        for(int i=5;i<((Rectwidth-2*(Rectheight-4*2)+3*ArcSpace)/((Rectheight-4*2)+ArcSpace))-1;i++){
            painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2+5+i*((Rectheight-4*2)+ArcSpace),4,
                                           Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);
        }
    }else if(m_clickflag & 0x20){
        for(int i=0;i<5;i++){
            painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+i*((Rectheight-4*2)+ArcSpace),4,
                                           Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);
        }

        painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+5*((Rectheight-4*2)+ArcSpace),4,
                                       Rectheight-4*2+20,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);

        for(int i=6;i<((Rectwidth-2*(Rectheight-4*2)+3*ArcSpace)/((Rectheight-4*2)+ArcSpace))-1;i++){
            painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2+5+i*((Rectheight-4*2)+ArcSpace),4,
                                           Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);
        }
    }else if(m_clickflag & 0x40){
        for(int i=0;i<6;i++){
            painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+i*((Rectheight-4*2)+ArcSpace),4,
                                           Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);
        }

        painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2-15+6*((Rectheight-4*2)+ArcSpace),4,
                                       Rectheight-4*2+20,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);

        for(int i=7;i<((Rectwidth-2*(Rectheight-4*2)+3*ArcSpace)/((Rectheight-4*2)+ArcSpace))-1;i++){
            painter.drawRoundedRect(QRectF((Rectheight-4*2)*3/2+5+i*((Rectheight-4*2)+ArcSpace),4,
                                           Rectheight-4*2,Rectheight-4*2), Rectheight/2.5,Rectheight/2.5);
        }
    }

    painter.restore();

    //set Style...
    QStyleOption opt;
    opt.init(this);
    painter.setClipping(true);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}

bool NavigationNode::eventFilter(QObject *obj, QEvent *e)
{
    QMouseEvent* event = static_cast<QMouseEvent*>(e);
    if(e->type() == QEvent::MouseButtonPress){
        setClickPoint(event->pos());
    }else if(e->type() == QEvent::MouseButtonRelease){
        setClickPoint(event->pos());
    }
    return QObject::eventFilter(obj,e);
}

void NavigationNode::changeNode()
{
    if(m_clickflag & 0x04){
        if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+0*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag0 true";
            changeClickFlag(0);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+1*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag1 true";
            changeClickFlag(1);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+2*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag2 true";
            changeClickFlag(2);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+3*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag3 true";
            changeClickFlag(3);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+4*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag4 true";
            changeClickFlag(4);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+5*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag5 true";
            changeClickFlag(5);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+6*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag6 true";
            changeClickFlag(6);
            update();
        }else{
            qDebug()<<"false";
        }
    }else if(m_clickflag & 0x08){
        if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+0*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag0 true";
            changeClickFlag(0);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+1*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag1 true";
            changeClickFlag(1);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+2*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag2 true";
            changeClickFlag(2);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+3*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag3 true";
            changeClickFlag(3);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+4*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag4 true";
            changeClickFlag(4);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+5*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag5 true";
            changeClickFlag(5);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+6*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag6 true";
            changeClickFlag(6);
            update();
        }else{
            qDebug()<<"false";
        }
    }else if(m_clickflag & 0x10){
        if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+0*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag0 true";
            changeClickFlag(0);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+1*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag1 true";
            changeClickFlag(1);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+2*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag2 true";
            changeClickFlag(2);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+3*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag3 true";
            changeClickFlag(3);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+4*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag4 true";
            changeClickFlag(4);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+5*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag5 true";
            changeClickFlag(5);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+6*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag6 true";
            changeClickFlag(6);
            update();
        }else{
            qDebug()<<"false";
        }
    }else if(m_clickflag & 0x20){
        if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+0*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag0 true";
            changeClickFlag(0);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+1*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag1 true";
            changeClickFlag(1);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+2*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag2 true";
            changeClickFlag(2);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+3*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag3 true";
            changeClickFlag(3);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+4*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag4 true";
            changeClickFlag(4);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+5*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag5 true";
            changeClickFlag(5);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+6*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag6 true";
            changeClickFlag(6);
            update();
        }else{
            qDebug()<<"false";
        }
    }else if(m_clickflag & 0x40){
        if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+0*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag0 true";
            changeClickFlag(0);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+1*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag1 true";
            changeClickFlag(1);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+2*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag2 true";
            changeClickFlag(2);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+3*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag3 true";
            changeClickFlag(3);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+4*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag4 true";
            changeClickFlag(4);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+5*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag5 true";
            changeClickFlag(5);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+6*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag6 true";
            changeClickFlag(6);
            update();
        }else{
            qDebug()<<"false";
        }
    }else{
        if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2-15+0*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag0 true";
            changeClickFlag(0);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+1*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag1 true";
            changeClickFlag(1);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+2*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag2 true";
            changeClickFlag(2);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+3*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag3 true";
            changeClickFlag(3);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+4*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag4 true";
            changeClickFlag(4);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+5*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag5 true";
            changeClickFlag(5);
            update();
        }else if((qreal)qPow(getClickPoint().x()-((Rectheight-4*2)*3/2+5+6*((Rectheight-4*2)+ArcSpace)+(Rectheight-4*2)/2),2)+
                 (qreal)qPow(getClickPoint().y()-((Rectheight-4*2)/2+4),2)
                 <=(qreal)qPow((Rectheight-4*2)/2,2)){
            qDebug()<<"m_clickflag6 true";
            changeClickFlag(6);
            update();
        }else{
            qDebug()<<"false";
        }
    }
}
