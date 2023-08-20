#pragma once
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QDebug>
#include <QEventLoop>
#include <vector>
#include <QString>
#include <QSharedPointer>

class Synch_GET_request_in_loop_whith_auth: public QObject
{
    Q_OBJECT
signals:
    void data_ready(std::vector<std::string> ans);
public:
    Synch_GET_request_in_loop_whith_auth(
        QSharedPointer<QNetworkAccessManager> manager,
        int number_of_iterations,
        std::vector<std::string> character_id,
        std::string scope,
        std::string error_message,
        std::vector<std::string> access_token
        );
    QSharedPointer<QNetworkAccessManager> manager;
    void my_connect();
public slots:
    void onFinished(QNetworkReply* reply);
private:
    int i = 0;
    std::vector<std::string> character_id;
    std::string scope;
    std::string error_message;
    int number_of_iterations = 0;
    std::vector<std::string> data;
    std::vector<std::string> access_token;
};

