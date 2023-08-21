#include "../include/Refresh_Manager.h"

Refresh_Manager::Refresh_Manager(
    QSharedPointer<Authorization_engine> m_authorization_engine,
    std::string scope,
    std::string error_message,
    std::string _application_client_ID
    ):
    m_authorization_engine(m_authorization_engine)
{
    post_req_manager.reset(new RefreshTokenSeveralPostRequest(
        m_authorization_engine->manager,
        std::move(scope),
        std::move(error_message),
        std::move(_application_client_ID)
        ));
}

bool Refresh_Manager::timer_is_work()
{
    return timer.isActive();
}

void Refresh_Manager::set_up_for_refreshing()
{
    mp_id_refreshTocken = m_authorization_engine->getUser_data_handler()->get_refresh_tokens();
    std::vector<std::string> v ;

    for (const auto& [f, s] : mp_id_refreshTocken){
        qDebug() << "xxxxxxxxxxx" <<QString::fromStdString(s) ;
        v.push_back(s);

    }

    post_req_manager->set_up(
        m_authorization_engine->getUser_data_handler()->count_of_characters(),
        std::move(v)
        );
}

void Refresh_Manager::start_refreshing()
{
    qDebug() << "func start_refreshing" << "\n";
    disconnect(m_authorization_engine->getUser_data_handler().get(), &User_data_handler::test, this, &Refresh_Manager::start_refreshing);
    auto refresing_tokens = m_authorization_engine->getUser_data_handler()->get_refresh_tokens();
    if (refresing_tokens.size() == 0){
        qDebug() << "nothing to refresh";
        return;
    }
    else if (timer.isActive()){
        qDebug() << "";
        qDebug() << "Already timer works";
        qDebug() << "";
        return;
    }
    else{
        auto conn = std::make_shared<QMetaObject::Connection>();
        *conn = connect(post_req_manager.get(), &RefreshTokenSeveralPostRequest::data_ready,
                [this, conn](std::vector<std::string> ans){
            //QObject::disconnect(*conn);
            qDebug() << "labda of RefareshManager" << "\n";
            qDebug() << "thre is ans after refreshing tokens\n\n";
            for (auto x : ans){
                //qDebug() << QString::fromStdString(x);
                QJsonDocument doc = QJsonDocument::fromJson(std::move(QString::fromStdString(x).toUtf8()));
                qDebug() << doc;

                // TODO
                //m_authorization_engine->getValidating_JWT()->start(std::move(doc));
                //m_authorization_engine->getValidating_JWT->start(std::move(doc));
            }

        });
        //auto conn2 = std::make_shared<QMetaObject::Connection>();
        connect(&timer, &QTimer::timeout, this, [this](){
            //QObject::disconnect(*conn2);
            qDebug() << "timer called!" << "\n";
            set_up_for_refreshing();
            post_req_manager->my_connect();
        });
        timer.start(10*1000);
        //post_req_manager->my_connect();


    }
}

void Refresh_Manager::stop_refreshing()
{

}
