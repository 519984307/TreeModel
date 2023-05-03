#include "treemodeldelegate.h"

#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QDebug>

using namespace TreeItemTypes;

TreeModelDelegate::TreeModelDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

/*!
 * \brief TreeModelDelegate::paint - Отрисовывает ячейку элемента
 */
void TreeModelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    if(index.column() == 0 || index.parent().isValid()) {
        QStyledItemDelegate::paint(painter, opt, index);
        return;
    }


    const QWidget *widget = opt.widget;
    QStyle *style = widget ? widget->style() : QApplication::style();
    QStyleOptionButton button;
    button.rect = QRect(opt.rect.right() - 20, opt.rect.top(), 20, opt.rect.height());
    button.text = "+";
    button.state |= QStyle::State_Enabled;

    style->drawControl(QStyle::CE_PushButton, &button, painter);

    opt.rect = QRect(opt.rect.left(), opt.rect.top(), opt.rect.width() - 20, opt.rect.height());
    QStyledItemDelegate::paint(painter, opt, index);
}

/*!
 * \brief TreeModelDelegate::createEditor - Создаёт виджет редактора
 */
QWidget *TreeModelDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    TreeItem *item = treeItemByIndex(index);
    QWidget *widget = nullptr;
    switch (item->typeValue()) {
    case TypeValue::LineEdit: {
        QLineEdit *textEdit = new QLineEdit(parent);
        textEdit->setAutoFillBackground(true);
        widget = textEdit;
        break;
    }
    case TypeValue::SpinBox: {
        QSpinBox *spinBox = new QSpinBox(parent);
        spinBox->setAutoFillBackground(true);
        widget = spinBox;
        break;
    }
    case TypeValue::DoubleSpinBox: {
        QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox(parent);
        doubleSpinBox->setAutoFillBackground(true);
        widget = doubleSpinBox;
        break;
    }
    case TypeValue::ComboBox: {
        QComboBox *comboBox = new QComboBox(parent);
        comboBox->setAutoFillBackground(true);
        comboBox->addItems(QStringList() << "No" << "Yes");
        widget = comboBox;
        break;
    }
    default: break;
    }
    return widget;
}

/*!
 * \brief TreeModelDelegate::setEditorData - Передаёт значение от модели в редактор
 */
void TreeModelDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    TreeItem *item = treeItemByIndex(index);
    switch (item->typeValue()) {
    case TypeValue::LineEdit: {
        QLineEdit *textEdit = static_cast<QLineEdit*>(editor);
        textEdit->setText(index.data().toString());
        break;
    }
    case TypeValue::SpinBox: {
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->setValue(index.data().toInt());
        break;
    }
    case TypeValue::DoubleSpinBox: {
        QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
        doubleSpinBox->setValue(index.data().toDouble());
        break;
    }
    case TypeValue::ComboBox: {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        comboBox->setCurrentText(index.data().toString());
        break;
    }
    default: break;
    }
}

/*!
 * \brief TreeModelDelegate::setModelData - Передаёт значение от редактора в модель
 */
void TreeModelDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    TreeItem *item = treeItemByIndex(index);
    switch (item->typeValue()) {
    case TypeValue::LineEdit: {
        QLineEdit *textEdit = static_cast<QLineEdit*>(editor);
        model->setData(index,textEdit->text());
        break;
    }
    case TypeValue::SpinBox: {
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        model->setData(index,spinBox->value());
        break;
    }
    case TypeValue::DoubleSpinBox: {
        QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
        model->setData(index,doubleSpinBox->value());
        break;
    }
    case TypeValue::ComboBox: {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        model->setData(index,comboBox->currentText());
        break;
    }
    default: break;
    }
}

/*!
 * \brief TreeModelDelegate::updateEditorGeometry - Задаёт геометрию редактора
 */
void TreeModelDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

/*!
 * \brief TreeModelDelegate::sizeHint - Возвращает размер, необходимый делегату для отображения элемента
 */
QSize TreeModelDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option,index);
    size.setHeight(size.height() + 1);
    size.setWidth(size.width() + 1);
    return size;
}

bool TreeModelDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(index.column() == 0 || index.parent().isValid()) {
        return false;
    }
    if (event->type() == QEvent::MouseButtonPress) {
        const QRect buttonRect = QRect(option.rect.right() - 20, option.rect.top(), 20, option.rect.height());
        if (static_cast<QMouseEvent*>(event)->button() == Qt::LeftButton && buttonRect.contains(static_cast<QMouseEvent*>(event)->pos())) {
            qDebug() << Q_FUNC_INFO;
            return true;
        }
    }
}

TreeItem *TreeModelDelegate::treeItemByIndex(const QModelIndex &index) const
{
    return static_cast<TreeItem*>(index.internalPointer());
}
