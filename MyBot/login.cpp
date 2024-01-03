#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>

#include "query.hpp"

int login(SQLHANDLE SQLStatementHandle) {
	int result = 0;

	if (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
		result = 1;
	}

	return result;
}

bool login(const char DiscordID[]) {
	char buffor[128];
	
	sprintf(buffor, "EXECUTE [Login] %s", DiscordID);

	return (QUERY(buffor, login) == 1);
}