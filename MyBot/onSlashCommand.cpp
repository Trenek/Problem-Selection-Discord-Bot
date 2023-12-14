#include <dpp/dpp.h>
#include <dpp/unicode_emoji.h>

#include "sqlQueries.hpp"

bool ifIsNot(const char name[]) {
    bool result = true;

    if (strcmp(name, "155149108183695360") == 0) {
        result = false;
    }
    else if (strcmp(name, "804741883388887120") == 0) {
        result = false;
    }
    else if (strcmp(name, "1171151634932441101") == 0) {
        result = false;
    }
    else if (strcmp(name, "632253018439417856") == 0) {
        result = false;
    }
    else if (strcmp(name, "738549305404555316") == 0) {
        result = false;
    }
    else if (strcmp(name, "377151958575742978") == 0) {
        result = false;
    }

    return result;
}

void onSlashCommand(const dpp::slashcommand_t& event) {
    std::string operation = event.command.get_command_name();
    std::string emoji[] = { dpp::unicode_emoji::raccoon,
                            dpp::unicode_emoji::christmas_tree,
                            dpp::unicode_emoji::duck,
                            dpp::unicode_emoji::robot,
                            dpp::unicode_emoji::crossed_swords };
    int colour[] = { 2, 3, 1, 2, 3, 1 };
    int i = 0;
    char label[] = "Tura 1 (od 12:00 do 17:00)";
    char id[] = "myid1";

    extern dpp::cluster* bot;

    if (operation == "show") {
        dpp::message message(SHOW());
        message.add_component(dpp::component());

        while (i < TURY) {
            message.components.at(0).add_component(
                dpp::component().
                set_label(label).
                set_type(dpp::cot_button).
                set_emoji(emoji[i]).
                set_style((dpp::component_style)(colour[i])).
                set_id(id)
            );
            i += 1;
            id[4] += 1;
            label[5] += 1;
            label[14] += 1;
        }

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

        message.set_channel_id(event.command.channel_id);
        bot->message_create(message);

        UPDATE_MESSAGE(bot->channel_get_sync(event.command.channel_id).last_message_id.str().c_str(), event.command.channel_id.str().c_str());

        event.reply(dpp::message("Pokazano B)").set_flags(dpp::m_ephemeral));
    }
    else if (operation == "prezapisy") {
        dpp::message message("Zareaguj emotk\xC4\x85 :pray: aby uczestniczy\xC4\x87 w kolejnych zapisach");

        message.add_component(dpp::component().
            add_component(
                dpp::component().
                set_label("Zlicz").
                set_type(dpp::cot_button).
                set_emoji(dpp::unicode_emoji::church).
                set_style(dpp::cos_success).
#ifdef TEST
                set_id("countIDTEST")
#else // TEST
                set_id("countID")
#endif
            )
        );

        event.reply(message);
    }
    else if (operation == "wszyscy") {
        event.thinking();
        dpp::guild_member_map mapp = bot->guild_get_members_sync(event.command.guild_id, 1000, 0);
        int i = 0;

        QUERY("UPDATE [Wybraniec] SET [Status] = 'S' \
                UPDATE [MatematykaDyskretna].dbo.[Wybraniec] \
                SET[Status] = 'Z' \
                FROM[Zadania] RIGHT OUTER JOIN[Wybraniec] \
                ON[Zadania].[Wybraniec] = [Wybraniec].[DiscordID] \
                WHERE[Zadania].[Tura] = 'Z'");

        for (std::pair<const dpp::snowflake, dpp::guild_member> user : mapp) {
            if (ifIsNot(user.second.get_user()->id.str().c_str())) {
                INSERT_MEMBERS(user.second.get_user()->username.c_str(), user.second.get_user()->id.str().c_str());
            }
        }
        QUERY("DELETE FROM [Wybraniec] WHERE [Status] = 'S'; \
                WITH NewSequence AS ( \
                SELECT ID, ROW_NUMBER() OVER(ORDER BY ID) as ID_New \
                FROM[MatematykaDyskretna].dbo.[Wybraniec] \
                ) \
                UPDATE NewSequence SET ID = ID_New; ");

        event.edit_original_response(SHOW_MEMBERS());
    }
    /**
    else if (operation == "wymiana") {
        dpp::message message(showMarket());

        message.add_component(
            dpp::component().
            add_component(dpp::component().
                set_label("Zaproponuj").
                set_type(dpp::cot_button).
                set_emoji(dpp::unicode_emoji::palm_down_hand).
                set_style(dpp::cos_success).
                set_id("propositionID")
            )
        ).add_component(
            dpp::component().
            add_component(dpp::component().
                set_label("Wycofaj").
                set_type(dpp::cot_button).
                set_emoji(dpp::unicode_emoji::palm_up_hand).
                set_style(dpp::cos_danger).
                set_id("backoutpropositionID")
            )
        );

        event.reply(message);
    }
    /**/
}
