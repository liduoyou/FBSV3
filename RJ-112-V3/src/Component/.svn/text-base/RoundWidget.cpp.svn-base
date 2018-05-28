#include "RoundWidget.h"
//#include "ui_RoundWidget.h"
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QTime>
#include <QStyleOption>
#include "CPushbutton.h"
#include "../DataHeaderDefine.h"
#ifdef MAXRESOLUTION
static int standardWidth = 200;
#else
static int standardWidth = 100;
#endif
RoundWidget::RoundWidget(QString name, QWidget *parent) :
    QWidget(parent)
  , m_angle(0)
  , curangle(0.0)
  , shouldchangeangle(0.0)
  , m_pushBtn(NULL)
  , m_flag(false)
  , m_timeLabel(NULL)
  , m_durTime(0)
  , m_name(name)
{
    m_value = "0.00";

    setupUI();

    m_timer = new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(turnRound()));
//    m_timer->start(30);
}

RoundWidget::~RoundWidget()
{
}

void RoundWidget::setValue(QString value)
{
    m_value = value;
    if(m_pushBtn != NULL){
        m_pushBtn->setValue(m_value);
    }
}

QString RoundWidget::getValue() const
{
    return m_value;
}

void RoundWidget::setNormalAngle(qreal a, qreal nearmax, qreal max)
{
    m_angle = ((double)a/max)*360;
//    qDebug()<<"a= "<<a<<"m_angle ="<<m_angle;
    if(a >= max){
//        m_angle = 360;
        m_colorstr = "#DB4437";
    }else if(a >= nearmax && a < max){
        m_colorstr = "#f4b400";
    }else if (a < nearmax){
        m_colorstr = "#0dd06f";//16cb30
    }
    update();
}

qreal RoundWidget::getNormalAngle() const
{
    return m_angle;
}

void RoundWidget::setSpecificAngle(qreal a, qreal min, qreal nearmin, qreal nearmax, qreal max)
{
    m_angle = ((double)a/max)*360;
//    qDebug()<<"a= "<<a<<"m_angle ="<<m_angle;

    if ((a > nearmin && a < nearmax) || a == 0){
        m_colorstr = "#0dd06f";//16cb30
    }else if(a <= min||a >= max){
//        m_angle = 360;
        m_colorstr = "#DB4437";
    }else if((a > min && a <= nearmin)||
             (a >= nearmax && a < max)){
        m_colorstr = "#f4b400";
    }
    update();
}

qreal RoundWidget::getSpecificAngle() const
{
    return m_angle;
}


void RoundWidget::setupUI()
{
//    setWindowOpacity(0.5);
//    setAutoFillBackground(false);
//    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
#ifdef MAXRESOLUTION
    setMaximumHeight(220);
    setMaximumWidth(220);
#else
    setMaximumHeight(120);
    setMaximumWidth(120);
#endif
//    setStyleSheet("QWidget{border-radius:0px;background-color:rgba(255, 251, 240, 50%);}");
//    setStyleSheet("QWidget{border-radius:0px;background-color:rgb(255, 251, 240);}");
//    setAttribute(Qt::WA_LayoutUsesWidgetRect,true);

    m_colorstr = "#0dd06f";

    m_pushBtn = new CPushbutton(m_name,this);//
    m_pushBtn->installEventFilter(this);
    m_pushBtn->setFixedSize(standardWidth-(standardWidth/2/10),standardWidth-(standardWidth/2/10));
    m_pushBtn->move(width()/2-(standardWidth-standardWidth/2/10)/2,height()/2-(standardWidth-standardWidth/2/10)/2);
    connect(m_pushBtn,SIGNAL(CPushbuttonClicked(bool)),this,SLOT(onButtonClicked(bool)));

    m_timeLabel = new QLabel();//this
    m_timeLabel->setAlignment(Qt::AlignCenter);
    m_timeLabel->setFocusPolicy(Qt::NoFocus);
    m_timeLabel->setFixedSize(120,20);
    m_timeLabel->setText(tr("0.00KN*M"));
    m_timeLabel->setStyleSheet("QLabel{border-radius:0px;font:bold;font-size:14px;color:#0dd06f;}");
//    m_timeLabel->move((width()-m_timeLabel->width())/2,height()/2-(standardWidth-standardWidth/2/10)/2+200);
    m_timeLabel->move((width()-m_timeLabel->width())/2,standardWidth+2);
}

void RoundWidget::positionChanged(qint64 pos)
{
//    qDebug()<<"pos ="<<pos;
//    m_timeLabel->setText(QTime::fromMSecsSinceStartOfDay(m_durTime - pos).toString("mm:ss"));
}

void RoundWidget::durationChanged(qint64 dur)
{
//    qDebug()<<"total durtime ="<<dur<<QTime::fromMSecsSinceStartOfDay(dur).toString("mm:ss");
    m_durTime = dur;
    shouldchangeangle = (360.0f/m_durTime)*(double)(m_timer->interval()+5);
//    qDebug()<<"shouldchangeangle = "<<shouldchangeangle;
}

void RoundWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QColor("transparent"));
    painter.setBrush(QColor("transparent"));

    painter.save();

    QRect bgRect;
    bgRect.setWidth(width());
    bgRect.setHeight(height());
    painter.drawRect(bgRect);

    painter.setPen(QPen(QColor("#e0ffff"),standardWidth/2/10,Qt::SolidLine));
    painter.setBrush(QColor("#e0ffff"));
    painter.drawArc(width()/2-standardWidth/2,height()/2-standardWidth/2,standardWidth,standardWidth,90*16,360 * -16);

    //画线角度 int 以1度为单位
//    painter.setPen(QPen(QColor(m_colorstr),standardWidth/2/10,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
//    painter.drawArc(width()/2-standardWidth/2,height()/2-standardWidth/2,standardWidth,standardWidth,90*16,m_angle * -16);

    //画线角度 qreal 以qreal类型的任意度数为单位
    QPainterPath myPath;
    myPath.moveTo(width()/2-standardWidth/2+(standardWidth-standardWidth/2/10)/2,height()/2-standardWidth/2);
    qreal startAngle = 90*1;
    qreal sweepLength = m_angle * -1;
    myPath.arcTo(QRectF(width()/2-standardWidth/2,height()/2-standardWidth/2,standardWidth,standardWidth),
                 startAngle,
                 sweepLength);
//    myPath.closeSubpath();
    painter.setPen(QPen(QColor(m_colorstr),standardWidth/2/10,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    painter.setBrush(QColor("transparent"));
    painter.drawPath(myPath);

    painter.restore();
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

    QWidget::paintEvent(event);
}

void RoundWidget::turnRound()
{
//    qDebug()<<"xxxxxxx"<<m_angle<<"shouldchangeangle ="<<shouldchangeangle;
//    curangle += 0.054;//shouldchangeangle
//    m_angle = curangle;
    m_angle += 1;
    if(m_angle >= 360){
        m_angle = 0;
        curangle = 0.0;shouldchangeangle = 0.0;
    }
    if((m_angle >= 330) && (m_angle < 350)){
        m_colorstr = "#f9be34";
    }else if(m_angle >= 350){
        m_colorstr = "#fb5d51";
    }else{
        m_colorstr = "#0dd06f";//16cb30
    }
    update();
    m_pushBtn->move(width()/2-(standardWidth-standardWidth/2/10)/2,height()/2-(standardWidth-standardWidth/2/10)/2);
    m_timeLabel->move((width()-m_timeLabel->width())/2,standardWidth+2);
}

void RoundWidget::onButtonClicked(bool flag)
{
    QPushButton* btn = static_cast<QPushButton*>(sender());
    if(btn == m_pushBtn){
        if(m_name.split(",").at(0) == tr("风速")){
            emit circleClicked(flag);
        }
        m_flag = flag;
        update();
    }
    if(!flag){
//        if(!m_timer->isActive()){
//            m_timer->start();
//        }
    }else{
//        if(m_timer->isActive()){
//            m_timer->stop();
//        }
    }
}

bool RoundWidget::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == m_pushBtn){
        QMouseEvent* event = static_cast<QMouseEvent*>(e);
        if(e->type() == QEvent::MouseButtonPress){
            m_pushBtn->setClickPoint(event->pos());
        }else if(e->type() == QEvent::MouseButtonRelease){
            m_pushBtn->setClickPoint(event->pos());
        }
    }
    return QObject::eventFilter(obj, e);
}
