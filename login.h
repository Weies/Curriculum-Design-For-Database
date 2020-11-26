#ifndef LOGIN_H
#define LOGIN_H
#include<superbutton.h>
#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void reLoadUser();
    superButton *btn_loginin;
    superButton *btn_register;
private:
    Ui::login *ui;
};


#endif // LOGIN_H
