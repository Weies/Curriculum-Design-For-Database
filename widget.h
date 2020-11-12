#ifndef WIDGET_H
#define WIDGET_H
#include<no_frame_widget.h>
#include<QWidget>
#include<pick.h>
#include<QSqlTableModel>
#include<QLabel>
#include<superbutton.h>
class Widget:public No_Frame_Widget//多场景窗口
{
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

    //superButton* btn;
    pick* pick;//选择网站页面，已经写了
    QWidget* login;//登录页面
    QWidget* reg;//注册页面
    QWidget* controlPanel;//控制面板页面
    QWidget* usrinfo;//用户个人信息页面

};

#endif // WIDGET_H
