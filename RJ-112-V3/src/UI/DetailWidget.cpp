#include "DetailWidget.h"
#include <QDebug>
#include <QStackedWidget>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QMouseEvent>
#include "../Component/NavigationNode.h"
#include "../DataHeaderDefine.h"
DetailWidget::DetailWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUI();
    installEventFilter(this);
    //test
    m_HookNo1Widget->setWeight(23.45);
    m_HookNo2Widget->setHeight(42.11);
    m_HookNo3Widget->setSpeed(65.31);
    m_HookNo4Widget->setWeight(85.31);
    quint8 limitstatus = m_HookNo1Widget->getLimitStatus();
    clrbit(limitstatus,0);clrbit(limitstatus,1);
    m_HookNo1Widget->setLimitStatus(limitstatus);
    m_HookNo1Widget->setUp(true);
    m_littleVehicleNo1Widget->setDistance(2.31);
    m_littleVehicleNo2Widget->setSpeed(34.31);
    m_bigVehicleWidget->setSteelLegDistance(56.31);
    m_bigVehicleWidget->setWindSpeed(6.31);

    m_HookNo1Widget->updateValueChange();
    m_HookNo2Widget->updateValueChange();
    m_HookNo3Widget->updateValueChange();
    m_HookNo4Widget->updateValueChange();
    m_littleVehicleNo1Widget->updateValueChange();
    m_littleVehicleNo2Widget->updateValueChange();
    m_bigVehicleWidget->updateValueChange();
}

DetailWidget::~DetailWidget()
{
    qDebug()<<"DetailWidget::~DetailWidget()";
}

void DetailWidget::setupUI()
{
    m_bigVehicleWidget = new BigVehicleWidget(BigVehicle::BVtype_NoSpeed);

    m_HookNo1Widget = new HookWidget(HookWidget::Htype_NO1);
    m_HookNo2Widget = new HookWidget(HookWidget::Htype_NO2);
    m_HookNo3Widget = new HookWidget(HookWidget::Htype_NO3);
    m_HookNo4Widget = new HookWidget(HookWidget::Htype_NO4);

    m_littleVehicleNo1Widget = new LittleVehicleWidget(LittleVehicleWidget::LVtype_UpVehicle);
    m_littleVehicleNo2Widget = new LittleVehicleWidget(LittleVehicleWidget::LVtype_DownVehicle);

    m_stackedWidget = new QStackedWidget();
    m_stackedWidget->setFocusPolicy(Qt::StrongFocus);
    m_stackedWidget->addWidget(m_HookNo1Widget);
    m_stackedWidget->addWidget(m_HookNo2Widget);
    m_stackedWidget->addWidget(m_HookNo3Widget);
    m_stackedWidget->addWidget(m_HookNo4Widget);

    m_stackedWidget->setCurrentIndex(0);

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(m_stackedWidget);
    shadow_effect->setOffset(4,4);
    shadow_effect->setColor(QColor("#787878"));
    shadow_effect->setBlurRadius(8);
    m_stackedWidget->setGraphicsEffect(shadow_effect);

    m_stackedWidget->addWidget(m_littleVehicleNo1Widget);
    m_stackedWidget->addWidget(m_littleVehicleNo2Widget);
    m_stackedWidget->addWidget(m_bigVehicleWidget);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);//5
    layout->setSpacing(0);
    layout->addWidget(initTopBtnGroup(),1,Qt::AlignCenter);
    layout->addWidget(m_stackedWidget,1,Qt::AlignCenter);
    layout->addWidget(initNavigationNode(),1,Qt::AlignCenter);

    setLayout(layout);
}

QWidget *DetailWidget::initTopBtnGroup()
{
    m_topWidget = new QWidget();
#ifdef MAXRESOLUTION
    m_topWidget->setFixedSize(1024-4,40);
#else
    m_topWidget->setFixedSize(800-4,40);
#endif
    m_topWidget->setStyleSheet("QWidget{background-color:#FDFDFD;}");
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(m_topWidget);
    shadow_effect->setOffset(4,4);
    shadow_effect->setColor(QColor("#787878"));
    shadow_effect->setBlurRadius(8);
    m_topWidget->setGraphicsEffect(shadow_effect);

    m_previousBtn = new QPushButton();
    m_previousBtn->setFixedSize(30,30);
    m_previousBtn->setFocusPolicy(Qt::NoFocus);
    m_previousBtn->setFlat(true);
    m_previousBtn->setCheckable(true);
    m_previousBtn->setChecked(false);
    m_previousBtn->setStyleSheet("QPushButton{border:0px;image: url(:/Main/left.png);} \
                                 QPushButton:hover:pressed{border:0px;image: url(:/Main/left_p.png);}\
                            QPushButton:hover:!pressed{border:0px;image: url(:/Main/left_p.png);}");
    connect(m_previousBtn,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
//    m_previousBtn->setText(tr("PREVIOUS"));

    m_moreBtn = new QPushButton();
    m_moreBtn->setFixedSize(30,30);
    m_moreBtn->setFocusPolicy(Qt::NoFocus);
    m_moreBtn->setFlat(true);
    m_moreBtn->setCheckable(true);
    m_moreBtn->setChecked(false);
    m_moreBtn->setStyleSheet("QPushButton{border:0px;image: url(:/Main/more.png);} \
                             QPushButton:hover:pressed{border:0px;image: url(:/Main/more_p.png);}\
                            QPushButton:hover:!pressed{border:0px;image: url(:/Main/more_p.png);}");
    connect(m_moreBtn,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
//    m_moreBtn->setText(tr("MORE"));

    m_nextBtn = new QPushButton();
    m_nextBtn->setFixedSize(30,30);
    m_nextBtn->setFocusPolicy(Qt::NoFocus);
    m_nextBtn->setFlat(true);
    m_nextBtn->setCheckable(true);
    m_nextBtn->setChecked(false);
    m_nextBtn->setStyleSheet("QPushButton{border:0px;image: url(:/Main/right.png);} \
                             QPushButton:hover:pressed{image: url(:/Main/right_p.png);border:0px;}\
                            QPushButton:hover:!pressed{image: url(:/Main/right_p.png);border:0px;}");
    connect(m_nextBtn,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
//    m_nextBtn->setText(tr("NEXT"));

    QHBoxLayout* Hlayout = new QHBoxLayout();
    Hlayout->setContentsMargins(0,0,0,0);
    Hlayout->addWidget(m_previousBtn,1,Qt::AlignRight);
    Hlayout->addWidget(m_moreBtn);
    Hlayout->addWidget(m_nextBtn);

    m_topWidget->setLayout(Hlayout);

    return m_topWidget;
}

bool DetailWidget::eventFilter(QObject *obj, QEvent *event)
{
    int offset = 0;
    if(obj == this){
        if (event->type() == QEvent::MouseMove){
            QMouseEvent* me = (QMouseEvent*) event;
            if ((me->buttons() & Qt::LeftButton)) {
                if (!mMoveStart) {
                    mMoveStart = true;
                    mContinousMove =false;
                    mMousePoint = me->globalPos();

                    mMousestartPoint = mMousePoint;//add new code
                }else{
                    QPoint p = me->globalPos();
                    offset = p.x() - mMousePoint.x();
                    if( !mContinousMove && ( offset > -10 && offset < 10 ) )
                        return false;

                    mContinousMove = true;
//                    qDebug()<<"offset 1 ="<<offset<<p;
                    mMousePoint = p;
                }
                return true;
            }
        }
        if (event->type() == QEvent::MouseButtonRelease) {
            //add new code
            QMouseEvent* me = (QMouseEvent*) event;
            QPoint mMouseendPoint = me->globalPos();
            int offset = 0;
            offset = mMouseendPoint.x()-mMousestartPoint.x();
            if(offset > 200){
                tabPageButtonClicked(m_stackedWidget->currentIndex()-1);
                m_navigationNode->changeClickFlag(m_navigationNode->getClickedFlag()-1);
            }else if(offset < -200){
                tabPageButtonClicked(m_stackedWidget->currentIndex()+1);
                m_navigationNode->changeClickFlag(m_navigationNode->getClickedFlag()+1);
            }

            mMoveStart = false;
        }
    }
    return QObject::eventFilter(obj, event);
}

QWidget *DetailWidget::initNavigationNode()
{
    m_navigationNode = new NavigationNode();
    connect(m_navigationNode,SIGNAL(NodeClicked(int)),this,SLOT(tabPageButtonClicked(int)));
//    m_navigationNode->move(this->width()/2-m_navigationNode->width()/2,this->height()-40);
//    m_navigationNode->show();
    return m_navigationNode;
}

void DetailWidget::onButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(btn == m_previousBtn){
        tabPageButtonClicked(m_stackedWidget->currentIndex()-1);
        m_navigationNode->changeClickFlag(m_navigationNode->getClickedFlag()-1);
    }else if(btn == m_nextBtn){
        tabPageButtonClicked(m_stackedWidget->currentIndex()+1);
        m_navigationNode->changeClickFlag(m_navigationNode->getClickedFlag()+1);
    }else if(btn == m_moreBtn){

    }
}

void DetailWidget::tabPageButtonClicked(int index){
    if(index >= 0  && index < m_stackedWidget->count()){
        m_stackedWidget->setCurrentIndex(index);
        needReactiveWindow();
    }
}

void DetailWidget::activeNotice(bool isActive){
    if(isActive){
        needReactiveWindow();
    }
}

void DetailWidget::needReactiveWindow(){
    activateWindow();
    m_stackedWidget->currentWidget()->activateWindow();
}
