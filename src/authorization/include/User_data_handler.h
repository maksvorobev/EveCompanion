#pragma once
#include <QJsonDocument>
#include "../../../third-party-lib/jwt-cpp/jwt-cpp/jwt.h"
#include "Auth_user_data.h"
#include <QSettings>
#include <nlohmann/json.hpp>


class User_data_handler
{
    /*
     * This class provides store user data such as class Auth_user_data into storage
    */
public:
    User_data_handler();
    void Receive_user_data(QJsonDocument JSON_payload);
};

