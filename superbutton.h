#ifndef TOOLBOTTON_H
#define TOOLBOTTON_H
#include<QToolButton>
#include<QPainter>
#include<QLabel>
#include<QPainter>
#include<QTimer>
#include<QDebug>
#include<QEventLoop>
#include<QEvent>
enum BtnType{
    TextOnly,PixOnly,Both
};

class superButton : public QToolButton
{
    Q_OBJECT
private:
    QString s;QPixmap pix;QLabel label;
    BtnType type;
    QColor bkgdColor=QColor(200,200,200,0);
    QColor mouseOutColor=QColor(200,200,200,0);
    QColor mouseInColor=QColor(100,100,255,50);
    int frame=5;
    int px=0;int py=0;
    bool pixed=false;
    int radius=0;
signals:void Clicked();
public:
    void setPixSize(int x,int y){px=x;py=y;pixed=true;};
    void setRadius(int newradius)
    {
        radius=newradius;
    }
    superButton(const QString& str,QWidget* p=nullptr)
    {
        setStyleSheet("background-color:transparent");
        label.setParent(this);setParent(p);
        s=str;type=TextOnly;label.setText(s);
        label.setAttribute(Qt::WA_TransparentForMouseEvents);
        label.setAlignment(Qt::AlignCenter);
        setAttribute(Qt::WA_TransparentForMouseEvents,false);
        setMinimumSize(label.text().length()*36,50);
    }

    superButton(const QString& str,const QPixmap& px,QWidget* p=nullptr)
    {
        setStyleSheet("background-color:transparent");
        label.setParent(this);setParent(p);
        s=str;pix=px;type=Both;label.setText(s);
        label.setAttribute(Qt::WA_TransparentForMouseEvents);
        label.setAlignment(Qt::AlignCenter);
        this->setAttribute(Qt::WA_TransparentForMouseEvents,false);
    }

    superButton(const QPixmap& px,QWidget* p=Q_NULLPTR)
    {
        setStyleSheet("background-color:transparent");
        label.setParent(this);setParent(p);
        pix=px;type=PixOnly;label.setText(s);
        label.setAttribute(Qt::WA_TransparentForMouseEvents);
        label.setAlignment(Qt::AlignCenter);
        setAttribute(Qt::WA_TransparentForMouseEvents,false);
    };

    void resizeEvent(QResizeEvent* )
    {
        if(pixed==false&&type!=TextOnly)
        {
            setPixSize(width()*0.7,height()*0.7);
            pixed=true;
            pix.scaled(px,py,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        }

        label.move(0,0);label.resize(width(),height());
    }

    void setMouseOutColor(QColor c){mouseOutColor=c;bkgdColor=c;repaint();};
    void setBackColor(QColor c){bkgdColor=c;};
    void setMouseInColor(QColor c){mouseInColor=c;};
    void setPixmap(const QPixmap& p){pix=p;};

    void paintEvent(QPaintEvent *)
    {
        QPainter p(this);
        p.fillRect(0,0,width(),height(),bkgdColor);
        if(type!=TextOnly)
        {
            p.drawPixmap((width()-px)/2,(height()-py)/2,px,py,pix);
        }
        p.end();
    }

    void enterEvent(QEvent *)
    {
        setBackColor(mouseInColor);
    }

    void leaveEvent(QEvent *)
    {
        setBackColor(mouseOutColor);
    }

    void mousePressEvent(QMouseEvent *)
    {
        QEventLoop el;
        for(int i=0;i<frame;i++)
        {
            move(x()+1,y()+1);
            QTimer::singleShot(6,this,[=,&el](){el.quit();});
            el.exec();
        }

    }

    void mouseMoveEvent(QMouseEvent*){};
    void mouseReleaseEvent(QMouseEvent *)
    {
        QEventLoop el;
        for(int i=0;i<frame;i++)
        {
            move(x()-1,y()-1);
            QTimer::singleShot(6,this,[=,&el](){el.quit();});
            el.exec();
        }
        emit Clicked();
    }
};

#endif // TOOLBOTTON_H
