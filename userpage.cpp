#include "userpage.h"
#include "ui_userpage.h"

userpage::userpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userpage)
{
    ui->setupUi(this);
}

userpage::~userpage()
{
    delete ui;
}
