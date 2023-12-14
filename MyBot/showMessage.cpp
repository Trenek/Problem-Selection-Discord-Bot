#include "query.hpp"

bool SHOW_MESSAGE(SQLHANDLE SQLStatementHandle, long long int* messageID, long long int* channelID) {
    bool updated = false;

    if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
        SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, messageID, sizeof(*messageID), NULL);
        SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, channelID, sizeof(*channelID), NULL);
        SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &updated, sizeof(updated), NULL);
    }

    return updated;
}

bool SHOW_MESSAGE(long long int* messageID, long long int* channelID) {
    return QUERY("SELECT [MessageID], [ChannelID], [Updated] FROM [DataBase] \
                    UPDATE [MatematykaDyskretna].dbo.[DataBase] SET [Updated] = 0", messageID, channelID, SHOW_MESSAGE);
}