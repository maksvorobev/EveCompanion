#include "../include/RestRequestManagerWithoutAuth.h"

Synch_GET_request_in_loop_whithout_auth::Synch_GET_request_in_loop_whithout_auth(
    QSharedPointer<QNetworkAccessManager> manager,
    int number_of_iterations,
    std::vector<std::string> character_id,
    std::string scope,
    std::string error_message
    ):
    manager(manager),
    number_of_iterations(number_of_iterations),
    character_id(std::move(character_id)),
    scope(std::move(scope)),
    error_message(std::move(error_message))
{

    my_connect();

}

void Synch_GET_request_in_loop_whithout_auth::onFinished(QNetworkReply* reply)
{
    disconnect(manager.get(), &QNetworkAccessManager::finished, this, &Synch_GET_request_in_loop_whithout_auth::onFinished);
        if (reply->error()) {
            qDebug() << reply->errorString();
            reply->deleteLater();
            throw std::runtime_error(error_message);
            //return;
        }
        QString answer = reply->readAll();

        data.push_back(std::move(answer.toStdString()));
        reply->deleteLater();
        ++i;
        my_connect();
}

void Synch_GET_request_in_loop_whithout_auth::my_connect()
{
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

    /*
    qDebug() << QUrl(QString("https://esi.evetech.net/latest/characters/") +
                     QString::fromStdString(character_id[i]) +
                     QString("/") +
                     QString::fromStdString(scope) +
                     QString("/")
                     );
    */
    connect(manager.get(), &QNetworkAccessManager::finished, this, &Synch_GET_request_in_loop_whithout_auth::onFinished);
    manager->get(req);
}
