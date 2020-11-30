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
#include<QMessageBox>
#include<qsqlquery.h>
QSqlDatabase db;
bool is_admin=false;
bool regestered=false;
QString username;
QString password;
QString ID;
server* svr;

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
    db=opendb();
    if(!db.open())QMessageBox::warning(this,"Failed","Failed to connect to server:"+db.lastError().text());
    pick=new class pick(this);
    pick->move(0,80);
    currentwidget=pick;
    login= new class login(this);login->hide();
    login->resize(1000,720);
    login->move(0,80);
    reg=new register_widget(this);reg->hide();
    reg->resize(1000,720);
    reg->move(0,80);
    person=new person_widget(this);person->hide();
    person->move(0,80);
    person->resize(1000,720);
    controlPanel=new control(this);controlPanel->hide();
    controlPanel->resize(1000,720);
    controlPanel->move(0,80);
    purch=new purchase(this);purch->hide();
    purch->resize(1000,720);
    purch->move(0,80);
    detail=new domain_detail(this);detail->hide();
    detail->resize(1000,720);
    detail->move(0,80);
    admini=new adminwidget(this);admini->hide();
    admini->resize(1000,720);
    admini->move(0,80);

    connect(this,&Widget::isadmin,[=](){
        if(regestered)
        {
            QString str = QString("select is_administrator from user where account_id='%1'").arg(ID);
            QSqlQuery query(db);
            query.exec(str);
            QString admin_str;
            while(query.next())admin_str=query.value(0).toString();
            if(admin_str=="yes")is_admin=true;
            else is_admin=false;
        }
        pick->admin_update();
    });
    login= new class login(this);login->hide();
    login->resize(1000,720);
    login->move(0,80);

    initialUser();
    loadinfo();


    title=new QLabel(this);title->setText(" /* EasyWeber 一键成为网络的主人*/");title->setStyleSheet("color:rgb(79,141,255)");
    title->move(0,5);
    timer0=new QTimer(this);
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    timer3=new QTimer(this);

    connect(timer0,&QTimer::timeout,[=](){
        targetwidget->move(0,targetwidget->y()-20);
        currentwidget->move(0,currentwidget->y()-20);
        if(targetwidget->y()<=90)
        {
            timer0->stop();
            currentwidget->hide();
            currentwidget=targetwidget;
            currentwidget->move(0,80);
        }
    });
    connect(timer1,&QTimer::timeout,[=](){
        targetwidget->move(0,targetwidget->y()+20);
        currentwidget->move(0,currentwidget->y()+20);
        if(targetwidget->y()>=90)
        {
            timer1->stop();
            currentwidget->hide();
            currentwidget=targetwidget;
            currentwidget->move(0,80);
        }
    });
    connect(timer2,&QTimer::timeout,[=](){
        targetwidget->move(targetwidget->x()-20,80);
        currentwidget->move(currentwidget->x()-20,80);
        if(targetwidget->x()<=0)
        {
            timer2->stop();
            currentwidget->hide();
            currentwidget=targetwidget;
            currentwidget->move(0,80);
        }
    });
    connect(timer3,&QTimer::timeout,[=](){
        targetwidget->move(targetwidget->x()+20,80);
        currentwidget->move(currentwidget->x()+20,80);
        if(targetwidget->x()>=0)
        {
            timer3->stop();
            currentwidget->hide();
            currentwidget=targetwidget;
            currentwidget->move(0,80);
        }
    });

    btn_control=new superButton("控制台");btn_control->setMinimumSize(470,50);
    btn_sites=new superButton("网站列表");btn_sites->setMinimumSize(470,50);

    header=new QHeaderView(Qt::Horizontal,this);header->move(0,40);header->resize(width()-50,50);
    QHBoxLayout *lay=new QHBoxLayout(header);
    lay->setMargin(0);
    header->setStyleSheet("background-color:rgba(255,255,255,50)");

    portrait=new superButton(QPixmap(":/icon/un_reg_user.png"),this);
    portrait->setPixSize(50,50);
    portrait->move(950,40);portrait->resize(50,50);



    /*连接按钮*/
    connect(pick->buy,&QToolButton::clicked,[=](){
        if(regestered)
        {
            if(pick->view->currentIndex().row()>=0)
            {
                QSqlRecord reco=model->record(pick->view->currentIndex().row());
                purch->update(&reco);
                emit gotopurchase();
            }
            else QMessageBox::critical(this,"critical","请先选中域名");
        }
        else emit gotologin();
    });
    connect(controlPanel->btn_next,&superButton::Clicked,[=](){
        if(controlPanel->view->currentIndex().row()>=0)
        {
            QSqlRecord reco=model->record(controlPanel->view->currentIndex().row());
            detail->update(&reco);
            emit gotodetail();
        }
        else QMessageBox::critical(this,"critical","请先选中域名");
    });
    connect(btn_control,&superButton::Clicked,[=](){
        if(currentwidget!=controlPanel)emit gotocontrol();
        svr->conToSvr();
    });
    connect(portrait,&superButton::Clicked,[=](){
        if(currentwidget!=person)emit gotoperson();
    });
    connect(btn_sites,&superButton::Clicked,[=](){
        if(currentwidget!=pick)emit gotopick();
    });

    /*连接goto,切换窗口*/
    connect(this,&Widget::gotopick,[=](){
        targetwidget=pick;
        change_widget();
    });
    connect(this,&Widget::gotocontrol,[=](){
        if(regestered)
        {
            controlPanel->update();
            targetwidget=controlPanel;
            change_widget();
        }
        else QMessageBox::critical(this,"critical","请先登录");
    });
    connect(this,&Widget::gotopurchase,[=](){
        targetwidget=purch;
        change_widget();
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
        if(regestered)
        {
            targetwidget=person;
            change_widget();
        }
        else if(currentwidget!=login)
        {
            targetwidget=login;
            change_widget();
        }
    });
    connect(this,&Widget::gotodetail,[=](){
        targetwidget=detail;
        change_widget();
    });
    connect(this,&Widget::gotoadmin,[=](){
        targetwidget=admini;
        change_widget();
    });

    QLabel* l=new QLabel("|");
    l->setMaximumWidth(4);
    l->setStyleSheet("background-color:transparent;");
    lay->addWidget(btn_sites);
    lay->addWidget(l);
    lay->addWidget(btn_control);
    connect(btn_sites,&superButton::Clicked,this,[=](){btn_sites->setMouseOutColor(QColor(100,100,255,150));});

    if(!regestered)
    portrait->setPixmap(QPixmap(":/icon/un_reg_user.png"));//未注册设置默认头像
    else
    {
        portrait->setPixmap(QPixmap(":/icon/un_reg_user.png"));
    }

    svr=new server;

}

void Widget::initialUser()//读文件，自动为用户登录
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
        login->reLoadUser();
        emit isadmin();
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
    connect(pick->searchbutton,&QToolButton::clicked,[=](){model->setFilter("dm_name like '%"+pick->input->text()+"%'");});
}

QSqlDatabase& Widget::opendb()
{
    static QSqlDatabase dbase=QSqlDatabase::addDatabase("QMYSQL");
    dbase.setPort(3366);
    dbase.setHostName("101.132.173.39");
    dbase.setPassword("123456");
    dbase.setUserName("teleconnect");
    dbase.setDatabaseName("EasyWeberDB");
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
        targetwidget->move(0,800);timer0->start(1);
    }
    if(direction==1)
    {
        targetwidget->move(0,-720);timer1->start(1);
    }
    if(direction==2)
    {
        targetwidget->move(1000,90);timer2->start(1);
    }
    if(direction==3)
    {
        targetwidget->move(-1000,90);timer3->start(1);
    }
}
