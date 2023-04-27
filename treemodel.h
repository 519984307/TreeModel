#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QSharedPointer>

#include "treeitem.h"

class TreeModel : public QAbstractItemModel
{
public:
    TreeModel(QObject *parent = nullptr);
    void setRoot(const QSharedPointer<TreeItem> &rootItem);
    void setColumns(const QStringList &columns);

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

protected:
     QSharedPointer<TreeItem> _rootItem;
     QStringList _columns;
     TreeItem* treeItemByIndex(const QModelIndex &index) const;
};

#endif // TREEMODEL_H
