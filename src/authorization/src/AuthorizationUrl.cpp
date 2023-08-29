#include "../include/AuthorizationUrl.h"

#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QUrlQuery>
#include <QUuid>
#include <QDebug>

AuthorizationUrl::AuthorizationUrl(QUrl CallbackUrl, QString AplicationId, QString Scopes)
    :
    callbackUrl_(std::move(CallbackUrl)),
    aplicationId_(std::move(AplicationId)),
    scopes_(std::move(Scopes))
{
}

void AuthorizationUrl::MakeAuthorizationUrl()
{
    qDebug() << "make auth url";
    QUrl url = QString("https://login.eveonline.com/v2/oauth/authorize/");
    QUrlQuery q;
    q.addQueryItem(PercentEncoding("response_type"), PercentEncoding("code"));
    q.addQueryItem(PercentEncoding("redirect_uri"), PercentEncoding(callbackUrl_.toString()));
    q.addQueryItem(PercentEncoding("client_id"), PercentEncoding(aplicationId_));

    q.addQueryItem(PercentEncoding("scope"), PercentEncoding(scopes_));

    codeVerifier_ = AuthorizationUrl::GenerateCodeVerifier();
    q.addQueryItem(PercentEncoding("code_challenge"), PercentEncoding(AuthorizationUrl::CreateCodeChallenge(codeVerifier_)));
    q.addQueryItem(PercentEncoding("code_challenge_method"), PercentEncoding("S256"));
    q.addQueryItem(PercentEncoding("state"), PercentEncoding(QUuid::createUuid().toString()));
    url.setQuery(q);
    authorizationUrl_ = std::move(url);
    return;
}

QByteArray AuthorizationUrl::CreateCodeChallenge(const QByteArray &codeVerifier)
{
    // Hashing the code identifier using SHA-256
    QByteArray hash = QCryptographicHash::hash(codeVerifier, QCryptographicHash::Sha256);

    return hash.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
}

QByteArray AuthorizationUrl::GenerateCodeVerifier()
{
    // Generate 32 random bites
    QByteArray randomBytes(32, Qt::Uninitialized);
    for (int i = 0; i < randomBytes.size(); ++i) {
        randomBytes[i] = static_cast<quint8>(QRandomGenerator::global()->generate());
    }
    return randomBytes.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
}

QString AuthorizationUrl::PercentEncoding(const QString &param)
{
    return QString::fromStdString(QUrl::toPercentEncoding(param).toStdString());
}

QString AuthorizationUrl::authorizationUrl() const
{
    return authorizationUrl_.toString();
}

QByteArray AuthorizationUrl::codeVerifier() const
{
    return codeVerifier_;
}
