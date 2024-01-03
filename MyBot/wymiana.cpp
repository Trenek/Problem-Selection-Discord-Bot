#include <dpp/dpp.h>
#include <dpp/unicode_emoji.h>

#include "sqlQueries.hpp"

void wymiana(const dpp::slashcommand_t& event) {
    dpp::message message;

    message.set_content(showMarket());

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