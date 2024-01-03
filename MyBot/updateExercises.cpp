#define _CRT_SECURE_NO_WARNINGS

#include "query.hpp"

void UPDATE(const char* wybraniec, int tura, int ID) {
    char SQLQuery[1024];

    sprintf(SQLQuery, "EXECUTE [UpdateExercises] %s, '%i', %i;", wybraniec, tura, ID);

    QUERY(SQLQuery);
}