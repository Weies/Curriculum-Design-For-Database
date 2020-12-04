#include "domain_detail.h"
#include "ui_domain_detail.h"
#include<qlabel.h>
#include<qsqlrecord.h>
#include<widget.h>
#include<ReadOnlyDelegate.h>
#include<qsqlquery.h>
#include<QSqlError>
#include<qstandarditemmodel.h>
extern QSqlDatabase db;
extern bool regestered;
extern QString ID;
domain_detail::domain_detail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::domain_detail)
{
    ui->setupUi(this);
    QLabel *head1=new QLabel("主机记录",this);
    QLabel *head2=new QLabel("访问记录",this);
    head1->move(450,40);head2->move(450,245);
    btn_back=new superButton("返回",this);btn_back->resize(250,40);
    btn_back->move(380,640);
    btn_back->setMouseOutColor(QColor(4,186,251));
    connect(btn_back,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotocontrol();
    });
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
    ui->tableView->setItemDelegateForColumn(0,readOnlyDelegate);
    ui->tableView->setItemDelegateForColumn(4,readOnlyDelegate);
    model=new QSqlTableModel(this,db);
    ui->tableView->setModel(model);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    model->setTable("domain_record");
    if(!model->select())
    {
        QMessageBox::warning(this,"Failed","Failed to get the data:"+db.lastError().text());
    }
    ui->tableView->setStyleSheet("background-color:transparent");
}
void domain_detail::update(QStandardItem *reco)
{
    model->setFilter("dm_name like '%"+reco->text()+"%'");
}
domain_detail::~domain_detail()
{
    delete ui;
}
