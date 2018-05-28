#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QMutex>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "../Menu/MenuInfo.h"
class ControlPanel : public QWidget
{
    Q_OBJECT
public:
     ~ControlPanel();

    static ControlPanel *instance();

    QVBoxLayout *initControlPanel();

    void  structMenuList();

signals:
    void gotoTargetPage(int index);
    void settingCompleted(QList<MenuInfo>);
private slots:
    void onButtonClicked();
    void widgetHide(bool);
    void translatePage(const QString& targetname);

private:
    explicit ControlPanel(QWidget *parent = 0);
    void setupUI();

    static QMutex m_instanceLock;
    static ControlPanel* m_ControlPanelInstance;

    QSize            m_size;

    QLabel*             m_OperateAndControlName;//操作与控制
    QPushButton*        m_OperateAndControlFoldBtn;

    QHBoxLayout*        cphlayout;
    QPushButton*        m_RuningStatus;//运行状态
    QPushButton*        m_AbstractWidgetInfo;//摘要信息
    QPushButton*        m_DetailWidgetInfo;//详细信息
    QPushButton*        m_ControlCondition;//控制条件

    QLabel*             m_MaintainAndManagerName;//维护与管理
    QPushButton*        m_MaintainAndManagerFoldBtn;

    QHBoxLayout*        cphlayout1;
    QPushButton*        m_DataProcess;//数据处理
    QPushButton*        m_EquipmentCalibration;//设备标定
    QPushButton*        m_SystemSettings;//系统设置 1.设备信息 2.参数设置

    QLabel*             m_DataAndStatisticsName;//数据与统计
    QPushButton*        m_DataAndStatisticsFoldBtn;

    QHBoxLayout*        cphlayout2;
    QPushButton*        m_DataSheet;//参数报表
    QPushButton*        m_DetectionObject;//检测对象
    QPushButton*        m_AuxiliaryFunction;//辅助功能

    QList<MenuInfo>     m_menuinfolist;
};

#endif // CONTROLPANEL_H
