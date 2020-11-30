#include "adminwidget.h"
#include "ui_adminwidget.h"
#include<widget.h>
adminwidget::adminwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminwidget)
{
    ui->setupUi(this);
    btn_next=new superButton("查看",this);btn_next->resize(250,40);btn_next->move(500,70);btn_next->setMouseOutColor(QColor(4,186,251));
    btn_next1=new superButton("查看",this);btn_next1->resize(250,40);btn_next1->move(500,160);btn_next1->setMouseOutColor(QColor(4,186,251));
    btn_next2=new superButton("查看",this);btn_next2->resize(250,40);btn_next2->move(500,250);btn_next2->setMouseOutColor(QColor(4,186,251));
    btn_next3=new superButton("查看",this);btn_next3->resize(250,40);btn_next3->move(500,340);btn_next3->setMouseOutColor(QColor(4,186,251));
    btn_next4=new superButton("查看",this);btn_next4->resize(250,40);btn_next4->move(500,430);btn_next4->setMouseOutColor(QColor(4,186,251));
    btn_next5=new superButton("查看",this);btn_next5->resize(250,40);btn_next5->move(500,520);btn_next5->setMouseOutColor(QColor(4,186,251));
    btn_back=new superButton("返回",this);btn_back->resize(250,40);btn_back->move(380,640);btn_back->setMouseOutColor(QColor(4,186,251));
    QLabel* label=new QLabel("总域名",this);label->move(330,77);
    QLabel* label1=new QLabel("在售域名",this);label1->move(330,167);
    QLabel* label2=new QLabel("已售域名",this);label2->move(330,257);
    QLabel* label3=new QLabel("域名资源",this);label3->move(330,347);
    QLabel* label4=new QLabel("实体主机",this);label4->move(330,437);
    QLabel* label5=new QLabel("IP资源",this);label5->move(330,527);
    connect(btn_back,&superButton::Clicked,[=](){
        emit dynamic_cast<Widget*>(parent)->gotopick();
    });

}

adminwidget::~adminwidget()
{
    delete ui;
}
