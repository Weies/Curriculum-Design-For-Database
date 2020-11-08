#include "line.h"
#include<QTimer>
Line::Line(QWidget* p)
{
    setParent(p);
}

void Line::focusInEvent(QFocusEvent *)
{
    QTimer::singleShot(0, this, &QLineEdit::selectAll);
}
