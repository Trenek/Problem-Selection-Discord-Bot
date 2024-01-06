#define _CRT_SECURE_NO_WARNINGS

#include <dpp/dpp.h>

#include "query.hpp"

std::string showRounds(SQLHANDLE SQLStatementHandle) {
    int nrTury = 0;
    int kolor = 0;
    char emoji[64];
    int startM = 0;
    int startH = 0;
    int endM = 0;
    int endH = 0;
    char buffor[2048];
    std::string color;

    sprintf(buffor,  "`+----+-------+--------+-------+-------+\n");
    sprintf(buffor, "%s| Nr | Start | Koniec | Kolor | Emoji |\n", buffor);
    sprintf(buffor, "%s+----+-------+--------+-------+-------+\n", buffor);

    while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
        SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &nrTury, sizeof(nrTury), NULL);
        SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &kolor, sizeof(kolor), NULL);
        SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &emoji, sizeof(emoji), NULL);
        SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &startH, sizeof(startH), NULL);
        SQLGetData(SQLStatementHandle, 5, SQL_C_DEFAULT, &startM, sizeof(startM), NULL);
        SQLGetData(SQLStatementHandle, 6, SQL_C_DEFAULT, &endH, sizeof(endH), NULL);
        SQLGetData(SQLStatementHandle, 7, SQL_C_DEFAULT, &endM, sizeof(endM), NULL);

        switch (kolor) {
            case 1:
                color = "\xF0\x9F\x92\x99\x00";
                break;
            case 2:
                color = "\xF0\x9F\xA4\x8D\x00";
                break;
            case 3:
                color = "\xF0\x9F\x92\x9A\x00";
                break;
            case 4:
                color = "\xE2\x9D\xA4\xEF\xB8\x8F\x00";
                break;
        }
        sprintf(buffor, "%s| %2i | %02i:%02i | %02i:%02i  | %s    | %s  \n", buffor, nrTury, startH, startM, endH, endM, color.c_str(), emoji);
    }
    sprintf(buffor, "%s+----+-------+--------+-------+-------+`", buffor);

    return buffor;
}

void showRounds(const dpp::slashcommand_t& event) {
    event.thinking();

    event.edit_original_response(QUERY("EXECUTE [ShowRounds]", showRounds));
}