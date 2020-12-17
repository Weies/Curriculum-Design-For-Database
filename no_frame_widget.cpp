#include "no_frame_widget.h"
#include "ui_widget.h"
#include<QMouseEvent>

bool maxstate;//最大化状态，初识为0
No_Frame_Widget::No_Frame_Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    close=new superButton(QPixmap(":/icon/close.png"),this);//初始化关闭按钮
    close->setPixSize(34,34);
    close->resize(60,40);close->setMouseInColor(QColor(250,100,100));

    min=new superButton(QPixmap(":/icon/min.png"),this);
    min->setPixSize(35,35);
    min->resize(60,40);

    max=new superButton(QPixmap(":/icon/max.png"),this);
    max->setPixSize(30,30);max->resize(60,40);

    connect(close,SIGNAL(Clicked()),SLOT(close()));
    connect(min,&superButton::Clicked,this,&No_Frame_Widget::showMinimized);
    connect(max,&superButton::Clicked,this,[=](){
        maxstate=!maxstate;
        if(maxstate)
        {
            w=width();h=height();xx=x();yy=y();
            this->move(0,0);this->resize(1920,1030);
            movable=false;
        }
        else
        {
            resize(w,h);move(xx,yy);movable=true;
        }
    });
}

void No_Frame_Widget::resizeEvent(QResizeEvent *)
{
    max->move(width()-120,0);
    close->move(width()-60,0);
    min->move(width()-180,0);
}

void No_Frame_Widget::mousePressEvent(QMouseEvent *event)
{
    px=event->x();
    py=event->y();
}

void No_Frame_Widget::mouseMoveEvent(QMouseEvent* e)
{
    if(movable)
    move(e->globalX()-px,e->globalY()-py);
}

No_Frame_Widget::~No_Frame_Widget()
{
    delete ui;
}

