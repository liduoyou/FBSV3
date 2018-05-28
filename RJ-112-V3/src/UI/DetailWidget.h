#ifndef DETAILWIDGET_H
#define DETAILWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QScrollBar>
#include <QStackedWidget>
#include "../BaseWidgets/BigVehicleWidget.h"
#include "../BaseWidgets/HookWidget.h"
#include "../BaseWidgets/LittleVehicleWidget.h"
class NavigationNode;
class DetailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DetailWidget(QWidget *parent = 0);
    ~DetailWidget();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
signals:
    
private slots:
    void tabPageButtonClicked(int index);
    void activeNotice(bool isActive);
    void needReactiveWindow();
    void onButtonClicked();
private:
    void                        setupUI();
    QWidget*                    initTopBtnGroup();
    QWidget*                    initNavigationNode();

    QStackedWidget*             m_stackedWidget;

    BigVehicleWidget*           m_bigVehicleWidget;
    HookWidget*                 m_HookNo1Widget;
    HookWidget*                 m_HookNo2Widget;
    HookWidget*                 m_HookNo3Widget;
    HookWidget*                 m_HookNo4Widget;
    LittleVehicleWidget*        m_littleVehicleNo1Widget;
    LittleVehicleWidget*        m_littleVehicleNo2Widget;

    QWidget*                    m_topWidget;
    QPushButton*                m_previousBtn;
    QPushButton*                m_moreBtn;
    QPushButton*                m_nextBtn;

    NavigationNode*              m_navigationNode;

    bool mMoveStart;
    bool mContinousMove;
    QPoint mMousePoint;
    QPoint mMousestartPoint;
    QScrollBar* scrollBar;
};

#endif // DETAILWIDGET_H
