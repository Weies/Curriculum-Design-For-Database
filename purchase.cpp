#include "purchase.h"
#include "ui_purchase.h"
#include<widget.h>
#include<string.h>
#include<qmessagebox.h>
#include<qsqlquery.h>
#include<qdatetime.h>
extern QSqlDatabase db;
extern bool regestered;
extern QString ID;
#include<QSqlRecord>
using namespace std;
purchase::purchase(QWidget *parent) :
    QWidget(parent), parent(parent),
    ui(new Ui::purchase)
{
    ui->setupUi(this);
    QLabel *head=new QLabel("购买",this);
    head->move(480,40);
    btn_commit=new superButton("提交",this);btn_commit->resize(250,40);
    btn_return=new superButton("返回",this);btn_return->resize(250,40);
    btn_commit->move(220,600);btn_return->move(530,600);
    btn_commit->setMouseOutColor(QColor(4,186,251));
    btn_return->setMouseOutColor(QColor(4,186,251));
    ui->groupBox->setStyleSheet(QObject::tr("#groupBox{border: 0px solid;}"));
    this->setStyleSheet("QLineEdit{border :1px ;background-color: rgba(0,0,0,0)}");
    ui->lineEdit->setReadOnly(true);ui->lineEdit_2->setReadOnly(true);ui->lineEdit_3->setReadOnly(true);ui->lineEdit_4->setReadOnly(true);ui->lineEdit_5->setReadOnly(true);
    ui->spinBox->setSuffix("年");
    connect(btn_commit,&superButton::Clicked,[=](){
        int num=ui->spinBox->value();
        if(num==0)QMessageBox::critical(this,"critical","购买时长不能为0年");
        else if(!ui->radioButton->isChecked()&&!ui->radioButton_2->isChecked()&&!ui->radioButton_3->isChecked())QMessageBox::warning(this,"critical","请选择一种支付方式");
        else
        {
            QDateTime buytime = QDateTime::currentDateTime(); //获取系统现在的时间
            QDateTime endtime = buytime.addYears(ui->spinBox->value());
            QString time_str = buytime.toString("yyyy-MM-dd"); //设置显示格式
            QString time_str1 = endtime.toString("yyyy-MM-dd");
            QString str = QString("insert into sold_domain values('%1','%2','%3',str_to_date('%4','%Y-%m-%d'),str_to_date('%5','%Y-%m-%d'),'%6','')").arg(ui->lineEdit_2->text()).arg(ui->lineEdit_3->text()).arg(ID).arg(time_str).arg(time_str1).arg(ui->lineEdit->text());
            QString str2 = QString("update all_domain set is_sold='yes' where dm_name='%1'").arg(ui->lineEdit_2->text());
            QString str3 = QString("delete from available_dn where dm_name='%1'").arg(ui->lineEdit_2->text());
            QSqlQuery query(db);
            query.exec(str);
            query.exec(str2);
            query.exec(str3);
            static_cast<Widget*>(parent)->pick->model->select();
            emit dynamic_cast<Widget*>(parent)->gotopick();
        }
    });
    connect(btn_return,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotopick();
    });
    connect(ui->spinBox,&QSpinBox::textChanged,[=](){
        cost_update();
    });
}

purchase::~purchase()
{
    delete ui;
}

void purchase::update(QSqlRecord* reco)
{
    ui->lineEdit_2->setText(reco->value(0).toString());
    ui->lineEdit_3->setText(reco->value(1).toString());
    ui->lineEdit_4->setText(reco->value(2).toString());
    ui->lineEdit_5->setText(reco->value(3).toString());
    cost_update();
}

void purchase::cost_update()
{
    int num=ui->spinBox->value();
    string price=ui->lineEdit_4->text().toStdString();
    char buf[32] = {0};
    sscanf(price.c_str(),"%[0-9]",buf);
    ui->lineEdit->setText(QString::number(num*atoi(buf))+"元");
}
