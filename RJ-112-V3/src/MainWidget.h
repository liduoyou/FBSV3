/*------------------------------------------------------------------------------*
** <auto-generated
**      Editer :           liduoyou
**      Class name:        MainWidget
**      Class starttime :  2016-03-04
**      Last modified :    2016-06-17
**      Description :      This is a class main UI>
** </auto-generated>
/*------------------------------------------------------------------------------*/
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QProcess>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include "./UI/AbstractWidget.h"
#include "./UI/DetailWidget.h"
#include "./UI/NavigatePointWidget.h"
#include "./Component/VScrollArea.h"
#include "./Component/CardWidget.h"
#include "./ListViewManager/CardManagerWidget.h"
class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    static MainWidget *instance();
protected:
    void paintEvent(QPaintEvent *event);
signals:
    void changsecondNavigate(int index);
    void preappendImage(QStringList);
    void hasCards();
    void noCards();

    void positionChanged();
private slots:
    void onButtonClicked();
    void receivescorllPage(int index);
    void receivescorllValue(int newValue);
    void updateData();
private:
    void                setupUI();

    QWidget*            initMainNavigate();//主导航
    QWidget*            initSecondNavigate();//次要导航
    QWidget*            initAbstractWidget();//摘要信息
    QWidget*            initDetailWidget();//详细信息
    QWidget*            initCardWidgets();//卡片布局界面

    QSize               m_size;
    QVBoxLayout *       layout;
    VScrollArea*        m_scrollArea;
    QWidget*            m_contents;

    static MainWidget* _instance;

    QWidget*                 m_NaveWidget;//索引界面
    QPushButton*             m_pBtnMain;//运行状态
    QPushButton*             m_pBtnDetail;//详细信息
    QPushButton*             m_pbtnlimit;//限位状态
    QPushButton*             m_pBtnAcPort;//采集端在线状态
    QLabel*                  m_pNaveLabel;//索引条
    QPropertyAnimation*      m_posAnimation;//索引条动画
    QPropertyAnimation*      m_posAnimation1;//次要索引点整体动画

    NavigatePointWidget*     m_navigatePointWidget;
    AbstractWidget*          m_abstractWidget;//各机构摘要信息
    DetailWidget*            m_detailWidget;//各机构详细信息
    QWidget*                 m_cardWidgets;//卡片界面
    CardWidget* cardwidget1;
    CardWidget* cardwidget2;
    CardWidget* cardwidget3;
    CardWidget* cardwidget4;
    CardWidget* cardwidget5;
    CardWidget* cardwidget6;
    CardWidget* cardwidget7;
    CardWidget* cardwidget8;
    CardWidget* cardwidget9;
    CardManagerWidget*      m_cardManagerWidget;   //卡片管理
    QProcess* myProcess;
    QStringList arguments;
};

#endif // MAINWIDGET_H
