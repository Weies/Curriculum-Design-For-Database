#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H
#include<superbutton.h>
#include <QWidget>
namespace Ui {
class adminwidget;
}

class adminwidget : public QWidget
{
    Q_OBJECT

public:
    explicit adminwidget(QWidget *parent = nullptr);
    ~adminwidget();
    superButton *btn_next;
    superButton *btn_next1;
    superButton *btn_next2;
    superButton *btn_next3;
    superButton *btn_next4;
    superButton *btn_next5;
    superButton *btn_back;

private:
    Ui::adminwidget *ui;
};

#endif // ADMINWIDGET_H
