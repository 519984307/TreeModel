#include "treemodeldelegate.h"

#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>


using namespace TreeItemTypes;

TreeModelDelegate::TreeModelDelegate(QObject *parent) : QItemDelegate(parent)
{

}

/*!
 * \brief TreeModelDelegate::paint - Отрисовывает ячейку элемента
 */
void TreeModelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::paint(painter,option,index);
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
    QSize size = QItemDelegate::sizeHint(option,index);
    size.setHeight(size.height() + 7);
    return size;
}

TreeItem *TreeModelDelegate::treeItemByIndex(const QModelIndex &index) const
{
    return static_cast<TreeItem*>(index.internalPointer());
}
