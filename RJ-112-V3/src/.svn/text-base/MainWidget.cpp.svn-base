#include "MainWidget.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QPainter>
#include <QStyleOption>
#include <QDateTime>
#include <QFile>
#include <QPropertyAnimation>
#include "./UI/AbstractWidget.h"
#include "./UI/DetailWidget.h"
#include "./UI/NavigatePointWidget.h"
#include "./DataHeaderDefine.h"
#include "./Component/CardWidget.h"
#include "./Component/CommonNotify.h"
#include "./ListViewManager/CardManagerWidget.h"
MainWidget *MainWidget::_instance = NULL;
const QString topcmd  = "/usr/bin/top";
#ifdef MAXRESOLUTION
quint8 m_CardWidthstandard = 240;
#else
quint8 m_CardWidthstandard = 180;
#endif
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    #ifdef MAXRESOLUTION
    , m_size(1024,768)
    #else
    , m_size(800,480)
    #endif
    , m_NaveWidget(NULL)
    , m_pBtnMain(NULL)
    , m_pBtnDetail(NULL)
    , m_pbtnlimit(NULL)
    , m_pBtnAcPort(NULL)
    , m_pNaveLabel(NULL)
    , m_posAnimation(NULL)
    , m_navigatePointWidget(NULL)
    , m_abstractWidget(NULL)
{
    if(_instance == NULL){
        _instance = this;
    }

    setupUI();

//    QStringList argument;
//    argument<<"name"<<"file"<<"manager"<<"detail"<<"name"<<"manager"<<"detail"<<"name"<<"manager"
//           <<"manager"<<"detail"<<"name"/**/;
//    emit preappendImage(argument);
//    emit hasCards();
//    qDebug()<<"per content height"<<m_contents->height();
//    m_contents->setFixedSize(width(),40*7+160*(12/4));
//    qDebug()<<"back content height"<<m_contents->height();

}

MainWidget::~MainWidget()
{
    qDebug()<<"MainWidget::~MainWidget()";

}

MainWidget *MainWidget::instance()
{
    return _instance;
}

void MainWidget::updateData()
{

}

void MainWidget::setupUI()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_LayoutUsesWidgetRect);
    setFixedSize(m_size);
    setFocusPolicy(Qt::StrongFocus);

    QVBoxLayout* VLayout = new QVBoxLayout();
    VLayout->setContentsMargins(0, 0, 15, 0);
    VLayout->setSpacing(10);
//    VLayout->addWidget(initMainNavigate());

    layout = new QVBoxLayout();
    m_scrollArea = new VScrollArea();
    m_scrollArea->setFixedWidthEx(width());
    m_scrollArea->setFixedHeightEx(height());
    m_scrollArea->setFocusPolicy(Qt::StrongFocus);
    layout->addWidget(m_scrollArea);

    m_contents = new QWidget();
    m_contents->installEventFilter(m_scrollArea);
    m_contents->setStyleSheet("QWidget{border:0px;}");
//    m_contents->setFixedSize(width(),40*7+160*(12/4));
//    qDebug()<<"mainwidget height="<<40*7+160*(12/4);
    m_scrollArea->setWidget(m_contents);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setAcceptDrops(true);
    m_contents->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QVBoxLayout* foldVlayout = new QVBoxLayout(m_contents);
    foldVlayout->setSizeConstraint(QLayout::SetMaximumSize);
    foldVlayout->setContentsMargins(0,0,0,0);
    foldVlayout->setSpacing(5);
//    foldVlayout->addWidget(initAbstractWidget(),Qt::AlignCenter);
    foldVlayout->addWidget(initDetailWidget(),Qt::AlignCenter);
//    foldVlayout->addWidget(initCardWidgets());
//    foldVlayout->addWidget(initSecondNavigate());
//    m_cardManagerWidget = new CardManagerWidget();
//    foldVlayout->addWidget(m_cardManagerWidget,Qt::AlignCenter);

    VLayout->addLayout(layout);
//    initSecondNavigate();

    setLayout(VLayout);
}

QWidget *MainWidget::initMainNavigate()
{
    m_NaveWidget = new QWidget();
    m_NaveWidget->setObjectName("m_NaveWidget");
    m_NaveWidget->setStyleSheet("#m_NaveWidget{border:0px;}");
    m_NaveWidget->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QHBoxLayout* hNaveLayout = new QHBoxLayout();
    hNaveLayout->setContentsMargins(15, 0, 15, 0);
    hNaveLayout->setSpacing(10);

    m_pBtnMain = new QPushButton();
    connect(m_pBtnMain,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_pBtnMain->setFocusPolicy(Qt::NoFocus);
    m_pBtnMain->setObjectName("m_pBtnMain");
    m_pBtnMain->setCheckable(true);
    m_pBtnMain->setChecked(true);
    m_pBtnMain->setText(tr("运行状态"));
    m_pBtnMain->setFixedSize(80,45);
    m_pBtnMain->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    m_pBtnMain->setStyleSheet("QPushButton{border:0px;color:#8F8F8F;font-size:15px;background-color:transparent;}\
                               QPushButton:checked{border:0px;color:#0f9d58;font-size:15px;background-color:transparent;}");

    m_pBtnDetail = new QPushButton();
    connect(m_pBtnDetail,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_pBtnDetail->setFocusPolicy(Qt::NoFocus);
    m_pBtnDetail->setObjectName("m_pBtnDetail");
    m_pBtnDetail->setCheckable(true);
    m_pBtnDetail->setChecked(false);
    m_pBtnDetail->setText(tr("详细信息"));
    m_pBtnDetail->setFixedSize(80,45);
    m_pBtnDetail->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    m_pBtnDetail->setStyleSheet("QPushButton{border:0px;color:#8F8F8F;font-size:15px;background-color:transparent;}\
                                QPushButton:checked{border:0px;color:#0f9d58;font-size:15px;background-color:transparent;}");

    m_pbtnlimit = new QPushButton();
    connect(m_pbtnlimit,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_pbtnlimit->setFocusPolicy(Qt::NoFocus);
    m_pbtnlimit->setObjectName("m_pbtnlimit");
    m_pbtnlimit->setCheckable(true);
    m_pbtnlimit->setChecked(false);
    m_pbtnlimit->setText(tr("限位状态"));
    m_pbtnlimit->setFixedSize(80,45);
    m_pbtnlimit->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    m_pbtnlimit->setStyleSheet("QPushButton{border:0px;color:#8F8F8F;font-size:15px;background-color:transparent;}\
                               QPushButton:checked{border:0px;color:#0f9d58;font-size:15px;background-color:transparent;}");

    m_pBtnAcPort = new QPushButton();
    connect(m_pBtnAcPort,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_pBtnAcPort->setFocusPolicy(Qt::NoFocus);
    m_pBtnAcPort->setObjectName("m_pBtnAcPort");
    m_pBtnAcPort->setCheckable(true);
    m_pBtnAcPort->setChecked(false);
    m_pBtnAcPort->setText(tr("采集端"));//状态
    m_pBtnAcPort->setFixedSize(80,45);
    m_pBtnAcPort->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    m_pBtnAcPort->setStyleSheet("QPushButton{border:0px;color:#8F8F8F;font-size:15px;background-color:transparent;}\
                                QPushButton:checked{border:0px;color:#0f9d58;font-size:15px;background-color:transparent;}");

    hNaveLayout->addWidget(m_pBtnMain,Qt::AlignCenter);
    hNaveLayout->addWidget(m_pBtnDetail,Qt::AlignCenter);
    hNaveLayout->addWidget(m_pbtnlimit,Qt::AlignCenter);
    hNaveLayout->addWidget(m_pBtnAcPort,Qt::AlignCenter);

    m_pNaveLabel = new QLabel(m_NaveWidget);
    m_pNaveLabel->setObjectName("m_pNaveLabel");
    m_pNaveLabel->setFixedSize(QSize(80,3));
#ifdef MAXRESOLUTION
    m_pNaveLabel->setGeometry(137,11,80,3);
#else
    m_pNaveLabel->setGeometry(93,11,80,3);
#endif
    m_pNaveLabel->setStyleSheet("QLabel{border:0px;background-color:#0f9d58;}");
    //索引条动画
    m_posAnimation = new QPropertyAnimation(m_pNaveLabel, "pos");
    m_posAnimation->setEasingCurve(QEasingCurve::OutQuint);

    m_NaveWidget->setLayout(hNaveLayout);
    m_NaveWidget->setVisible(true);
    return m_NaveWidget;
}

QWidget *MainWidget::initSecondNavigate()
{
   m_navigatePointWidget = new NavigatePointWidget(m_contents);
   connect(MainWidget::instance(),SIGNAL(changsecondNavigate(int)),m_navigatePointWidget,SLOT(scorllPage(int)));
//   connect(m_navigatePointWidget,SIGNAL(signalscorllPage(int)),MainWidget::instance(),SLOT(receivescorllPage(int)));
   connect(m_scrollArea,SIGNAL(sendVerticalScrollBarValue(int)),this,SLOT(receivescorllValue(int)));

   m_navigatePointWidget->setFocusPolicy(Qt::StrongFocus);
   m_navigatePointWidget->raise();
   m_navigatePointWidget->show();

   m_posAnimation1 = new QPropertyAnimation(m_navigatePointWidget, "pos");
   m_posAnimation1->setEasingCurve(QEasingCurve::OutQuint);
   m_posAnimation1->setEndValue(QPoint(width()-m_navigatePointWidget->width()-20,height()/2));
   m_posAnimation1->setDuration(500);
   m_posAnimation1->start();
   return m_navigatePointWidget;
}

QWidget *MainWidget::initAbstractWidget()
{
    m_abstractWidget = new AbstractWidget();
    return m_abstractWidget;
}

QWidget *MainWidget::initDetailWidget()
{
    m_detailWidget = new DetailWidget();
    return m_detailWidget;
}

QWidget *MainWidget::initCardWidgets()
{
    m_cardWidgets = new QWidget();
    m_cardWidgets->setObjectName("m_cardWidgets");
    m_cardWidgets->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(5, 0, 5, 75);
    vLayout->setSpacing(5);

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(5, 0, 5, 0);
    hLayout->setSpacing(5);

    QHBoxLayout* hLayout1 = new QHBoxLayout();
    hLayout1->setContentsMargins(5, 0, 5, 0);
    hLayout1->setSpacing(5);

    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout2->setContentsMargins(5, 0, 5, 0);
    hLayout2->setSpacing(5);

    cardwidget1 = new CardWidget();
    cardwidget2 = new CardWidget();
    cardwidget3 = new CardWidget();
    cardwidget4 = new CardWidget();

    hLayout->addWidget(cardwidget1,1,Qt::AlignLeft);
    hLayout->addWidget(cardwidget2,1,Qt::AlignLeft);
    hLayout->addWidget(cardwidget3,1,Qt::AlignLeft);
    hLayout->addWidget(cardwidget4,1,Qt::AlignLeft);

    cardwidget5 = new CardWidget();
    cardwidget6 = new CardWidget();
    cardwidget7 = new CardWidget();
    cardwidget8 = new CardWidget();

    hLayout1->addWidget(cardwidget5,1,Qt::AlignLeft);
    hLayout1->addWidget(cardwidget6,1,Qt::AlignLeft);
    hLayout1->addWidget(cardwidget7,1,Qt::AlignLeft);
    hLayout1->addWidget(cardwidget8,1,Qt::AlignLeft);

    cardwidget9 = new CardWidget();

    hLayout2->addWidget(cardwidget9,1,Qt::AlignLeft);

    vLayout->addLayout(hLayout);
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    m_cardWidgets->setLayout(vLayout);
    return m_cardWidgets;
}

void MainWidget::receivescorllPage(int index)
{
//    QPoint pos = m_pNaveLabel->pos();
    switch (index){
    case 0:
    {
        m_pBtnMain->setChecked(true);
        m_pBtnDetail->setChecked(false);
        m_pbtnlimit->setChecked(false);
        m_pBtnAcPort->setChecked(false);
        m_posAnimation->setEndValue(QPoint(m_pBtnMain->x(),11));
        m_posAnimation->setDuration(500);
        m_posAnimation->start();
    }break;
    case 1:
    {
        m_pBtnMain->setChecked(false);
        m_pBtnDetail->setChecked(true);
        m_pbtnlimit->setChecked(false);
        m_pBtnAcPort->setChecked(false);
        m_posAnimation->setEndValue(QPoint(m_pBtnDetail->x(),11));
        m_posAnimation->setDuration(500);
        m_posAnimation->start();
    }break;
    case 2:
    {
        m_pBtnMain->setChecked(false);
        m_pBtnDetail->setChecked(false);
        m_pbtnlimit->setChecked(true);
        m_pBtnAcPort->setChecked(false);
        m_posAnimation->setEndValue(QPoint(m_pbtnlimit->x(),11));
        m_posAnimation->setDuration(500);
        m_posAnimation->start();
    }break;
    case 3:
    {
        m_pBtnMain->setChecked(false);
        m_pBtnDetail->setChecked(false);
        m_pbtnlimit->setChecked(false);
        m_pBtnAcPort->setChecked(true);
        m_posAnimation->setEndValue(QPoint(m_pBtnAcPort->x(),11));
        m_posAnimation->setDuration(500);
        m_posAnimation->start();
    }break;
    default:
        break;
    }
}

void MainWidget::receivescorllValue(int newValue)
{
    m_posAnimation1->setEndValue(QPoint(width()-m_navigatePointWidget->width()-20,newValue+250));//左移 20
    m_posAnimation1->setDuration(2000);
    m_posAnimation1->start();
}

void MainWidget::onButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
//    QPoint pos = m_pNaveLabel->pos();
//    qDebug()<<"POS = "<<pos;
//    m_posAnimation->setStartValue(pos);
    if(btn == m_pBtnMain){
        m_pBtnMain->setChecked(true);
        m_pBtnDetail->setChecked(false);
        m_pbtnlimit->setChecked(false);
        m_pBtnAcPort->setChecked(false);

//        m_cardManagerWidget->setVisible(false);
//        m_contents->setVisible(true);

        m_posAnimation->setEndValue(QPoint(m_pBtnMain->x(),11));
        m_posAnimation->setDuration(500);
        m_posAnimation->start();
        emit changsecondNavigate(0);
    }else if(btn == m_pBtnDetail){
        m_pBtnMain->setChecked(false);
        m_pBtnDetail->setChecked(true);
        m_pbtnlimit->setChecked(false);
        m_pBtnAcPort->setChecked(false);

//        m_cardManagerWidget->setVisible(true);
//        m_contents->setVisible(false);

        m_posAnimation->setEndValue(QPoint(m_pBtnDetail->x(),11));
        m_posAnimation->setDuration(500);
        m_posAnimation->start();
        emit changsecondNavigate(1);
    }else if(btn == m_pbtnlimit){
        m_pBtnMain->setChecked(false);
        m_pBtnDetail->setChecked(false);
        m_pbtnlimit->setChecked(true);
        m_pBtnAcPort->setChecked(false);
        m_posAnimation->setEndValue(QPoint(m_pbtnlimit->x(),11));
        m_posAnimation->setDuration(500);
        m_posAnimation->start();
        emit changsecondNavigate(2);
    }else if(btn == m_pBtnAcPort){
        m_pBtnMain->setChecked(false);
        m_pBtnDetail->setChecked(false);
        m_pbtnlimit->setChecked(false);
        m_pBtnAcPort->setChecked(true);
        m_posAnimation->setEndValue(QPoint(m_pBtnAcPort->x(),11));
        m_posAnimation->setDuration(500);
        m_posAnimation->start();
        emit changsecondNavigate(3);
    }
}

void MainWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//启用反走样以得到平滑的边缘
    painter.setPen(QColor("#FDFDFD"));//设置画笔 494949
    painter.setBrush(QColor("#FDFDFD"));//设置画布

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
