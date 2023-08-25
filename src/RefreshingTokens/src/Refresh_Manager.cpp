#include "../include/Refresh_Manager.h"


Refresh_Manager::Refresh_Manager(
    std::shared_ptr<CastomNetworkAccessManager> manager,
    std::shared_ptr<AuthUserDataManager> userDataHandler,
    std::shared_ptr<Validating_JWT> validatingJwt,
    std::string scope,
    std::string error_message,
    std::string _application_client_ID
    ):
    userDataHandler_(userDataHandler),
    postRreqManager_(std::make_unique<RefreshTokenSeveralPostRequest>(
          manager,
          std::move(scope),
          std::move(error_message),
          std::move(_application_client_ID)
          )),
    validatingJwt_(validatingJwt)
{

    start_refreshing_tokens();
}

bool Refresh_Manager::timer_is_work()
{
    return timer.isActive();
}

void Refresh_Manager::set_up_for_refreshing(const std::map<std::string, std::string>& mp_id_refreshTocken, int count_of_characters)
{


    for (auto [l, r] : mp_id_refreshTocken){
        qInfo() << QString::fromStdString(l) << QString::fromStdString(r);
    }
    std::vector<std::string> v ;

    for (const auto& [f, s] : mp_id_refreshTocken){
        qDebug() << "refresh token  = " <<QString::fromStdString(s) ;
        v.push_back(s);

    }

    postRreqManager_->set_up(
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

    //QObject *context = new QObject;
    connect(&timer, &QTimer::timeout, [this](){
        //delete context;
        qDebug() << "finc call - refreshing_process_flow" << "\n";
        refreshing_process_flow();
    });
    timer.start(time_interval);

    return;
}



void Refresh_Manager::refreshing_process_flow()
{
    /*
     * Be carefull !!! my_connect() func will executed in other threads !!!
     */
    qDebug() << "info";
    set_up_for_refreshing(userDataHandler_->getMapIdRefreshToken(), userDataHandler_->countOfCharacters());
    qDebug() << userDataHandler_->countOfCharacters();


    QObject *context = new QObject;
    connect(postRreqManager_.get(), &RefreshTokenSeveralPostRequest::data_ready, context, [this, context](auto reply){
        delete context;

        /*
        qDebug() << reply.size();
        for (auto x : reply){
            qDebug() << QString::fromStdString(x);
        }
        */

        for (auto x : reply){
            //qDebug() << "Reply = " << QString::fromStdString(x);

            QObject *context2 = new QObject;
                connect(
                validatingJwt_.get(),
                &Validating_JWT::Sent_user_data_to_handler,
                context2,
                [this, context2](auto x)
                {
                    delete context2;

                    userDataHandler_->storeJsonPayload(x);
                });
            qInfo() << QJsonDocument::fromJson((QString::fromStdString(x).toUtf8()));
            validatingJwt_->start(QJsonDocument::fromJson(QString::fromStdString(x).toUtf8()));


        }



    });
    postRreqManager_->my_connect();

}

void Refresh_Manager::stop_refreshing()
{

}
