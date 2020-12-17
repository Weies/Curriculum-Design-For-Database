#include "widget.h"
#include<QMessageBox>
#include <QApplication>
#include<QSqlError>

extern QSqlDatabase db;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("*{font:16pt;font-family:Microsoft Yahei Ui;color:dark;}"
                    "QTableView{selection-background-color:rgba(0,230,255,100);"
                    "selection-color:rgb(245,140,50);border:none;"
                    "background-color:transparent;border:0;alternate-background-color:rgba(255,255,255,100);"
                    "}"
                    ""
                    "QToolButton {background-color:rgba(180,180,180,20);border:0px;font:12pt;color:rgb(255,255,251)}"
                    "QLabel {alignment:center;} QCheckBox{font:12pt;}");
    a.setWindowIcon(QIcon(":/icon/emoji_01.png"));//selected{color:red;}
    Widget w;
    w.show();
    return a.exec();
}
