#ifndef NAVIGATIONNODE_H
#define NAVIGATIONNODE_H

#include <QWidget>
#include <QPropertyAnimation>
class NavigationNode : public QWidget
{
    Q_OBJECT
public:
    explicit NavigationNode(QWidget *parent = 0);
    ~NavigationNode();
    void setClickPoint(QPoint point);
    QPoint getClickPoint()const;
    void changeClickFlag(int bit);
    int getClickedFlag()const;
signals:
    void NodeClicked(int);
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *e);
private slots:

private:
    void             changeNode();
    QSize            m_size;
    QPoint           m_point;
    quint8           m_clickflag;//点击点标志
    QPropertyAnimation* animation;
    QRectF rectf;
};

#endif // NAVIGATIONNODE_H
