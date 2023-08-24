#pragma once

#include <QObject>
#include "AuthorizationUrl.h"
#include "CastomNetworkAccessManager.h"
#include "TcpServer.h"
#include "Validating_JWT.h"
#include "AuthUserDataManager.h"

class Authorization_engine : public QObject
{
    Q_OBJECT

public:
    Authorization_engine(
        QString aplicationId,
        QString scopes,
        std::shared_ptr<TcpServer> tcpServer,
        std::shared_ptr<CastomNetworkAccessManager> manager
        );

    std::shared_ptr<CastomNetworkAccessManager> manager_;
    Q_INVOKABLE void startAuthProcess();
private:
    std::unique_ptr<AuthorizationUrl> authorizationUrl_;
    std::shared_ptr<TcpServer> tcpServer_;
    std::unique_ptr<AuthUserDataManager> authUserDataManager_;

    QString aplicationId_;
    QUrl callbackUrl_ = QString("http://localhost:8080/oauth-callback");
    QString scopes_;
    std::unique_ptr<Validating_JWT> validating_Jwt_;

    QUrl Direct_URL = QString("https://login.eveonline.com/v2/oauth/authorize/");

    void postRequestForToken(const QString& code) const ;
    void getReplyFromTcpServerAndSendPostRequestForToken() const;
    void startAuthFlow();
    void jwtValidation(QJsonDocument jsonPayload) const;
    void storeAuthUserDataIntoStorage() const;


public:


    AuthorizationUrl *authorizationUrl() const;


};


