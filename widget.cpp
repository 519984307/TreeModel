#include "widget.h"

#include <QHeaderView>
#include <QDebug>

using namespace TreeItemTypes;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    TreeItem *rootItem = new TreeItem();
    TreeItem *child1 = new TreeItem(rootItem,"RootChild", "Object-1", TypeValue::LineEdit, false);
    TreeItem *child2 = new TreeItem(child1,"SS", "proverka", TypeValue::LineEdit, false);
    TreeItem *child3 = new TreeItem(child2,"Параметр SpinBox", 0, TypeValue::SpinBox);
    TreeItem *child4 = new TreeItem(child2,"Параметр DoubleSpinBox", 0.0, TypeValue::DoubleSpinBox);
    TreeItem *child5 = new TreeItem(child2,"Параметр СomboBox", "", TypeValue::ComboBox);
    TreeItem *child6 = new TreeItem(child2,"Параметр LineEdit");

    _treeModel.setColumns(QStringList() << "Параметр" << "Значение");
    _treeModel.setRoot(QSharedPointer<TreeItem>(rootItem));
    _treeView.header()->resizeSections(QHeaderView::ResizeToContents);

    _treeView.setModel(&_treeModel);
    _treeView.setItemDelegate(&_treeModelDelegate);
    this->resize(800,800);

    _mainGridLayout.addWidget(&_treeView);
    _mainGridLayout.addWidget(&_pbClose);

    connect(&_pbClose,&QPushButton::clicked,
            this,&Widget::close);

    Q_UNUSED(child3)
    Q_UNUSED(child4)
    Q_UNUSED(child5)
    Q_UNUSED(child6)
}

