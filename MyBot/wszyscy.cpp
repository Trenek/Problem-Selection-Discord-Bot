#include <dpp/dpp.h>
#include <algorithm>

#include "sqlQueries.hpp"

void wszyscy(const dpp::slashcommand_t& event) {
    extern dpp::cluster* bot;

    event.thinking();

    dpp::guild_member_map mapp = bot->guild_get_members_sync(event.command.guild_id, 1000, 0);

    QUERY("EXECUTE [BeforeInsert]");
    for (std::pair<const dpp::snowflake, dpp::guild_member> user : mapp) {
        dpp::user interUser = *user.second.get_user();
        std::vector<dpp::snowflake> roles = user.second.get_roles();
        
        if (interUser.is_bot() == false) {
            if (std::find(roles.begin(), roles.end(), 1180455098791506022) != roles.end()) {
                INSERT_MEMBERS(interUser.id.str().c_str(), interUser.username.c_str());
            }
        }
    }
    QUERY("EXECUTE [AfterInsert]");

    event.edit_original_response(SHOW_MEMBERS());
}