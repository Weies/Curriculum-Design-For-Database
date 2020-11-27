#ifndef PURCHASE_H
#define PURCHASE_H
#include<superbutton.h>
#include <QWidget>
#include<QSqlRecord>
namespace Ui {
class purchase;
}

class purchase : public QWidget
{
    Q_OBJECT
public:
    explicit purchase(QWidget *parent = nullptr);
    ~purchase();
    void update(QSqlRecord* w);
    superButton *btn_commit;
    superButton *btn_return;
private:
    QWidget* parent;
    Ui::purchase *ui;
};

#endif // PURCHASE_H
