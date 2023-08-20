#include "User_data_handler.h"
using json = nlohmann::json;

User_data_handler::User_data_handler(QSharedPointer<QNetworkAccessManager> manager) :
    model_ptr(new MainPageModel),
    storage(new QSettings("EveCompanion", "maksvorobev")),
    manager(manager)
{

}

void User_data_handler::Receive_user_data(const QJsonDocument& JSON_payload)
{
    auto access_token = JSON_payload["access_token"].toString();
    std::string token = access_token.toStdString();
    auto decoded = jwt::decode(std::move(token));
    qDebug() << "i from onWrite_into_QSettings_user_data";
    qDebug() << "below decoding of your JWT token";
    ns_data::Auth_user_data data = {decoded.get_payload_json()["name"].to_str(),
        QString::fromStdString(decoded.get_payload_json()["sub"].to_str()).split(":")[2].toStdString(),
        access_token.toStdString(),
        JSON_payload["refresh_token"].toString().toStdString()
    };
    store_data(data);


    //Auth_user_data data = {decoded.get_payload_json()["name"], };
    for (auto& e : decoded.get_header_json())
        qDebug() << QString::fromStdString(e.first) << " = " << QString::fromStdString(e.second.to_str());
    for (auto& e : decoded.get_payload_json())
        qDebug() << QString::fromStdString(e.first) << " = " << QString::fromStdString(e.second.to_str());
    qDebug() << "";
    qDebug() << "";



    fill_data_for_MainPageModelData();
    return;
}

void User_data_handler::store_data(const ns_data::Auth_user_data &data)
{
    json j = data;
    storage->setValue(QString::fromStdString(j["character_id"]), QString::fromStdString(j.dump()));
    qDebug() << "store_data";
    qDebug() << storage->fileName();
    //qDebug() << storage->value(QString("2114312667")).toString();
    //qDebug()<<  QString::fromStdString(j.dump());

    return;
}

QSharedPointer<MainPageModel> User_data_handler::getModel_ptr() const
{
    return model_ptr;
}

void User_data_handler::fill_data_for_MainPageModelData()
{
    /*
     * Fill m_data in MainPageModel
    */
    std::vector<MainPageModelData> data_vector;
    qDebug() <<" test" <<model_ptr->rowCount();
    qDebug() << "user data";

    for (const auto& user_id : storage->allKeys()){
        MainPageModelData data_struct;
        json j = json::parse(storage->value(user_id).toString().toStdString());
        data_struct.name = j["name"];
        ids.push_back(std::move(user_id.toStdString()));
        MainPageModelData model_data = {"", j["name"], ""};
        m_data.push_back(std::move(model_data));
        qDebug() << QString::fromStdString(data_struct.name);
    }
    Synch_GET_request_in_loop_whithout_auth* synch_GET = new Synch_GET_request_in_loop_whithout_auth(
        manager,
        storage->allKeys().size(),
        ids,
        "portrait",
        "issue image get requset"
        );
    connect(synch_GET, &Synch_GET_request_in_loop_whithout_auth::data_ready,
            this, &User_data_handler::receive_data_urls);
    //model_ptr->addData(data_vector);
    model_ptr->get_model_data();
    qDebug() << model_ptr->rowCount();

    return;
}

void User_data_handler::receive_data_urls(std::vector<std::string> data)
{
    qDebug() << "receive_data";
    //disconnect(manager, &Synch_GET_request_in_loop_whout_auth::data_ready, this, &test::receive_data);
    int i = 0;
    for (const auto& x : data){
        //qDebug() << QString::fromStdString(x);
        m_data[i].image_url = json::parse(std::move(x))["px64x64"];
        qDebug() << QString::fromStdString(m_data[i].name) << QString::fromStdString(m_data[i].image_url) << QString::fromStdString(m_data[i].wallet_balance);
        ++i;
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
    connect(synch_GET_with_auth, &Synch_GET_request_in_loop_whith_auth::data_ready, [this](std::vector<std::string> ans){
        int i = 0;
        for (const auto& x : ans){
            m_data[i].wallet_balance = QString::number(QString::fromStdString(std::move(x)).toDouble(), 'g', 10).toStdString();
            qDebug() << QString::fromStdString(x);
            ++i;
        }
        for (auto& x : m_data){
            model_ptr->addData(std::move(x));
        }
    });
    return;
}




