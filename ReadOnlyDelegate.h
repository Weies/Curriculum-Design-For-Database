#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H

#endif // READONLYDELEGATE_H
#include<qwidget.h>
#include<qitemdelegate.h>
class ReadOnlyDelegate: public QItemDelegate
{
public:
    ReadOnlyDelegate(QWidget *parent = NULL):QItemDelegate(parent)
    {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const override //final
    {
        Q_UNUSED(parent)
        Q_UNUSED(option)
        Q_UNUSED(index)
        return NULL;
    }
};
