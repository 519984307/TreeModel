#ifndef TREEITEM_H
#define TREEITEM_H

#include <QObject>
#include <QVariant>
#include <QColor>
#include <treemodeltypes.h>

class TreeItem : public QObject
{
    Q_OBJECT
public:
    TreeItem(QObject *parent = nullptr,
             QVariant param = QVariant(),
             QVariant value = QVariant(),
             TreeItemTypes::TypeValue typeValue = TreeItemTypes::TypeValue::LineEdit,
             bool isEditable = true);


    QVariant param() const;
    void setParam(const QVariant &param);

    QVariant value() const;
    void setValue(const QVariant &value);

    TreeItemTypes::TypeValue typeValue() const;
    void setTypeValue(const TreeItemTypes::TypeValue &typeValue);

    bool isEditable() const;
    void setIsEditable(bool isEditable);

private:
    QVariant _param;
    QVariant _value;
    TreeItemTypes::TypeValue _typeValue;
    bool _isEditable;
};

#endif // TREEITEM_H
