#ifndef TREEMODELDELEGATE_H
#define TREEMODELDELEGATE_H

#include <QStyledItemDelegate>

#include <treeitem.h>
#include <treemodeltypes.h>

class TreeModelDelegate : public QStyledItemDelegate
{
public:
    TreeModelDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
public:
    //!Отрисовывает ячейку элемента
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    //!Создаёт виджет редактора
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    //!Передаёт значение от модели в редактор
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    //!Передаёт значение от редактора в модель
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    //!Задаёт геометрию редактора
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    //!Возвращает размер, необходимый делегату для отображения элемента
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

protected:
    TreeItem *treeItemByIndex(const QModelIndex &index) const;

};

#endif // TREEMODELDELEGATE_H
