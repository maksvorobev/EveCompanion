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
#include <QScopedPointer>
#include "../../cppModels/include/MainPageModel.h"
#include "Authorization_engine.h"
#include <QEventLoop>
#include "../../RestRequestManager/include/RestRequestManagerWithoutAuth.h"
#include "../../RestRequestManager/include/RestRequestManagerWithAuth.h"
#include<unistd.h>
#include <map>

class Authorization_engine;

class User_data_handler: public QObject
{
    /*
     * This class provides store user data such as class Auth_user_data into storage
    */
    Q_OBJECT
public:
    User_data_handler(QSharedPointer<QNetworkAccessManager> manager, Authorization_engine* ptr);
    void Receive_user_data(const QJsonDocument& JSON_payload);
    void store_data(const ns_data::Auth_user_data& data);
    QSharedPointer<MainPageModel> getModel_ptr() const;
    std::map<std::string, std::string> get_refresh_tokens();
    int count_of_characters();
signals:
    void pushSecondPage();
    void test();

private:
    QSharedPointer<QNetworkAccessManager> manager;
    QScopedPointer<QSettings> storage;
    QSharedPointer<MainPageModel> model_ptr;
    void fill_data_for_MainPageModelData();
    std::vector<MainPageModelData> m_data; // data for MainPageModel model
    std::vector<std::string> ids;
    Authorization_engine* ptr;
    Synch_GET_request_in_loop_whithout_auth* synch_GET;
protected slots:
    void receive_data_urls(std::vector<std::string> data);
};

