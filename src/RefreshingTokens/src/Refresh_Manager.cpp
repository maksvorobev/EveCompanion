#include "../include/Refresh_Manager.h"

Refresh_Manager::Refresh_Manager(
    QSharedPointer<User_data_handler> user_data_handler,
    QSharedPointer<QNetworkAccessManager> manager,
    int number_of_iterations,
    std::vector<std::string> refresh_tokens,
    std::string scope,
    std::string error_message,
    std::string _application_client_ID
    ):
    user_data_handler(user_data_handler)
{
    refersh_manager.reset(new RefreshTokenSeveralPostRequest(
        manager,
        number_of_iterations,
        std::move(refresh_tokens),
        std::move(scope),
        std::move(error_message),
        std::move(_application_client_ID)
        ));
}

void Refresh_Manager::start_refreshing()
{
    auto refresing_tokens = user_data_handler->get_refresh_tokens();
    if (refresing_tokens.size() == 0){
        qDebug() << "nothing to refresh";
        return;
    }
    else{
        connect(refersh_manager.get(), &RefreshTokenSeveralPostRequest::data_ready,
                [this](std::vector<std::string> ans){
                    qDebug() << "thre is ans after refreshing tokens";
                    for (auto x : ans){
                qDebug() << QString::fromStdString(x);
            }
        });
    }
}

void Refresh_Manager::stop_refreshing()
{

}
