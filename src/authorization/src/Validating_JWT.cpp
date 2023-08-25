#include "../include/Validating_JWT.h"

#include <QEventLoop>

Validating_JWT::Validating_JWT(
    std::shared_ptr<CastomNetworkAccessManager>  manager
    ):
    manager_(manager)
{

}

void Validating_JWT::start(QJsonDocument _JSON_payload)
{

    qDebug() << _JSON_payload;

    JSON_payload = std::move(_JSON_payload);
    access_token = JSON_payload["access_token"].toString();

    send_GET_request_to_SSO_key_storage();

    /*
    QNetworkAccessManager l_nm;
    QNetworkRequest req;
    req.setUrl(SSO_key_storage);
    QNetworkReply *l_reply = l_nm.get(req);
    QEventLoop l_event_loop;
    QObject::connect(l_reply, SIGNAL(finished()), &l_event_loop, SLOT(quit()));
    l_event_loop.exec();



    if (l_reply->error()) {
        //QMutexLocker ml(&mMutex);
        qDebug() << l_reply->errorString();
        throw std::runtime_error("error with get_responce_from_SSO_key_storage");
        l_reply->deleteLater();
        return;
    }

    QByteArray answer = l_reply->readAll();
    qDebug() << answer;
    // extract nn ee that call ConvertJwkToPem_V2()
    extract_nn_and_ee(answer);
    l_reply->deleteLater();
    */

}

void Validating_JWT::veri_jwt_token(QString strToken, QString rsa_pub_key)
{
    /*
     * rs 256 jwt token validation
     *
    */

    std::string token = strToken.toStdString();

    auto verify = jwt::verify().allow_algorithm(jwt::algorithm::rs256(rsa_pub_key.toStdString(), "", "", "")).with_issuer("login.eveonline.com").with_audience("EVE Online").leeway(5);
    qDebug() << "current unix time : " << (QDateTime::currentMSecsSinceEpoch()/1000);

    qInfo() << "It's your access token :\n" << QString::fromStdString(token);
    auto decoded = jwt::decode(std::move(token));


    verify.verify(std::move(decoded)); // there Validate the JWT tocken (signature, issuer, date, audience), if all will valid nothing will happen, else will thow exapthion
    qInfo() << "Verify JWT token was successful";

    qDebug() << "below decoding of your JWT token";
    for (auto& e : decoded.get_header_json())
        qInfo() << QString::fromStdString(e.first) << " = " << QString::fromStdString(e.second.to_str());
    for (auto& e : decoded.get_payload_json())
        qInfo() << QString::fromStdString(e.first) << " = " << QString::fromStdString(e.second.to_str());



    // there is we want store info about user from auth. after valid verify

    emit Sent_user_data_to_handler(JSON_payload);
    return;



}


QString Validating_JWT::ConvertJwkToPem_V2(const QString& nn, const QString& ee){
    /* accepts nn and ee from get request to SSO_key_storage and return
     * PEM-fomat JWK tocken (it's our private key)
     *
     *
     *
     *
    */

    QString nnInBase64 = QString::fromLatin1(nn.toUtf8()).replace(QLatin1Char('-'), QLatin1Char('+')).replace(QLatin1Char('_'), QLatin1Char('/'));
    QString eeInBase64 = QString::fromLatin1(ee.toUtf8()).replace(QLatin1Char('-'), QLatin1Char('+')).replace(QLatin1Char('_'), QLatin1Char('/'));

    QByteArray nnBin = QByteArray::fromBase64(nnInBase64.toLatin1());
    QByteArray eeBin = QByteArray::fromBase64(eeInBase64.toLatin1());

    BIGNUM* modul = BN_bin2bn(reinterpret_cast<const unsigned char*>(nnBin.constData()), nnBin.length(), NULL);
    BIGNUM* expon = BN_bin2bn(reinterpret_cast<const unsigned char*>(eeBin.constData()), eeBin.length(), NULL);

    RSA* rr = RSA_new();
    RSA_set0_key(rr, modul, expon, NULL);

    BIO* mem = BIO_new(BIO_s_mem());
    PEM_write_bio_RSA_PUBKEY(mem, rr);

    char* data;
    long length = BIO_get_mem_data(mem, &data);
    std::string pemData(data, length);

    BIO_free(mem);
    RSA_free(rr);

    return QString::fromStdString(pemData);

}

void Validating_JWT::send_GET_request_to_SSO_key_storage()
{
    /*
     * old version but not not suitable for loop
    connect(manager_.get(), &QNetworkAccessManager::finished, this, &Validating_JWT::get_responce_from_SSO_key_storage);
    QNetworkRequest req;
    req.setUrl(SSO_key_storage);
    manager_->get(req);
    return;
    */

    // Unfortunately there i make blocking event loop get request, but is's for very simlify (and it's it rarely happens)
    QNetworkAccessManager l_nm;
    QNetworkRequest req;
    req.setUrl(SSO_key_storage);
    QNetworkReply *l_reply = l_nm.get(req);
    QEventLoop l_event_loop;
    QObject::connect(l_reply, SIGNAL(finished()), &l_event_loop, SLOT(quit()));
    l_event_loop.exec();



    if (l_reply->error()) {

        qDebug() << l_reply->errorString();
        throw std::runtime_error("error with get_responce_from_SSO_key_storage");
        l_reply->deleteLater();
        return;
    }

    QByteArray answer = l_reply->readAll();
    // extract nn ee that call ConvertJwkToPem_V2()
    extract_nn_and_ee(answer);
    l_reply->deleteLater();

    return;
}

void Validating_JWT::extract_nn_and_ee(const QByteArray& answer)
{
    QJsonDocument doc = QJsonDocument::fromJson(answer);
    QString ee =  doc["keys"][0]["e"].toString();
    QString nn =  doc["keys"][0]["n"].toString();
    final_check(ee, nn);

    return;
}

void Validating_JWT::final_check(const QString& ee, const QString& nn)
{

    // this is func unite ConvertJwkToPem_V2 and veri_jwt_token
    QString public_key =  ConvertJwkToPem_V2(nn, ee);
    veri_jwt_token(access_token, std::move(public_key));

    return;
}

void Validating_JWT::get_responce_from_SSO_key_storage(QNetworkReply *reply)
{
    disconnect(manager_.get(), &QNetworkAccessManager::finished, this, &Validating_JWT::get_responce_from_SSO_key_storage);

    if (reply->error()) {
        //QMutexLocker ml(&mMutex);
        //qDebug() << reply->errorString();
        throw std::runtime_error("error with get_responce_from_SSO_key_storage");
        reply->deleteLater();
        return;
    }

    QByteArray answer = reply->readAll();

    // extract nn ee that call ConvertJwkToPem_V2()
    extract_nn_and_ee(answer);
    reply->deleteLater();
    return;
}

