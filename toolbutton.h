#ifndef TOOLBOTTON_H
#define TOOLBOTTON_H
#include<QToolButton>
#include<QPainter>
class toolButton : public QToolButton
{
public:
    toolButton(const QString& ss,const QString& p,QWidget* par)
    {
        s=ss;pix=QPixmap(p);setParent(par);resize(200,100);
        setToolButtonStyle(Qt::ToolButtonTextOnly);setText(s);
    }
    QString s;
    QPixmap pix;
    void setPixmap(const QPixmap& p){pix=p;};
    void paintEvent(QPaintEvent *)
    {
        QPainter p(this);
        p.drawPixmap(0,0,width(),height(),pix);
        setText(s);
        p.end();
    }
};

#endif // TOOLBOTTON_H
