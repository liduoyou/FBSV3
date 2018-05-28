#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include <QWidget>
#include <QToolButton>
#include <QPushButton>
#include <QListView>
#include <QSortFilterProxyModel>
#include "CardListModel.h"
#include "CardListview.h"

class QStackedWidget;

class CardManager : public QWidget
{
    Q_OBJECT
public:
    explicit CardManager(QWidget *parent = 0);

signals:
    void switchToSdManagePage(const QString& phoneDir, const QString& phoneFileName);

private slots:
    void toggleSelectAll();
    void toggleSelectAll(const QItemSelection& selection, const QItemSelection& pselection);
    void onSearchTextChanged(const QString &text);
//    void onPageChanged(ModulePage);
    void onNoPictures();
    void onHasPictures();

private:
    void setupUI();
    void createconnections();
    void addFolder(const QString& dirPath);
    //void createActions();
    // 图片视窗控件
    CardListView *m_cardView;
    QWidget *initCardViewWidget();
    QStackedWidget *m_stackedWidget;
    // models
    CardListModel *m_cardListModel;
    QItemSelectionModel *m_cardSelectionModel;
    QSortFilterProxyModel *m_dataChangedModel;
};

#endif // CARDMANAGER_H
