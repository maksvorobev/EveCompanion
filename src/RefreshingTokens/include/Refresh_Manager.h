#pragma once


#include <QTimer>
#include "CastomNetworkAccessManager.h"
#include "AuthUserDataManager.h"
#include "Validating_JWT.h"
#include "../../RestRequestManager/include/RefreshTokenSeveralPostRequest.h"
#include "../../authorization/include/AuthUserDataManager.h"
#include <memory>



class Refresh_Manager: public QObject
{
    // maybe it must be as singleton
    Q_OBJECT
public:
    Refresh_Manager(
        std::shared_ptr<CastomNetworkAccessManager> manager,
        std::shared_ptr<AuthUserDataManager> userDataHandler,
        std::shared_ptr<Validating_JWT> validatingJwt,
        std::string scope,
        std::string error_message,
        std::string _application_client_ID
        );

    bool timer_is_work();
    void set_up_for_refreshing(const std::map<std::string, std::string>& mp_id_refreshTocken,
                                int count_of_characters);

    void refreshing_process_flow();
private:
    QTimer timer;
    std::unique_ptr<RefreshTokenSeveralPostRequest> postRreqManager_;
    std::shared_ptr<AuthUserDataManager> userDataHandler_;
    std::shared_ptr<Validating_JWT> validatingJwt_;
    const int time_interval = 10*1000;


public:
    void start_refreshing_tokens();
    void stop_refreshing();

};

