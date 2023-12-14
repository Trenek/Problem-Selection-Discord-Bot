#define _CRT_SECURE_NO_WARNINGS

#include "query.hpp"

void INSERT_MEMBERS(const char name[], const char id[]) {
    char SQLQuery[1024];

    sprintf(SQLQuery, "UPDATE [Wybraniec] SET [Status] = NULL WHERE [DiscordID] = '%s'\
                        IF (@@ROWCOUNT = 0) INSERT INTO [Wybraniec] ([DiscordID], [Nick]) VALUES ('%s', '%s') \
                        ", id, id, name);
    QUERY(SQLQuery);
}
