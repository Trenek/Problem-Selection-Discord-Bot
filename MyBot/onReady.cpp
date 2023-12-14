#include <dpp/dpp.h>

#include "define.hpp"

void onReady(const dpp::ready_t& event) {
	extern dpp::cluster* bot;

	if (dpp::run_once<struct register_bot_commands>()) {
		std::vector<dpp::slashcommand> commands;

		commands.push_back(dpp::slashcommand("show", "objaw zadania", bot->me.id));
		commands.push_back(dpp::slashcommand("prezapisy", "prezapisy", bot->me.id));
		commands.push_back(dpp::slashcommand("wszyscy", "daj wszystkich", bot->me.id));
		//		commands.push_back(dpp::slashcommand("wymiana", "system wymiany", bot->me.id));

#ifdef TEST
		bot->set_presence(dpp::presence(dpp::ps_idle, dpp::at_game, "Testowanie"));
#else
		bot->set_presence(dpp::presence(dpp::ps_online, dpp::at_game, "Zapisy B)"));
#endif

		bot->global_bulk_command_create(commands);
	}
}