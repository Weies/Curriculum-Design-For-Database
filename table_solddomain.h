#ifndef TABLE_SOLDDOMAIN_H
#define TABLE_SOLDDOMAIN_H

#include <QWidget>
#include<qtableview.h>
#include<qsqltablemodel.h>
#include<superbutton.h>

namespace Ui {
class table_solddomain;
}

class table_solddomain : public QWidget
{
    Q_OBJECT

public:
    explicit table_solddomain(QWidget *parent = nullptr);
    ~table_solddomain();
    QTableView* view;
    QSqlTableModel *model;
    superButton *btn_back;

private:
    Ui::table_solddomain *ui;
};

#endif // TABLE_SOLDDOMAIN_H
