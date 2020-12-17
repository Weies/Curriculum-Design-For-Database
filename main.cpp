#include "widget.h"
#include<QMessageBox>
#include <QApplication>
#include<QSqlError>

extern QSqlDatabase db;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("*{font:16pt;font-family:Microsoft Yahei Ui;color:dark;} QTableView::Item{border-bottom:1px solid rgb(100,100,100);} "
                    "QToolButton {background-color:rgba(180,180,180,20);border:0px;font:12pt;color:rgb(255,255,251)}"
                    "QLabel {alignment:center;} QCheckBox{font:12pt;}");
    a.setWindowIcon(QIcon(":/icon/emoji_01.png"));
    Widget w;
    w.show();
    return a.exec();
}
