#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
Dialog::Dialog(QString S,QWidget* f)
{
    ui->label->setText(S);
    if(f)
    setParent(f);
    setModal(true);
}
