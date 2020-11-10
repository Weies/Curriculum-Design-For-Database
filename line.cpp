#include "line.h"
#include<QTimer>
#include<QMouseEvent>
#include<pick.h>
Line::Line(QWidget* p)
{
    setParent((p));
//    connect(this,&QLineEdit::editingFinished,[=](){
//        emit dynamic_cast<pick*>(p)->searchbutton->clicked();});
    this->installEventFilter(p);
}

void Line::focusInEvent(QFocusEvent *)
{
    QTimer::singleShot(0, this, &QLineEdit::selectAll);
}

//void Line::keyPressEvent(QKeyEvent *e)
//{
//    if(e->key()==Qt::Key_Enter)
//    {
//        emit dynamic_cast<pick*>(par)->searchbutton->click();
//    }
//    else if(1)
//    {
//        this->selectedText();
//    }
//    else
//    {
//        this->setText(this->text()+e->key());
//    }
//}
