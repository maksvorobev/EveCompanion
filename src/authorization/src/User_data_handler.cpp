#include "User_data_handler.h"
using json = nlohmann::json;

User_data_handler::User_data_handler()
{

}

void User_data_handler::Receive_user_data(QJsonDocument JSON_payload)
{
    auto strToken = JSON_payload["access_token"].toString();
    std::string token = strToken.toStdString();
    auto decoded = jwt::decode(token);
    qDebug() << "i from onWrite_into_QSettings_user_data";
    qDebug() << "below decoding of your JWT token";
    Auth_user_data data = {QString::fromStdString(decoded.get_payload_json()["name"].to_str()),
        QString::fromStdString(decoded.get_payload_json()["sub"].to_str()).split(":")[2],
        strToken,
        JSON_payload["refresh_token"].toString()
    };

    //Auth_user_data data = {decoded.get_payload_json()["name"], };
    for (auto& e : decoded.get_header_json())
        qDebug() << QString::fromStdString(e.first) << " = " << QString::fromStdString(e.second.to_str());
    for (auto& e : decoded.get_payload_json())
        qDebug() << QString::fromStdString(e.first) << " = " << QString::fromStdString(e.second.to_str());
    qDebug() << "";
    qDebug() << "";

}
