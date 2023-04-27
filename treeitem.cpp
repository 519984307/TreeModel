#include "treeitem.h"

TreeItem::TreeItem(QObject *parent) : QObject(parent)
{

}

QVariant TreeItem::param() const
{
    return _param;
}

void TreeItem::setParam(const QVariant &param)
{
    _param = param;
}

QVariant TreeItem::value() const
{
    return _value;
}

void TreeItem::setValue(const QVariant &value)
{
    _value = value;
}





