#include "CardListView.h"
#include <QDebug>
#include <QSortFilterProxyModel>

CardListView::CardListView(QWidget *parent) :
    QListView(parent)
{
}

static bool checkArea(const QRect& larger, const QRect& smaller) {
    if(smaller.width() == 0) {
        return false;
    }
    int up = smaller.top()>larger.top()? smaller.top():larger.top();
    int down = smaller.bottom()<larger.bottom()? smaller.bottom():larger.bottom();
    return  down-up>=1;
}

bool CardListView::isItemVisiable(const QModelIndex &srcIndex) {
    const QSortFilterProxyModel *_proxyModel = qobject_cast<const QSortFilterProxyModel*>(model());
    QModelIndex index = _proxyModel->mapFromSource(srcIndex);
//    qDebug() << viewport()->rect() << " ax" << index << " bx" << visualRect(index);
    return checkArea(viewport()->rect(), visualRect(index));
}

void CardListView::onSetCurrentIndex(QModelIndex idx) {
    const QSortFilterProxyModel *_proxyModel = qobject_cast<const QSortFilterProxyModel*>(model());
    QModelIndex index = _proxyModel->mapFromSource(idx);
    if(index.isValid()) {
        setCurrentIndex(index);
    }
}
