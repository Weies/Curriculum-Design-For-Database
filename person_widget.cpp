#include "person_widget.h"
#include "ui_person_widget.h"
#include<widget.h>

person_widget::person_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::person_widget)
{
    ui->setupUi(this);
    QLabel *head=new QLabel("个人信息",this);
    head->move(440,40);
    comboBox_type=new QComboBox(this);
    comboBox_type->addItems(QStringList()<<"居民身份证"<<"港澳通行证"<<"护照");
    comboBox_type->setAttribute(Qt::WA_TransparentForMouseEvents,false);
    comboBox_type->installEventFilter(this);
    comboBox_type->move(480,375);
    btn_commit=new superButton("提交",this);btn_commit->resize(250,40);
    btn_return=new superButton("返回",this);btn_return->resize(250,40);
    btn_commit->move(220,650);btn_return->move(530,650);
    btn_commit->setMouseOutColor(QColor(4,186,251));
    btn_return->setMouseOutColor(QColor(4,186,251));
    btn_commit->setEnabled(false);
    //this->setStyleSheet("QLineEdit{border :1px ;background-color: rgba(0,0,0,0)}");
//    ui->username->setStyleSheet("border :1px ;background-color: rgba(0,0,0,0)");
//    ui->phonenum->setStyleSheet("border :1px ;background-color: rgba(0,0,0,0)");
//    ui->idnum->setStyleSheet("border :1px ;background-color: rgba(0,0,0,0)");
//    ui->beian->setStyleSheet("border :1px ;background-color: rgba(0,0,0,0)");
//    ui->address->setStyleSheet("border :1px ;background-color: rgba(0,0,0,0)");
//    ui->truename->setStyleSheet("border :1px ;background-color: rgba(0,0,0,0)");
    connect(btn_commit,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotopick();
    });
    connect(btn_return,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotopick();
    });
}

person_widget::~person_widget()
{
    delete ui;
}

bool person_widget::eventFilter(QObject* obj,QEvent* e)
{
    if(obj==comboBox_type&&e->type()==QEvent::MouseMove)
    return true;
    return false;
}
