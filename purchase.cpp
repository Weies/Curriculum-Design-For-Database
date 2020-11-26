#include "purchase.h"
#include "ui_purchase.h"
extern bool regestered;
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
}

purchase::~purchase()
{
    delete ui;
}
