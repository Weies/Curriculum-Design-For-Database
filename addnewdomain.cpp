#include "addnewdomain.h"
#include "ui_addnewdomain.h"
#include<qmessagebox.h>
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include<widget.h>
extern QSqlDatabase db;
addnewdomain::addnewdomain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addnewdomain)
{
    ui->setupUi(this);
    QLabel *head=new QLabel("添加新域名",this);
    head->move(430,80);
    btn_commit=new superButton("提交",this);btn_commit->resize(250,40);
    btn_back=new superButton("返回",this);btn_back->resize(250,40);
    btn_commit->move(230,600);
    btn_back->move(540,600);
    btn_commit->setMouseOutColor(QColor(4,186,251));
    btn_back->setMouseOutColor(QColor(4,186,251));
    connect(btn_commit,&superButton::Clicked,[=](){
        if(ui->lineEdit->text()=="")QMessageBox::critical(this,"critical","域名不能为空");
        else if(ui->lineEdit_2->text()=="")QMessageBox::critical(this,"critical","性质不能为空");
        else if(ui->lineEdit_3->text()=="")QMessageBox::critical(this,"critical","价格不能为空");
        else if(ui->lineEdit_4->text()=="")QMessageBox::critical(this,"critical","地域不能为空");
        else {
            QString dm_str=ui->lineEdit->text();
            QString quality_str=ui->lineEdit_2->text();
            QString price_str=ui->lineEdit_3->text();
            QString area_str=ui->lineEdit_4->text();
            QString str=QString("select dm_name from all_domain where dm_name='%1' ").arg(dm_str);
            QSqlQuery query(db);
            query.exec(str);
            QString dm_str1="";
            while(query.next())dm_str1=query.value(0).toString();
            if(dm_str1!="")QMessageBox::critical(this,"critical","域名库中已存在该域名");
            else {
                QString str1 = QString("insert into all_domain values('%1','%2','%3','%4','no')").arg(dm_str).arg(quality_str).arg(price_str).arg(area_str);
                QString str2 = QString("insert into available_dn values('%1','%2','%3','%4')").arg(dm_str).arg(quality_str).arg(price_str).arg(area_str);
                query.exec(str1);
                query.exec(str2);
                emit dynamic_cast<Widget*>(parent)->gotoalldomain();
            }
        }
    });
    connect(btn_back,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotoalldomain();
    });
}

addnewdomain::~addnewdomain()
{
    delete ui;
}
