#include "query.hpp"

/**
std::string showMarket(SQLHANDLE SQLStatementHandle) {
    int osoba = 0;
    int posiadane = 0;
    int szukane = 0;
    char buffor[4096];

    sprintf(buffor,  "`+---------+-----------+---------+\n");
    sprintf(buffor, "%s| Oferant | Oferowane | Chciane |\n", buffor);
    sprintf(buffor, "%s+---------+-----------+---------+", buffor);

    while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
        SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &osoba, sizeof(osoba), NULL);
        SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &posiadane, sizeof(posiadane), NULL);
        SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &szukane, sizeof(szukane), NULL);

        sprintf(buffor, "%s\n| %5i | %9i | %7i |", buffor, osoba, posiadane, szukane);
    }
    sprintf(buffor, "%s\n+---------+-----------+---------+`", buffor);

    return buffor;
}

std::string showMarket() {
    return QUERY(  "SELECT [Oferant], [Oferowane], [Chciane] \
                    FROM [Market]", showMarket);
}
/**/