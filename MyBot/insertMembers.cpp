#define _CRT_SECURE_NO_WARNINGS

#include "query.hpp"

void INSERT_MEMBERS(const char DiscordID[], const char Nick[]) {
    char SQLQuery[1024];

    sprintf(SQLQuery, "EXECUTE [InsertMembers] %s, '%s'", DiscordID, Nick);

    QUERY(SQLQuery);
}
