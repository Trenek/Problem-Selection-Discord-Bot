#include <dpp/dpp.h>

#include "onSlashCommand.hpp"
#include "sqlQueries.hpp"

void onSlashCommand(const dpp::slashcommand_t& event) {
    std::string operation = event.command.get_command_name();
    void (*function)(const dpp::slashcommand_t&) = [](const dpp::slashcommand_t& event){};

    if (operation == "show_tasksets") {
        function = showTasksets;
    }
    else {
        if (login(event.command.get_issuing_user().id.str().c_str())) {
            if (operation == "show_tasks") {
                function = show;
            }
            else if (operation == "update_tasks") {

            }
            else if (operation == "show_rounds") {
                function = showRounds;
            }
            else if (operation == "update_round") {
                function = updateRound;
            }
            else if (operation == "prezapisy") {
                function = prezapisy;
            }
            else if (operation == "get_everybody") {
                function = wszyscy;
            }
            else if (operation == "update_taskset") {
                function = updateTaskset;
            }
            else if (operation == "task_exchange") {
                function = wymiana;
            }
        }
        else {
            event.reply(dpp::message("Nie wolno Ci :(").set_flags(dpp::m_ephemeral));
        }
    }

    function(event);
}
