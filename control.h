#ifndef CONTROL_H
#define CONTROL_H
#include<qlabel.h>
#include <QWidget>
#include<superbutton.h>
#include<qtableview.h>
#include<qstandarditemmodel.h>
namespace Ui {
class control;
}

class control : public QWidget
{
    Q_OBJECT

public:
    explicit control(QWidget *parent = nullptr);
    ~control();

    QTableView* view;
    QStandardItemModel *control_model;
    superButton *btn_back;
    superButton *btn_next;
    void update();
private:
    Ui::control *ui;
};

#endif // CONTROL_H
