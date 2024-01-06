#define _CRT_SECURE_NO_WARNINGS

#include <dpp/dpp.h>
#include <dpp/unicode_emoji.h>

#include "sqlQueries.hpp"

int addComponent(SQLHANDLE SQLStatementHandle, void* message) {
    int row = -1;
    int quantity = 1;
    int nrTury = 0;
    int kolor = 0;
    char emoji[64];
    char label[128];
    char id[128];
    int startH = 0;
    int startM = 0;
    int endH = 0;
    int endM = 0;
    dpp::message* Message = (dpp::message*)message;

    while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
        SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &nrTury, sizeof(nrTury), NULL);
        SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &kolor, sizeof(kolor), NULL);
        SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &emoji, sizeof(emoji), NULL);
        SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &startH, sizeof(startH), NULL);
        SQLGetData(SQLStatementHandle, 5, SQL_C_DEFAULT, &startM, sizeof(startM), NULL);
        SQLGetData(SQLStatementHandle, 6, SQL_C_DEFAULT, &endH, sizeof(endH), NULL);
        SQLGetData(SQLStatementHandle, 7, SQL_C_DEFAULT, &endM, sizeof(endM), NULL);

        sprintf(label, "Tura %i (od %02d:%02d do %02d:%02d)", nrTury, startH, startM, endH, endM);
        sprintf(id, "myid%i", nrTury);

        if (quantity % 5 == 1) {
            Message->add_component(dpp::component());
            row += 1;
        }

        Message->components.at(row).add_component(
            dpp::component().
            set_label(label).
            set_type(dpp::cot_button).
            set_emoji(emoji).
            set_style((dpp::component_style)kolor).
            set_id(id)
        );

        quantity += 1;
    }

    return 0;
}

void show(const dpp::slashcommand_t& event) {
    dpp::message message("Pokazano :>");

    extern dpp::cluster* bot;

    message.set_flags(dpp::m_ephemeral);
    message.set_channel_id(event.command.channel_id);

    event.reply(message);

    QUERY("EXECUTE [AddComponents]", addComponent, (void*)&message);

    message.set_content(SHOW());

    message.add_component(dpp::component().
        add_component(
            dpp::component().
            set_label("Wycofaj si\xC4\x99 z zadania").
            set_type(dpp::cot_button).
            set_emoji(dpp::unicode_emoji::skull).
            set_style(dpp::cos_danger).
            set_id("backoutid")
        )
    );

    bot->message_create(message);

    UPDATE_MESSAGE(bot->channel_get_sync(event.command.channel_id).last_message_id.str().c_str(), event.command.channel_id.str().c_str());
}