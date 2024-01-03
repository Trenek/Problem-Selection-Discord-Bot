#include <dpp/dpp.h>
#include <thread>

#include "MyBot.h"
#include "discordBot.hpp"
#include "updater.hpp"

bool update = false;
dpp::cluster* bot;

int main() {
    std::thread updateServer(updater);
    dpp::cluster bot(BOT_TOKEN, dpp::i_guilds |
                                dpp::i_guild_members |
                                dpp::i_guild_messages |
                                dpp::i_guild_message_reactions
    );
    ::bot = &bot;

    bot.on_log(dpp::utility::cout_logger());

    bot.on_form_submit(onFormSubmit);
    bot.on_button_click(onButtonClick);
    bot.on_slashcommand(onSlashCommand);
    bot.on_ready(onReady);

    bot.start(dpp::st_wait);

    return 0;
}
