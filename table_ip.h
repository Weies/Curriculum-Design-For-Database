#ifndef TABLE_IP_H
#define TABLE_IP_H

#include <QWidget>

namespace Ui {
class table_ip;
}

class table_ip : public QWidget
{
    Q_OBJECT

public:
    explicit table_ip(QWidget *parent = nullptr);
    ~table_ip();

private:
    Ui::table_ip *ui;
};

#endif // TABLE_IP_H
