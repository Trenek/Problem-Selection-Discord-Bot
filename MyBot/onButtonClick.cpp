#define _CRT_SECURE_NO_WARNINGS

#include <dpp/dpp.h>
#include <dpp/unicode_emoji.h>

#include "sqlQueries.hpp"

void onButtonClick(const dpp::button_click_t& event) {
    extern dpp::cluster* bot;

    if (event.custom_id == "countID") {
        if (login(event.command.get_issuing_user().id.str().c_str())) {
            event.thinking();
            dpp::message message = bot->message_get_sync(event.command.message_id, event.command.channel_id);
            dpp::user_map map = bot->message_get_reactions_sync(message, dpp::unicode_emoji::pray, 0, 0, 0);

            QUERY("EXECUTE [BeforeInsert]");
            for (std::pair<const dpp::snowflake, dpp::user> user : map) {
                INSERT_MEMBERS(user.second.id.str().c_str(), user.second.username.c_str());
            }
            QUERY("EXECUTE [AfterInsert]");
            event.edit_original_response(SHOW_MEMBERS());
        }
        else {
            event.reply(dpp::message("Nie wolno Ci :(").set_flags(dpp::m_ephemeral));
        }
    }
    else if (event.custom_id == "backoutid") {
        dpp::interaction_modal_response modal("modal_backout", "Wybierz zadanie");

        modal.add_component(
            dpp::component().
            set_label("Podaj ID").
            set_id("field_id").
            set_type(dpp::cot_text).
            set_placeholder("Tutaj wpisz ID upiornego zadania").
            set_min_length(1).
            set_max_length(2).
            set_text_style(dpp::text_short)
        );

        event.dialog(modal);
    }
    /**
    else if (event.custom_id == "propositionID") {
        dpp::interaction_modal_response modal("modal_proposition", "Wybierz zadanie");

        modal.add_component(
            dpp::component().
            set_label("Podaj ID swojego zadania").
            set_id("propositionID").
            set_type(dpp::cot_text).
            set_placeholder("Podaj ID swojego zadania, lub wpisz A").
            set_min_length(1).
            set_max_length(2).
            set_text_style(dpp::text_short)
        );
        modal.add_row();
        modal.add_component(
            dpp::component().
            set_label("Podaj ID chcianego zadania").
            set_id("backoutID").
            set_type(dpp::cot_text).
            set_placeholder("Podaj ID chcianego zadania, lub wpisz A").
            set_min_length(1).
            set_max_length(2).
            set_text_style(dpp::text_short)
        );

        event.dialog(modal);
    }
    else if (event.custom_id == "backoutpropositionID") {
        dpp::interaction_modal_response modal("modal_propositionbackout", "Wybierz zadanie");

        modal.add_component(
            dpp::component().
            set_label("Podaj ID").
            set_id("field_id").
            set_type(dpp::cot_text).
            set_placeholder("Tutaj wpisz ID upiornego zadania").
            set_min_length(1).
            set_max_length(2).
            set_text_style(dpp::text_short)
        );

        event.dialog(modal);
    }
    /**/
    else {
        char name[] = "my_modal0";
        name[8] = event.custom_id[4];

        dpp::interaction_modal_response modal(name, "Wybierz zadanie");

        modal.add_component(
            dpp::component().
            set_label("Podaj ID").
            set_id("field_id").
            set_type(dpp::cot_text).
            set_placeholder("Tutaj wpisz ID upragnionego zadania").
            set_min_length(1).
            set_max_length(2).
            set_text_style(dpp::text_short)
        );

        event.dialog(modal);
    }
}
