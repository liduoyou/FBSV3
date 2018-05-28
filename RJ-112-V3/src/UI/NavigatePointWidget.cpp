#include "NavigatePointWidget.h"
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QPainter>
#include <QStyleOption>
#include "../Component/ZoomPushButton.h"
NavigatePointWidget::NavigatePointWidget(QWidget *parent) :
    QWidget(parent)
//  , m_size(160,40*4)
  , m_BtnPoint1(NULL)
  , m_BtnPoint2(NULL)
  , m_BtnPoint3(NULL)
  , m_BtnPoint4(NULL)
{
    setupUI();
}

NavigatePointWidget::~NavigatePointWidget()
{
    qDebug()<<"NavigatePointWidget::~NavigatePointWidget()";
}

void NavigatePointWidget::setupUI()
{
    setFixedHeight(40*4);
    setObjectName("NavigatePointWidget");
    setStyleSheet("#NavigatePointWidget{border:0px;}");
    setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* Vbox = new QVBoxLayout();
    Vbox->setContentsMargins(0, 0, 0, 0);
    Vbox->setSpacing(10);

    QHBoxLayout* hbox1 = new QHBoxLayout();
    hbox1->setContentsMargins(0, 0, 0, 0);
    hbox1->setSpacing(0);

    m_BtnPoint1 = new ZoomPushButton();
    connect(m_BtnPoint1,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_BtnPoint1->setLabelName(tr("运行状态"));
    hbox1->addWidget(m_BtnPoint1);

    QHBoxLayout* hbox2 = new QHBoxLayout();
    hbox2->setContentsMargins(0, 0, 0, 0);
    hbox2->setSpacing(0);

    m_BtnPoint2 = new ZoomPushButton();
    connect(m_BtnPoint2,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_BtnPoint2->setLabelName(tr("详细信息"));
    hbox2->addWidget(m_BtnPoint2);

    QHBoxLayout* hbox3 = new QHBoxLayout();
    hbox3->setContentsMargins(0, 0, 0, 0);
    hbox3->setSpacing(0);

    m_BtnPoint3 = new ZoomPushButton();
    connect(m_BtnPoint3,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_BtnPoint3->setLabelName(tr("限位状态"));
    hbox3->addWidget(m_BtnPoint3);

    QHBoxLayout* hbox4 = new QHBoxLayout();
    hbox4->setContentsMargins(0, 0, 0, 0);
    hbox4->setSpacing(0);

    m_BtnPoint4 = new ZoomPushButton();
    connect(m_BtnPoint4,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_BtnPoint4->setLabelName(tr("采集端"));//状态
    hbox4->addWidget(m_BtnPoint4);

    Vbox->addLayout(hbox1);
    Vbox->addLayout(hbox2);
    Vbox->addLayout(hbox3);
    Vbox->addLayout(hbox4);

    setLayout(Vbox);
}

void NavigatePointWidget::scorllPage(int index)
{

}

void NavigatePointWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//启用反走样以得到平滑的边缘
    painter.setPen(QColor("transparent"));//设置画笔
    painter.setBrush(QColor("transparent"));//设置画布

    painter.save();

    QRect bgRect = rect();
    bgRect.setWidth(rect().width());
    bgRect.setHeight(rect().height());
    painter.drawRect(bgRect);

    painter.restore();

    //set Style...
    QStyleOption opt;
    opt.init(this);
    painter.setClipping(true);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}

void NavigatePointWidget::onButtonClicked()
{
    ZoomPushButton *btn = qobject_cast<ZoomPushButton*>(sender());
    if(btn == m_BtnPoint1){
        emit signalscorllPage(0);
    }else if(btn == m_BtnPoint2){
        emit signalscorllPage(1);
    }else if(btn == m_BtnPoint3){
        emit signalscorllPage(2);
    }else if(btn == m_BtnPoint4){
        emit signalscorllPage(3);
    }
}
