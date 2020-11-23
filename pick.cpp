#include "pick.h"
#include<ui_pick.h>
#include<superbutton.h>
#include<QDebug>
extern QSqlDatabase db;
#include<QKeyEvent>
pick::pick(QWidget *parent) : QWidget(parent),ui(new Ui::Form)
{
    ui->setupUi(this);
    resize(parent->width(),parent->height()-40);
    view=ui->tableView;view->setShowGrid(0);
    view->setStyleSheet("background-color:rgba(255,255,255,100);border:0px;");
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->horizontalHeader()->setSectionsClickable(false);
    view->setMinimumWidth(800);
    view->installEventFilter(this);
    buy=new QToolButton(this);buy->move(800,650);buy->setText("立即购买");
    buy->setStyleSheet("width:150px;height:60px;background-color:rgb(53,150,255);border-radius:10px;");
    view->setEditTriggers(QTableView::NoEditTriggers);
    input=new Line(this);input->move(20,45);input->resize(800,50);input->setText("请输入您心仪的网站名称");
    searchbutton=new QToolButton(this);searchbutton->move(850,50);searchbutton->setText("搜索");
    searchbutton->setStyleSheet("width:100px;height:40px;background-color:rgb(53,150,255);border-radius:5px;");

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
