#pragma once
#include <QNetworkAccessManager>

class CastomNetworkAccessManager: public QNetworkAccessManager
{
    Q_OBJECT
public:

    static CastomNetworkAccessManager* GetInstance();


    CastomNetworkAccessManager(const CastomNetworkAccessManager&) = delete;
    CastomNetworkAccessManager& operator=(const CastomNetworkAccessManager&) = delete;
protected:
    CastomNetworkAccessManager();

    static CastomNetworkAccessManager* manager_;
};


