#include "treeitem.h"

using namespace TreeItemTypes;

TreeItem::TreeItem(QObject *parent, QVariant param, QVariant value, TypeValue typeValue, bool isEditable)
    : QObject(parent), _param(param), _value(value),_typeValue(typeValue), _isEditable(isEditable)
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

TypeValue TreeItem::typeValue() const
{
    return _typeValue;
}

void TreeItem::setTypeValue(const TypeValue &typeValue)
{
    _typeValue = typeValue;
}

bool TreeItem::isEditable() const
{
    return _isEditable;
}

void TreeItem::setIsEditable(bool isEditable)
{
    _isEditable = isEditable;
}





