#ifndef ROUNDWIDGET_H
#define ROUNDWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
class CPushbutton;

class RoundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoundWidget(QString name,QWidget *parent = 0);
    ~RoundWidget();

    void setValue(QString value);
    QString getValue()const;/*    turnRound();update();*/
    void setNormalAngle(qreal a, qreal nearmax, qreal max);
    qreal getNormalAngle()const;

    void setSpecificAngle(qreal a,qreal min,qreal nearmin,qreal nearmax,qreal max);
    qreal getSpecificAngle()const;

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject * obj, QEvent * e);
signals:
    void circleClicked(bool);
private slots:
    void positionChanged(qint64 pos);
    void durationChanged(qint64 dur);
    void turnRound();
    void onButtonClicked(bool flag);

private:
    void setupUI();
    QTimer* m_timer;
    qreal m_angle;
    qreal curangle;
    qreal shouldchangeangle;
    QString m_colorstr;
    CPushbutton* m_pushBtn;
    bool m_flag;
    QString sheet;
    QLabel*    m_timeLabel;
    qint64     m_durTime;
    QString    m_name;
    QString    m_value;
};

#endif // ROUNDWIDGET_H
