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
class Widget:public No_Frame_Widget//多场景窗口
{
    Q_OBJECT
public:
    Widget();
    void paintEvent(QPaintEvent*);
    QSqlDatabase& opendb();
    void loadinfo();
    void initialUser();
    QTimer* timer0;
    QTimer* timer1;
    QTimer* timer2;
    QTimer* timer3;

    QLabel* title;
    QSqlTableModel *model;
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
signals:
    void gotologin();
    void gotoregister();
    void gotoperson();
    void gotopick();
    void gotocontrol();
    void gotopurchase();
    void gotodetail();
};

#endif // WIDGET_H
