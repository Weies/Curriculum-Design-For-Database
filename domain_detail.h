#ifndef DOMAIN_DETAIL_H
#define DOMAIN_DETAIL_H
#include<qsqlrecord.h>
#include <QWidget>
#include<superbutton.h>
namespace Ui {
class domain_detail;
}

class domain_detail : public QWidget
{
    Q_OBJECT

public:
    explicit domain_detail(QWidget *parent = nullptr);
    ~domain_detail();
    void update(QSqlRecord* reco);
    superButton* btn_back;

private:
    Ui::domain_detail *ui;
};

#endif // DOMAIN_DETAIL_H