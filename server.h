#ifndef SERVER_H
#define SERVER_H
#include<QString>
#include <QObject>
#include<QTcpSocket>
#include<QDebug>
class server:public QObject
{
    Q_OBJECT
public:
    QTcpSocket* skt;
    QString str;
    server(){
        skt=new QTcpSocket(this);
        connect(skt,&QTcpSocket::readyRead,[=](){
            str=skt->readAll();
        });
    };
    void conToSvr()
    {
        skt->connectToHost("101.132.173.39",5566,QIODevice::ReadWrite,QAbstractSocket::IPv4Protocol);
    }
};

#endif // SERVER_H
