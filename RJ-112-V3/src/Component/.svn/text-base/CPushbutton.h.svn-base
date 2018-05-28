#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include <QPushButton>
#include <QLabel>
#include <QTimer>
class CPushbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit CPushbutton(QString name,QWidget *parent = 0);
    ~CPushbutton();

    void setAngle(qreal a);
    qreal getAngle()const;
    void setClickPoint(QPoint point);
    QPoint getclickPoint()const;

    void setValue(QString value);
    QString getValue()const;

protected:
    void paintEvent(QPaintEvent *event);
    
signals:
    void CPushbuttonClicked(bool);
private slots:
    void onButtonClicked(bool flag);
    void turnRound();
private:
    QString sheet;
    QTimer* m_timer;
    bool m_flag;
    QImage* image;
    QPixmap* pixmap;
    qreal    m_angle;
    QPoint   m_point;
    QString  m_name;
    QString  m_value;
};

#endif // CPUSHBUTTON_H
