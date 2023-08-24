#include "../include/Refresh_Manager.h"

Refresh_Manager::Refresh_Manager(
    QSharedPointer<QNetworkAccessManager> manager,
    QSharedPointer<User_data_handler> _m_user_data_handler,
    QSharedPointer<Validating_JWT> m_validating_JWT,
    std::string scope,
    std::string error_message,
    std::string _application_client_ID
    ):
    m_user_data_handler(_m_user_data_handler),
    post_req_manager(std::make_unique<RefreshTokenSeveralPostRequest>(
          manager,
          std::move(scope),
          std::move(error_message),
          std::move(_application_client_ID)
          )),
    m_validating_JWT(m_validating_JWT)
{

}

bool Refresh_Manager::timer_is_work()
{
    return timer.isActive();
}

void Refresh_Manager::set_up_for_refreshing(std::map<std::string, std::string> mp_id_refreshTocken, int count_of_characters)
{
    this->mp_id_refreshTocken = std::move(mp_id_refreshTocken);
    std::vector<std::string> v ;

    for (const auto& [f, s] : mp_id_refreshTocken){
        qDebug() << "refresh token  = " <<QString::fromStdString(s) ;
        v.push_back(s);

    }

    post_req_manager->set_up(
        count_of_characters,
        std::move(v)
        );
}

void Refresh_Manager::start_refreshing_tokens()
{

    if (timer.isActive()){
        qWarning() << "refresh token Timer already executed !";
        return;
    }

    connect(&timer, &QTimer::timeout, this, [this](){
        //QObject::disconnect(*conn2);
        qDebug() << "finc call - refreshing_process_flow" << "\n";
        refreshing_process_flow();
    });
    timer.start(time_interval);


}



void Refresh_Manager::refreshing_process_flow()
{
    /*
     * Be carefull !!! my_connect() func will executed in other threads !!!
     */

    set_up_for_refreshing(m_user_data_handler->get_refresh_tokens(), m_user_data_handler->count_of_characters());



    auto conn = std::make_shared<QMetaObject::Connection>();
    *conn = connect(post_req_manager.get(), &RefreshTokenSeveralPostRequest::data_ready, [this, conn](auto reply){
        qDebug() << "lamda";

        QObject::disconnect(*conn);
        for (auto x : reply){
            qDebug() << "Reply = " << QString::fromStdString(x);

            auto conn2 = std::make_shared<QMetaObject::Connection>();
            *conn2 = connect(
                m_validating_JWT.get(),
                &Validating_JWT::Sent_user_data_to_handler,
                this,
                [conn2](auto x)
                {
                    QObject::disconnect(*conn2);
                    qDebug() << "token is valid";
                });

            m_validating_JWT->start(QJsonDocument::fromJson(std::move(QString::fromStdString(x).toUtf8())));
            //QJsonDocument doc = QJsonDocument::fromJson(std::move(QString::fromStdString(x).toUtf8()));

            // TODO
            //m_authorization_engine->getValidating_JWT()->start(std::move(doc));
        }
    });
    post_req_manager->my_connect();
}

void Refresh_Manager::stop_refreshing()
{

}
