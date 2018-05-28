#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>
class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QWidget *parent = 0);
    ~CustomLabel();
    void     setLabelName(QString name);//索引点名称
    QString  getLabelName()const;

protected:
    void      paintEvent(QPaintEvent *event);
signals:
    
private slots:

private:
    void                   setupUI();
    QSize                  m_size;
    QString                m_labelName;
};

#endif // CUSTOMLABEL_H
