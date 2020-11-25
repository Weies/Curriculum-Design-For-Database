#include "register_widget.h"
#include "ui_register_widget.h"
#include<widget.h>
#include<qdebug.h>
#include<qmessagebox.h>
register_widget::register_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::register_widget)
{
    //QMessageBox password_wrong;
    ui->setupUi(this);
    btn_commit=new superButton("提交",this);btn_commit->resize(250,40);
    btn_commit->move(400,500);
    btn_commit->setMouseOutColor(QColor(4,186,251));
    connect(btn_commit,&superButton::Clicked,[=](){
        if(ui->lineEdit->text()=="")QMessageBox::critical(this,"critical","账号不能为空");
        else if(ui->lineEdit_2->text()=="")QMessageBox::critical(this,"critical","密码不能为空");
        else if(ui->lineEdit_2->text()!=ui->lineEdit_3->text())QMessageBox::critical(this,"critical","密码与确认密码必须相同");
        else if(ui->lineEdit_4->text()=="")QMessageBox::critical(this,"critical","手机号不能为空");
        else emit dynamic_cast<Widget*>(parent)->gotologin();
    });
}

register_widget::~register_widget()
{
    delete ui;
}
