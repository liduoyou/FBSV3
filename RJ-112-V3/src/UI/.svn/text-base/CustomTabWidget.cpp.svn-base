#include "CustomTabWidget.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include "../UI/ControlPanel.h"
#include "../MainWidget.h"
CustomTabWidget::CustomTabWidget(QWidget *parent) :
    QTabWidget(parent)
{//,QTabBar::tab:hover
    setStyleSheet("QTabWidget{border:2px;border-radius:0px;background-color:transparent;} \
                               QTabWidget::pane {border: none;} \
                               QTabBar::tear {image: url(:Main/WindDe.png);}\
                               QTabWidget::tab-bar{alignment:center;}\
                               QTabBar::tab:selected{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                                               stop: 0 #FDFDFD, stop: 0.4 #FDFDFD,\
                                                               stop: 0.5 #FDFDFD, stop: 1.0 #FDFDFD);\
                                                               border-bottom-color: #0f9d58;}\
                               QTabBar::tab{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  \
                                                                        stop: 0 #FDFDFD, stop: 0.4 #FDFDFD,  \
                                                                        stop: 0.5 #FDFDFD, stop: 1.0 #FDFDFD);  \
                                                                        border: 2px solid #FDFDFD;    \
                                                                        border-bottom-color: #FDFDFD; \
                                                                        border-right-color: #FDFDFD;  \
                                                                        border-top-left-radius: 0px;  \
                                                                        border-top-right-radius: 0px;  \
                                                                        min-width: 8px;min-height:35px; \
                                                                        padding: 4px;}");
    setTabPosition(QTabWidget::South);
    setTabShape(QTabWidget::Triangular);
    setAutoFillBackground(true);
    setUsesScrollButtons(true);
    setDocumentMode(false);
    setMovable(true);
    setTabsClosable(true);
    setTabEnabled(0,false);
    setFocusPolicy(Qt::NoFocus);

    QIcon* icon = new QIcon(QPixmap(":/Main/Title.png"));
    addTab(ControlPanel::instance(),*icon, tr("控制面板"));

    connect(ControlPanel::instance(),SIGNAL(gotoTargetPage(int)),this,SLOT(addTabPage(int)));

    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTargetTab(int)));
}

CustomTabWidget::~CustomTabWidget()
{
    qDebug()<<"CustomTabWidget::~CustomTabWidget()";
}

void CustomTabWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//启用反走样以得到平滑的边缘
    painter.setPen(QColor("#FDFDFD"));
    painter.setBrush(QColor("#FDFDFD"));
    painter.save();

    QRect bgRect = rect();
    bgRect.setWidth(rect().width());
    bgRect.setHeight(rect().height());
    painter.drawRect(bgRect);

    painter.restore();


    //set Style...
    QStyleOption opt;
    initStyleOption((QStyleOptionTabWidgetFrame*)&opt);
    opt.init(this);
    painter.setClipping(true);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}

void CustomTabWidget::closeTargetTab(int index)
{
    if(tabText(index) != tr("控制面板")){
        removeTab(index);
    }
}

void CustomTabWidget::addTabPage(int index)
{
    if(index <= -1 || index > 15){
        return;
    }

    QString   str;
    switch (index) {
    case 0:{
        QIcon* icon = new QIcon(QPixmap(":/Main/Title.png"));
        insertTab(index,ControlPanel::instance(),*icon, tr("控制面板"));
        str = tr("控制面板");
    }break;
    case 1:{
//        QIcon* icon = new QIcon(QPixmap(":/Main/Title.png"));
//        insertTab(index,ControlPanel::instance(),*icon, tr("运行状态"));
        str = tr("运行状态");
    }break;
    case 2:{
        QIcon* icon = new QIcon(QPixmap(":/Main/Title.png"));
        insertTab(index,MainWidget::instance(),*icon, tr("详细信息"));
        str = tr("详细信息");
    }break;
    case 3:{
    }break;
    case 4:{
    }break;
    case 5:{
    }break;
    case 6:{
    }
        break;
    case 7:{
    }break;
    case 8:{
    }break;
    case 9:{
    }break;
    default:
        break;
    }
    for(int i=0;i<count();i++){
        if(tabText(i) == str){
            setCurrentIndex(i);
        }
    }
}

void CustomTabWidget::initStyleOption(QStyleOptionTabWidgetFrame *option) const
{
    option->rect.setWidth(200);
    option->rect.setHeight(50);
    option->lineWidth = 4;
    option->midLineWidth = 4;
    option->shape = QTabBar::RoundedWest;
    option->tabBarSize = QSize(400,50);
    option->rightCornerWidgetSize = QSize(23,23);
    option->leftCornerWidgetSize = QSize(23,32);

//    qDebug()<<"option->lineWidth="<<option->lineWidth;
//    qDebug()<<"option->midLineWidth="<<option->midLineWidth;
}
