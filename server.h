#ifndef SERVER_H
#define SERVER_H
#include<QString>
#include <QObject>
#include<QTcpSocket>
#include<QDebug>
#include<QFile>
#include<QTimer>
#include<QFileInfo>
#include<QEventLoop>
#include<QMessageBox>
class server:public QObject
{
    Q_OBJECT
public:
    QTcpSocket* skt;bool ready=false;
    QByteArray buffer;QEventLoop evt;

    server(){
        skt=new QTcpSocket(this);
        conToSvr();
        connect(skt,&QTcpSocket::readyRead,[=](){buffer+=skt->readAll();emit newPkg();});
        connect(skt,&QTcpSocket::connected,[=](){ready=true;});
        QTimer::singleShot(100,this,[=](){
            evt.quit();
        });
        evt.exec();
    };

    void conToSvr(qint16 port=5566)
    {
        skt->connectToHost("101.132.173.39",port,QIODevice::ReadWrite,QAbstractSocket::IPv4Protocol);
    }

    QString getLogs()
    {
        if(ready)
        {
            skt->write("GETLOGS\n");
            connect(this,&server::newPkg,[=](){
                evt.quit();
            });
            evt.exec();
            return buffer;
        }
        QMessageBox::warning(NULL,"Failed","Failed to connect to the server.Please restart the application.");
        return QString();
    }

    void update()
    {
        if(ready)
        skt->write("UPDATE\n");
        else QMessageBox::warning(NULL,"Failed","Failed to connect to the server.Please restart the application.");
    }

    void upload(QString ifo)
    {
        if(ready)
        {
            QFileInfo info(ifo);
            skt->write("UPLOAD\n"+info.fileName().toUtf8()+"#"+QString::number(info.size()).toLocal8Bit()+'\n');
            QTimer::singleShot(50,this,[=](){
                QFile f(info.filePath());
                f.open(QIODevice::ReadOnly);
                QByteArray ar;
                int len=1;
                while(len)
                {
                    ar=f.read(1024*16);
                    len=skt->write(ar);
                }
            });
        }
        else QMessageBox::warning(NULL,"Failed","Failed to connect to the server.Please restart the application.");
    }

    void send(QByteArray s)
    {
        if(ready)
        skt->write(s);
        else QMessageBox::warning(NULL,"Failed","Failed to connect to the server.Please restart the application.");
    }

    ~server()
    {
        skt->disconnectFromHost();
        delete skt;
    }
signals:
    void newPkg();
};

#endif // SERVER_H
