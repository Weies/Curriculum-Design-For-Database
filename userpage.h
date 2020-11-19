#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWidget>

namespace Ui {
class userpage;
}

class userpage : public QWidget
{
    Q_OBJECT

public:
    explicit userpage(QWidget *parent = nullptr);
    ~userpage();

private:
    Ui::userpage *ui;
};

#endif // USERPAGE_H
