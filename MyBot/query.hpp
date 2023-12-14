#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>

#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

#include "define.hpp"

std::string QUERY(const char* query, std::string(*function)(SQLHANDLE) = 0);
bool QUERY(const char* query, long long int* one, long long int* two, bool(*function)(SQLHANDLE, long long int*, long long int*));