#ifndef ADDNEWDOMAIN_H
#define ADDNEWDOMAIN_H

#include <QWidget>
#include<superbutton.h>
namespace Ui {
class addnewdomain;
}

class addnewdomain : public QWidget
{
    Q_OBJECT

public:
    explicit addnewdomain(QWidget *parent = nullptr);
    ~addnewdomain();
    superButton* btn_commit;
    superButton* btn_back;
private:
    Ui::addnewdomain *ui;
};

#endif // ADDNEWDOMAIN_H
