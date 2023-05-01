#include "treemodel.h"

#include <QDebug>
#include <QColor>

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent), _rootItem(QSharedPointer<TreeItem>(new TreeItem))
{

}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent))
        return QModelIndex();
    TreeItem *parentTreeItem = treeItemByIndex(parent);
    return createIndex(row,column,parentTreeItem->children().at(row));
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    TreeItem *childTreeItem = treeItemByIndex(child);
    TreeItem *parentTreeItem = static_cast<TreeItem*>(childTreeItem->parent());
    if(parentTreeItem == _rootItem.data())
        return QModelIndex();
    TreeItem *grandParentTreeItem = static_cast<TreeItem*>(parentTreeItem->parent());
    int row = grandParentTreeItem->children().indexOf(parentTreeItem);
    return createIndex(row,0,parentTreeItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    return treeItemByIndex(parent)->children().count();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _columns.count();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(role == Qt::DisplayRole)
    {
        if(index.column() == 0) {
            return treeItemByIndex(index)->param();
        } else if(index.column() == 1) {
            return treeItemByIndex(index)->value();
        }
    }
    return QVariant();
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }
    if(orientation == Qt::Horizontal)
    {
        return _columns.at(section);
    }
    return QVariant();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole || index.column() == 0)
        return false;
    treeItemByIndex(index)->setValue(value);
    dataChanged(index,index);
    return true;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if(index.column() != 0)
    {
        if(treeItemByIndex(index)->isEditable())
        {
            flags |= Qt::ItemIsEditable;
        }
    }
    return flags;
}

void TreeModel::setRoot(const QSharedPointer<TreeItem> &rootItem)
{
    if(rootItem.isNull())
        qCritical() << Q_FUNC_INFO << "invalid null parameter";
    _rootItem = rootItem;
    _rootItem->setParent(this);
}

void TreeModel::setColumns(const QStringList &columns)
{
    _columns = columns;
}

TreeItem *TreeModel::treeItemByIndex(const QModelIndex &index) const
{
    if(!index.isValid())
        return _rootItem.data();
    return static_cast<TreeItem*>(index.internalPointer());
}
