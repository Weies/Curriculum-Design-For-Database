#include "control.h"
#include "ui_control.h"
#include<widget.h>
#include<qstandarditemmodel.h>
#include<qsqlquery.h>
#include<qmessagebox.h>
extern QSqlDatabase db;
extern bool regestered;
extern QString ID;
control::control(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::control)
{
    ui->setupUi(this);
    view=ui->tableView;
    QLabel *head=new QLabel("控制台",this);
    head->resize(100,40);
    head->move(470,40);
    btn_back=new superButton("返回",this);btn_back->resize(250,40);
    btn_back->move(200,640);
    btn_back->setMouseOutColor(QColor(4,186,251));
    btn_next=new superButton("查看详情",this);btn_next->resize(250,40);
    btn_next->move(600,640);
    btn_next->setMouseOutColor(QColor(4,186,251));
    connect(btn_back,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotopick();
    });
}
void control::update()
{

}
control::~control()
{
    delete ui;
}
