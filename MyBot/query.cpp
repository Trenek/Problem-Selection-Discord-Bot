#include "query.hpp"

void showSQLError(unsigned int handleType, const SQLHANDLE& handle) {
    SQLCHAR SQLState[1024];
    SQLCHAR message[1024];
    if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL)) {
        std::cout << "SQL driver message: " << message << "\nSQL state: " << SQLState << "." << std::endl;
    }
}

std::string QUERY(const char* query, std::string(*function)(SQLHANDLE)) {
    SQLHANDLE SQLEnvHandle = NULL;
    SQLHANDLE SQLConnectionHandle = NULL;
    SQLHANDLE SQLStatementHandle = NULL;
    SQLRETURN retCode = 0;
    std::string result = "-";

    do {
        if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle)) {
            break;
        }

        if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) {
            break;
        }

        if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle)) {
            break;
        }

        if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0)) {
            break;
        }

        SQLCHAR retConString[1024];
        switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=MatematykaDyskretna; UID=DiscordBot; PWD=BotPass", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
            case SQL_SUCCESS:
                break;
            case SQL_SUCCESS_WITH_INFO:
                break;
            case SQL_NO_DATA_FOUND:
                showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
                retCode = -1;
                break;
            case SQL_INVALID_HANDLE:
                showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
                retCode = -1;
                break;
            case SQL_ERROR:
                showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
                retCode = -1;
                break;
            default:
                break;
        }

        if (retCode == -1) {
            break;
        }

        if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle)) {
            break;
        }

        switch (SQLExecDirect(SQLStatementHandle, (SQLCHAR*)query, SQL_NTS)) {
            case SQL_SUCCESS:
            case SQL_SUCCESS_WITH_INFO:
                if (function != 0) {
                    result = function(SQLStatementHandle);
                }
                break;
            default:
                showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
                break;
        }
    } while (false);

    SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
    SQLDisconnect(SQLConnectionHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);

    return result;
}

bool QUERY(const char* query, long long int* one, long long int* two, bool(*function)(SQLHANDLE, long long int*, long long int*)) {
    SQLHANDLE SQLEnvHandle = NULL;
    SQLHANDLE SQLConnectionHandle = NULL;
    SQLHANDLE SQLStatementHandle = NULL;
    SQLRETURN retCode = 0;
    bool result = false;

    do {
        if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle)) {
            break;
        }

        if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) {
            break;
        }

        if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle)) {
            break;
        }

        if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0)) {
            break;
        }

        SQLCHAR retConString[1024];
        switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=MatematykaDyskretna; UID=DiscordBot; PWD=BotPass", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
            case SQL_SUCCESS:
                break;
            case SQL_SUCCESS_WITH_INFO:
                break;
            case SQL_NO_DATA_FOUND:
                showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
                retCode = -1;
                break;
            case SQL_INVALID_HANDLE:
                showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
                retCode = -1;
                break;
            case SQL_ERROR:
                showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
                retCode = -1;
                break;
            default:
                break;
        }

        if (retCode == -1) {
            break;
        }

        if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle)) {
            break;
        }

        switch (SQLExecDirect(SQLStatementHandle, (SQLCHAR*)query, SQL_NTS)) {
            case SQL_SUCCESS:
            case SQL_SUCCESS_WITH_INFO:
                if (function != 0) {
                    result = function(SQLStatementHandle, one, two);
                }
                break;
            default:
                showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
                break;
        }
    } while (false);

    SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
    SQLDisconnect(SQLConnectionHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);

    return result;
}