#include "table_solddomain.h"
#include "ui_table_solddomain.h"
#include<qmessagebox.h>
#include<QSqlError>
#include<qsqlquery.h>
#include<qsqlrecord.h>
#include<ReadOnlyDelegate.h>
#include<widget.h>
extern QSqlDatabase db;
table_solddomain::table_solddomain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::table_solddomain)
{
    ui->setupUi(this);
    btn_back=new superButton("返回",this);btn_back->resize(250,40);
    btn_back->move(400,650);
    btn_back->setMouseOutColor(QColor(4,186,251));
    view=ui->tableView;view->setShowGrid(0);
    view->setStyleSheet("background-color:rgba(255,255,255,100);border:0px;");
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->horizontalHeader()->setSectionsClickable(false);
    view->setMinimumWidth(800);
    view->installEventFilter(this);
    view->setEditTriggers(QTableView::NoEditTriggers);
    model=new QSqlTableModel(this,db);
    view->setModel(model);
    model->setTable("sold_domain");
    if(!model->select())
    {
        QMessageBox::warning(this,"Failed","Failed to get the data:"+db.lastError().text());
    }
    connect(btn_back,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotoadmin();
    });
}

table_solddomain::~table_solddomain()
{
    delete ui;
}
