#include "addnewhost.h"
#include "ui_addnewhost.h"
#include<qmessagebox.h>
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include<widget.h>
extern QSqlDatabase db;
addnewhost::addnewhost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addnewhost)
{
    ui->setupUi(this);
    QLabel *head=new QLabel("添加新主机",this);
    head->move(430,80);
    btn_commit=new superButton("提交",this);btn_commit->resize(250,40);
    btn_back=new superButton("返回",this);btn_back->resize(250,40);
    btn_commit->move(230,600);
    btn_back->move(540,600);
    btn_commit->setMouseOutColor(QColor(4,186,251));
    btn_back->setMouseOutColor(QColor(4,186,251));
    connect(btn_commit,&superButton::Clicked,[=](){
        if(ui->lineEdit->text()=="")QMessageBox::critical(this,"critical","主机不能为空");
        else if(ui->lineEdit_2->text()=="")QMessageBox::critical(this,"critical","库房编号不能为空");
        else if(ui->lineEdit_3->text()=="")QMessageBox::critical(this,"critical","版本不能为空");
        else {
            QString host_str=ui->lineEdit->text();
            QString str=QString("select host_id from entity_host where host_id='%1' ").arg(host_str);
            QSqlQuery query(db);
            query.exec(str);
            QString host_str1="";
            while(query.next())host_str1=query.value(0).toString();
            if(host_str1!="")QMessageBox::critical(this,"critical","主机库中已存在该主机");
            else {
                QString str1 = QString("insert into entity_host values('%1','%2','%3','no',0)").arg(host_str).arg(ui->lineEdit_2->text()).arg(ui->lineEdit_3->text());
                query.exec(str1);
                emit dynamic_cast<Widget*>(parent)->gotoallhost();
            }
        }
    });
    connect(btn_back,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotoallhost();
    });
}

addnewhost::~addnewhost()
{
    delete ui;
}
