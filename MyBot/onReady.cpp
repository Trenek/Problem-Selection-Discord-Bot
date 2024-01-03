#include <dpp/dpp.h>

#include "define.hpp"

void onReady(const dpp::ready_t& event) {
	extern dpp::cluster* bot;

	if (dpp::run_once<struct register_bot_commands>()) {
		std::vector<dpp::slashcommand> commands;

		commands.push_back(dpp::slashcommand("show_tasks", "objaw zadania", bot->me.id));
		commands.push_back(dpp::slashcommand("update_tasks", "objaw zadania", bot->me.id));
		commands.push_back(dpp::slashcommand("show_rounds", "objaw zadania", bot->me.id));
		commands.push_back(dpp::slashcommand("update_round", "ustaw ture", bot->me.id));
		commands.back().
			add_option(dpp::command_option(dpp::co_integer, "nr", "Wybierz nr tury", true)).
			add_option(dpp::command_option(dpp::co_string, "emoji", "Wybierz emoji (wpisz kodowanie w UTF-8, np. F09F92A9)", true)).
			add_option(
				dpp::command_option(dpp::co_integer, "kolor", "Wybierz kolor", true).
				add_choice(dpp::command_option_choice("niebieski", 1)).
				add_choice(dpp::command_option_choice("szary", 2)).
				add_choice(dpp::command_option_choice("zielony", 3)).
				add_choice(dpp::command_option_choice("czerwony", 4))
			).
			add_option(dpp::command_option(dpp::co_string, "start", "Godzina Startowa (Format jak TIME w T-SQL)", true)).
			add_option(dpp::command_option(dpp::co_string, "finisz", "Godzina Finiszowa (Format jak TIME w T-SQL)", true));
		commands.push_back(dpp::slashcommand("prezapisy", "prezapisy", bot->me.id));
		commands.push_back(dpp::slashcommand("get_everybody", "daj wszystkich", bot->me.id));
		commands.push_back(dpp::slashcommand("show_tasksets", "Pokazuje twoje bazy zadanek", bot->me.id));
		commands.push_back(dpp::slashcommand("update_taskset", "ustaw liczbe tur", bot->me.id));
		commands.back().
			add_option(
				dpp::command_option(dpp::co_integer, "liczba", "Wybierz liczbe tur", true).
				set_min_value(0).
				set_max_value(20)
			);
		commands.push_back(dpp::slashcommand("task_exchange", "system wymiany", bot->me.id));

#ifdef TEST
		bot->set_presence(dpp::presence(dpp::ps_idle, dpp::at_game, "Testowanie"));
#else
		bot->set_presence(dpp::presence(dpp::ps_online, dpp::at_game, "Zapisy B)"));
#endif

		bot->global_bulk_command_create(commands);
	}
}