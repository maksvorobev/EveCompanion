#include "Aplication.h"



Aplication::Aplication(QString aplicationId, QString scopes)
    :
    manager_(std::shared_ptr<CastomNetworkAccessManager>(CastomNetworkAccessManager::GetInstance())),
    tcpServer_(std::make_shared<TcpServer>()),
    authEngine_(std::make_unique<Authorization_engine>(aplicationId, scopes, tcpServer_, manager_)),
    refreshManager_(std::move(std::make_unique<Refresh_Manager>(manager_, authEngine_->authUserDataManager(),
                                                                  authEngine_->validating_Jwt(), scopes.toStdString(), "refresh token error", aplicationId.toStdString())))
{

}


Authorization_engine* Aplication::authEngine() const
{
    return authEngine_.get();
}

