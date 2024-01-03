#define _CRT_SECURE_NO_WARNINGS

#include <dpp/dpp.h>

#include "sqlQueries.hpp"

void updateTaskset(const dpp::slashcommand_t& event) {
    char buffor[500];
    int tury = (int)std::get<int64_t>(event.get_parameter("liczba"));

    event.reply(dpp::message("Zaktualizowano").set_flags(dpp::m_ephemeral));

    sprintf(buffor, "EXECUTE [UpdateRoundQuantity] %i", tury);

    QUERY(buffor);
}