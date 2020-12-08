#ifndef ADDNEWIP_H
#define ADDNEWIP_H

#include <QWidget>
#include<superbutton.h>
namespace Ui {
class addnewip;
}

class addnewip : public QWidget
{
    Q_OBJECT

public:
    explicit addnewip(QWidget *parent = nullptr);
    ~addnewip();
    superButton* btn_commit;
    superButton* btn_back;

private:
    Ui::addnewip *ui;
};

#endif // ADDNEWIP_H
