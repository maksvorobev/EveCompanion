#include "../include/RefreshTokenSeveralPostRequest.h"

RefreshTokenSeveralPostRequest::RefreshTokenSeveralPostRequest(
    QSharedPointer<QNetworkAccessManager> manager,
    int number_of_iterations,
    std::vector<std::string> refresh_tokens,
    std::string scope,
    std::string error_message,
    std::string _application_client_ID

    ):
    manager(manager),
    number_of_iterations(number_of_iterations),
    refresh_tokens(std::move(refresh_tokens)),
    scope(std::move(scope)),
    error_message(std::move(error_message)),
    application_client_ID(std::move(_application_client_ID))
{

    my_connect();

}

void RefreshTokenSeveralPostRequest::onFinished(QNetworkReply* reply)
{
    qDebug() << "xxxxxx";
    disconnect(manager.get(), &QNetworkAccessManager::finished, this, &RefreshTokenSeveralPostRequest::onFinished);
    if (reply->error()) {
        qDebug() << reply->errorString();
        reply->deleteLater();
        throw std::runtime_error(error_message);
        //return;
    }
    qDebug() << "there is data";
    QString answer = reply->readAll();

    //qDebug() << answer;
    ans_data.push_back(std::move(answer.toStdString()));
    reply->deleteLater();
    ++i;
    my_connect();
}

void RefreshTokenSeveralPostRequest::my_connect()
{
    qDebug() << "wwwgerg";
    if(i == number_of_iterations){
        emit data_ready(std::move(ans_data));
        return;
    }
    //++i;
    auto url = QUrl("https://login.eveonline.com/v2/oauth/token");
    QUrlQuery q;
    q.addQueryItem(QUrl::toPercentEncoding("grant_type"), QUrl::toPercentEncoding("refresh_token"));
    q.addQueryItem(QUrl::toPercentEncoding("refresh_token"), QUrl::toPercentEncoding(QString::fromStdString(refresh_tokens[i])));
    url.setQuery(q);

    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setRawHeader("Host", "login.eveonline.com");

    connect(manager.get(), &QNetworkAccessManager::finished, this, &RefreshTokenSeveralPostRequest::onFinished);
    qDebug() << "yyyyyyyyyyy";
    manager->post(request, QByteArray());
}
