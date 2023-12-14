#include <dpp/dpp.h>

#include "sqlQueries.hpp"

void onFormSubmit(const dpp::form_submit_t& event) {
    extern bool update;

    if (event.custom_id == "modal_backout") {
        event.reply();

        freeTask(event.command.get_issuing_user().id.str().c_str(), atoi(std::get<std::string>(event.components[0].components[0].value).c_str()));
        update = true;
    }
    /**
    else if (event.custom_id == "modal_proposition") {
       // propositionID, backoutID
       // QUERY("");
    }
    else if (event.custom_id == "backoutpropositionID") {

    }
    /**/
    else {
        int number = event.custom_id[8] - '1';

        event.reply();

        UPDATE(number + 1, event.command.get_issuing_user().id.str().c_str(), atoi(std::get<std::string>(event.components[0].components[0].value).c_str()), 12, number);
        update = true;
    }
}
