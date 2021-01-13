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
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    model=new QSqlTableModel(this,db);
    ui->tableView->setModel(model);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    model->setTable("domain_record");
    if(!model->select())
    {
        QMessageBox::warning(this,"Failed","Failed to get the data:"+db.lastError().text());
    }
    ui->tableView->horizontalHeader()->resizeSection(0,300);
    ui->tableView->horizontalHeader()->resizeSection(1,90);
    ui->tableView->horizontalHeader()->resizeSection(2,90);
    ui->tableView->horizontalHeader()->resizeSection(3,90);
    ui->tableView->horizontalHeader()->resizeSection(4,200);
    ui->tableView->horizontalHeader()->resizeSection(5,100);
    ui->tableView->horizontalHeader()->resizeSection(6,100);

    record_model=new QSqlTableModel(this,db);
    record_model->setTable("domain_visit");
    ui->tableView_2->setModel(record_model);
//    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_2->setEditTriggers(QTableView::NoEditTriggers);
    ui->tableView_2->horizontalHeader()->resizeSection(0,0);
    ui->tableView_2->horizontalHeader()->resizeSection(1,300);
    ui->tableView_2->horizontalHeader()->resizeSection(2,335);
    ui->tableView_2->horizontalHeader()->resizeSection(3,300);
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
            QStringList list=filename.split('/');
            QStringList list1=list[list.length()-1].split('.');
            QSqlQuery query(db);
            QString str = QString("select dm_name from domain_resource where dm_name = '%1'").arg(dm_name);
            query.exec(str);
            query.next();
            int iswrong=0;
            QString str1;
            if(query.value(0).toString()=="")
            {
                if(list1[list1.length()-1]=="html")str1 = QString("insert into domain_resource values('%1','%2','','')").arg(dm_name).arg(list[list.length()-1]);
                else if(list1[list1.length()-1]=="css")str1 = QString("insert into domain_resource values('%1','','%2','')").arg(dm_name).arg(list[list.length()-1]);
                else if(list1[list1.length()-1]=="js")str1 = QString("insert into domain_resource values('%1','','','%2')").arg(dm_name).arg(list[list.length()-1]);
                else QMessageBox::critical(this,"critical","文件格式有错误"),iswrong=1;
            }
            else
            {
                if(list1[list1.length()-1]=="html")str1 = QString("update domain_resource set html='%2' where dm_name='%1' ").arg(dm_name).arg(list[list.length()-1]);
                else if(list1[list1.length()-1]=="css")str1 = QString("update domain_resource set css='%2' where dm_name='%1' ").arg(dm_name).arg(list[list.length()-1]);
                else if(list1[list1.length()-1]=="js")str1 = QString("update domain_resource set js='%2' where dm_name='%1' ").arg(dm_name).arg(list[list.length()-1]);
                else QMessageBox::critical(this,"critical","文件格式有错误"),iswrong=1;
            }
            if(iswrong==0)query.exec(str1);
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
    dm_name=reco->text();
}
domain_detail::~domain_detail()
{
    delete ui;
}
