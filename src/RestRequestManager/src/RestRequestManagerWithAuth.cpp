#include "../include/RestRequestManagerWithAuth.h"

Synch_GET_request_in_loop_whith_auth::Synch_GET_request_in_loop_whith_auth(
    QSharedPointer<QNetworkAccessManager> manager,
    int number_of_iterations,
    std::vector<std::string> character_id,
    std::string scope,
    std::string error_message,
    std::vector<std::string> access_token

    ):
    manager(manager),
    number_of_iterations(number_of_iterations),
    character_id(std::move(character_id)),
    scope(std::move(scope)),
    error_message(std::move(error_message)),
    access_token(std::move(access_token))
{

    my_connect();

}

void Synch_GET_request_in_loop_whith_auth::onFinished(QNetworkReply* reply)
{
    qDebug() << "xxxxxx";
    disconnect(manager.get(), &QNetworkAccessManager::finished, this, &Synch_GET_request_in_loop_whith_auth::onFinished);
        if (reply->error()) {
            qDebug() << reply->errorString();
            reply->deleteLater();
            throw std::runtime_error(error_message);
            //return;
        }
        qDebug() << "there is data";
        QString answer = reply->readAll();

        //qDebug() << answer;
        data.push_back(std::move(answer.toStdString()));
        reply->deleteLater();
        ++i;
        my_connect();
}

void Synch_GET_request_in_loop_whith_auth::my_connect()
{
        qDebug() << "wwwgerg";
    if(i == number_of_iterations){
            emit data_ready(std::move(data));
        return;
    }
    //++i;
    QNetworkRequest req;
    req.setUrl(QUrl(QString("https://esi.evetech.net/latest/characters/") +
                    QString::fromStdString(character_id[i]) +
                    QString("/") +
                    QString::fromStdString(scope) +
                    QString("/")
                    ));

    req.setRawHeader("Authorization", (QString("Bearer ") + QString::fromStdString(std::move(access_token[i]))).toUtf8());
    connect(manager.get(), &QNetworkAccessManager::finished, this, &Synch_GET_request_in_loop_whith_auth::onFinished);
    qDebug() << "yyyyyyyyyyy";
    manager->get(req);
}
