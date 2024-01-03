#define _CRT_SECURE_NO_WARNINGS

#include <dpp/dpp.h>

#include "sqlQueries.hpp"

void updateRound(const dpp::slashcommand_t& event) {
    char buffor[500];
    std::string emoji = std::get<std::string>(event.get_parameter("emoji"));
    int id = (int)std::get<int64_t>(event.get_parameter("nr"));
    int kolor = (int)std::get<int64_t>(event.get_parameter("kolor"));
    std::string start = std::get<std::string>(event.get_parameter("start"));
    std::string finisz = std::get<std::string>(event.get_parameter("finisz"));

    event.reply(dpp::message("Zaktualizowano").set_flags(dpp::m_ephemeral));

    sprintf(buffor, "EXECUTE [UpdateRound] '%s', %i, '%s', '%s', %i", emoji.c_str(), kolor, start.c_str(), finisz.c_str(), id);
    QUERY(buffor);
}