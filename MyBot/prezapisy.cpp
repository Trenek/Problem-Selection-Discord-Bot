#include <dpp/dpp.h>
#include <dpp/unicode_emoji.h>

void prezapisy(const dpp::slashcommand_t& event) {
    dpp::message message;

    event.thinking();
    message.set_content("Zareaguj emotk\xC4\x85 :pray: aby uczestniczy\xC4\x87 w kolejnych zapisach");

    message.add_component(dpp::component().
        add_component(
            dpp::component().
            set_label("Zlicz").
            set_type(dpp::cot_button).
            set_emoji(dpp::unicode_emoji::church).
            set_style(dpp::cos_success).
            set_id("countID")
        )
    );

    event.edit_original_response(message);
}