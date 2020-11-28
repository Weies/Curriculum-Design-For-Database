#include "control.h"
#include "ui_control.h"
#include<widget.h>
#include<qstandarditemmodel.h>
control::control(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::control)
{
    ui->setupUi(this);
    QLabel *head=new QLabel("控制台",this);
    head->resize(100,40);
    head->move(470,40);
    btn_back=new superButton("返回",this);btn_back->resize(250,40);
    btn_back->move(380,640);
    btn_back->setMouseOutColor(QColor(4,186,251));
    QStandardItemModel *control_model = new QStandardItemModel();
    control_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("域名")));
    control_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("性质")));
    control_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("购买日期")));
    control_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("到期时间")));
    control_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("费用")));
    control_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("访问记录")));
    control_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("主机记录")));
    control_model->setItem(0,0,new QStandardItem(QObject::tr("www.aoaoligei.com")));
    control_model->setItem(0,1,new QStandardItem(QObject::tr("顶级域名")));
    control_model->setItem(0,2,new QStandardItem(QObject::tr("2020-11-12")));
    control_model->setItem(0,3,new QStandardItem(QObject::tr("2020-11-12")));
    control_model->setItem(0,4,new QStandardItem(QObject::tr("10000元")));
    control_model->setItem(0,5,new QStandardItem(QObject::tr("点击查看")));
    control_model->setItem(0,6,new QStandardItem(QObject::tr("点击查看")));
    //利用setModel()方法将数据模型与QTableView绑定
    ui->tableView->setModel(control_model);
    ui->tableView->setStyleSheet("background-color:transparent");
    ui->tableView->setColumnWidth(0,300);ui->tableView->setColumnWidth(1,150);ui->tableView->setColumnWidth(2,170);ui->tableView->setColumnWidth(3,170);ui->tableView->setColumnWidth(4,150);ui->tableView->setColumnWidth(5,120);ui->tableView->setColumnWidth(6,120);


    connect(btn_back,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotopick();
    });
}

control::~control()
{
    delete ui;
}
