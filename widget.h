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
class Widget:public No_Frame_Widget//多场景窗口
{
    Q_OBJECT
public:
    Widget();
    void paintEvent(QPaintEvent*);
    QSqlDatabase& opendb();
    void loadinfo();
    void initialUser();
    QTimer* timer;
    QLabel* title;
    QSqlTableModel *model;
    superButton* portrait;
    QWidget* header;
    superButton* control;
    superButton* sites;
    QWidget* currentwidget;
    QWidget* targetwidget;

    //superButton* btn;
    pick* pick;//选择网站页面，已经写了
    login* login;//登录页面
    register_widget* reg;//注册页面
    QWidget* controlPanel;//控制面板页面
    QWidget* usrinfo;//用户个人信息页面
signals:
    void gotologin();
    void gotoregister();
    void gotoperson();
};

#endif // WIDGET_H
