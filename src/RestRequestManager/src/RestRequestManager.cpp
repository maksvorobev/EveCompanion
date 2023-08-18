#include "../include/RestRequestManager.h"

RestRequestManager::RestRequestManager(QSharedPointer<QNetworkAccessManager> manager):
    manager(manager)
{

}

QVariant RestRequestManager::GET_request_without_token_block_CHARACTER(std::string character_id, std::string
        scope, std::string error_message) const
{
    /*
     * Post get request WITHOUT scope in url and character_id with access_token in url header
     * return anseve by get requsest
     * throw std::runtime_error(std::move(error_message))
     */
    QString url = QString("https://esi.evetech.net/latest/characters/") +
                           QString::fromStdString(std::move(character_id))+
                           QString("/") + QString::fromStdString(scope) + QString("/");
    qDebug() << url;
    QNetworkRequest request(QUrl{std::move(url)});
    QNetworkReply* reply = manager->get(request);
    QEventLoop loop;
    connect(manager.get(), &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        reply->deleteLater();
        return responseData;
    } else {
        reply->deleteLater();
        qDebug() << "Error: " << reply->errorString();
        throw std::runtime_error(std::move(error_message));
    }
}

QVariant RestRequestManager::GET_request_with_token_block_CHARACTER(std::string character_id, std::string scope, std::string error_message, std::string access_token) const
{
    /*
     * Post get request WITH scope in url and character_id with access_token in url header
     * return anseve by get requsest
     * throw std::runtime_error(std::move(error_message))
     */
    QString url = QString("https://esi.evetech.net/latest/characters/") +
                           QString::fromStdString(std::move(character_id))+
                           QString("/") + QString::fromStdString(scope) + QString("/");
    qDebug() << url;
    QNetworkRequest request(QUrl{std::move(url)});
    request.setRawHeader("Authorization", (QString("Bearer ") + QString::fromStdString(std::move(access_token))).toUtf8());
    QNetworkReply* reply = manager->get(request);
    QEventLoop loop;
    connect(manager.get(), &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        reply->deleteLater();
        return responseData;
    } else {
        reply->deleteLater();
        qDebug() << "Error: " << reply->errorString();
        throw std::runtime_error(std::move(error_message));
    }
}
