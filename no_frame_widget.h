#ifndef NO_FRAME_WIDGET_H
#define NO_FRAME_WIDGET_H

#include <QWidget>
#include <QToolButton>
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
    QToolButton* close;//关闭
    QToolButton* min;//最小化
    QToolButton* max;//最大化

private:
    int w;int h;//最大化之前的宽度和高度
    int xx;int yy;

    int px;int py;
    Ui::Widget *ui;
};
#endif // WIDGET_H
