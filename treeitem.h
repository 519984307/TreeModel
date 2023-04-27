#ifndef TREEITEM_H
#define TREEITEM_H

#include <QObject>
#include <QVariant>

class TreeItem : public QObject
{
    Q_OBJECT
public:
    TreeItem(QObject *parent = nullptr);


    QVariant param() const;
    void setParam(const QVariant &param);

    QVariant value() const;
    void setValue(const QVariant &value);

private:
    QVariant _param;
    QVariant _value;
};

#endif // TREEITEM_H
