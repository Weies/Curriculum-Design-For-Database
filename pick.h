#ifndef PICK_H
#define PICK_H
#include <QWidget>
#include<QSqlDatabase>
#include<QTableWidget>
#include<QListView>
#include<line.h>
#include<QSqlTableModel>
#include<QToolButton>
QT_BEGIN_NAMESPACE
namespace Ui { class Form; }
QT_END_NAMESPACE

class pick : public QWidget
{
    Q_OBJECT
public:
    explicit pick(QWidget *parent = nullptr);
    bool eventFilter(QObject*,QEvent* );
    Ui::Form* ui;
    QSqlTableModel *model;
    QTableView* view;
    QToolButton* buy;
    QToolButton* searchbutton;
    QToolButton* managebutton;
    Line* input;
    void admin_update();
signals:
};

#endif // PICK_H
