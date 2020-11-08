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
    close=new QToolButton(this);//初始化关闭按钮
    close->resize(60,40);close->move(100,200);
    close->setIcon(QPixmap(":/icon/close.png"));

    min=new QToolButton(this);
    min->resize(60,40);min->move(200,200);
    min->setIcon(QPixmap(":/icon/min.png"));

    max=new QToolButton(this);
    max->resize(60,40);; max->move(300,200);
    max->setIcon(QPixmap(":/icon/max.png"));

    connect(close,SIGNAL(clicked()),SLOT(close()));
    connect(min,&QToolButton::clicked,this,&No_Frame_Widget::showMinimized);
    connect(max,&QToolButton::clicked,this,[=](){
        maxstate=!maxstate;
        if(maxstate)
        {
            w=width();h=height();xx=x();yy=y();
            this->move(0,0);this->resize(1920,1040);
        }
        else
        {
            resize(w,h);move(xx,yy);
        }
    });
}

void No_Frame_Widget::resizeEvent(QResizeEvent *)
{
    close->move(width()-60,0);
    max->move(width()-120,0);
    min->move(width()-180,0);
}

void No_Frame_Widget::mousePressEvent(QMouseEvent *event)
{
    px=event->x();
    py=event->y();
}

void No_Frame_Widget::mouseMoveEvent(QMouseEvent* e)
{
    move(e->globalX()-px,e->globalY()-py);
}

No_Frame_Widget::~No_Frame_Widget()
{
    delete ui;
}

