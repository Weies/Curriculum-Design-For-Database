#ifndef PICK_H
#define PICK_H
#include <QWidget>
#include<QSqlDatabase>
#include<QTableWidget>
#include<QListView>
#include<line.h>
#include<QToolButton>
QT_BEGIN_NAMESPACE
namespace Ui { class Form; }
QT_END_NAMESPACE

class pick : public QWidget
{
    Q_OBJECT
public:
    explicit pick(QWidget *parent = nullptr);
    Ui::Form* ui;
    QTableView* view;
    QToolButton* buy;
    QToolButton* searchbutton;
    Line* input;
signals:
};

#endif // PICK_H
