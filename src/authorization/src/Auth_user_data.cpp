#include "../include/Auth_user_data.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;


namespace ns_data {


void to_json(json& j, const Auth_user_data& p) {
    j = json{ {"name", p.name}, {"character_id", p.character_id},
             {"access_token", p.access_token}, {"refresh_token", p.refresh_token} };
}

void from_json(const json& j, Auth_user_data& p) {
    j.at("name").get_to(p.name);
    j.at("character_id").get_to(p.character_id);
    j.at("access_token").get_to(p.access_token);
    j.at("refresh_token").get_to(p.refresh_token);
}

}

