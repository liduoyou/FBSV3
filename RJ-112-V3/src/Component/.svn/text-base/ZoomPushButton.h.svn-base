#ifndef ZOOMPUSHBUTTON_H
#define ZOOMPUSHBUTTON_H

#include <QPushButton>
#include <QLabel>
#include "CustomLabel.h"
class ZoomPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ZoomPushButton(QWidget *parent = 0);
    ~ZoomPushButton();

    void     setLabelName(QString name);//索引点名称
    QString  getLabelName()const;
protected:
    void                    paintEvent(QPaintEvent *event);
    void                   leaveEvent(QEvent *event);
    void                   enterEvent(QEvent *event);
signals:
    
private slots:

private:
    void                   setupUI();
    QSize                  m_size;
    bool                   m_enter;
    QString                m_labelName;
    CustomLabel*                m_label;
};

#endif // ZOOMPUSHBUTTON_H
