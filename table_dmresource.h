#ifndef TABLE_DMRESOURCE_H
#define TABLE_DMRESOURCE_H

#include <QWidget>
#include<qtableview.h>
#include<qsqltablemodel.h>
#include<superbutton.h>

namespace Ui {
class table_dmresource;
}

class table_dmresource : public QWidget
{
    Q_OBJECT

public:
    explicit table_dmresource(QWidget *parent = nullptr);
    ~table_dmresource();
    QTableView* view;
    QSqlTableModel *model;
    superButton *btn_back;

private:
    Ui::table_dmresource *ui;
};

#endif // TABLE_DMRESOURCE_H
