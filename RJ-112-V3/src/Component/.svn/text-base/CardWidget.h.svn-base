#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QtGui/QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProgressBar>
class CardWidget : public QWidget
{
    Q_OBJECT
public:
    CardWidget(QWidget *parent = 0);
    ~CardWidget();

    void setImageFilename(QString filename = ":Main/Title.png");
    QString getImageFilename()const;

    void setTitlename(QString titlename = "吊 重");
    QString getTitlename()const;

    void setCurrentValue(double value = 0.000f);
    double getCurrentValue()const;

    void setUnit(QString unit = "m");
    QString getUnit()const;

    void setBarChangeflag(bool bartype = false);
    bool getBarChangeflag()const;

    int updateProgressBarStatusValue(double curValue, double earlywarn, double warn);
    int updateProgressBarStatusValue(double curValue, double maxValue,
                                     double warn1, double earlywarn1,
                                     double earlywarn2, double warn2);
protected:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
private:
    void                 setupUI();
    void                 accordingToValueChange();//依照值更新界面

    QSize                m_size;//卡片尺寸
    QLabel*              m_LabelTitleimage;//标题图片
    QLabel*              m_LabelTitleName;//标题名
    QLabel*              m_LabelValue;//当前实际数值
    QLabel*              m_LabelUnit;//显示单位
    QProgressBar*        m_ProgressbarStatus;//进度条状态

    QString              m_imagefilename;//图片文件名
    QString              m_titlename;//标题名
    double               m_currentvalue;//当前数值
    QString              m_unit;//单位
    bool                 m_bartype;//进度条改变依据什么类型
};

#endif // CARDWIDGET_H
