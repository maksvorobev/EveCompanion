#include "Aplication.h"



Aplication::Aplication(QString aplicationId, QString scopes)
    :
    manager_(std::shared_ptr<CastomNetworkAccessManager>(CastomNetworkAccessManager::GetInstance())),
    tcpServer_(std::make_shared<TcpServer>()),
    authEngine_(std::make_unique<Authorization_engine>(aplicationId, scopes, tcpServer_, manager_))
{

}


Authorization_engine* Aplication::authEngine() const
{
    return authEngine_.get();
}

