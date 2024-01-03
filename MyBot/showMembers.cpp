#define _CRT_SECURE_NO_WARNINGS

#include "query.hpp"

std::string SHOW_MEMBERS(SQLHANDLE SQLStatementHandle) {
    int ID = 0;
    long long int DiscordID = 0;
    char wybraniec[25];
    char buffor[2048];
    char status[2];

    sprintf(buffor,   "`+----+----------------+----------------`\n");
    sprintf(buffor, "%s`| ID | %-14s | %-14s `\n", buffor, "Nick", "Wzmianka");
    sprintf(buffor, "%s`+----+----------------+----------------`", buffor);

    while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
        *status = 0;

        SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &ID, sizeof(ID), NULL);
        SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &DiscordID, sizeof(DiscordID), NULL);
        SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &wybraniec, sizeof(wybraniec), NULL);
        SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &status, sizeof(status), NULL);

        sprintf(buffor, "%s\n`| %2i | %-14.14s | `<@%lld>", buffor, ID, wybraniec, DiscordID);
    }
    sprintf(buffor, "%s\n`+----+----------------+----------------`", buffor);

    return buffor;
}

std::string SHOW_MEMBERS() {
    return QUERY("EXECUTE [ShowMembers]", SHOW_MEMBERS);
}