#ifndef TABLE_IP_H
#define TABLE_IP_H

#include <QWidget>
#include<qtableview.h>
#include<qsqltablemodel.h>
#include<superbutton.h>
namespace Ui {
class table_ip;
}

class table_ip : public QWidget
{
    Q_OBJECT

public:
    explicit table_ip(QWidget *parent = nullptr);
    ~table_ip();
    QTableView* view;
    QSqlTableModel *model;
    superButton *btn_back;
    superButton *btn_add;

private:
    Ui::table_ip *ui;
};

#endif // TABLE_IP_H
