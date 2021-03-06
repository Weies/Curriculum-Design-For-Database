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
#include<QTime>
#include<QThread>
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>
#include<regex>
#include<dialog.h>
using namespace std;

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

    svr= new server();
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
    alldomain=new table_alldomain(this);alldomain->hide();
    alldomain->resize(1000,720);
    alldomain->move(0,80);
    newdomain=new addnewdomain(this);newdomain->hide();
    newdomain->resize(1000,720);
    newdomain->move(0,80);
    solddomain=new table_solddomain(this);solddomain->hide();
    solddomain->resize(1000,720);
    solddomain->move(0,80);
    allip=new table_ip(this);allip->hide();
    allip->resize(1000,720);
    allip->move(0,80);
    newip=new addnewip(this);newip->hide();
    newip->resize(1000,720);
    newip->move(0,80);
    allhost=new table_allhost(this);allhost->hide();
    allhost->resize(1000,720);
    allhost->move(0,80);
    newhost=new addnewhost(this);newhost->hide();
    newhost->resize(1000,720);
    newhost->move(0,80);
    dmsource=new table_dmresource(this);dmsource->hide();
    dmsource->resize(1000,720);
    dmsource->move(0,80);
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
    timecheck();

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
            QStandardItem* reco=control_model->item(controlPanel->view->currentIndex().row(),0);
            detail->update(reco);
            emit gotodetail();
        }
        else QMessageBox::critical(this,"critical","请先选中域名");
    });
    connect(btn_control,&superButton::Clicked,[=](){
        if(currentwidget!=controlPanel)emit gotocontrol();
    });
    connect(portrait,&superButton::Clicked,[=](){
        if(currentwidget!=person)emit gotoperson();
    });
    connect(btn_sites,&superButton::Clicked,[=](){
        if(currentwidget!=pick)emit gotopick();
    });

    /*连接goto,切换窗口*/
    connect(this,&Widget::gotopick,[=](){
        model->select();
        pick->admin_update();
        targetwidget=pick;
        change_widget();
    });
    connect(this,&Widget::gotocontrol,[=](){
        if(regestered)
        {
            controlload();
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
    connect(this,&Widget::gotoalldomain,[=](){
        alldomain->model->select();
        targetwidget=alldomain;
        change_widget();
    });
    connect(this,&Widget::gotoadddomain,[=](){
        targetwidget=newdomain;
        change_widget();
    });
    connect(this,&Widget::gotosolddomain,[=](){
        solddomain->model->select();
        targetwidget=solddomain;
        change_widget();
    });
    connect(this,&Widget::gotoallip,[=](){
        allip->model->select();
        targetwidget=allip;
        change_widget();
    });
    connect(this,&Widget::gotonewip,[=](){
        targetwidget=newip;
        change_widget();
    });
    connect(this,&Widget::gotosource,[=](){
        dmsource->model->select();
        targetwidget=dmsource;
        change_widget();
    });
    connect(this,&Widget::gotoallhost,[=](){
        allhost->model->select();
        targetwidget=allhost;
        change_widget();
    });
    connect(this,&Widget::gotonewhost,[=](){
        targetwidget=newhost;
        change_widget();
    });

    QLabel* l=new QLabel("|");
    l->setMaximumWidth(4);
    l->setStyleSheet("background-color:transparent;");
    lay->addWidget(btn_sites);
    lay->addWidget(l);
    lay->addWidget(btn_control);
    //connect(btn_sites,&superButton::Clicked,this,[=](){btn_sites->setMouseOutColor(QColor(100,100,255,150));});

    if(!regestered)
    portrait->setPixmap(QPixmap(":/icon/un_reg_user.png"));//未注册设置默认头像
    else
    {
        portrait->setPixmap(QPixmap(":/icon/un_reg_user.png"));
    }

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
    timer=new QTimer(this);
    model=new QSqlTableModel(this,db);
    pick->view->setModel(model);
    model->setTable("available_DN");
    if(!model->select())
    {
        QMessageBox::warning(this,"Failed","Failed to get the data:"+db.lastError().text());
    }
    //QTableView::Item{border:none;border-bottom:1px solid rgb(100,100,100);
//    pick->view->setStyleSheet("selection-background-color:rgba(0,230,255,100);"
//                              "selection-color:rgb(245,140,50);border:none;"
//                              "background-color:transparent;border:0;alternate-background-color:rgba(255,255,255,100);"
//                              "selected{color:red;}");
    pick->view->setSelectionBehavior(QAbstractItemView::SelectRows);
    pick->view->horizontalHeader()->setDisabled(true);
    connect(pick->searchbutton,&QToolButton::clicked,[=](){model->setFilter("dm_name like '%"+pick->input->text()+"%'");});
    connect(model,&QSqlTableModel::beforeUpdate,[=](){
        QSqlRecord reco=model->record(pick->view->currentIndex().row());
        QString dm_str,quality_str,price_str,area_str;
        dm_str=reco.value(0).toString();
        quality_str=reco.value(1).toString();
        price_str=reco.value(2).toString();
        area_str=reco.value(3).toString();
        QSqlQuery query(db);
        QString str=QString("update all_domain set quality='%1',price='%2',area='%3' where dm_name='%4' ").arg(quality_str).arg(price_str).arg(area_str).arg(dm_str);
        query.exec(str);
    });
    timer->start(5000);
    connect(timer,&QTimer::timeout,[=](){
        model->select();
    });
    pick->view->horizontalHeader()->resizeSection(0,400);
    pick->view->horizontalHeader()->resizeSection(1,160);
    pick->view->horizontalHeader()->resizeSection(2,180);
    pick->view->horizontalHeader()->resizeSection(3,190);
}

void Widget::controlload()
{
    int row=0;//行数
    control_model = new QStandardItemModel();
    control_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("域名")));
    control_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("性质")));
    control_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("购买日期")));
    control_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("到期时间")));
    control_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("费用")));
    //利用setModel()方法将数据模型与QTableView绑定
    controlPanel->view->setEditTriggers(QTableView::NoEditTriggers);
    controlPanel->view->setModel(control_model);
    controlPanel->view->setStyleSheet("background-color:transparent");
    controlPanel->view->setColumnWidth(0,310);controlPanel->view->setColumnWidth(1,170);controlPanel->view->setColumnWidth(2,170);controlPanel->view->setColumnWidth(3,170);controlPanel->view->setColumnWidth(4,150);

    QSqlQuery query(db);
    QString str=QString("select dm_name,quality,buytime,endtime,cost from sold_domain where account_id ='%1'").arg(ID);
    query.exec(str);
    QString dmname_str,quality_str,buytime_str,endtime_str,cost_str;
    while(query.next())
    {
        dmname_str=query.value(0).toString();
        quality_str=query.value(1).toString();
        buytime_str=query.value(2).toString();
        endtime_str=query.value(3).toString();
        cost_str=query.value(4).toString();
        control_model->setItem(row,0,new QStandardItem(dmname_str));
        control_model->setItem(row,1,new QStandardItem(quality_str));
        control_model->setItem(row,2,new QStandardItem(buytime_str));
        control_model->setItem(row,3,new QStandardItem(endtime_str));
        control_model->setItem(row++,4,new QStandardItem(cost_str));
    }
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
        targetwidget->move(0,800);timer0->start(10);
    }
    if(direction==1)
    {
        targetwidget->move(0,-720);timer1->start(10);
    }
    if(direction==2)
    {
        targetwidget->move(1000,90);timer2->start(10);
    }
    if(direction==3)
    {
        targetwidget->move(-1000,90);timer3->start(10);
    }
}

void Widget::timecheck()
{
    QSqlQuery query(db);
    QString str = QString("select dm_name,endtime from sold_domain");
    query.exec(str);
    while(query.next())
    {
        QString dm_str=query.value(0).toString();
        QString endtime=query.value(1).toString();
        QDateTime currenttime = QDateTime::currentDateTime(); //获取系统现在的时间
        QString time_str = currenttime.toString("yyyy-MM-dd"); //设置显示格式
        QStringList current=time_str.split('-');
        QStringList end=endtime.split('-');
        int currentyear=current[0].toInt();
        int currentmonth=current[1].toInt();
        int currentday=current[2].toInt();
        int endyear=end[0].toInt();
        int endmonth=end[1].toInt();
        int endday=end[2].toInt();
        if(currentyear>endyear||(currentyear==endyear&&currentmonth>endmonth)||(currentyear==endyear&&currentmonth==endmonth&&currentday>endday))
        {
            QSqlQuery query1(db);
            QString str1 = QString("update all_domain set is_sold='no' where dm_name='%1'").arg(dm_str);
            QString str2 = QString("select quality,price,area from all_domain where dm_name='%1'").arg(dm_str);
            query1.exec(str1);
            query1.exec(str2);
            QString quality,price,area;
            while(query1.next())
            {
                quality=query.value(0).toString();
                price=query.value(1).toString();
                area=query.value(2).toString();
            }
            QString str3 = QString("insert into available_dn values('%1','%2','%3','%4')").arg(dm_str).arg(quality).arg(price).arg(area);
            query1.exec(str3);
            QString str4 = QString("select ip from sold_domain where dm_name='%1'").arg(dm_str);
            query1.exec(str4);
            query1.next();
            QString ip_str=query.value(0).toString();
            QString str5 = QString("delete from sold_domain where dm_name='%1'").arg(dm_str);
            query1.exec(str5);
            QString str6 = QString("update ip_resource set is_used='no' where IP='%1'").arg(ip_str);
            query1.exec(str6);
        }
    }
}
