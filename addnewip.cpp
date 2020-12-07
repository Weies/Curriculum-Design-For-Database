#include "addnewip.h"
#include "ui_addnewip.h"
#include<qmessagebox.h>
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include<widget.h>
extern QSqlDatabase db;
addnewip::addnewip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addnewip)
{
    ui->setupUi(this);
    QLabel *head=new QLabel("添加新IP",this);
    head->move(430,80);
    btn_commit=new superButton("提交",this);btn_commit->resize(250,40);
    btn_back=new superButton("返回",this);btn_back->resize(250,40);
    btn_commit->move(230,600);
    btn_back->move(540,600);
    btn_commit->setMouseOutColor(QColor(4,186,251));
    btn_back->setMouseOutColor(QColor(4,186,251));
    connect(btn_commit,&superButton::Clicked,[=](){
        if(ui->lineEdit->text()=="")QMessageBox::critical(this,"critical","IP地址不能为空");
        else {
            QString ip_str=ui->lineEdit->text();
            QString str=QString("select IP from ip_resource where ip='%1' ").arg(ip_str);
            QSqlQuery query(db);
            query.exec(str);
            QString ip_str1="";
            while(query.next())ip_str1=query.value(0).toString();
            if(ip_str1!="")QMessageBox::critical(this,"critical","IP库中已存在该IP");
            else {
                QString str0 = QString("select host_id from entity_host where ip_num<10").arg(ip_str);
                query.exec(str0);
                QString host_str;
                if(query.next())host_str=query.value(0).toString();
                QString str1 = QString("insert into ip_resource values('%1','no','%2','yes')").arg(ip_str).arg(host_str);
                query.exec(str1);
                QString str2 = QString("update entity_host set ip_num=ip_num+1 where host_id='%1'").arg(host_str);
                query.exec(str2);
                emit dynamic_cast<Widget*>(parent)->gotoallip();
            }
        }
    });
    connect(btn_back,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotoallip();
    });
}

addnewip::~addnewip()
{
    delete ui;
}
