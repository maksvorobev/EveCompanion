#pragma once

#include <QObject>
#include <QTimer>
#include "../../authorization/include/User_data_handler.h"
#include "../../RestRequestManager/include/RefreshTokenSeveralPostRequest.h"

class Authorization_engine;
class User_data_handler;

class Refresh_Manager: public QObject
{
    Q_OBJECT
public:
    Refresh_Manager(
        QSharedPointer<User_data_handler> user_data_handler,
        QSharedPointer<QNetworkAccessManager> manager,
        int number_of_iterations,
        std::vector<std::string> refresh_tokens,
        std::string scope,
        std::string error_message,
        std::string _application_client_ID
        );


private:
    QTimer timer;
    QScopedPointer<RefreshTokenSeveralPostRequest> refersh_manager;
    QSharedPointer<User_data_handler> user_data_handler;
protected slots:
    void start_refreshing();
    void stop_refreshing();
};

