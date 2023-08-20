#ifndef AUTHORIZATION_ENGINE_H
#define AUTHORIZATION_ENGINE_H

#include <QObject>
#include <QUrl>
#include <string>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QUrlQuery>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QUuid>
#include "Validating_JWT.h"
#include <QSharedPointer>
#include <vector>
#include "Auth_user_data.h"
#include "User_data_handler.h"
#include <QScopedPointer>
#include "../../RefreshingTokens/include/Refresh_Manager.h"

class Validating_JWT;
class User_data_handler;
class Refresh_Manager;

class Authorization_engine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString p_Direct_URL READ p_Direct_URL CONSTANT)

public:
    Authorization_engine(
        QString Client_ID,
        QString requirements,
        QObject *parent = nullptr
        );

    QSharedPointer<QNetworkAccessManager> manager;
private:
    //QScopedPointer<Refresh_Manager> refresh_Manager;
    QScopedPointer<User_data_handler> user_data_handler;
    QScopedPointer<Validating_JWT> validating_JWT;
    QString Client_ID;
    QUrl Callback_URL = QString("http://localhost:8080/oauth-callback");
    QString requirements;
    QUrl POST_URL = QString("https://login.eveonline.com/v2/oauth/token");
    QByteArray Code_verifier;
    QUrl Direct_URL = QString("https://login.eveonline.com/v2/oauth/authorize/");
    QString percent_encoding(const QString& param);
    QString codeChallenge;
    QString authorization_code;

    QUrl make_authorization_url();
    QNetworkReply* GET_request(const QUrl& url);
    void POST_request_for_token(const QUrl& url);
    QByteArray generateCodeVerifier();
    QByteArray createCodeChallenge(const QByteArray& Code_verifier);

public:
    QString p_Direct_URL();
    //User_data_handler* get_User_data_handler();
    QSharedPointer<MainPageModel> getModel_ptr() const;
signals:
    void laod_main_page_in_qml();

public slots:
    void get_code(QString code);
    void onSent_user_data_to_handler(const QJsonDocument& JSON_payload);
protected slots:
    void get_answer(QNetworkReply *reply);
    void get_POST_RESPONSE_for_token(QNetworkReply *reply);
};

#endif // AUTHORIZATION_ENGINE_H
