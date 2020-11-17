#include "register_widget.h"
#include "ui_register_widget.h"
#include<widget.h>
register_widget::register_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::register_widget)
{
    ui->setupUi(this);
    btn_commit=new superButton("提交",this);btn_commit->resize(250,40);
    btn_commit->move(400,500);
    btn_commit->setMouseOutColor(QColor(4,186,251));
    connect(btn_commit,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotologin();
    });
}

register_widget::~register_widget()
{
    delete ui;
}
