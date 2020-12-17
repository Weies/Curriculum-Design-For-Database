#include "domain_detail.h"
#include "ui_domain_detail.h"
#include<qlabel.h>
#include<qsqlrecord.h>
#include<widget.h>
#include<ReadOnlyDelegate.h>
#include<qsqlquery.h>
#include<QSqlError>
#include<qfiledialog.h>
#include<qstandarditemmodel.h>
extern QSqlDatabase db;
extern bool regestered;
extern QString ID;
extern server* svr;
domain_detail::domain_detail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::domain_detail)
{
    ui->setupUi(this);
    QLabel *head1=new QLabel("主机记录",this);
    QLabel *head2=new QLabel("访问记录",this);
    QLabel *head3=new QLabel("上传网页文件（html、css、js文件）：",this);
    head1->move(450,40);head2->move(450,195);head3->move(190,550);
    btn_back=new superButton("返回",this);btn_back->resize(250,40);
    btn_back->move(380,640);
    btn_back->setMouseOutColor(QColor(4,186,251));
    addfile=new superButton("上传",this);addfile->resize(150,40);
    addfile->move(690,543);
    addfile->setMouseOutColor(QColor(4,186,251));

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

    record_model=new QSqlTableModel(this,db);
    record_model->setTable("domain_visit");
    ui->tableView_2->setModel(record_model);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    if(!record_model->select())
    {
        QMessageBox::warning(this,"Failed","Failed to get the data:"+db.lastError().text());
    }

    ui->tableView->setStyleSheet("background-color:transparent");
    connect(addfile,&superButton::Clicked,[=](){
        QString filename=QFileDialog::getOpenFileName(this,"上传文件","C:");
        if(filename!="")
        {
            svr->upload(filename);
        }
    });

    refresh=new superButton("刷新",this);
    refresh->move(900,190);refresh->resize(40,15);
    connect(refresh,&superButton::Clicked,[=](){
        svr->update();
        QTimer::singleShot(2000,record_model,[=](){
            record_model->select();
        });
    });
}
void domain_detail::update(QStandardItem *reco)
{
    model->setFilter("dm_name like '%"+reco->text()+"%'");
}
domain_detail::~domain_detail()
{
    delete ui;
}
