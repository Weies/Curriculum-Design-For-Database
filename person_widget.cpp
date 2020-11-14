#include "person_widget.h"
#include "ui_person_widget.h"

person_widget::person_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::person_widget)
{
    ui->setupUi(this);
}

person_widget::~person_widget()
{
    delete ui;
}
