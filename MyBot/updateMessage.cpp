#define _CRT_SECURE_NO_WARNINGS

#include "query.hpp"

void UPDATE_MESSAGE(const char* messageID, const char* channelID) {
    char SQLQuery[1024];

    sprintf(SQLQuery, "EXECUTE [UpdateMessage] %s, %s", messageID, channelID);

    QUERY(SQLQuery);
}