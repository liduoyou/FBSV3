#ifndef NAVIGATEPOINTWIDGET_H
#define NAVIGATEPOINTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "../Component/ZoomPushButton.h"
class NavigatePointWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NavigatePointWidget(QWidget *parent = 0);
    ~NavigatePointWidget();
    
signals:
    void      signalscorllPage(int index);
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void      scorllPage(int index);
    void      onButtonClicked();
private:
    void              setupUI();

    QSize             m_size;
    ZoomPushButton*      m_BtnPoint1;//索引点
    ZoomPushButton*      m_BtnPoint2;//索引点
    ZoomPushButton*      m_BtnPoint3;//索引点
    ZoomPushButton*      m_BtnPoint4;//索引点
};

#endif // NAVIGATEPOINTWIDGET_H
