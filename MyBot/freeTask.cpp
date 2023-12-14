#define _CRT_SECURE_NO_WARNINGS

#include "query.hpp"

void freeTask(const char* name, int id) {
    char SQLQuery[1024];

    sprintf(SQLQuery, "UPDATE [Zadania] SET [Wybraniec] = NULL, [Tura] = NULL WHERE [Wybraniec] = '%s' AND [ID] = %i \
                        UPDATE [DataBase] SET [Updated] = 1", name, id);

    QUERY(SQLQuery);
}