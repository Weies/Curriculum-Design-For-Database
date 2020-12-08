#include "pick.h"
#include<ui_pick.h>
#include<superbutton.h>
#include<QDebug>
#include<widget.h>
#include<ReadOnlyDelegate.h>
#include<QSqlQuery>
#include<QKeyEvent>
#include<QSqlError>
extern QSqlDatabase db;
extern bool is_admin;
extern bool regestered;
pick::pick(QWidget *parent) : QWidget(parent),ui(new Ui::Form)
{
    ui->setupUi(this);
    resize(parent->width(),parent->height()-40);
    view=ui->tableView;view->setShowGrid(0);
    model=new QSqlTableModel(this,db);
    view->setModel(model);
    model->setTable("available_DN");
    view->setStyleSheet("background-color:rgba(255,255,255,100);border:0px;");
    //view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    view->horizontalHeader()->setSectionsClickable(false);
    view->setMinimumWidth(800);
    view->installEventFilter(this);
    buy=new QToolButton(this);buy->move(800,650);buy->setText("立即购买");
    buy->setStyleSheet("width:150px;height:60px;background-color:rgb(53,150,255);border-radius:10px;");
    input=new Line(this);input->move(20,45);input->resize(800,50);input->setText("请输入您心仪的网站名称");
    searchbutton=new QToolButton(this);searchbutton->move(850,50);searchbutton->setText("搜索");
    searchbutton->setStyleSheet("width:100px;height:40px;background-color:rgb(53,150,255);border-radius:5px;");
    managebutton=new QToolButton(this);managebutton->move(100,650);managebutton->setText("管理台");
    managebutton->setStyleSheet("width:150px;height:60px;background-color:rgb(53,150,255);border-radius:10px;");
    managebutton->hide();
    connect(managebutton,&QToolButton::clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotoadmin();
    });
    if(!model->select())
    {
        QMessageBox::warning(this,"Failed","Failed to get the data:"+db.lastError().text());
    }

    view->horizontalHeader()->resizeSection(0,800);
    connect(searchbutton,&QToolButton::clicked,[=](){
        model->setFilter("dm_name like '%"+input->text()+"%'");

    });

    connect(model,&QSqlTableModel::beforeUpdate,[=](){
        QSqlRecord reco=model->record(view->currentIndex().row());
        QString dm_str,quality_str,price_str,area_str;
        dm_str=reco.value(0).toString();
        quality_str=reco.value(1).toString();
        price_str=reco.value(2).toString();
        area_str=reco.value(3).toString();
        QSqlQuery query(db);
        QString str=QString("update all_domain set quality='%1',price='%2',area='%3' where dm_name='%4' ").arg(quality_str).arg(price_str).arg(area_str).arg(dm_str);
        query.exec(str);
    });
}

bool pick::eventFilter(QObject* obj,QEvent* evt)
{
    if(obj==this->input)
    {
        if(evt->type()==QEvent::KeyPress)
        {
            QKeyEvent* key=dynamic_cast<QKeyEvent*>(evt);
            if(key->key()==Qt::Key_Enter||key->key()==Qt::Key_Return)
            {
                emit this->searchbutton->clicked();
                return true;
            }
        }
        return false;
    }
    if(obj==this->view)
    {
        //qDebug()<<evt->type();
        if(evt->type()==QEvent::FocusIn)
        {
           return true;
        }
        return false;
    }
    return false;
}

void pick::admin_update()
{
    if(regestered&&is_admin)
    {
        managebutton->show();
        ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
        view->setItemDelegateForColumn(0,readOnlyDelegate);
    }
    else view->setEditTriggers(QTableView::NoEditTriggers);
}

