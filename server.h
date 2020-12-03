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
    bool returned=false;qint64 filesize;
    bool transport=false;
    server(){
        skt=new QTcpSocket(this);
        conToSvr();
        connect(skt,&QTcpSocket::readyRead,[=](){
            if(transport)
            {
                buffer+=skt->readAll();
                if(buffer.size()>=filesize)
                {
                    transport=false;emit newPkg();
                }
                return;
            }
            buffer.resize(0);
            filesize=QString(skt->readLine()).section('#',1,1).toInt();
            transport=true;
        });
        connect(skt,&QTcpSocket::connected,[=](){ready=true;});
        QTimer::singleShot(500,this,[=](){
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
            returned =false;
            QTimer::singleShot(10,this,[=](){
                skt->write("GETLOGS\n");
            });
            connect(this,&server::newPkg,[=](){
                evt.quit();
            });
            QTimer::singleShot(500,this,[=](){
                 if(!returned)
                 {
                     QMessageBox::warning(NULL,"Failed","Failed to get the log file.");
                     evt.quit();
                     returned=true;
                 }
            });
            evt.exec();
            returned=true;
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
            QTimer::singleShot(20,this,[=](){
                skt->write("UPLOAD\n"+createHead(info));
            });
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
                f.close();
            });
        }
        else QMessageBox::warning(NULL,"Failed","Failed to connect to the server.Please restart the application.");
    }

    void send(QByteArray s)
    {
        if(ready)
        QTimer::singleShot(30,this,[=](){
            skt->write(s);
        });
        else QMessageBox::warning(NULL,"Failed","Failed to connect to the server.Please restart the application.");
    }

    ~server()
    {
        skt->disconnectFromHost();
        delete skt;
    }

    QByteArray createHead(QFileInfo info)
    {
        return info.fileName().toUtf8()+"#"+QString::number(info.size()).toUtf8()+'\n';
    }
signals:
    void newPkg();
};

#endif // SERVER_H
