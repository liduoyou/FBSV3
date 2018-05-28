#ifndef CUSTOMTABWIDGET_H
#define CUSTOMTABWIDGET_H

#include <QTabWidget>
class MainWidget;
class CustomTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit CustomTabWidget(QWidget *parent = 0);
    ~CustomTabWidget();

protected:
    void paintEvent(QPaintEvent * event);
    void initStyleOption(QStyleOptionTabWidgetFrame *option) const;
signals:
    
private slots:
    void     closeTargetTab(int index);
    void     addTabPage(int index);
private:
    MainWidget*       m_mainWidget;
};

#endif // CUSTOMTABWIDGET_H
