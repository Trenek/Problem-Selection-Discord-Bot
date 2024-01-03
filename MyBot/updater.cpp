#include <dpp/dpp.h>
#include <chrono>

#include "sqlQueries.hpp"

int SHOW_MESSAGE(SQLHANDLE SQLStatementHandle, stack** base) {
    stack* first = NULL;

    while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
        first = new stack;

        SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &first->messageID, sizeof(first->messageID), NULL);
        SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &first->channelID, sizeof(first->channelID), NULL);
        first->next = *base;

        *base = first;
    }

    return 0;
}

void updater() {
    stack* base = NULL;
    stack* help = NULL;

    extern bool update;
    extern dpp::cluster* bot;

    using namespace std::chrono_literals;

    while (true) {
        if (update) {
            update = false;

            QUERY("EXECUTE [Updater]", SHOW_MESSAGE, &base);

            while (base != NULL) {
                bot->message_edit(bot->message_get_sync(base->messageID, base->channelID).set_content(SHOW()));

                help = base;
                base = base->next;
                delete help;
            }

        }

        std::this_thread::sleep_for(2s);
    }
}