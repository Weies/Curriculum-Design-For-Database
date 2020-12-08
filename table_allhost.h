#ifndef TABLE_ALLHOST_H
#define TABLE_ALLHOST_H

#include <QWidget>
#include<qtableview.h>
#include<qsqltablemodel.h>
#include<superbutton.h>

namespace Ui {
class table_allhost;
}

class table_allhost : public QWidget
{
    Q_OBJECT

public:
    explicit table_allhost(QWidget *parent = nullptr);
    ~table_allhost();
    QTableView* view;
    QSqlTableModel *model;
    superButton *btn_back;
    superButton *btn_add;

private:
    Ui::table_allhost *ui;
};

#endif // TABLE_ALLHOST_H
