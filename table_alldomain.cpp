#include "table_alldomain.h"
#include "ui_table_alldomain.h"
#include<qmessagebox.h>
#include<QSqlError>
#include<qsqlquery.h>
#include<qsqlrecord.h>
#include<ReadOnlyDelegate.h>
#include<widget.h>
extern QSqlDatabase db;
table_alldomain::table_alldomain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::table_alldomain)
{
    ui->setupUi(this);
    btn_back=new superButton("返回",this);btn_back->resize(250,40);
    btn_back->move(600,650);
    btn_back->setMouseOutColor(QColor(4,186,251));
    btn_add=new superButton("添加",this);btn_add->resize(250,40);
    btn_add->move(200,650);
    btn_add->setMouseOutColor(QColor(4,186,251));
    view=ui->tableView;view->setShowGrid(0);
    view->setStyleSheet("background-color:rgba(255,255,255,100);border:0px;");
//    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->horizontalHeader()->setSectionsClickable(false);
    view->setMinimumWidth(800);
    view->installEventFilter(this);
//    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
//    view->setItemDelegateForColumn(0,readOnlyDelegate);
    view->setEditTriggers(QTableView::NoEditTriggers);
    model=new QSqlTableModel(this,db);
    view->setModel(model);
    model->setTable("all_domain");
    if(!model->select())
    {
        QMessageBox::warning(this,"Failed","Failed to get the data:"+db.lastError().text());
    }
    view->horizontalHeader()->resizeSection(0,305);
    view->horizontalHeader()->resizeSection(1,160);
    view->horizontalHeader()->resizeSection(2,190);
    view->horizontalHeader()->resizeSection(3,160);
    view->horizontalHeader()->resizeSection(4,100);
    connect(model,&QSqlTableModel::beforeUpdate,[=](){
        QSqlRecord reco=model->record(view->currentIndex().row());
        QString dm_str,quality_str,price_str,area_str;
        dm_str=reco.value(0).toString();
        quality_str=reco.value(1).toString();
        price_str=reco.value(2).toString();
        area_str=reco.value(3).toString();
        QSqlQuery query(db);
        QString str=QString("update available_dn set quality='%1',price='%2',area='%3' where dm_name='%4' ").arg(quality_str).arg(price_str).arg(area_str).arg(dm_str);
        query.exec(str);
    });
    connect(btn_back,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotoadmin();
    });
    connect(btn_add,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotoadddomain();
    });
}

table_alldomain::~table_alldomain()
{
    delete ui;
}
