#ifndef NO_FRAME_WIDGET_H
#define NO_FRAME_WIDGET_H

#include <QWidget>
#include <superbutton.h>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class No_Frame_Widget : public QWidget
{
    Q_OBJECT

public:
    No_Frame_Widget(QWidget *parent = nullptr);
    ~No_Frame_Widget();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent*);
    superButton* close;//关闭
    superButton* min;//最小化
    superButton* max;//最大化
    bool movable=true;
private:
    int w=0;int h=0;//最大化之前的宽度和高度
    int xx=0;int yy=0;
    int px=0;int py=0;
    Ui::Widget *ui;
};
#endif // WIDGET_H
