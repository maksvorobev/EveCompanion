#pragma once
#include <QJsonDocument>
#include "../../../third-party-lib/jwt-cpp/jwt-cpp/jwt.h"
#include "Auth_user_data.h"
#include <QSettings>
#include <nlohmann/json.hpp>
#include <iostream>
#include <QDebug>
#include <QSettings>
#include <QAnyStringView>
#include <QObject>

class User_data_handler: public QObject
{
    /*
     * This class provides store user data such as class Auth_user_data into storage
    */
    Q_OBJECT
public:
    User_data_handler();
    void Receive_user_data(const QJsonDocument& JSON_payload);
    void store_data(const ns_data::Auth_user_data& data);
signals:
    void pushSecondPage();

private:
    QSettings* storage;
};

