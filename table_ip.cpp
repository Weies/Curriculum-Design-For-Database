#include "table_ip.h"
#include "ui_table_ip.h"

table_ip::table_ip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::table_ip)
{
    ui->setupUi(this);
}

table_ip::~table_ip()
{
    delete ui;
}
