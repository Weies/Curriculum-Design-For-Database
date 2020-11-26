#include "purchase.h"
#include "ui_purchase.h"
#include<widget.h>
extern bool regestered;
#include<QSqlRecord>
purchase::purchase(QWidget *parent) :
    QWidget(parent),
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
}

purchase::~purchase()
{
    delete ui;
}

void purchase::update()
{
    QSqlRecord reco=dynamic_cast<Widget*>(parent())->model->record(dynamic_cast<Widget*>(parent())->currentindex.row());
    ui->lineEdit_2->setText(reco.value(0).toString());
    ui->lineEdit_3->setText(reco.value(1).toString());
    ui->lineEdit_4->setText(reco.value(2).toString());
    ui->lineEdit_5->setText(reco.value(3).toString());



}
