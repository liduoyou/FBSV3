#ifndef ABSTRACTWIDGET_H
#define ABSTRACTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QLabel>
#include <QLineEdit>
#include "../BaseWidgets/BigVehicleWidget.h"
#include "../BaseWidgets/HookWidget.h"
#include "../BaseWidgets/LittleVehicleWidget.h"
class AbstractWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractWidget(QWidget *parent = 0);
    ~AbstractWidget();
    
signals:
    
public slots:
    void      updateData();

private:
    void                        setupUI();
    QSize                       m_size;
    BigVehicleWidget*           m_bigVehicleWidget;
    HookWidget*                 m_HookNo1Widget;
    HookWidget*                 m_HookNo2Widget;
    HookWidget*                 m_HookNo3Widget;
    HookWidget*                 m_HookNo4Widget;
    LittleVehicleWidget*        m_littleVehicleNo1Widget;
    LittleVehicleWidget*        m_littleVehicleNo2Widget;
    QTimer*        m_timer;
    QLineEdit *nameEdit;
    QLabel    *nameLabel;
    QLineEdit *phoneEdit;
    QLabel    *phoneLabel;
};

#endif // ABSTRACTWIDGET_H
