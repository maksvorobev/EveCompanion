#pragma once

#include <QObject>
#include <QVariant>
#include <QSharedPointer>
#include <QNetworkAccessManager>
#include <string>
#include <QEventLoop>
#include <QNetworkReply>

class RestRequestManager: public QObject
{
    Q_OBJECT
public:

    RestRequestManager(QSharedPointer<QNetworkAccessManager> manager);
    QVariant GET_request_without_token_block_CHARACTER(
        std::string character_id,
        std::string scope,
        std::string error_message) const;
    QVariant GET_request_with_token_block_CHARACTER(
        std::string character_id,
        std::string scope,
        std::string error_message,
        std::string access_token) const;
private:
    QSharedPointer<QNetworkAccessManager> manager;
};

