#include "User_data_handler.h"
using json = nlohmann::json;

User_data_handler::User_data_handler()
{
    storage = new QSettings("maksvorobev", "EveCompanion");
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

}

void User_data_handler::store_data(const ns_data::Auth_user_data &data)
{
    json j = data;
    storage->setValue(QString::fromStdString(j["character_id"]), QString::fromStdString(j.dump()));
    qDebug() << "wfwfwf";
    qDebug() << storage->value(QString("2114312667")).toString();
    //qDebug()<<  QString::fromStdString(j.dump());

    emit pushSecondPage();
}

