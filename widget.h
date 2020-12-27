#ifndef WIDGET_H
#define WIDGET_H
#include<no_frame_widget.h>
#include<QWidget>
#include<pick.h>
#include<QSqlTableModel>
#include<QLabel>
#include<superbutton.h>
#include<login.h>
#include<register_widget.h>
#include<person_widget.h>
#include<control.h>
#include<purchase.h>
#include<QModelIndex>
#include<domain_detail.h>
#include<server.h>
#include<adminwidget.h>
#include<table_alldomain.h>
#include<addnewdomain.h>
#include<table_solddomain.h>
#include<table_ip.h>
#include<addnewip.h>
#include<table_allhost.h>
#include<addnewhost.h>
#include<table_dmresource.h>
class Widget:public No_Frame_Widget//多场景窗口
{
    Q_OBJECT
public:
    Widget();
    void paintEvent(QPaintEvent*);
    QSqlDatabase& opendb();
    void loadinfo();
    void initialUser();
    void controlload();
    void timecheck();
    QTimer* timer0;
    QTimer* timer1;
    QTimer* timer2;
    QTimer* timer3;
    QTimer* timer;

    int i=0;
    QStringList timestr;
    QLabel* title;
    QSqlTableModel *model;
    QStandardItemModel *control_model;
    superButton* portrait;
    QWidget* header;
    superButton* btn_control;
    superButton* btn_sites;
    QWidget* currentwidget;
    QWidget* targetwidget;
    int direction;
    void change_widget();
    //superButton* btn;
    pick* pick;//选择网站页面，done
    login* login;//登录页面,done
    register_widget* reg;//注册页面，done
    control* controlPanel;//控制面板页面
    person_widget* person;//用户个人信息页面，done
    purchase* purch;
    domain_detail* detail;
    adminwidget* admini;
    table_alldomain* alldomain;
    addnewdomain* newdomain;
    table_solddomain* solddomain;
    table_ip* allip;
    addnewip* newip;
    table_allhost* allhost;
    addnewhost* newhost;
    table_dmresource* dmsource;

signals:
    void gotologin();
    void gotoregister();
    void gotoperson();
    void gotopick();
    void gotocontrol();
    void gotopurchase();
    void gotodetail();
    void gotoadmin();
    void isadmin();
    void gotoalldomain();
    void gotoadddomain();
    void gotosolddomain();
    void gotoallip();
    void gotonewip();
    void gotoallhost();
    void gotonewhost();
    void gotosource();
};

#endif // WIDGET_H
