#ifndef AUTH_USER_DATA_H
#define AUTH_USER_DATA_H
#include <QString>

struct Auth_user_data
{
    Auth_user_data() = default;
    const QString name;
    const QString character_id;
    QString access_token;
    QString refresh_token;
};

#endif // AUTH_USER_DATA_H
