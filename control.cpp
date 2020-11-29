#include "control.h"
#include "ui_control.h"
#include<widget.h>
#include<qstandarditemmodel.h>
#include<qsqlquery.h>
extern QSqlDatabase db;
extern bool regestered;
extern QString ID;
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
    connect(btn_back,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotopick();
    });
}
void control::update()
{
    int row=0;//行数
    QStandardItemModel *control_model = new QStandardItemModel();
    control_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("域名")));
    control_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("性质")));
    control_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("购买日期")));
    control_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("到期时间")));
    control_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("费用")));
    //利用setModel()方法将数据模型与QTableView绑定
    ui->tableView->setModel(control_model);
    ui->tableView->setStyleSheet("background-color:transparent");
    ui->tableView->setColumnWidth(0,310);ui->tableView->setColumnWidth(1,170);ui->tableView->setColumnWidth(2,170);ui->tableView->setColumnWidth(3,170);ui->tableView->setColumnWidth(4,150);
    QSqlQuery query(db);
    QString str=QString("select dm_name,quality,buytime,endtime,cost from sold_domain where account_id ='%1'").arg(ID);
    query.exec(str);
    QString dmname_str,quality_str,buytime_str,endtime_str,cost_str;
    while(query.next())
    {
        dmname_str=query.value(0).toString();
        quality_str=query.value(1).toString();
        buytime_str=query.value(2).toString();
        endtime_str=query.value(3).toString();
        cost_str=query.value(4).toString();
        control_model->setItem(row,0,new QStandardItem(dmname_str));
        control_model->setItem(row,1,new QStandardItem(quality_str));
        control_model->setItem(row,2,new QStandardItem(buytime_str));
        control_model->setItem(row,3,new QStandardItem(endtime_str));
        control_model->setItem(row++,4,new QStandardItem(cost_str));
    }
}
control::~control()
{
    delete ui;
}
