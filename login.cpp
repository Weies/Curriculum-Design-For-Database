#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    btn_loginin=new superButton("登录",this);
    btn_register=new superButton("注册",this);
    btn_loginin->move(350,400);btn_loginin->resize(100,50);
    btn_register->move(550,400);btn_register->resize(100,50);
    btn_loginin->setMouseOutColor(QColor(200,200,255));
}

login::~login()
{
    delete ui;
}
