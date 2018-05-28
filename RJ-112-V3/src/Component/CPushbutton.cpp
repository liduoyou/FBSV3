#include "CPushbutton.h"
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <qmath.h>
#include <QTimer>
#include <QPainter>
#include <QStyleOption>
#include "../DataHeaderDefine.h"
#ifdef MAXRESOLUTION
static int standardWidthx = 200;
#else
static int standardWidthx = 100;
#endif
CPushbutton::CPushbutton(QString name, QWidget *parent) :
    QPushButton(parent)
  , m_flag(false)
  , m_angle(0)
  , m_point(0,0)
  , m_name(name)
{
    m_value = "0.00";
    setFlat(true);
    setCheckable(true);
    setFocusPolicy(Qt::NoFocus);//border-image:url(:images/album.png); border-color:1px solid #0dd06f;
    sheet = "QPushButton{border-radius:%1px;font:blod;font-size:12px;}";
    sheet = sheet.arg(QString::number((standardWidthx-(standardWidthx/2/10))/2,10,0));
    setStyleSheet(sheet);

    m_timer = new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(turnRound()));
//    m_timer->start(30);

    connect(this,SIGNAL(clicked(bool)),this,SLOT(onButtonClicked(bool)));
}

CPushbutton::~CPushbutton()
{
}

void CPushbutton::setAngle(qreal a)
{
    m_angle = a;
    update();
}

qreal CPushbutton::getAngle() const
{
    return m_angle;
}

void CPushbutton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QColor("transparent"));
    painter.setBrush(QColor("transparent"));

    QFont bigfont,smallfont;
    bigfont.setPixelSize(16);
    smallfont.setPixelSize(12);
    painter.setFont(bigfont);

    painter.save();

    painter.setPen(QColor("#000000"));
    painter.setBrush(QColor("#000000"));

//    painter.drawText((width()/2-m_name.size()*8), (height()/2+m_name.size()*2),m_name);
    painter.drawText((width()/2-m_name.split(",").at(0).size()*8), (height()/2-8),m_name.split(",").at(0));
    painter.drawText((width()/2-m_value.size()*5), (height()/2+8*1),m_value);
    painter.drawText((width()/2-m_name.split(",").at(1).size()*5), (height()/2+4*6),m_name.split(",").at(1));

    if(m_flag){
        painter.translate(0.0,0.0);
        QPolygonF polygon;
        polygon << QPointF((standardWidthx-(standardWidthx/2/10))/2-1.732*(standardWidthx/8)/4,((standardWidthx-(standardWidthx/2/10))-(standardWidthx/8))/2)
                <<QPointF((standardWidthx-(standardWidthx/2/10))/2-1.732*(standardWidthx/8)/4,((standardWidthx-(standardWidthx/2/10))-(standardWidthx/8))/2+(standardWidthx/8))
                << QPointF((standardWidthx-(standardWidthx/2/10))/2-1.732*(standardWidthx/8)/4+1.732*(standardWidthx/8)/2,((standardWidthx-(standardWidthx/2/10))-(standardWidthx/8))/2+(standardWidthx/8)/2);
        painter.setPen(QPen(QColor("#0dd06f"),8,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        painter.setBrush(QBrush(QColor("#0dd06f")));
//        painter.drawPolygon(polygon, Qt::WindingFill);
        painter.setOpacity(0.15);
    }

    int cx = width()/2;
    int cy = height()/2;
    painter.translate(cx, cy);

    painter.rotate(m_angle);

    painter.setPen(QPen(QColor("transparent"),2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
     //设置纹理
//    painter.setBrush(QBrush(QPixmap(":/Main/Title.png").
//                          scaled(standardWidthx-(standardWidthx/2/10),standardWidthx-(standardWidthx/2/10),
//                                 Qt::KeepAspectRatioByExpanding,
//                                 Qt::SmoothTransformation)));//使用画刷
//    painter.setBrush(QBrush(QColor("transparent")));
    painter.translate(-width()/2,-height()/2);
//    QRectF target(0,0,standardWidthx-(standardWidthx/2/10),standardWidthx-(standardWidthx/2/10));
//    painter.drawEllipse(target);  //绘制椭圆

    if(m_flag){
    }

    painter.restore();

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

    QWidget::paintEvent(event);
}

void CPushbutton::onButtonClicked(bool flag)
{
    if((qreal)qPow((getclickPoint().x()-(standardWidthx-(standardWidthx/2/10))/2),2)+
            (qreal)qPow((getclickPoint().y()-(standardWidthx-(standardWidthx/2/10))/2),2)
            <=(qreal)qPow((standardWidthx-(standardWidthx/2/10))/2,2)){
        m_flag = flag;
//        if(m_timer->isActive()){
//            m_timer->stop();
//        }else{
//            m_timer->start(30);
//        }
        emit CPushbuttonClicked(flag);
    }else{
//        qDebug()<<tr("无效点击");
//        qDebug()<<tr("Click invalid");
    }
//    qDebug()<<"flag = "<<flag;
    if(m_name.split(",").at(0) == tr("风速")){
        if(flag){
            m_name = (QString)tr("风速,级");
        }else{
            m_name = (QString)tr("风速,M/S");
        }
    }
    update();
}

void CPushbutton::turnRound()
{
    m_angle+=1;
    if(m_angle == 360){
        m_angle = 0;
    }
    update();
    setAngle(m_angle);
}

void CPushbutton::setClickPoint(QPoint point)
{
    m_point = point;
//    qDebug()<<"m_point = "<<m_point;
}

QPoint CPushbutton::getclickPoint() const
{
    return m_point;
}

void CPushbutton::setValue(QString value)
{
    m_value = value;
}

QString CPushbutton::getValue() const
{
    return m_value;
}
