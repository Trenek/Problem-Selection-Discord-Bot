#define _CRT_SECURE_NO_WARNINGS

#include "query.hpp"

void UPDATE(int tura, const char* name, int ID, int hour, int minute) {
    char SQLQuery[1024];

#ifdef TEST
    hour = 0;
    minute = 0;
#undef FINISH
#define FINISH 23
#endif

    sprintf(SQLQuery, "IF (CONVERT (TIME, GETDATE()) BETWEEN '%i:%i0:00' AND '%i:00:00') BEGIN \
                            BEGIN TRANSACTION \
                                UPDATE [MatematykaDyskretna].dbo.[Zadania] SET [Wybraniec] = '%s', [Tura] = '%i' WHERE [ID] = %i AND [Wybraniec] is NULL \
                                IF @@ROWCOUNT = 1 BEGIN \
                                    UPDATE [MatematykaDyskretna].dbo.[Zadania] SET [Wybraniec] = NULL, [Tura] = NULL WHERE [Wybraniec] = '%s' AND [Tura] = '%i' AND [ID] <> %i \
                                    UPDATE [MatematykaDyskretna].dbo.[DataBase] SET [Updated] = 1 \
                                END \
                            COMMIT TRANSACTION \
                        END", hour, minute, FINISH, name, tura, ID, name, tura, ID);

    QUERY(SQLQuery);
}