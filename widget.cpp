#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setGeometry(width(),height(),300,800);
    _treeView.setModel(&_treeModel);

    _mainGridLayout.addWidget(&_treeView);
    _mainGridLayout.addWidget(&_pbClose);

    connect(&_pbClose,&QPushButton::clicked,
            this,&Widget::close);

    TreeItem *rootItem = new TreeItem();
    TreeItem *child1 = new TreeItem(rootItem);
    TreeItem *child2 = new TreeItem(child1);
    TreeItem *child3 = new TreeItem(child1);
    TreeItem *child4 = new TreeItem(child1);
    TreeItem *child5 = new TreeItem(child1);

    child1->setParam("child1");
    child1->setValue("111");

    child2->setParam("child2");
    child2->setValue("222");

    child3->setParam("child3");
    child3->setValue("333");

    child4->setParam("child4");
    child4->setValue("444");

    child5->setParam("child5");
    child5->setValue("555");

    _treeModel.setColumns(QStringList() << "Параметр" << "Значение");
    _treeModel.setRoot(QSharedPointer<TreeItem>(rootItem));
}

