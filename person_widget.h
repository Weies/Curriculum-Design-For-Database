#ifndef PERSON_WIDGET_H
#define PERSON_WIDGET_H

#include <QWidget>

namespace Ui {
class person_widget;
}

class person_widget : public QWidget
{
    Q_OBJECT

public:
    explicit person_widget(QWidget *parent = nullptr);
    ~person_widget();

private:
    Ui::person_widget *ui;
};

#endif // PERSON_WIDGET_H
