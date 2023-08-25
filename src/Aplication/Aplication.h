#pragma once

#include "Authorization_engine.h"
#include "Refresh_Manager.h"

class Aplication: QObject
{
    Q_OBJECT
public:
    Aplication(
        QString aplicationId,
        QString scopes
        );

    Authorization_engine* authEngine() const;

private:
    std::shared_ptr<CastomNetworkAccessManager> manager_;
    std::shared_ptr<TcpServer> tcpServer_;
    std::unique_ptr<Authorization_engine> authEngine_;
    std::unique_ptr<Refresh_Manager> refreshManager_;
};

