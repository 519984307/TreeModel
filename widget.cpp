#include "widget.h"

#include <QHeaderView>
#include <QDebug>

using namespace TreeItemTypes;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    _treeModel.addItem(new TreeItem(nullptr,"1"),QModelIndex());
    _treeModel.addItem(new TreeItem(nullptr,"2"),QModelIndex());
    _treeModel.addItem(new TreeItem(nullptr,"3"),QModelIndex());
    _treeModel.addItem(new TreeItem(nullptr,"4"),QModelIndex());


    _treeModel.setColumns(QStringList() << "Параметр" << "Значение");
    _treeView.header()->resizeSections(QHeaderView::ResizeToContents);

    _treeView.setModel(&_treeModel);
    _treeView.setItemDelegate(&_treeModelDelegate);
    this->resize(800,800);

    _mainGridLayout.addWidget(&_treeView);
    _mainGridLayout.addWidget(&_pbClose);

    connect(&_pbClose,&QPushButton::clicked,
            this,&Widget::close);

    _treeModel.addSS();
}

