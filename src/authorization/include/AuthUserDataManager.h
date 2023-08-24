#pragma once

#include <QJsonDocument>
#include <QObject>
#include <QEventLoop>
#include<unistd.h>
#include <map>
#include "DataStorage.h"



class AuthUserDataManager: public QObject
{
    /*
     * This class provides store and managemenet user data such as class Auth_user_data into storage
    */
    Q_OBJECT
public:
    AuthUserDataManager();
    void storeJsonPayload(const QJsonDocument& JSON_payload);
    std::map<std::string, std::string> getMapIdRefreshToken() const;
    int countOfCharacters() const;

signals:
    void pushSecondPage();
    void test();

private:
    DataStorage storage_;


/*
protected slots:
    void receive_data_urls(std::vector<std::string> data);
*/
};

