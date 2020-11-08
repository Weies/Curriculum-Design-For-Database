#include "widget.h"
#include<QMessageBox>
#include <QApplication>
#include<QSqlError>

extern QSqlDatabase db;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("*{font:16pt;font-family:Microsoft Yahei Ui;color:dark;} QTableView::Item{border-bottom:1px solid rgb(100,100,100);} "
                    "QToolButton {background-color:rgba(180,180,180,20);border:0px;}");
    //a.setStyleSheet("");
    Widget w;
    w.show();
    db=w.opendb();
    if(!db.open())
    {
        QMessageBox::warning(&w,"Failed","Failed to connect to server:"+db.lastError().text());
    }
    else
    {
        w.loadinfo();
    }
    return a.exec();
}