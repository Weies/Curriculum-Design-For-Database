#ifndef TABLE_ALLDOMAIN_H
#define TABLE_ALLDOMAIN_H

#include <QWidget>
#include<qtableview.h>
#include<qsqltablemodel.h>
#include<superbutton.h>
namespace Ui {
class table_alldomain;
}

class table_alldomain : public QWidget
{
    Q_OBJECT

public:
    explicit table_alldomain(QWidget *parent = nullptr);
    ~table_alldomain();
    QTableView* view;
    QSqlTableModel *model;
    superButton *btn_back;
    superButton *btn_add;

private:
    Ui::table_alldomain *ui;
};

#endif // TABLE_ALLDOMAIN_H
