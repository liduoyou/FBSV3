#include "ControlPanel.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QMutexLocker>
#include "../MainWidget.h"
#include "../DataHeaderDefine.h"
QMutex ControlPanel::m_instanceLock;
ControlPanel* ControlPanel::m_ControlPanelInstance = NULL;

ControlPanel* ControlPanel::instance(){
    QMutexLocker lock(&m_instanceLock);
    if(m_ControlPanelInstance == NULL){
        m_ControlPanelInstance = new ControlPanel();
    }
    return m_ControlPanelInstance;
}

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent)
  #ifdef MAXRESOLUTION
  , m_size(1024,768)
  #else
  , m_size(800,480)
  #endif
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_LayoutUsesWidgetRect);
    setFixedSize(m_size);
    setFocusPolicy(Qt::StrongFocus);

    setupUI();
}

ControlPanel::~ControlPanel()
{
    qDebug()<<"ControlPanel::~ControlPanel()";
}

void ControlPanel::setupUI()
{
    setLayout(initControlPanel());
}

QVBoxLayout* ControlPanel::initControlPanel()
{
    QVBoxLayout* pVBoxlayout = new QVBoxLayout();
    pVBoxlayout->setSizeConstraint(QLayout::SetMaximumSize);
    pVBoxlayout->setContentsMargins(40,0,40,70);
    pVBoxlayout->setSpacing(20);

    QWidget* pwidget = new QWidget();
    pwidget->setFixedHeight(30);//m_size.width()-80,
    pwidget->setStyleSheet("QWidget{background-color:#ABABAB;}");

    QHBoxLayout* phlayout = new QHBoxLayout();
    phlayout->setContentsMargins(15,0,0,0);
    phlayout->setSpacing(0);

    cphlayout = new QHBoxLayout();
    cphlayout->setContentsMargins(0,0,0,0);
    cphlayout->setSpacing(0);

    QVBoxLayout* pVlayout = new QVBoxLayout();
    pVlayout->setContentsMargins(0,0,0,0);
    pVlayout->setSpacing(20);

    m_OperateAndControlName = new QLabel();//操作与控制
    m_OperateAndControlName->setText(tr("操作与控制"));
    m_OperateAndControlName->setStyleSheet("QLabel{font:blod;color:#FDFDFD}");
    m_OperateAndControlFoldBtn = new QPushButton();
    m_OperateAndControlFoldBtn->setText(tr("折叠"));//展开
    m_OperateAndControlFoldBtn->setFlat(true);
    m_OperateAndControlFoldBtn->setFocusPolicy(Qt::NoFocus);
    m_OperateAndControlFoldBtn->setCheckable(true);
    m_OperateAndControlFoldBtn->setChecked(true);
    connect(m_OperateAndControlFoldBtn,SIGNAL(clicked(bool)),this,SLOT(widgetHide(bool)));
    m_OperateAndControlFoldBtn->setStyleSheet("QPushButton{background-color:transparent;}");

    phlayout->addWidget(m_OperateAndControlName,1,Qt::AlignLeft);
//    phlayout->addWidget(m_OperateAndControlFoldBtn,1,Qt::AlignRight);
    pwidget->setLayout(phlayout);

    m_RuningStatus = new QPushButton();//运行状态
    m_RuningStatus->setFixedSize(80,50);
    connect(m_RuningStatus,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_RuningStatus->setFocusPolicy(Qt::NoFocus);
//    m_RuningStatus->setIcon(QIcon(QPixmap(":/Main/Title.png")));
    m_RuningStatus->setText(tr("运行状态"));
    m_DetailWidgetInfo = new QPushButton();//详细信息
    m_DetailWidgetInfo->setFixedSize(80,50);
    connect(m_DetailWidgetInfo,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_DetailWidgetInfo->setFocusPolicy(Qt::NoFocus);
    m_DetailWidgetInfo->setText(tr("详细信息"));
    m_ControlCondition = new QPushButton();//控制条件
    m_ControlCondition->setFixedSize(80,50);
    connect(m_ControlCondition,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_ControlCondition->setFocusPolicy(Qt::NoFocus);
    m_ControlCondition->setText(tr("控制条件"));

    cphlayout->addWidget(m_RuningStatus,1,Qt::AlignLeft);
    cphlayout->addWidget(m_DetailWidgetInfo,1,Qt::AlignLeft);
    cphlayout->addWidget(m_ControlCondition,1,Qt::AlignLeft);

    pVlayout->addWidget(pwidget);
    pVlayout->addLayout(cphlayout);


    QWidget* pwidget1 = new QWidget();
    pwidget1->setFixedHeight(30);//->setFixedSize(m_size.width()-80,30);
    pwidget1->setStyleSheet("QWidget{background-color:#ABABAB;}");

    QHBoxLayout* phlayout1 = new QHBoxLayout();
    phlayout1->setContentsMargins(15,0,0,0);
    phlayout1->setSpacing(0);

    cphlayout1 = new QHBoxLayout();
    cphlayout1->setContentsMargins(0,0,0,0);
    cphlayout1->setSpacing(0);

    QVBoxLayout* pVlayout1 = new QVBoxLayout();
    pVlayout1->setContentsMargins(0,0,0,0);
    pVlayout1->setSpacing(20);

    m_MaintainAndManagerName = new QLabel();//维护与管理
    m_MaintainAndManagerName->setText(tr("维护与管理"));
    m_MaintainAndManagerName->setStyleSheet("QLabel{font:blod;color:#FDFDFD}");
    m_MaintainAndManagerFoldBtn = new QPushButton();
    m_MaintainAndManagerFoldBtn->setText(tr("折叠"));//展开
    m_MaintainAndManagerFoldBtn->setFlat(true);
    m_MaintainAndManagerFoldBtn->setFocusPolicy(Qt::NoFocus);
    m_MaintainAndManagerFoldBtn->setCheckable(true);
    m_MaintainAndManagerFoldBtn->setChecked(true);
    connect(m_MaintainAndManagerFoldBtn,SIGNAL(clicked(bool)),this,SLOT(widgetHide(bool)));
    m_MaintainAndManagerFoldBtn->setStyleSheet("QPushButton{background-color:transparent;}");

    phlayout1->addWidget(m_MaintainAndManagerName,1,Qt::AlignLeft);
//    phlayout1->addWidget(m_MaintainAndManagerFoldBtn,1,Qt::AlignRight);
    pwidget1->setLayout(phlayout1);

    m_DataProcess = new QPushButton();//数据处理
    m_DataProcess->setFixedSize(80,50);
    connect(m_DataProcess,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_DataProcess->setFocusPolicy(Qt::NoFocus);
    m_DataProcess->setText(tr("数据处理"));
    m_EquipmentCalibration = new QPushButton();//设备标定
    m_EquipmentCalibration->setFixedSize(80,50);
    connect(m_EquipmentCalibration,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_EquipmentCalibration->setFocusPolicy(Qt::NoFocus);
    m_EquipmentCalibration->setText(tr("设备标定"));
    m_SystemSettings = new QPushButton();//系统设置
    m_SystemSettings->setFixedSize(80,50);
    connect(m_SystemSettings,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_SystemSettings->setFocusPolicy(Qt::NoFocus);
    m_SystemSettings->setText(tr("系统设置"));

    cphlayout1->addWidget(m_DataProcess,1,Qt::AlignLeft);
    cphlayout1->addWidget(m_EquipmentCalibration,1,Qt::AlignLeft);
    cphlayout1->addWidget(m_SystemSettings,1,Qt::AlignLeft);

    pVlayout1->addWidget(pwidget1);
    pVlayout1->addLayout(cphlayout1);


    QWidget* pwidget2 = new QWidget();
    pwidget2->setFixedHeight(30);//->setFixedSize(m_size.width()-80,30);
    pwidget2->setStyleSheet("QWidget{background-color:#ABABAB;}");

    QHBoxLayout* phlayout2 = new QHBoxLayout();
    phlayout2->setContentsMargins(15,0,0,0);
    phlayout2->setSpacing(0);

    cphlayout2 = new QHBoxLayout();
    cphlayout2->setContentsMargins(0,0,0,0);
    cphlayout2->setSpacing(0);

    QVBoxLayout* pVlayout2 = new QVBoxLayout();
    pVlayout2->setContentsMargins(0,0,0,0);
    pVlayout2->setSpacing(20);

    m_DataAndStatisticsName = new QLabel();
    m_DataAndStatisticsName->setText(tr("数据与统计"));
    m_DataAndStatisticsName->setStyleSheet("QLabel{font:blod;color:#FDFDFD}");
    m_DataAndStatisticsFoldBtn = new QPushButton();
    m_DataAndStatisticsFoldBtn->setText(tr("折叠"));//展开
    m_DataAndStatisticsFoldBtn->setFlat(true);
    m_DataAndStatisticsFoldBtn->setFocusPolicy(Qt::NoFocus);
    m_DataAndStatisticsFoldBtn->setCheckable(true);
    m_DataAndStatisticsFoldBtn->setChecked(true);
    connect(m_DataAndStatisticsFoldBtn,SIGNAL(clicked(bool)),this,SLOT(widgetHide(bool)));
    m_DataAndStatisticsFoldBtn->setStyleSheet("QPushButton{background-color:transparent;}");

    phlayout2->addWidget(m_DataAndStatisticsName,1,Qt::AlignLeft);
//    phlayout2->addWidget(m_DataAndStatisticsFoldBtn,1,Qt::AlignRight);
    pwidget2->setLayout(phlayout2);

    m_DataSheet = new QPushButton();//参数报表
    m_DataSheet->setFixedSize(80,50);
    connect(m_DataSheet,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_DataSheet->setFocusPolicy(Qt::NoFocus);
    m_DataSheet->setText(tr("参数报表"));
    m_DetectionObject = new QPushButton();//检测对象
    m_DetectionObject->setFixedSize(80,50);
    connect(m_DetectionObject,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_DetectionObject->setFocusPolicy(Qt::NoFocus);
    m_DetectionObject->setText(tr("检测对象"));
    m_AuxiliaryFunction = new QPushButton();//辅助功能
    m_AuxiliaryFunction->setFixedSize(80,50);
    connect(m_AuxiliaryFunction,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
    m_AuxiliaryFunction->setFocusPolicy(Qt::NoFocus);
    m_AuxiliaryFunction->setText(tr("辅助功能"));

    cphlayout2->addWidget(m_DataSheet,1,Qt::AlignLeft);
    cphlayout2->addWidget(m_DetectionObject,1,Qt::AlignLeft);
    cphlayout2->addWidget(m_AuxiliaryFunction,1,Qt::AlignLeft);

    pVlayout2->addWidget(pwidget2);
    pVlayout2->addLayout(cphlayout2);


    pVBoxlayout->addLayout(pVlayout);
    pVBoxlayout->addLayout(pVlayout1);
    pVBoxlayout->addLayout(pVlayout2);

    return pVBoxlayout;
}

void ControlPanel::widgetHide(bool)
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(btn == m_OperateAndControlFoldBtn){
        if(m_OperateAndControlFoldBtn->text().contains(tr("展开"))){
            m_RuningStatus->setHidden(true);
            m_DetailWidgetInfo->setHidden(true);
            m_ControlCondition->setHidden(true);
            m_OperateAndControlFoldBtn->setText(tr("折叠"));
        }else if(m_OperateAndControlFoldBtn->text().contains(tr("折叠"))){
            m_RuningStatus->setHidden(false);
            m_DetailWidgetInfo->setHidden(false);
            m_ControlCondition->setHidden(false);
            m_OperateAndControlFoldBtn->setText(tr("展开"));
        }
    }else if(btn == m_MaintainAndManagerFoldBtn){
        if(m_MaintainAndManagerFoldBtn->text().contains(tr("展开"))){
            m_DataProcess->setVisible(true);
            m_EquipmentCalibration->setVisible(true);
            m_SystemSettings->setVisible(true);
            m_MaintainAndManagerFoldBtn->setText(tr("折叠"));
        }else if(m_MaintainAndManagerFoldBtn->text().contains(tr("折叠"))){
            m_DataProcess->setVisible(false);
            m_EquipmentCalibration->setVisible(false);
            m_SystemSettings->setVisible(false);
            m_MaintainAndManagerFoldBtn->setText(tr("展开"));
        }
    }else if(btn == m_DataAndStatisticsFoldBtn){
        if(m_DataAndStatisticsFoldBtn->text().contains(tr("展开"))){
            m_DataSheet->setVisible(true);
            m_DetectionObject->setVisible(true);
            m_AuxiliaryFunction->setVisible(true);
            m_DataAndStatisticsFoldBtn->setText(tr("折叠"));
        }else if(m_DataAndStatisticsFoldBtn->text().contains(tr("折叠"))){
            m_DataSheet->setVisible(false);
            m_DetectionObject->setVisible(false);
            m_AuxiliaryFunction->setVisible(false);
            m_DataAndStatisticsFoldBtn->setText(tr("展开"));
        }
    }
}

void ControlPanel::onButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(btn == m_RuningStatus){
        emit gotoTargetPage(1);//0
    }else if(btn == m_DetailWidgetInfo){
        emit gotoTargetPage(2);//1
    }else if(btn == m_ControlCondition){
        emit gotoTargetPage(3);//2
    }else if(btn == m_DataProcess){
        emit gotoTargetPage(4);//0
    }else if(btn == m_EquipmentCalibration){
        emit gotoTargetPage(5);//1
    }else if(btn == m_SystemSettings){
        emit gotoTargetPage(6);//2
    }else if(btn == m_DataSheet){
        emit gotoTargetPage(7);//0
    }else if(btn == m_DetectionObject){
        emit gotoTargetPage(8);//1
    }else if(btn == m_AuxiliaryFunction){
        emit gotoTargetPage(9);//2
    }
}

void ControlPanel::structMenuList()
{
    MenuInfo menuinfo;
    menuinfo.setIconName(":/Main/Title.png");
    menuinfo.setlabelText(tr("控制面板"));
    m_menuinfolist.insert(m_menuinfolist.begin(),menuinfo);

    for(int i=0;i<cphlayout->count();i++){
        QWidgetItem* widgetItem = static_cast<QWidgetItem*>(cphlayout->itemAt(i));
        if(widgetItem != NULL){
            QWidget* widget = static_cast<QWidget*>(widgetItem->widget());
            if(widget != NULL){
                QPushButton* btn = static_cast<QPushButton*>(widget);
                MenuInfo menuinfo;
                menuinfo.setIconName(":/Main/Title.png");//(btn->icon().name());
                menuinfo.setlabelText(btn->text());
                m_menuinfolist.insert(m_menuinfolist.end(),menuinfo);
            }
        }
    }
    for(int i=0;i<cphlayout1->count();i++){
        QWidgetItem* widgetItem = static_cast<QWidgetItem*>(cphlayout1->itemAt(i));
        if(widgetItem != NULL){
            QWidget* widget = static_cast<QWidget*>(widgetItem->widget());
            if(widget != NULL){
                QPushButton* btn = static_cast<QPushButton*>(widget);
                MenuInfo menuinfo;
                menuinfo.setIconName(btn->icon().name());
                menuinfo.setlabelText(btn->text());
                m_menuinfolist.insert(m_menuinfolist.end(),menuinfo);
            }
        }
    }
    for(int i=0;i<cphlayout2->count();i++){
        QWidgetItem* widgetItem = static_cast<QWidgetItem*>(cphlayout2->itemAt(i));
        if(widgetItem != NULL){
            QWidget* widget = static_cast<QWidget*>(widgetItem->widget());
            if(widget != NULL){
                QPushButton* btn = static_cast<QPushButton*>(widget);
                MenuInfo menuinfo;
                menuinfo.setIconName(btn->icon().name());
                menuinfo.setlabelText(btn->text());
                m_menuinfolist.insert(m_menuinfolist.end(),menuinfo);
            }
        }
    }

    emit settingCompleted(m_menuinfolist);
}

void ControlPanel::translatePage(const QString &targetname)
{
    if(targetname == tr("控制面板")){
        emit gotoTargetPage(0);
        return;
    }
    for(int i=0;i<cphlayout->count();i++){
        QWidgetItem* widgetItem = static_cast<QWidgetItem*>(cphlayout->itemAt(i));
        if(widgetItem != NULL){
            QWidget* widget = static_cast<QWidget*>(widgetItem->widget());
            if(widget != NULL){
                QPushButton* btn = static_cast<QPushButton*>(widget);
                if(btn->text() == targetname){
                    emit gotoTargetPage(i+1);
                    break;
                }
            }
        }
    }
    for(int i=0;i<cphlayout1->count();i++){
        QWidgetItem* widgetItem = static_cast<QWidgetItem*>(cphlayout1->itemAt(i));
        if(widgetItem != NULL){
            QWidget* widget = static_cast<QWidget*>(widgetItem->widget());
            if(widget != NULL){
                QPushButton* btn = static_cast<QPushButton*>(widget);
                if(btn->text() == targetname){
                    emit gotoTargetPage(i+4);
                    break;
                }
            }
        }
    }
    for(int i=0;i<cphlayout2->count();i++){
        QWidgetItem* widgetItem = static_cast<QWidgetItem*>(cphlayout2->itemAt(i));
        if(widgetItem != NULL){
            QWidget* widget = static_cast<QWidget*>(widgetItem->widget());
            if(widget != NULL){
                QPushButton* btn = static_cast<QPushButton*>(widget);
                if(btn->text() == targetname){
                    emit gotoTargetPage(i+7);
                    break;
                }
            }
        }
    }

}
