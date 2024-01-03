#define _CRT_SECURE_NO_WARNINGS

#include "query.hpp"

void freeTask(const char* DiscordID, int IDZadania) {
    char SQLQuery[1024];

    sprintf(SQLQuery, "EXECUTE [FreeTask] %s, %i", DiscordID, IDZadania);

    QUERY(SQLQuery);
}