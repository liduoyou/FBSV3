#ifndef CARDVIEWITEMDELEGATE_H
#define CARDVIEWITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QSize>

class CardViewItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CardViewItemDelegate(QObject *parent = 0);
    ~CardViewItemDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const;

protected:

signals:

public slots:

private:
};

#endif // CARDVIEWITEMDELEGATE_H
