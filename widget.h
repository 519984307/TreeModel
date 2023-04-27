#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTreeView>
#include <QPushButton>

#include "treemodel.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);

    TreeModel _treeModel {this};
    QTreeView _treeView;
    QGridLayout _mainGridLayout {this};
    QPushButton _pbClose {"Закрыть"};
};

#endif // WIDGET_H
