#pragma once


#include <QString>
#include <string>
#include <iostream>
#include <QByteArray>
#include <QDebug>
#include <sstream>
#include "../../../third-party-lib/jwt-cpp/jwt-cpp/jwt.h"
#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QDateTime>
#include <memory>
#include "CastomNetworkAccessManager.h"
#include <QMutex>


class Validating_JWT: public QObject
{
    Q_OBJECT
public:
    Validating_JWT(std::shared_ptr<CastomNetworkAccessManager>  manager);
    void start(QJsonDocument _JSON_payload);
private:
    QMutex mMutex;
    QJsonDocument JSON_payload;
    QString access_token;
    QByteArray doc_nn_ee_;
    void extract_nn_and_ee(const QByteArray& answer);
    void final_check(const QString& ee, const QString& nn);
    QUrl SSO_key_storage = QUrl("https://login.eveonline.com/oauth/jwks");
    std::shared_ptr<CastomNetworkAccessManager> manager_;
    QByteArray send_GET_request_to_SSO_key_storage();
    QString ConvertJwkToPem_V2(const QString& nn, const QString& ee);
    void veri_jwt_token(QString strToken, QString rsa_pub_key);

protected slots:
    void get_responce_from_SSO_key_storage(QNetworkReply *reply);

signals:
    void Sent_user_data_to_handler(const QJsonDocument& JSON_payload);
};


