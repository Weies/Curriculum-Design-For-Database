#ifndef DOMAIN_DETAIL_H
#define DOMAIN_DETAIL_H
#include<qsqlrecord.h>
#include <QWidget>
#include<superbutton.h>
#include<qtableview.h>
#include<qsqltablemodel.h>
#include<qstandarditemmodel.h>
namespace Ui {
class domain_detail;
}

class domain_detail : public QWidget
{
    Q_OBJECT

public:
    explicit domain_detail(QWidget *parent = nullptr);
    ~domain_detail();
    void update(QStandardItem *reco);
    superButton* btn_back;
    superButton* addfile;
    QTableView* view;
    QSqlTableModel *model;
    superButton* refresh;
    QSqlTableModel *record_model;

private:
    Ui::domain_detail *ui;
};

#endif // DOMAIN_DETAIL_H
