#include "../include/AuthUserDataManager.h"

#include <QDebug>
#include <nlohmann/json.hpp>
#include "../../../third-party-lib/jwt-cpp/jwt-cpp/jwt.h"
#include "Auth_user_data.h"
using json = nlohmann::json;



AuthUserDataManager::AuthUserDataManager() :
    storage_(DataStorage())
{
    //qDebug() << "create storage, his location: "<<storage->fileName();
    storage_.clear();
}

void AuthUserDataManager::storeJsonPayload(const QJsonDocument& JSON_payload)
{
    /*
     * Receive and store JSON_payload getting after auth/refresh. Token
     * must be such as: (https://docs.esi.evetech.net/docs/sso/refreshing_access_tokens.html#sso-response)
     * {
     *  "access_token":"MXP...tg2",
     *  "token_type":"Bearer",
     *  "expires_in":1200,
     *  "refresh_token":"gEy...fM0"
     *  }
     */

    qDebug() << "Store auth user data into stoage!/n";
    auto accessToken = JSON_payload["access_token"].toString();
    std::string token = accessToken.toStdString();
    auto decoded = jwt::decode(std::move(token));
    ns_data::Auth_user_data data = {decoded.get_payload_json()["name"].to_str(),
        QString::fromStdString(decoded.get_payload_json()["sub"].to_str()).split(":")[2].toStdString(),
        accessToken.toStdString(),
        JSON_payload["refresh_token"].toString().toStdString()
    };

    json j = std::move(data);
    storage_.setValue(std::move(j["character_id"]), j.dump());
    qDebug() << "store_data func : " << "store key = " <<
        QString::fromStdString(j["character_id"]) <<
        "value = " << QString::fromStdString(j.dump());




    return;
}



/*
QSharedPointer<MainPageModel> User_data_handler::getModel_ptr() const
{
    return model_ptr;
}
*/


std::map<std::string, std::string> AuthUserDataManager::getMapIdRefreshToken() const
{

    /*
     * Return map as {id : refresh_token, ...}
     *
    */
    std::map<std::string, std::string> map;
    for (const auto& user_id : storage_.allKeys()){
        json j = json::parse(storage_[user_id]);
        map[user_id] = std::move(j["refresh_token"]);
    }
    return std::move(map);
}


int AuthUserDataManager::countOfCharacters() const
{
    return storage_.allKeys().size();
}

//void User_data_handler::fill_data_for_MainPageModelData()
//{
    /*
     * Fill m_data in MainPageModel
    */
    //std::vector<MainPageModelData> data_vector;
    //qDebug() <<" test" <<model_ptr->rowCount();
    //qDebug() << "user data";
    /*
    for (const auto& user_id : storage->allKeys()){
        MainPageModelData data_struct;
        json j = json::parse(storage->value(user_id).toString().toStdString());
        data_struct.name = j["name"];
        qDebug() << "name = " << QString::fromStdString(data_struct.name);
        ids.push_back(std::move(user_id.toStdString()));
        MainPageModelData model_data = {"", j["name"], ""};
        m_data.push_back(std::move(model_data));
        //qDebug() << QString::fromStdString(data_struct.name);
    }

    synch_GET = new Synch_GET_request_in_loop_whithout_auth(
        manager,
        storage->allKeys().size(),
        ids,
        "portrait",
        "issue image get requset"
        );
    connect(synch_GET, &Synch_GET_request_in_loop_whithout_auth::data_ready,
            this, &User_data_handler::receive_data_urls);
    //model_ptr->addData(data_vector);
    //model_ptr->get_model_data();
    //qDebug() << model_ptr->rowCount();

    return;
}
    */
/*
void User_data_handler::receive_data_urls(std::vector<std::string> data)
{
    //qDebug() << "receive_data";
    disconnect(synch_GET, &Synch_GET_request_in_loop_whithout_auth::data_ready,
            this, &User_data_handler::receive_data_urls);
    int i = 0;
    for (const auto& x : data){
        //qDebug() << QString::fromStdString(x);
        m_data[i].image_url = json::parse(std::move(x))["px64x64"];
        qDebug() << "image_url =  " << QString::fromStdString(m_data[i].image_url);
        //qDebug() << QString::fromStdString(m_data[i].name) << QString::fromStdString(m_data[i].image_url) << QString::fromStdString(m_data[i].wallet_balance);
        ++i;
    }

    for (auto& x : m_data){
        qDebug()<< "before adding in model :" << QString::fromStdString(x.image_url) << QString::fromStdString(x.name) << QString::fromStdString(x.wallet_balance);
        //model_ptr->addData(std::move(x));
    }

    std::vector<std::string> access_tokens;
    for (const auto& user_id : storage->allKeys()){
        MainPageModelData data_struct;
        json j = json::parse(storage->value(user_id).toString().toStdString());
        access_tokens.push_back(j["access_token"]);
    }
    Synch_GET_request_in_loop_whith_auth* synch_GET_with_auth = new Synch_GET_request_in_loop_whith_auth(
        manager,
        storage->allKeys().size(),
        ids, "wallet",
        "issue waller get requset",
        std::move(access_tokens)
        );


    auto conn = std::make_shared<QMetaObject::Connection>();
    *conn = connect(synch_GET_with_auth, &Synch_GET_request_in_loop_whith_auth::data_ready, [this, conn](std::vector<std::string> ans){
        QObject::disconnect(*conn);
        int i = 0;
        for (const auto& x : ans){
            m_data[i].wallet_balance = QString::number(QString::fromStdString(std::move(x)).toDouble(), 'g', 10).toStdString();
            //qDebug() << QString::fromStdString(x);
            ++i;
        }
        for (auto& x : m_data){
            qDebug()<< "before adding in model :" << QString::fromStdString(x.image_url) << QString::fromStdString(x.name) << QString::fromStdString(x.wallet_balance);
            model_ptr->addData(std::move(x));
        }
        // end of thread
        qDebug() << "testing refraeshing";
        ptr->get_refresh_Manager();
        if (!ptr->get_refresh_Manager()->timer_is_work()){
            //qWarning() << "TIMER ALREADY WORK!!!!";
            connect(this, &User_data_handler::test, ptr->get_refresh_Manager().get(), &Refresh_Manager::start_refreshing_tokens);
            emit test();
        }
        qWarning() << "TIMER ALREADY WORK!!!!";
        //emit test();
    });
    return;
}
*/



