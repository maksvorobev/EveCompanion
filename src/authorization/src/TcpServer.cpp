#include "../include/TcpServer.h"

TcpServer::TcpServer():
    /*QTcpServer(),*/
    socket_(new QTcpSocket)
{

}

void TcpServer::runTcpServer()
{
    if (listen(QHostAddress::Any, 8080)){
        qDebug() << "server is starting";
        return;
    }
    else {
        // TODO
        qCritical() << "server dosen't run";
        throw std::runtime_error("server dosen't run");
        return;
    }
}


void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    socket_->setSocketDescriptor(socketDescriptor);
    connect(socket_, &QTcpSocket::readyRead, this, &TcpServer::sockReady);
    connect(socket_, &QTcpSocket::disconnected, this, &TcpServer::sockDisc);

    return;
}

void TcpServer::sockReady()
{

    auto reply = QString::fromStdString(socket_->readAll().toStdString());
    /*
    QString queryString = QUrl(ans_string).query();
    QUrlQuery query(queryString);
    code = query.queryItemValue("code");
    */

    emit dataReady(reply);
    return;
}

void TcpServer::sockDisc()
{
    socket_->deleteLater();
    return;
}
