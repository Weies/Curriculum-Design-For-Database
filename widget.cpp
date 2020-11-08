#include "widget.h"
#include<QPainter>
#include<QPen>

#include<QTimer>
#include<QSqlError>
#include<QMessageBox>
#include<QDebug>
#include<QSqlRecord>
#include<QHeaderView>
QSqlDatabase db;
Widget::Widget()
{
    resize(1000,800);
    pick=new class pick(this);
    pick->move(0,40);
}

void Widget::loadinfo()
{
    model=new QSqlTableModel(this,db);
    pick->view->setModel(model);
    model->setTable("available_DN");
    if(!model->select())
    {
        QMessageBox::warning(this,"Failed","Failed to connect to server:"+db.lastError().text());
    }
    connect(pick->searchbutton,&QToolButton::clicked,[=](){model->setFilter("网站 like '%"+pick->input->text()+"%'");});
}

QSqlDatabase& Widget::opendb()
{
    static QSqlDatabase dbase=QSqlDatabase::addDatabase("QMYSQL");
    dbase.setPort(3366);
    dbase.setHostName("123.57.26.158");
    dbase.setPassword("123456");
    dbase.setUserName("root");
    dbase.setDatabaseName("mydb");
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
