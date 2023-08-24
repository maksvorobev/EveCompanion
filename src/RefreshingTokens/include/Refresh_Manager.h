#pragma once

#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include "../../RestRequestManager/include/RefreshTokenSeveralPostRequest.h"
#include "../../authorization/include/AuthUserDataManager.h"
#include <memory>

//class Authorization_engine;
//class User_data_handler;
//class MainPageModel;

class Refresh_Manager: public QObject
{
    // maybe it must be as singleton
    Q_OBJECT
public:
    Refresh_Manager(
        QSharedPointer<QNetworkAccessManager> manager,
        //QSharedPointer<User_data_handler> m_user_data_handler,
        //QSharedPointer<Validating_JWT>,
        std::string scope,
        std::string error_message,
        std::string _application_client_ID
        );

    bool timer_is_work();
    void set_up_for_refreshing(std::map<std::string, std::string> mp_id_refreshTocken,
                                int count_of_characters);

    void refreshing_process_flow();
private:
    QTimer timer;
    std::unique_ptr<RefreshTokenSeveralPostRequest> post_req_manager;
    QSharedPointer<User_data_handler> m_user_data_handler;
    QSharedPointer<Validating_JWT> m_validating_JWT;
    std::map<std::string, std::string> mp_id_refreshTocken;
    const int time_interval = 10*1000;


public slots:
    void start_refreshing_tokens();
    void stop_refreshing();

};

