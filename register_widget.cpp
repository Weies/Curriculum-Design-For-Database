#include "register_widget.h"
#include "ui_register_widget.h"
#include<widget.h>
#include<qdebug.h>
#include<qmessagebox.h>
#include<qsqlquery.h>
#include<qsqlerror.h>
#include<QFile>
extern QSqlDatabase db;
register_widget::register_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::register_widget)
{
    ui->setupUi(this);
    btn_commit=new superButton("提交",this);btn_commit->resize(250,40);
    btn_commit->move(400,500);
    btn_commit->setMouseOutColor(QColor(4,186,251));
    connect(btn_commit,&superButton::Clicked,[=](){
        if(ui->lineEdit->text()=="")QMessageBox::critical(this,"critical","账号不能为空");
        else if(ui->lineEdit_5->text()=="")QMessageBox::critical(this,"critical","用户名不能为空");
        else if(ui->lineEdit_2->text()=="")QMessageBox::critical(this,"critical","密码不能为空");
        else if(ui->lineEdit_2->text()!=ui->lineEdit_3->text())QMessageBox::critical(this,"critical","密码与确认密码必须相同");
        else if(ui->lineEdit_4->text()=="")QMessageBox::critical(this,"critical","手机号不能为空");  
        else {
            QString id_str=ui->lineEdit->text();
            QString password_str=ui->lineEdit_2->text();
            QString phone_str=ui->lineEdit_4->text();
            QString nickname=ui->lineEdit_5->text();
            QString str=QString("select account_id from user where account_id='%1' ").arg(id_str);
            QSqlQuery query(db);
            query.exec(str);
            QString id_str1="";
            while(query.next())id_str1=query.value(0).toString();
            if(id_str1!="")QMessageBox::critical(this,"critical","该账号已存在，请更换账号");
            else{
                QString str = QString("insert into user values('%1','%2','%3','no','','','%4','','','','')").arg(id_str).arg(password_str).arg(nickname).arg(phone_str);
                query.exec(str);
                QFile f(QApplication::applicationDirPath()+"/userinfo.dat");
                f.open(QIODevice::WriteOnly);
                f.write(id_str.toLatin1()+"\r\n");
                f.write(nickname.toLatin1()+"\r\n");
                f.write(password_str.toLatin1()+"\r\n");
                f.close();
                dynamic_cast<Widget*>(parent)->initialUser();
                emit dynamic_cast<Widget*>(parent)->gotopick();
            }
        }
    });
}

register_widget::~register_widget()
{
    delete ui;
}
