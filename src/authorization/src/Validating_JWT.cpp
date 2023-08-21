#include "../include/Validating_JWT.h"

Validating_JWT::Validating_JWT(
    QSharedPointer<QNetworkAccessManager> manager,
    Authorization_engine* auth_engine
    ):
    manager(manager),
    auth_engine(auth_engine)
{

}

void Validating_JWT::start(QJsonDocument _JSON_payload)
{
    JSON_payload = std::move(_JSON_payload);
    access_token = JSON_payload["access_token"].toString();
    send_GET_request_to_SSO_key_storage();
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

    qDebug() << QString::fromStdString(token);
    auto decoded = jwt::decode(std::move(token));
    qDebug() << "1111111";
    /*
    qDebug() << "below decoding of your JWT token";
    for (auto& e : decoded.get_header_json())
        qDebug() << QString::fromStdString(e.first) << " = " << QString::fromStdString(e.second.to_str());
    for (auto& e : decoded.get_payload_json())
        qDebug() << QString::fromStdString(e.first) << " = " << QString::fromStdString(e.second.to_str());
    qDebug() << "";
    qDebug() << "";
    */
    verify.verify(std::move(decoded)); // there Validate the JWT tocken (signature, issuer, date, audience), if all will valid nothing will happen, else will thow exapthion


    // there we want store info about user from auth. after valid verify
    connect(this, &Validating_JWT::Sent_user_data_to_handler,
            auth_engine, &Authorization_engine::onSent_user_data_to_handler);
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
    connect(manager.get(), &QNetworkAccessManager::finished, this, &Validating_JWT::get_responce_from_SSO_key_storage);
    QNetworkRequest req;
    req.setUrl(SSO_key_storage);
    manager->get(req);
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
    disconnect(manager.get(), &QNetworkAccessManager::finished, this, &Validating_JWT::get_responce_from_SSO_key_storage);

    if (reply->error()) {
        qDebug() << reply->errorString();
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

