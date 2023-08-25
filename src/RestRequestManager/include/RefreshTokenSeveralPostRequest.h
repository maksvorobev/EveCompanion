#pragma once

#include "CastomNetworkAccessManager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QDebug>
#include <QEventLoop>
#include <vector>
#include <QString>
#include <QSharedPointer>
#include <QUrlQuery>

class RefreshTokenSeveralPostRequest: public QObject
{
    Q_OBJECT
signals:
    void data_ready(std::vector<std::string> ans);
public:
    RefreshTokenSeveralPostRequest(
        std::shared_ptr<CastomNetworkAccessManager> manager,
        std::string scope,
        std::string error_message,
        std::string application_client_ID
        );
    std::shared_ptr<CastomNetworkAccessManager> manager_;
    void set_up(int number_of_iterations, std::vector<std::string> refresh_tokens);
    void my_connect();
public slots:
    void onFinished(QNetworkReply* reply);
private:
    int i = 0;
    std::vector<std::string> refresh_tokens;
    std::string scope;
    std::string error_message;
    int number_of_iterations = 0;
    std::vector<std::string> ans_data;
    std::vector<std::string> access_token;
    std::string application_client_ID;
};

