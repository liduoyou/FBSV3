#include "HookWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QGroupBox>
#include <QPainter>
#include <QStyleOption>
#include <QEvent>
#include <QDebug>
#include "../DataHeaderDefine.h"
#include "../Component/RoundWidget.h"
#include "../Component/SubLimitStatus.h"
HookWidget::HookWidget(HookType _type,QWidget *parent) :
    QWidget(parent)
  #ifdef MAXRESOLUTION
  , m_size(1012,675)
  #else
  , m_size(792,390)
  #endif
  , m_UpName(NULL)
  , m_UpStatus(NULL)
  , m_DownName(NULL)
  , m_DownStatus(NULL)
  , m_BrakingName(NULL)
  , m_BrakingStatus(NULL)
  , m_BrakingNumber(NULL)
  , m_BrakingNumberUnit(NULL)
  , m_HookUpLimit(NULL)
  , m_HookDownLimit(NULL)
  , m_HookUpCutSpeedLimit(NULL)
  , m_HookDownCutSpeedLimit(NULL)
  , m_HookUpOverLimit(NULL)
  , m_HookDownOverLimit(NULL)
  , m_GearName(NULL)
  , m_GearStatus(NULL)
  , m_WeightName(NULL)
  , m_WeightValue(NULL)
  , m_HeightName(NULL)
  , m_HeightValue(NULL)
  , m_SpeedName(NULL)
  , m_SpeedValue(NULL)
  , m_ScopeName(NULL)
  , m_ScopeValue(NULL)
  , m_RoundwidgetWeight(NULL)
  , m_RoundwidgetHeight(NULL)
  , m_RoundwidgetSpeed(NULL)
  , m_RoundwidgetScope(NULL)
  , m_RoundwidgetMoment(NULL)
  , m_type(_type)
{
    setupUI();
    setHookName();
    updateValueChange();
}

HookWidget::~HookWidget()
{
}

void HookWidget::setHookName()
{
    switch ((HookType)m_type){
    case Htype_NO1:
        m_BtnHookName->setText(tr("上小车")+tr("起升1"));//上小车1号吊钩
        break;
    case Htype_NO2:
        m_BtnHookName->setText(tr("上小车")+tr("起升2"));//上小车2号吊钩
        break;
    case Htype_NO3:
        m_BtnHookName->setText(tr("下小车")+tr("主起升"));
        break;
    case Htype_NO4:
        m_BtnHookName->setText(tr("下小车")+tr("副起升"));
        break;
    case Htype_NO5:
        m_BtnHookName->setText(tr("前天车\n")+tr("1号吊钩"));
        break;
    case Htype_NO6:
        m_BtnHookName->setText(tr("前天车\n")+tr("2号吊钩"));
        break;
    case Htype_NO7:
        m_BtnHookName->setText(tr("后天车\n")+tr("1号吊钩"));
        break;
    case Htype_NO8:
        m_BtnHookName->setText(tr("后天车\n")+tr("2号吊钩"));
        break;
    case Htype_NO9:
        m_BtnHookName->setText(tr("1#小车\n")+tr("1号吊钩"));
        break;
    case Htype_NO10:
        m_BtnHookName->setText(tr("1#小车\n")+tr("2号吊钩"));
        break;
    case Htype_NO11:
        m_BtnHookName->setText(tr("2#小车\n")+tr("1号吊钩"));
        break;
    case Htype_NO12:
        m_BtnHookName->setText(tr("2#小车\n")+tr("2号吊钩"));
        break;
    default:
        break;
    }
}

void HookWidget::updateValueChange()
{
//    m_WeightValue->setText(QString::number(getWeight(),10,2));
//    m_HeightValue->setText(QString::number(getHeight(),10,2));
//    m_SpeedValue->setText(QString::number(getSpeed(),10,2));
//    m_ScopeValue->setText(QString::number(getScope(),10,2));
    if(m_RoundwidgetWeight != NULL){
        m_RoundwidgetWeight->setValue(QString::number(getWeight(),10,2));
        m_RoundwidgetWeight->setNormalAngle(getWeight(),getnearMaxWeight(),getMaxWeight());
    }
    if(m_RoundwidgetHeight != NULL){
        m_RoundwidgetHeight->setValue(QString::number(getHeight(),10,2));
        m_RoundwidgetHeight->setSpecificAngle(getHeight(),getMinHeight(),getnearMinHeight(),
                                              getnearMaxHeight(),getMaxHeight());
    }
    if(m_RoundwidgetSpeed != NULL){
        m_RoundwidgetSpeed->setValue(QString::number(getSpeed(),10,2));
        m_RoundwidgetSpeed->setNormalAngle(getSpeed(),getnearMaxSpeed(),getMaxSpeed());
    }
    if(m_RoundwidgetScope != NULL){
        m_RoundwidgetScope->setValue(QString::number(getScope(),10,2));
        m_RoundwidgetScope->setSpecificAngle(getScope(),getMinScope(),getnearMinScope(),
                                              getnearMaxScope(),getMaxScope());
    }
    if(m_RoundwidgetMoment != NULL){
        m_RoundwidgetMoment->setValue(QString::number(getMoment(),10,2));
        m_RoundwidgetMoment->setNormalAngle(getMoment(),getnearMaxMoment(),getMaxMoment());
    }
    updateStatusChange();
}

void HookWidget::updateStatusChange()
{
    if(getUp()){
        m_UpStatus->setStyleSheet("QLabel{border:0px;background-color:#0f9d58;}");
    }else{
        m_UpStatus->setStyleSheet("QLabel{border:0px;background-color:#ABABAB;}");
    }
    if(getDown()){
        m_DownStatus->setStyleSheet("QLabel{border:0px;background-color:#0f9d58;}");
    }else{
        m_DownStatus->setStyleSheet("QLabel{border:0px;background-color:#ABABAB;}");
    }
    if(!getBraking()){
        m_BrakingStatus->setStyleSheet("QLabel{border:0px;background-color:#0f9d58;}");
    }else{
        m_BrakingStatus->setStyleSheet("QLabel{border:0px;background-color:#DB4437;}");
    }
    if(m_GearStatus != NULL)
        m_GearStatus->setText(QString::number(getGear()));

    if(m_BrakingNumber != NULL)
        m_BrakingNumber->setText(QString::number(getBrakingNumber()));

    if(m_HookUpLimit != NULL){
        m_HookUpLimit->setStatus(getLimitStatus() & 0x01);
    }
    if(m_HookDownLimit != NULL){
        m_HookDownLimit->setStatus(getLimitStatus() & 0x02);
    }
    if(m_HookUpCutSpeedLimit != NULL){
        m_HookUpCutSpeedLimit->setStatus(getLimitStatus() & 0x04);
    }
    if(m_HookDownCutSpeedLimit != NULL){
        m_HookDownCutSpeedLimit->setStatus(getLimitStatus() & 0x08);
    }
    if(m_HookUpOverLimit != NULL){
        m_HookUpOverLimit->setStatus(getLimitStatus() & 0x10);
    }
    if(m_HookDownOverLimit != NULL){
        m_HookDownOverLimit->setStatus(getLimitStatus() & 0x20);
    }
}

bool HookWidget::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == m_BtnHookName){
        if(e->type() == QEvent::Enter){
            return true;
        }else if(e->type() == QEvent::Leave){
            return false;
        }
    }
    return QObject::eventFilter(obj, e);
}

void HookWidget::setupUI()
{
    setFixedSize(m_size);
    setObjectName("HookWidget");
    setStyleSheet("#HookWidget{background-color:transparent;}");

//    m_BtnHookName = new QPushButton();
//    m_BtnHookName->setFixedSize(100,30);
//    m_BtnHookName->setFlat(true);
//    m_BtnHookName->setFocusPolicy(Qt::NoFocus);
//    m_BtnHookName->setObjectName("m_BtnHookName");
//    m_BtnHookName->setStyleSheet("#m_BtnHookName{border:0px;color:black;font-size:16px;background-color:#0f9d58;}");

    QHBoxLayout* HLayout = new QHBoxLayout();
    HLayout->setSizeConstraint(QLayout::SetMaximumSize);
    HLayout->setContentsMargins(0, 0, 0, 0);
    HLayout->setSpacing(5);

//    HLayout->addWidget(m_BtnHookName,1,Qt::AlignLeft|Qt::AlignTop);
//    HLayout->addLayout(initAbstractValueLayout());
    HLayout->addWidget(initDetailValueWidget(),1,Qt::AlignCenter);//Qt::AlignRight|Qt::AlignBottom);

    setLayout(HLayout);
}

QHBoxLayout* HookWidget::initAbstractValueLayout()
{
    QHBoxLayout* m_SwitchValueLayout = new QHBoxLayout();
    m_SwitchValueLayout->setSizeConstraint(QLayout::SetMaximumSize);
    m_SwitchValueLayout->setContentsMargins(5, 0, 0, 0);
    m_SwitchValueLayout->setSpacing(15);

    QWidget* switchValue0 = new QWidget();
    switchValue0->setObjectName("switchValue0");
    switchValue0->setStyleSheet("#switchValue0{border:0px;}");
    switchValue0->setFixedSize(75,50);
    switchValue0->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout0 = new QVBoxLayout();
    vLayout0->setContentsMargins(0, 0, 0, 0);
    vLayout0->setSpacing(0);

    m_UpName = new QLabel();
    m_UpName->setAlignment(Qt::AlignCenter);
    m_UpName->setText(tr("上升"));
    m_UpName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout0->addWidget(m_UpName,1,Qt::AlignCenter);

    m_UpStatus = new QLabel();
    m_UpStatus->setFixedSize(20,20);
    m_UpStatus->setAlignment(Qt::AlignCenter);
    m_UpStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:#ABABAB;}");
    vLayout0->addWidget(m_UpStatus,1,Qt::AlignCenter);

    switchValue0->setLayout(vLayout0);

    QWidget* switchValue1 = new QWidget();
    switchValue1->setObjectName("switchValue1");
    switchValue1->setStyleSheet("#switchValue1{border:0px;}");
    switchValue1->setFixedSize(75,50);
    switchValue1->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout1 = new QVBoxLayout();
    vLayout1->setContentsMargins(0, 0, 0, 0);
    vLayout1->setSpacing(0);

    m_DownName = new QLabel();
    m_DownName->setAlignment(Qt::AlignCenter);
    m_DownName->setText(tr("下降"));
    m_DownName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout1->addWidget(m_DownName,1,Qt::AlignCenter);

    m_DownStatus = new QLabel();
    m_DownStatus->setFixedSize(20,20);
    m_DownStatus->setAlignment(Qt::AlignCenter);
    m_DownStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:#ABABAB;}");
    vLayout1->addWidget(m_DownStatus,1,Qt::AlignCenter);

    switchValue1->setLayout(vLayout1);

    QWidget* switchValue2 = new QWidget();
    switchValue2->setObjectName("switchValue2");
    switchValue2->setStyleSheet("#switchValue2{border:0px;}");
    switchValue2->setFixedSize(75,50);
    switchValue2->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout2 = new QVBoxLayout();
    vLayout2->setContentsMargins(0, 0, 0, 0);
    vLayout2->setSpacing(0);

    m_BrakingName = new QLabel();
    m_BrakingName->setAlignment(Qt::AlignCenter);
    m_BrakingName->setText(tr("制动"));
    m_BrakingName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout2->addWidget(m_BrakingName,1,Qt::AlignCenter);

    m_BrakingStatus = new QLabel();
    m_BrakingStatus->setFixedSize(20,20);
    m_BrakingStatus->setAlignment(Qt::AlignCenter);
    m_BrakingStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:#ABABAB;}");
    vLayout2->addWidget(m_BrakingStatus,1,Qt::AlignCenter);

    switchValue2->setLayout(vLayout2);

    QWidget* switchValue3 = new QWidget();
    switchValue3->setObjectName("switchValue3");
    switchValue3->setStyleSheet("#switchValue3{border:0px;}");
    switchValue3->setFixedSize(75,50);
    switchValue3->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout3 = new QVBoxLayout();
    vLayout3->setContentsMargins(0, 0, 0, 0);
    vLayout3->setSpacing(0);

    m_GearName = new QLabel();
    m_GearName->setAlignment(Qt::AlignCenter);
    m_GearName->setText(tr("档位"));
    m_GearName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout3->addWidget(m_GearName,1,Qt::AlignCenter);

    m_GearStatus = new QLabel();
    m_GearStatus->setFixedSize(20,20);
    m_GearStatus->setAlignment(Qt::AlignCenter);
    m_GearStatus->setText(tr("0"));
    m_GearStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#ABABAB;}");
    vLayout3->addWidget(m_GearStatus,1,Qt::AlignCenter);

    switchValue3->setLayout(vLayout3);

    QWidget* switchValue4 = new QWidget();
    switchValue4->setObjectName("switchValue4");
    switchValue4->setStyleSheet("#switchValue4{border:0px;}");
    switchValue4->setFixedSize(75,50);
    switchValue4->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout4 = new QVBoxLayout();
    vLayout4->setContentsMargins(0, 0, 0, 0);
    vLayout4->setSpacing(0);

    m_WeightName = new QLabel();
    m_WeightName->setAlignment(Qt::AlignCenter);
    m_WeightName->setText(tr("吨位"));
    m_WeightName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout4->addWidget(m_WeightName,1,Qt::AlignCenter);

    m_WeightValue = new QLabel();
    m_WeightValue->setFixedSize(75,20);
    m_WeightValue->setAlignment(Qt::AlignCenter);
    m_WeightValue->setText(tr("000.000"));
    m_WeightValue->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#ABABAB;}");
    vLayout4->addWidget(m_WeightValue,1,Qt::AlignCenter);

    switchValue4->setLayout(vLayout4);

    QWidget* switchValue5 = new QWidget();
    switchValue5->setObjectName("switchValue5");
    switchValue5->setStyleSheet("#switchValue5{border:0px;}");
    switchValue5->setFixedSize(75,50);
    switchValue5->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout5 = new QVBoxLayout();
    vLayout5->setContentsMargins(0, 0, 0, 0);
    vLayout5->setSpacing(0);

    m_HeightName = new QLabel();
    m_HeightName->setAlignment(Qt::AlignCenter);
    m_HeightName->setText(tr("高度"));
    m_HeightName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout5->addWidget(m_HeightName,1,Qt::AlignCenter);

    m_HeightValue = new QLabel();
    m_HeightValue->setFixedSize(75,20);
    m_HeightValue->setAlignment(Qt::AlignCenter);
    m_HeightValue->setText(tr("000.000"));
    m_HeightValue->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#ABABAB;}");
    vLayout5->addWidget(m_HeightValue,1,Qt::AlignCenter);

    switchValue5->setLayout(vLayout5);

    QWidget* switchValue6 = new QWidget();
    switchValue6->setObjectName("switchValue6");
    switchValue6->setStyleSheet("#switchValue6{border:0px;}");
    switchValue6->setFixedSize(75,50);
    switchValue6->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout6 = new QVBoxLayout();
    vLayout6->setContentsMargins(0, 0, 0, 0);
    vLayout6->setSpacing(0);

    m_SpeedName = new QLabel();
    m_SpeedName->setAlignment(Qt::AlignCenter);
    m_SpeedName->setText(tr("速度"));
    m_SpeedName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout6->addWidget(m_SpeedName,1,Qt::AlignCenter);

    m_SpeedValue = new QLabel();
    m_SpeedValue->setFixedSize(75,20);
    m_SpeedValue->setAlignment(Qt::AlignCenter);
    m_SpeedValue->setText(tr("000.000"));
    m_SpeedValue->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#ABABAB;}");
    vLayout6->addWidget(m_SpeedValue,1,Qt::AlignCenter);

    switchValue6->setLayout(vLayout6);

    QWidget* switchValue7 = new QWidget();
    switchValue7->setObjectName("switchValue4");
    switchValue7->setStyleSheet("#switchValue4{border:0px;}");
    switchValue7->setFixedSize(75,50);
    switchValue7->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout7 = new QVBoxLayout();
    vLayout7->setContentsMargins(0, 0, 0, 0);
    vLayout7->setSpacing(0);

    m_ScopeName = new QLabel();
    m_ScopeName->setAlignment(Qt::AlignCenter);
    m_ScopeName->setText(tr("幅度"));
    m_ScopeName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout7->addWidget(m_ScopeName,1,Qt::AlignCenter);

    m_ScopeValue = new QLabel();
    m_ScopeValue->setFixedSize(75,20);
    m_ScopeValue->setAlignment(Qt::AlignCenter);
    m_ScopeValue->setText(tr("000.000"));
    m_ScopeValue->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#ABABAB;}");
    vLayout7->addWidget(m_ScopeValue,1,Qt::AlignCenter);

    switchValue7->setLayout(vLayout7);

    m_SwitchValueLayout->addWidget(switchValue0);
    m_SwitchValueLayout->addWidget(switchValue1);
    m_SwitchValueLayout->addWidget(switchValue2);
    m_SwitchValueLayout->addWidget(switchValue3);
    m_SwitchValueLayout->addWidget(switchValue4);
    m_SwitchValueLayout->addWidget(switchValue5);
    m_SwitchValueLayout->addWidget(switchValue6);
    m_SwitchValueLayout->addWidget(switchValue7);

    return m_SwitchValueLayout;
}

QWidget *HookWidget::initDetailValueWidget()
{
    m_detailValueWidget = new QWidget();
#ifdef MAXRESOLUTION
    m_detailValueWidget->setFixedSize(1012,675);
#else
    m_detailValueWidget->setFixedSize(792,390);
#endif
    m_detailValueWidget->setStyleSheet("QWidget{background-color:transparent;}");

    m_BtnHookName = new QPushButton(m_detailValueWidget);
    m_BtnHookName->setFixedSize(100,30);
    m_BtnHookName->setFlat(true);
    m_BtnHookName->setFocusPolicy(Qt::NoFocus);
    m_BtnHookName->setObjectName("m_BtnHookName");
    m_BtnHookName->setStyleSheet("#m_BtnHookName{border:0px;color:#FDFDFD;font-size:16px;background-color:#0f9d58;}");
    m_BtnHookName->move(35,15);

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(m_BtnHookName);
    shadow_effect->setOffset(4,4);
    shadow_effect->setColor(QColor("#787878"));
    shadow_effect->setBlurRadius(8);
    m_BtnHookName->setGraphicsEffect(shadow_effect);

    QVBoxLayout* VLayout = new QVBoxLayout();
    VLayout->setSizeConstraint(QLayout::SetMaximumSize);
    VLayout->setContentsMargins(0, 0, 0, 0);
    VLayout->setSpacing(0);

    QHBoxLayout* hLayout1 = new QHBoxLayout();
    hLayout1->setContentsMargins(0, 0, 0, 0);
    hLayout1->setSpacing(0);

    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout2->setContentsMargins(0, 0, 0, 0);
    hLayout2->setSpacing(0);

    QWidget* switchValue0 = new QWidget();
    switchValue0->setObjectName("switchValue0");
    switchValue0->setStyleSheet("#switchValue0{border:0px;}");
#ifdef MAXRESOLUTION
    switchValue0->setFixedSize(75,220);
#else
    switchValue0->setFixedSize(75,120);
#endif
    switchValue0->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout0 = new QVBoxLayout();
    vLayout0->setContentsMargins(0, 0, 0, 0);
    vLayout0->setSpacing(0);

    m_UpName = new QLabel();
    m_UpName->setAlignment(Qt::AlignCenter);
    m_UpName->setText(tr("上升"));
    m_UpName->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:transparent;}");

    m_UpStatus = new QLabel();
    m_UpStatus->setFixedSize(40,40);
    m_UpStatus->setAlignment(Qt::AlignCenter);
    m_UpStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:#ABABAB;}");

    vLayout0->addWidget(m_UpName,1,Qt::AlignCenter);
    vLayout0->addWidget(m_UpStatus,1,Qt::AlignCenter);

    switchValue0->setLayout(vLayout0);

    QWidget* switchValue1 = new QWidget();
    switchValue1->setObjectName("switchValue1");
    switchValue1->setStyleSheet("#switchValue1{border:0px;}");
#ifdef MAXRESOLUTION
    switchValue1->setFixedSize(75,220);
#else
    switchValue1->setFixedSize(75,120);
#endif
    switchValue1->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout1 = new QVBoxLayout();
    vLayout1->setContentsMargins(0, 0, 0, 0);
    vLayout1->setSpacing(0);

    m_DownName = new QLabel();
    m_DownName->setAlignment(Qt::AlignCenter);
    m_DownName->setText(tr("下降"));
    m_DownName->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:transparent;}");

    m_DownStatus = new QLabel();
    m_DownStatus->setFixedSize(40,40);
    m_DownStatus->setAlignment(Qt::AlignCenter);
    m_DownStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:#ABABAB;}");

    vLayout1->addWidget(m_DownName,1,Qt::AlignCenter);
    vLayout1->addWidget(m_DownStatus,1,Qt::AlignCenter);

    switchValue1->setLayout(vLayout1);

    QWidget* switchValue2 = new QWidget();
    switchValue2->setObjectName("switchValue2");
    switchValue2->setStyleSheet("#switchValue2{border:0px;}");
#ifdef MAXRESOLUTION
    switchValue2->setFixedSize(75,220);
#else
    switchValue2->setFixedSize(75,120);
#endif
    switchValue2->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout2 = new QVBoxLayout();
    vLayout2->setContentsMargins(0, 0, 0, 0);
    vLayout2->setSpacing(0);

    m_GearName = new QLabel();
    m_GearName->setAlignment(Qt::AlignCenter);
    m_GearName->setText(tr("档位"));
    m_GearName->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:transparent;}");

    m_GearStatus = new QLabel();
    m_GearStatus->setFixedSize(40,40);
    m_GearStatus->setAlignment(Qt::AlignCenter);
    m_GearStatus->setText(tr("0"));
    m_GearStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:25px;background-color:#ABABAB;}");
    vLayout2->addWidget(m_GearName,1,Qt::AlignCenter);
    vLayout2->addWidget(m_GearStatus,1,Qt::AlignCenter);

    switchValue2->setLayout(vLayout2);

    QWidget* switchValue3 = new QWidget();
    switchValue3->setObjectName("switchValue3");
    switchValue3->setStyleSheet("#switchValue3{border:0px;}");
#ifdef MAXRESOLUTION
    switchValue3->setFixedSize(75,220);
#else
    switchValue3->setFixedSize(75,120);
#endif
    switchValue3->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout3 = new QVBoxLayout();
    vLayout3->setContentsMargins(0, 0, 0, 0);
    vLayout3->setSpacing(0);

    m_BrakingName = new QLabel();
    m_BrakingName->setAlignment(Qt::AlignCenter);
    m_BrakingName->setText(tr("制动"));
    m_BrakingName->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:transparent;}");

    m_BrakingStatus = new QLabel();
    m_BrakingStatus->setFixedSize(40,40);
    m_BrakingStatus->setAlignment(Qt::AlignCenter);
    m_BrakingStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:#DB4437;}");
    vLayout3->addWidget(m_BrakingName,1,Qt::AlignCenter);
    vLayout3->addWidget(m_BrakingStatus,1,Qt::AlignCenter);

    switchValue3->setLayout(vLayout3);

    QWidget* switchValue4 = new QWidget();
    switchValue4->setObjectName("switchValue4");
    switchValue4->setStyleSheet("#switchValue4{border:0px;}");
#ifdef MAXRESOLUTION
    switchValue4->setFixedSize(90,150);
#else
    switchValue4->setFixedSize(90,100);
#endif
    switchValue4->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QHBoxLayout* hLayout4 = new QHBoxLayout();
    hLayout4->setContentsMargins(0, 0, 0, 0);
    hLayout4->setSpacing(5);

    m_BrakingNumber = new QLabel();
    m_BrakingNumber->setAlignment(Qt::AlignCenter);
    m_BrakingNumber->setFixedSize(75,25);
    m_BrakingNumber->setText(tr("0"));
    m_BrakingNumber->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:#ABABAB;}");

    m_BrakingNumberUnit = new QLabel();
    m_BrakingNumberUnit->setAlignment(Qt::AlignCenter);
    m_BrakingNumberUnit->setText(tr("次"));
    m_BrakingNumberUnit->setStyleSheet("QLabel{border:0px;color:black;font-size:14px;background-color:transparent;}");
    hLayout4->addWidget(m_BrakingNumber,1,Qt::AlignBottom|Qt::AlignRight);
    hLayout4->addWidget(m_BrakingNumberUnit,1,Qt::AlignBottom|Qt::AlignRight);

    switchValue4->setLayout(hLayout4);

    QWidget* switchValue5 = new QWidget();
    switchValue5->setObjectName("switchValue5");
    switchValue5->setStyleSheet("#switchValue5{border:0px;}");
#ifdef MAXRESOLUTION
    switchValue5->setFixedSize(410,220);
#else
    switchValue5->setFixedSize(410,120);
#endif
    switchValue5->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QHBoxLayout* hLayout5 = new QHBoxLayout();
    hLayout5->setContentsMargins(0, 0, 0, 0);
    hLayout5->setSpacing(15);

    QVBoxLayout* vvLayout1 = new QVBoxLayout();
    vvLayout1->setContentsMargins(0, 0, 0, 0);
    vvLayout1->setSpacing(0);

    QVBoxLayout* vvLayout2 = new QVBoxLayout();
    vvLayout2->setContentsMargins(0, 0, 0, 0);
    vvLayout2->setSpacing(0);

    m_HookUpLimit=new SubLimitStatus();//起升上限位
    m_HookUpLimit->setObjectName("HookUpLimit");
    m_HookUpLimit->mygetmember("limitname")->setText(tr("起升上限位"));
    m_HookUpLimit->setLimitProperty(true);

    m_HookDownLimit=new SubLimitStatus();//起升下限位
    m_HookDownLimit->setObjectName("HookDownLimit");
    m_HookDownLimit->mygetmember("limitname")->setText(tr("起升下限位"));
    m_HookDownLimit->setLimitProperty(true);

    m_HookUpCutSpeedLimit=new SubLimitStatus();//起升上减速限位
    m_HookUpCutSpeedLimit->setObjectName("HookUpCutSpeedLimit");
    m_HookUpCutSpeedLimit->mygetmember("limitname")->setText(tr("起升上减速限位"));
    m_HookUpCutSpeedLimit->setLimitProperty(true);

    m_HookDownCutSpeedLimit=new SubLimitStatus();//起升下减速限位
    m_HookDownCutSpeedLimit->setObjectName("HookDownCutSpeedLimit");
    m_HookDownCutSpeedLimit->mygetmember("limitname")->setText(tr("起升下减速限位"));
    m_HookDownCutSpeedLimit->setLimitProperty(true);

    m_HookUpOverLimit=new SubLimitStatus();//起升上极限限位
    m_HookUpOverLimit->setObjectName("HookUpOverLimit");
    m_HookUpOverLimit->mygetmember("limitname")->setText(tr("起升上极限限位"));
    m_HookUpOverLimit->setLimitProperty(true);

    m_HookDownOverLimit=new SubLimitStatus();//起升下极限限位
    m_HookDownOverLimit->setObjectName("HookDownOverLimit");
    m_HookDownOverLimit->mygetmember("limitname")->setText(tr("起升下极限限位"));
    m_HookDownOverLimit->setLimitProperty(true);

    vvLayout1->addWidget(m_HookUpLimit);
    vvLayout2->addWidget(m_HookDownLimit);
    vvLayout1->addWidget(m_HookUpCutSpeedLimit);
    vvLayout2->addWidget(m_HookDownCutSpeedLimit);
    vvLayout1->addWidget(m_HookUpOverLimit);
    vvLayout2->addWidget(m_HookDownOverLimit);

    hLayout5->addLayout(vvLayout1);
    hLayout5->addLayout(vvLayout2);

    switchValue5->setLayout(hLayout5);

#ifndef MAXRESOLUTION
    hLayout1->addSpacing(100);
#endif
    m_RoundwidgetWeight = new RoundWidget(tr("吨位,T"));
    m_RoundwidgetHeight = new RoundWidget(tr("高度,M"));
    m_RoundwidgetSpeed = new RoundWidget(tr("速度,M/S"));
//    m_RoundwidgetScope = new RoundWidget(tr("幅度,M"));
//    m_RoundwidgetMoment = new RoundWidget(tr("力矩,KN*M"));
    hLayout1->addWidget(m_RoundwidgetWeight);
    hLayout1->addWidget(m_RoundwidgetHeight);
    hLayout1->addWidget(m_RoundwidgetSpeed);
//    hLayout1->addWidget(m_RoundwidgetScope);
//    hLayout1->addWidget(m_RoundwidgetMoment);
#ifndef MAXRESOLUTION
    hLayout1->addSpacing(85);//100
#endif
    hLayout1->addWidget(switchValue0);
    hLayout1->addWidget(switchValue1);

    hLayout2->addStretch(1);
    hLayout2->addWidget(switchValue5);
    hLayout2->addStretch(1);
    hLayout2->addWidget(switchValue2);
    hLayout2->addWidget(switchValue3);
    hLayout2->addWidget(switchValue4);
    hLayout2->addStretch(1);

    VLayout->addLayout(hLayout1);
    VLayout->addLayout(hLayout2);

    m_detailValueWidget->setLayout(VLayout);

    return m_detailValueWidget;
}

void HookWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QColor("#FDFDFD"));
    painter.setBrush(QColor("#FDFDFD"));

    painter.save();

    QRect bgRect;
    bgRect.setWidth(width());
    bgRect.setHeight(height());
    painter.drawRect(bgRect);

    painter.restore();
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

    QWidget::paintEvent(event);
}

