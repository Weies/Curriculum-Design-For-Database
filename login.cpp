#include "login.h"
#include "ui_login.h"
#include<widget.h>
#include<qsqlquery.h>
#include<qmessagebox.h>
extern QSqlDatabase db;
extern bool regestered;
extern QString ID;
extern QString password;
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
    connect(btn_loginin,&superButton::Clicked,[=](){
        QString id_str=ui->lineEdit->text();
        QString password_str=ui->lineEdit_2->text(),password_str1;
        QString str = QString("select passworld from user where account_id='%1'").arg(id_str);
        QSqlQuery query(db);
        query.exec(str);
        while(query.next())password_str1=query.value(0).toString();
        if(id_str=="")QMessageBox::critical(this,"critical","账号不能为空");
        else if(password_str=="")QMessageBox::critical(this,"critical","密码不能为空");
        else if(password_str!=password_str1)QMessageBox::critical(this,"critical","账号或密码错误");
        else if(password_str==password_str1){
            regestered=true;
            ID=id_str;password=password_str;
            emit dynamic_cast<Widget*>(parent)->gotopick();
        }
    });
}

login::~login()
{
    delete ui;
}
