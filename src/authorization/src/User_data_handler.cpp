#include "User_data_handler.h"
using json = nlohmann::json;

User_data_handler::User_data_handler(QSharedPointer<QNetworkAccessManager> manager) :
    model_ptr(new MainPageModel),
    storage(new QSettings),
    manager(manager)
{

}

void User_data_handler::Receive_user_data(const QJsonDocument& JSON_payload)
{
    auto strToken = JSON_payload["access_token"].toString();
    std::string token = strToken.toStdString();
    auto decoded = jwt::decode(token);
    qDebug() << "i from onWrite_into_QSettings_user_data";
    qDebug() << "below decoding of your JWT token";
    ns_data::Auth_user_data data = {decoded.get_payload_json()["name"].to_str(),
        QString::fromStdString(decoded.get_payload_json()["sub"].to_str()).split(":")[2].toStdString(),
        strToken.toStdString(),
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
    qDebug() << "wfwfwf";
    qDebug() << storage->value(QString("2114312667")).toString();
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
    std::vector<MainPageModelData> data_vector;;
    qDebug() <<" test" <<model_ptr->rowCount();
    qDebug() << "user data";
    for (const auto& user_id : storage->allKeys()){
        MainPageModelData data_struct;
        json j = json::parse(storage->value(user_id).toString().toStdString());
        data_struct.name = j["name"];
        qDebug() << QString::fromStdString(data_struct.name);

        RestRequestManager restRequestManager(manager);
        auto ans = restRequestManager.GET_request_without_token_block_CHARACTER(
            std::move(j["character_id"]),
            "portrait",
            "issue image get"
            );
        data_struct.image_url =  json::parse(std::string(ans.value<QByteArray>().constData()))["px64x64"];
        auto ans2 = restRequestManager.GET_request_with_token_block_CHARACTER(
            std::move(j["character_id"]),
            "wallet",
            "issue wallet get",
            j["access_token"]
            );
        data_struct.wallet_balance =QString::number(ans2.value<QByteArray>().toDouble(), 'g', 10).toStdString();
        //qDebug() << QString::number(ans2.value<QByteArray>().toDouble(), 'g', 10);
        model_ptr->addData(std::move(data_struct));
        //data_vector.push_back(std::move(data_struct));
    }

    //model_ptr->addData(data_vector);
    model_ptr->get_model_data();
    qDebug() << model_ptr->rowCount();

    return;
}





