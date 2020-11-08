#include "pick.h"
#include<ui_pick.h>
#include<toolbutton.h>
extern QSqlDatabase db;
pick::pick(QWidget *parent) : QWidget(parent),ui(new Ui::Form)
{
    ui->setupUi(this);
    resize(parent->width(),parent->height()-40);
    view=ui->tableView;view->setShowGrid(0);
    view->setStyleSheet("background-color:rgba(255,255,255,100);border:0px;");
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    buy=new QToolButton(this);buy->move(800,650);buy->setText("立即购买");
    buy->setStyleSheet("width:150px;height:60px;background-color:rgb(53,150,255);border-radius:20px;");
    //buy->setDisabled(1);
    input=new Line(this);input->move(20,45);input->resize(800,50);input->setText("请输入您心仪的网站名称");
    searchbutton=new QToolButton(this);searchbutton->move(850,50);searchbutton->setText("搜索");
    searchbutton->setStyleSheet("width:100px;height:40px;background-color:rgb(53,150,255);border-radius:5px;");
}
