#include "control.h"
#include "ui_control.h"
#include<widget.h>
control::control(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::control)
{
    ui->setupUi(this);
    QLabel *head=new QLabel("控制台",this);
    head->resize(100,40);
    head->move(470,40);
    btn_back=new superButton("返回",this);btn_back->resize(250,40);
    btn_back->move(380,640);
    btn_back->setMouseOutColor(QColor(4,186,251));
    connect(btn_back,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotopick();
    });
}

control::~control()
{
    delete ui;
}
