#pragma once

#include <QObject>
#include <QTimer>
#include "../../authorization/include/Authorization_engine.h"
#include "../../RestRequestManager/include/RefreshTokenSeveralPostRequest.h"

class Authorization_engine;
class User_data_handler;

class Refresh_Manager: public QObject
{
    Q_OBJECT
public:
    Refresh_Manager(
        QSharedPointer<Authorization_engine> m_authorization_engine,
        std::string scope,
        std::string error_message,
        std::string _application_client_ID
        );

    bool timer_is_work();
    void set_up_for_refreshing();
private:
    QTimer timer;
    QScopedPointer<RefreshTokenSeveralPostRequest> post_req_manager;
    QSharedPointer<Authorization_engine> m_authorization_engine;
    std::map<std::string, std::string> mp_id_refreshTocken;


public slots:
    void start_refreshing();
    void stop_refreshing();

};

