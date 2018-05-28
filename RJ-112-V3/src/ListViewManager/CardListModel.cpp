#include "CardListModel.h"
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include "ThumbnailProvider.h"
CardListModel::CardListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    qDebug() << "construct CardListModel";
}

CardListModel::~CardListModel()
{
    qDeleteAll(_cardList);
    qDebug() << "destruct CardListModel";
}

int CardListModel::rowCount(const QModelIndex &parent) const
{
//    qDebug()<<"_cardList.size()"<<_cardList.size();
    return _cardList.size();
}

QVariant CardListModel::data(const QModelIndex &index, int role) const
{
    //    qDebug() << index << "data" << role;
    if(!index.isValid()) {
        return QVariant();
    }
    if(index.row() < 0 || index.row() > _cardList.size()) {
        return QVariant();
    }
    if(role == Qt::DecorationRole) {
        // lazy population of data
        if(isVisible(index)) {
            //            qDebug() << index;
            // 用于显示图片缩略图
            return ThumbnailProvider::globalInstance()->thumb(file(index)->className());
        } else {
            return ThumbnailProvider::globalInstance()->defaultPixmap();
        }
    }else if(role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }else if(role == Qt::DisplayRole) {
        return file(index)->absolutePath();
    }else if(role == Qt::UserRole) {
        return file(index)->appName();
    }
    return QVariant();
}

CardInfo *CardListModel::file(QModelIndex index) const {
    if(!index.isValid()) {
        return NULL;
    }
    if(index.row() < 0 || index.row() > _cardList.size()) {
        return NULL;
    }
    return _cardList.at(index.row());
}

QModelIndex CardListModel::index(int row, int column, const QModelIndex &parent) const {
    return QAbstractListModel::index(row, column, parent);
}

QModelIndex CardListModel::index(const QString &imageFile) {
    for(int i=0;i<_cardList.size();++i) {
//        if(_cardList[i]->absolutePath() == imageFile) {
            return index(i);
//        }
    }
    return QModelIndex();
}

void CardListModel::setPhotoListView(CardListView *view) {
    _view = view;
}

bool CardListModel::insertRows(int row, int count, const QModelIndex &parent)
{
//    qDebug()<<"insertRows="<<"row"<<row<<"count"<<count;
    beginInsertRows(QModelIndex(), row, row+count-1);
    for(int i=0;i<count;i++) {
        CardInfo *fileItem = new CardInfo;
        if(_waitingImages.size()) {
            QString tmp(_waitingImages.front()), path, name;
            _waitingImages.pop_front();
            fileItem->setProcessName(name);
            fileItem->setClassName(path);
        }
        _cardList.insert(row, fileItem);
    }
    endInsertRows();
    emit setCurrentIndex(index(row+count-1));
    return true;
}

bool CardListModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(QModelIndex(), row, row+count-1);
    for(int i=0;i<count;++i) {
        _cardList.removeAt(row);
    }
    endRemoveRows();
    return true;
}

void CardListModel::onImageInfoAvaliable(const QStringList& imageFiles) {
    beginResetModel();
    qDeleteAll(_cardList);
    _cardList.clear();
    for(int i=0;i<imageFiles.size();++i) {
        _cardList.append(new CardInfo);
        QString tmp(imageFiles[i]), path, name;
//        FileManager::seperatePath(tmp, path, name);
//        _cardList[_cardList.size()-1]->setFilePath(path);
//        _cardList[_cardList.size()-1]->setFileName(name);
    }
    endResetModel();
}

void CardListModel::onPreappendImage(const QStringList& imageFiles) {
    foreach(const QString& imageFile, imageFiles) {
        QModelIndex idx = index(imageFile);
        if(idx.isValid()) {
            emit dataChanged(idx, idx);
        } else {
            _waitingImages.push_back(imageFile);
        }
    }
    if(_waitingImages.size()) {
        insertRows(0, _waitingImages.size(), QModelIndex());
    }
}

void CardListModel::onThumbAvaliable(const QString &imageFile) {
    QModelIndex idx = index(imageFile);
//    qDebug() << idx;
    if(idx.isValid()) {
        emit dataChanged(idx, idx);
    }
}

bool CardListModel::isVisible(const QModelIndex &index) const {
    if(_view == NULL) {
        return true;
    }
    return _view->isItemVisiable(index);
}

void CardListModel::resetModel() {
    beginResetModel();
    qDeleteAll(_cardList);
    _cardList.clear();
    endResetModel();
}

void CardListModel::onImageDeleted(const QStringList &imageFiles) {
    foreach (const QString& imageFile, imageFiles) {
        QModelIndex idx = index(imageFile);
        if(idx.isValid()) {
            removeRows(idx.row(), 1, QModelIndex());
        }
    }
}
