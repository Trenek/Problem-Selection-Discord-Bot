#include <dpp/dpp.h>
#include <chrono>

#include "sqlQueries.hpp"

void updater() {
    long long int messageID = 0;
    long long int channelID = 0;

    extern dpp::cluster* bot;
    extern bool update;

    using namespace std::chrono_literals;

    while (true) {
        if (update) {
            update = false;

            if (SHOW_MESSAGE(&messageID, &channelID)) {
                bot->message_edit(bot->message_get_sync(messageID, channelID).set_content(SHOW()));
            }
        }

        std::this_thread::sleep_for(2s);
    }
}