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
#include<QDebug>
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
    srand(time(NULL)-16056e6);
    resize(1000,800);
    pick=new class pick(this);
    pick->move(0,80);
    currentwidget=pick;
    //pick->hide();
    initialUser();
    login= new class login(this);login->hide();
    login->resize(1000,720);
    login->move(0,80);
    reg=new register_widget(this);reg->hide();
    reg->resize(1000,720);
    reg->move(0,80);
    person=new person_widget(this);person->hide();
    person->move(0,80);
    person->resize(1000,720);
//    btn=new superButton("hhs",QPixmap(":/icon/un_reg_user.png"),this);
//    btn->resize(60,60);
//    btn->move(400,400);

    title=new QLabel(this);title->setText(" /* EasyWeber 一键成为网络的主人*/");title->setStyleSheet("color:rgb(79,141,255)");
    title->move(0,5);
    timer=new QTimer(this);

    connect(timer,&QTimer::timeout,[=](){
        if(direction==0)
        {
            targetwidget->move(0,targetwidget->y()-20);
            currentwidget->move(0,currentwidget->y()-20);
            if(targetwidget->y()<=80)
            {
                timer->stop();
                currentwidget->hide();
                currentwidget=targetwidget;
            }
        }
        else if(direction==1)
        {
            targetwidget->move(0,targetwidget->y()+20);
            currentwidget->move(0,currentwidget->y()+20);
            if(targetwidget->y()>=80)
            {
                timer->stop();
                currentwidget->hide();
                currentwidget=targetwidget;
            }
        }
        else if(direction==2)
        {
            targetwidget->move(targetwidget->x()-20,80);
            currentwidget->move(currentwidget->x()-20,80);
            if(targetwidget->x()<=0)
            {
                timer->stop();
                currentwidget->hide();
                currentwidget=targetwidget;
            }
        }
        else if(direction==3)
        {
            targetwidget->move(targetwidget->x()+20,80);
            currentwidget->move(currentwidget->x()+20,80);
            if(targetwidget->x()>=0)
            {
                timer->stop();
                currentwidget->hide();
                currentwidget=targetwidget;
            }
        }
    });



    header=new QHeaderView(Qt::Horizontal,this);header->move(0,40);header->resize(width()-60,50);
    QHBoxLayout *lay=new QHBoxLayout(header);
    lay->setMargin(0);
    header->setStyleSheet("background-color:rgba(255,255,255,50)");

    portrait=new superButton(QPixmap(":/icon/un_reg_user.png"),this);
    portrait->setPixSize(50,50);
    portrait->move(950,40);portrait->resize(50,50);

    connect(portrait,&superButton::Clicked,[=](){
        emit gotoperson();
    });
    connect(this,&Widget::gotologin,[=](){
        targetwidget=login;
        change_widget();
    });
    connect(this,&Widget::gotoregister,[=](){
        targetwidget=reg;
        change_widget();
    });
    connect(this,&Widget::gotoperson,[=](){
        targetwidget=person;
        change_widget();
    });
    connect(this,&Widget::gotopick,[=](){
        targetwidget=pick;
        change_widget();
    });

    control=new superButton("控制台");
    sites=new superButton("网站列表");
    QLabel* l=new QLabel("|");
    l->setMaximumWidth(10);
    l->setStyleSheet("background-color:transparent;");
    lay->addWidget(control);
    lay->addWidget(l);
    lay->addWidget(sites);
    connect(sites,&superButton::Clicked,this,[=](){sites->setMouseOutColor(QColor(100,100,255,50));});


    if(!regestered)
    portrait->setPixmap(QPixmap(":/icon/un_reg_user.png"));//未注册设置默认头像
    else
    {
        //设置用户的头像
    }

    connect(pick->buy,&QToolButton::clicked,[=](){
        emit gotologin();qDebug()<<"did";
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

void Widget::change_widget()
{
    targetwidget->show();
    direction=rand()%4;
    if(direction==0)
    {
        targetwidget->move(0,800);
    }
    if(direction==1)
    {
        targetwidget->move(0,-720);
    }
    if(direction==2)
    {
        targetwidget->move(1000,80);
    }
    if(direction==3)
    {
        targetwidget->move(-1000,80);
    }
    timer->start(1);
}
