#pragma once

#include <QObject>
#include <QByteArray>
#include <QUrl>

class AuthorizationUrl: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString authorizationUrl_ READ authorizationUrl CONSTANT)
public:
    AuthorizationUrl() = default;
    AuthorizationUrl(QUrl CallbackUrl, QString AplicationId, QString Scopes);
    void MakeAuthorizationUrl();
    static QByteArray CreateCodeChallenge(const QByteArray &codeVerifier);
    static QByteArray GenerateCodeVerifier();
    static QString PercentEncoding(const QString& param);
    QString authorizationUrl() const;


    QByteArray codeVerifier() const;

private:
    QUrl authorizationUrl_;
    QUrl callbackUrl_;
    QString aplicationId_;
    QString scopes_;
    QByteArray codeVerifier_;
};

