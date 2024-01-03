#define _CRT_SECURE_NO_WARNINGS

#include "query.hpp"

std::string SHOW(SQLHANDLE SQLStatementHandle) {
    int ID = 0;
    int nr = 0;
    char podpunkt[2];
    char wybraniec[512];
    char tura[2];
    char buffor[4096];

    sprintf(buffor, "`+----+-----+---+----------------+\n");
    sprintf(buffor, "%s| ID | Nr  | T | Wybraniec      |\n", buffor);
    sprintf(buffor, "%s+----+-----+---+----------------+", buffor);

    while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
        *podpunkt = ' ';
        *tura = ' ';
        *wybraniec = ' ';
        *(wybraniec + 1) = 0;

        SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &ID, sizeof(ID), NULL);
        SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &nr, sizeof(nr), NULL);
        SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &podpunkt, sizeof(podpunkt), NULL);
        SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &wybraniec, sizeof(wybraniec), NULL);
        SQLGetData(SQLStatementHandle, 5, SQL_C_DEFAULT, &tura, sizeof(tura), NULL);

        sprintf(buffor, "%s\n| %2i | %2i%c | %c | %-14.14s |", buffor, ID, nr, *podpunkt, *tura, wybraniec);

    }
    sprintf(buffor, "%s\n+----+-----+---+----------------+`", buffor);

    return buffor;
}

std::string SHOW() {
    return QUERY("EXECUTE [ShowTasks]", SHOW);
}
