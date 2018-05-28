#ifndef CARDLISTMODEL_H
#define CARDLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QListView>
#include "CardListView.h"
#include "CardInfo.h"
class CardListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CardListModel(QObject *parent = 0);
    ~CardListModel();
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    CardInfo* file(QModelIndex index) const;
    QModelIndex index(int row, int column = 0, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex index(const QString& imageFile);
    void setPhotoListView(CardListView *view);
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

signals:
    void setCurrentIndex(QModelIndex idx);

public slots:
    void onImageInfoAvaliable(const QStringList& imageFiles);
    void onPreappendImage(const QStringList& imageFiles);
    void onThumbAvaliable(const QString& imageFile);
    void resetModel();
    void onImageDeleted(const QStringList& imageFiles);

private:
    bool isVisible(const QModelIndex& index) const;
    CardListView *_view;
    QList<CardInfo*> _cardList;
    QList<QString> _waitingImages;
};

#endif // CARDLISTMODEL_H
