#ifndef CONTROL_H
#define CONTROL_H
#include<qlabel.h>
#include <QWidget>
#include<superbutton.h>
namespace Ui {
class control;
}

class control : public QWidget
{
    Q_OBJECT

public:
    explicit control(QWidget *parent = nullptr);
    ~control();

    superButton *btn_back;
    void update();
private:
    Ui::control *ui;
};

#endif // CONTROL_H
