#ifndef AUTH_USER_DATA_H
#define AUTH_USER_DATA_H
#include <QString>
#include <nlohmann/json.hpp>
#include <string>
using json = nlohmann::json;

namespace ns_data {


struct Auth_user_data
{
    Auth_user_data() = default;
    std::string name;
    std::string character_id;
    std::string access_token;
    std::string refresh_token;
};

void to_json(nlohmann::json& j, const Auth_user_data& p);

void from_json(const nlohmann::json& j, Auth_user_data& p);

}
#endif // AUTH_USER_DATA_H
