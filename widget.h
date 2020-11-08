#ifndef WIDGET_H
#define WIDGET_H
#include<no_frame_widget.h>
#include<QWidget>
#include<pick.h>
#include<QSqlTableModel>

class Widget:public No_Frame_Widget//多场景窗口
{
public:
    Widget();
    void paintEvent(QPaintEvent*);
    QSqlDatabase& opendb();
    void loadinfo();
    QSqlTableModel *model;
    pick* pick;
    QWidget* login;
    QWidget* regetser;
    QWidget* controlPanel;
};

#endif // WIDGET_H
