#ifndef PERSON_WIDGET_H
#define PERSON_WIDGET_H
#include<superbutton.h>
#include <QWidget>
#include<QComboBox>
namespace Ui {
class person_widget;
}

class person_widget : public QWidget
{
    Q_OBJECT

public:
    explicit person_widget(QWidget *parent = nullptr);
    ~person_widget();
    QComboBox* comboBox_type;
    bool eventFilter(QObject* ,QEvent*);
    superButton *btn_commit;
    superButton *btn_return;
private:
    Ui::person_widget *ui;
};

#endif // PERSON_WIDGET_H
