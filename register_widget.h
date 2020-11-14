#ifndef REGISTER_WIDGET_H
#define REGISTER_WIDGET_H

#include <QWidget>

namespace Ui {
class register_widget;
}

class register_widget : public QWidget
{
    Q_OBJECT

public:
    explicit register_widget(QWidget *parent = nullptr);
    ~register_widget();

private:
    Ui::register_widget *ui;
};

#endif // REGISTER_WIDGET_H
