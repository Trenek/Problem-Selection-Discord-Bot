#define _CRT_SECURE_NO_WARNINGS

#include <dpp/dpp.h>

#include "query.hpp"

std::string myTaskSets(SQLHANDLE SQLStatementHandle) {
    char buffor[2048];
    char nazwa[17];
    int liczbaTur = 0;

    sprintf(buffor, "`+------------------+------------+\n");
    sprintf(buffor, "%s| Nazwa            | Liczba Tur |\n", buffor);
    sprintf(buffor, "%s+------------------+------------+\n", buffor);

    while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
        SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &nazwa, sizeof(nazwa), NULL);
        SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &liczbaTur, sizeof(liczbaTur), NULL);

        sprintf(buffor, "%s| %-16.16s | %-10i |\n", buffor, nazwa, liczbaTur);
    }
    sprintf(buffor, "%s+------------------+------------+`", buffor);

    return buffor;
}

void showTasksets(const dpp::slashcommand_t& event) {
    char buffor[500];

    event.thinking();

    sprintf(buffor, "EXECUTE [ShowMyTaskSets] %s", event.command.get_issuing_user().id.str().c_str());

    event.edit_original_response(QUERY(buffor, myTaskSets));
}