#ifndef LINE_H
#define LINE_H
#include<QLineEdit>

class Line:public QLineEdit
{
public:
    Line(QWidget* p);
    void focusInEvent(QFocusEvent *) override;
};

#endif // LINE_H
