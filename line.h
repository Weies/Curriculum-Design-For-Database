#ifndef LINE_H
#define LINE_H
#include<QLineEdit>
class pick;
class Line:public QLineEdit
{
    Q_OBJECT
public:
    Line(QWidget* p);
    void focusInEvent(QFocusEvent *) override;
    //void keyPressEvent(QKeyEvent* ) override;
};

#endif // LINE_H
