#pragma once

#include <QObject>
#include <QTcpServer>
#include <QHostAddress>
#include <stdexcept>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>
#include <QJsonDocument>
#include <QUrl>
#include <QUrlQuery>
#include <memory>

class TcpServer: public QTcpServer
{
    Q_OBJECT
public:
    TcpServer();
    void runTcpServer();


private:
    QTcpSocket* socket_;
    void incomingConnection(qintptr socketDescriptor) override;

signals:
    void dataReady(QString code);

public slots:
    void sockReady();
    void sockDisc();
};

