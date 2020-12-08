#ifndef ADDNEWHOST_H
#define ADDNEWHOST_H

#include <QWidget>
#include<superbutton.h>
namespace Ui {
class addnewhost;
}

class addnewhost : public QWidget
{
    Q_OBJECT

public:
    explicit addnewhost(QWidget *parent = nullptr);
    ~addnewhost();
    superButton* btn_commit;
    superButton* btn_back;

private:
    Ui::addnewhost *ui;
};

#endif // ADDNEWHOST_H
