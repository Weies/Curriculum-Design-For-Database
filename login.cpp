#include "login.h"
#include "ui_login.h"
#include<widget.h>
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    btn_loginin=new superButton("登录",this);btn_loginin->resize(250,40);
    btn_register=new superButton("注册",this);btn_register->resize(250,40);
    btn_loginin->move(210,400);
    btn_register->move(520,400);
    btn_loginin->setMouseOutColor(QColor(4,186,251));
    btn_register->setMouseOutColor(QColor(4,186,251));
    connect(btn_register,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotoregister();
    });
    ui->toolButton->setStyleSheet("color:blue");
}

login::~login()
{
    delete ui;
}
