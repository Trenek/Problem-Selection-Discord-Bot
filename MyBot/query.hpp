#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCKAPI_

#include <string>
#include <WTypesbase.h>
#include <dpp\message.h>

#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

#include "define.hpp"
#include "stack.hpp"

void showSQLError(unsigned int handleType, const SQLHANDLE& handle);
std::string QUERY(const char* query, std::string(*function)(SQLHANDLE));
int QUERY(const char* query, int(*function)(SQLHANDLE) = 0);
int QUERY(const char* query, int(*function)(SQLHANDLE, dpp::message*), dpp::message* message);
int QUERY(const char* query, int(*function)(SQLHANDLE, stack**), stack** message);