#include "table_ip.h"
#include "ui_table_ip.h"
#include<qmessagebox.h>
#include<QSqlError>
#include<qsqlquery.h>
#include<qsqlrecord.h>
#include<ReadOnlyDelegate.h>
#include<widget.h>
extern QSqlDatabase db;
table_ip::table_ip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::table_ip)
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
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->horizontalHeader()->setSectionsClickable(false);
    view->setMinimumWidth(800);
    view->installEventFilter(this);
//    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
//    view->setItemDelegateForColumn(0,readOnlyDelegate);
    view->setEditTriggers(QTableView::NoEditTriggers);
    model=new QSqlTableModel(this,db);
    view->setModel(model);
    model->setTable("ip_resource");
    if(!model->select())
    {
        QMessageBox::warning(this,"Failed","Failed to get the data:"+db.lastError().text());
    }
    connect(btn_back,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotoadmin();
    });
    connect(btn_add,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotonewip();
    });
}

table_ip::~table_ip()
{
    delete ui;
}
