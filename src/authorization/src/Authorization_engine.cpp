#include "../include/Authorization_engine.h"

#include "../include/AuthorizationUrl.h"
#include <QNetworkReply>

enum class RESPONSE{

};


Authorization_engine::Authorization_engine(
    QString aplicationId,
    QString scopes,
    std::shared_ptr<TcpServer> tcpServer,
    std::shared_ptr<CastomNetworkAccessManager> manager
    )
    :
    aplicationId_(aplicationId),
    scopes_(scopes),
    tcpServer_(tcpServer),
    manager_(manager)
    //manager(QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager(this)))
    //user_data_handler(new User_data_handler(manager, this))

{
    //manager_ = std::shared_ptr<CastomNetworkAccessManager>(CastomNetworkAccessManager::GetInstance());
    authorizationUrl_ = std::move(std::make_unique<AuthorizationUrl>(callbackUrl_, aplicationId_, scopes_));
    //tcpServer_ = std::move(std::make_unique<TcpServer>());
    validating_Jwt_ = std::make_shared<Validating_JWT>(manager_);
    authUserDataManager_ = std::make_shared<AuthUserDataManager>();

    tcpServer_->runTcpServer();
    //startAuthProcess();
}

void Authorization_engine::startAuthProcess()
{

    qDebug() << "startAuthProcess";
    authorizationUrl_->MakeAuthorizationUrl();
    qDebug() << "It's your auth url :\n" << authorizationUrl_->authorizationUrl();



    startAuthFlow();
}

std::shared_ptr<AuthUserDataManager> Authorization_engine::authUserDataManager() const
{
    return authUserDataManager_;
}

std::shared_ptr<Validating_JWT> Authorization_engine::validating_Jwt() const
{
    return validating_Jwt_;
}



void Authorization_engine::postRequestForToken(const QString& code) const
{
    QUrl postUrl = QString("https://login.eveonline.com/v2/oauth/token");
    QNetworkRequest request(postUrl);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setRawHeader("Host", "login.eveonline.com");

    QByteArray postData; // payload
    postData.append("grant_type=authorization_code");
    postData.append("&code=" + code.toUtf8());
    postData.append("&client_id=" + aplicationId_.toUtf8());
    postData.append("&code_verifier=" + QByteArray(authorizationUrl_->codeVerifier().constData()));

    QObject *context = new QObject;
    connect(manager_.get(), &QNetworkAccessManager::finished, context, [this, context](QNetworkReply *reply){
        delete context;
        if (reply->error()) {
            qCritical() << reply->readAll();
            reply->deleteLater();
            return;
        }

        auto answer = reply->readAll();

        qDebug()  << "It's your jwt payload :\n" << answer;
        QJsonDocument doc = QJsonDocument::fromJson(std::move(answer));



        QObject *context = new QObject;
        connect(validating_Jwt_.get(), &Validating_JWT::Sent_user_data_to_handler, context,  [this, context, &doc](const QJsonDocument& JSON_payload){
            delete context;
            storeAuthUserDataIntoStorage(doc);

        });

        jwtValidation(doc);



        reply->deleteLater();

    });
    manager_->post(request, postData);

    return;
}

void Authorization_engine::getReplyFromTcpServerAndSendPostRequestForToken() const
{
    QObject *context = new QObject;
    connect(tcpServer_.get(), &TcpServer::dataReady, context, [this, context](QString code){
        delete context;
        QString queryString = QUrl(code).query();
        QUrlQuery query(queryString);
        auto finalCode = query.queryItemValue("code");
        qDebug() << "code = " << finalCode;

        postRequestForToken(finalCode);
    });

}

void Authorization_engine::startAuthFlow()
{
    /*
     * This function call many others functions due to, that there exists
     * synchronous functions calls
     */

    getReplyFromTcpServerAndSendPostRequestForToken();
}

void Authorization_engine::jwtValidation(QJsonDocument jsonPayload) const
{
    validating_Jwt_->start(std::move(jsonPayload));
}

void Authorization_engine::storeAuthUserDataIntoStorage(const QJsonDocument& JSON_payload) const
{
    authUserDataManager_->storeJsonPayload(JSON_payload);
}

AuthorizationUrl *Authorization_engine::authorizationUrl() const
{
    return authorizationUrl_.get();
}

































