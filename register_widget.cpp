#include "register_widget.h"
#include "ui_register_widget.h"

register_widget::register_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::register_widget)
{
    ui->setupUi(this);
}

register_widget::~register_widget()
{
    delete ui;
}
