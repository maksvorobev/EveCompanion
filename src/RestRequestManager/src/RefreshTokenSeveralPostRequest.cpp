#include "../include/RefreshTokenSeveralPostRequest.h"

RefreshTokenSeveralPostRequest::RefreshTokenSeveralPostRequest(
    std::shared_ptr<CastomNetworkAccessManager> manager,
    std::string scope,
    std::string error_message,
    std::string _application_client_ID

    ):
    manager_(manager),
    scope(std::move(scope)),
    error_message(std::move(error_message)),
    application_client_ID(std::move(_application_client_ID))
{

    //my_connect();

}

void RefreshTokenSeveralPostRequest::set_up(int number_of_iterations, std::vector<std::string> refresh_tokens){
    this->number_of_iterations = number_of_iterations;
    this->refresh_tokens = std::move(refresh_tokens);

    qInfo() << this->refresh_tokens.size();
    for (auto x : refresh_tokens){
        qInfo() << QString::fromStdString(x);
    }

}


void RefreshTokenSeveralPostRequest::onFinished(QNetworkReply* reply)
{
    qDebug() << "info";
    disconnect(manager_.get(), &QNetworkAccessManager::finished, this, &RefreshTokenSeveralPostRequest::onFinished);
    if (reply->error()) {

        qDebug() << reply->error() << reply->readAll();
        //qDebug() << reply->header().toString();
        reply->deleteLater();
        throw std::runtime_error(error_message);
        //return;
    }
    QString answer = reply->readAll();
    qInfo() << answer;
    ans_data.push_back(std::move(answer.toStdString()));
    reply->deleteLater();
    ++i;
    my_connect();
    return;
}

void RefreshTokenSeveralPostRequest::my_connect()
{
    if(i == number_of_iterations){
        i = 0;
        emit data_ready(std::move(ans_data));
        return;
    }
    //++i;
    auto url = QUrl("https://login.eveonline.com/v2/oauth/token");
    /*
    QUrlQuery q;
    qDebug() << QString::fromStdString(refresh_tokens[i]) << QString::fromStdString(application_client_ID);
    q.addQueryItem(QUrl::toPercentEncoding("grant_type"), QUrl::toPercentEncoding("refresh_token"));
    q.addQueryItem(QUrl::toPercentEncoding("refresh_token"), QUrl::toPercentEncoding(QString::fromStdString(refresh_tokens[i])));
    q.addQueryItem(QUrl::toPercentEncoding("client_id"), QUrl::toPercentEncoding(QString::fromStdString(application_client_ID)));

    url.setQuery(q);
    */

    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setRawHeader("Host", "login.eveonline.com");
    qDebug() << url;
    connect(manager_.get(), &QNetworkAccessManager::finished, this, &RefreshTokenSeveralPostRequest::onFinished);
    qDebug() << "old refresh token " <<QString::fromStdString(refresh_tokens.at(i)) <<  "id = " <<QString::fromStdString(application_client_ID);

    QByteArray postData; // payload
    postData.append("grant_type=refresh_token");
    postData.append("&refresh_token=" + QString::fromStdString(refresh_tokens[i]).toUtf8());
    postData.append("&client_id=" + QString::fromStdString(application_client_ID).toUtf8());
    //postData.append("&code_verifier=" + QByteArray(Code_verifier.constData()));

    auto x  = manager_->post(request, postData);

}
