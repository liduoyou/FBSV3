#ifndef CARDLISTVIEW_H
#define CARDLISTVIEW_H

#include <QListView>

class CardListView : public QListView
{
    Q_OBJECT
public:
    explicit CardListView(QWidget *parent = 0);
    bool isItemVisiable(const QModelIndex& index);

signals:

public slots:
    void onSetCurrentIndex(QModelIndex idx);

private:
};

#endif // CARDLISTVIEW_H
