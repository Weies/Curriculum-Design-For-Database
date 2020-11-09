#include "widget.h"
#include<QPainter>
#include<QPen>
#include<QTimer>
#include<QSqlError>
#include<QMessageBox>
#include<QDebug>
#include<QSqlRecord>
#include<QHeaderView>
#include<QFile>
#include<QCryptographicHash>
#include<QApplication>
#include<QLabel>
#include<QHBoxLayout>

QSqlDatabase db;
bool regestered=false;
QString username;
QString password;
QString ID;

QString readLine(QFile& f)
{
    QString s;
    s=f.readLine();
    s.resize(s.length()-2);
    return s;
}

Widget::Widget()
{
    resize(1000,800);
    pick=new class pick(this);
    pick->move(0,80);
    initialUser();

    title=new QLabel(this);title->setText(" EasyWeber 一键成为网络的主人");title->setStyleSheet("color:rgb(79,141,255)");
    title->move(0,5);
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){
        pick->move(pick->x()+20,80);
    });

    header=new QHeaderView(Qt::Horizontal,this);header->move(0,40);header->resize(width(),60);
    QHBoxLayout *lay=new QHBoxLayout(header);

    header->setStyleSheet("background-color:rgba(255,255,255,50)");

    control=new QToolButton;control->setText("控制台");
    sites=new QToolButton;sites->setText("网站列表");
    QLabel* l=new QLabel("|");
    lay->addWidget(sites);
    lay->addWidget(l);
    lay->addWidget(control);


    portrait=new QToolButton(this);
    portrait->setIconSize(QSize(60,60));
    portrait->move(940,40);
    if(!regestered)
    portrait->setIcon(QIcon(QPixmap(":/icon/un_reg_user.png")));//未注册设置默认头像
    else
    {
        //设置用户的头像
    }
    connect(pick->buy,&QToolButton::clicked,[=](){
        timer->start(1);if(pick->y()>1000)timer->stop();
    });

    // 如果点击点击了头像，注册了查看详细用户的详细信息
    //未注册弹出注册页面

    //点击了注册按钮
//    if(!regestered)
//    {
//        // 注册页面
//    }
//    else { /*网站详细信息,付费页面*/ };
}

void Widget::initialUser()
{
    QFile f(QApplication::applicationDirPath()+"/userinfo.dat");
    if(f.exists())
    {
        regestered=true;
        f.open(QIODevice::ReadOnly);
        ID=readLine(f);
        username=readLine(f);
        password=readLine(f);
        f.close();
    }
    else regestered=false;
}

void Widget::loadinfo()
{
    model=new QSqlTableModel(this,db);
    pick->view->setModel(model);
    model->setTable("available_DN");
    if(!model->select())
    {
        QMessageBox::warning(this,"Failed","Failed to get the data:"+db.lastError().text());
    }
    connect(pick->searchbutton,&QToolButton::clicked,[=](){model->setFilter("网站 like '%"+pick->input->text()+"%'");});
}

QSqlDatabase& Widget::opendb()
{
    static QSqlDatabase dbase=QSqlDatabase::addDatabase("QMYSQL");
    dbase.setPort(3366);
    dbase.setHostName("123.57.26.158");
    dbase.setPassword("123456");
    dbase.setUserName("root");
    dbase.setDatabaseName("mydb");
    return dbase;
}

void Widget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":/bkg/bkg.png"));
    QPen pen;pen.setColor(QColor(150,150,150));
    p.fillRect(0,0,width(),40,QColor(255,255,255,200));
    p.setPen(pen);
    p.drawRect(0,0,width()-1,height()-1);
    p.end();
}
