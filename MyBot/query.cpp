#include <cstdio>

#include "query.hpp"

void showSQLError(unsigned int handleType, const SQLHANDLE& handle) {
    SQLCHAR SQLState[1024];
    SQLCHAR message[1024];
    if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL)) {
        printf("SQL driver message: %s\nSQL state: %s.\n", message, SQLState);
    }
}

bool setupSQL(SQLHANDLE* SQLEnvHandle, SQLHANDLE* SQLConnectionHandle, SQLHANDLE* SQLStatementHandle, const char* query) {
    bool result = true;
    SQLCHAR retConString[1024];

    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, SQLEnvHandle)) {
        result = false;
    }
    else if (SQL_SUCCESS != SQLSetEnvAttr(*SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) {
        result = false;
    }
    else if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, *SQLEnvHandle, SQLConnectionHandle)) {
        result = false;
    }
    else if (SQL_SUCCESS != SQLSetConnectAttr(*SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0)) {
        result = false;
    }
    else switch (SQLDriverConnect(*SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=MatematykaDyskretna; UID=DiscordBot; PWD=BotPass", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
        case SQL_NO_DATA_FOUND:
        case SQL_INVALID_HANDLE:
        case SQL_ERROR:
            showSQLError(SQL_HANDLE_DBC, *SQLConnectionHandle);
            result = false;
            break;
        default:
            if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, *SQLConnectionHandle, SQLStatementHandle)) {
                result = false;
            }
            else switch (SQLExecDirect(*SQLStatementHandle, (SQLCHAR*)query, SQL_NTS)) {
                case SQL_SUCCESS:
                case SQL_SUCCESS_WITH_INFO:
                    break;
                default:
                    showSQLError(SQL_HANDLE_STMT, *SQLStatementHandle);
                    result = false;
            }
    }

    return result;
}

void clearSQL(SQLHANDLE* SQLEnvHandle, SQLHANDLE* SQLConnectionHandle, SQLHANDLE* SQLStatementHandle) {
    SQLFreeHandle(SQL_HANDLE_STMT, *SQLStatementHandle);
    SQLDisconnect(*SQLConnectionHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, *SQLConnectionHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, *SQLEnvHandle);
}

std::string QUERY(const char* query, std::string(*function)(SQLHANDLE)) {
    SQLHANDLE SQLEnvHandle = NULL;
    SQLHANDLE SQLConnectionHandle = NULL;
    SQLHANDLE SQLStatementHandle = NULL;
    std::string result = "-";

    if (setupSQL(&SQLEnvHandle, &SQLConnectionHandle, &SQLStatementHandle, query)) {
        if (function != 0) {
            result = function(SQLStatementHandle);
        }
    }

    clearSQL(&SQLEnvHandle, &SQLConnectionHandle, &SQLStatementHandle);

    return result;
}

int QUERY(const char* query, int(*function)(SQLHANDLE)) {
    SQLHANDLE SQLEnvHandle = NULL;
    SQLHANDLE SQLConnectionHandle = NULL;
    SQLHANDLE SQLStatementHandle = NULL;
    int result = 0;

    if (setupSQL(&SQLEnvHandle, &SQLConnectionHandle, &SQLStatementHandle, query)) {
        if (function != 0) {
            result = function(SQLStatementHandle);
        }
    }

    clearSQL(&SQLEnvHandle, &SQLConnectionHandle, &SQLStatementHandle);

    return result;
}

int QUERY(const char* query, int(*function)(SQLHANDLE, void*), void* message) {
    SQLHANDLE SQLEnvHandle = NULL;
    SQLHANDLE SQLConnectionHandle = NULL;
    SQLHANDLE SQLStatementHandle = NULL;
    int result = 0;

    if (setupSQL(&SQLEnvHandle, &SQLConnectionHandle, &SQLStatementHandle, query)) {
        if (function != 0) {
            result = function(SQLStatementHandle, message);
        }
    }

    clearSQL(&SQLEnvHandle, &SQLConnectionHandle, &SQLStatementHandle);

    return result;
}