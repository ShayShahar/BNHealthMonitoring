#pragma once

#include <cstdlib>

int strlength(const char* str);
char* strcopy(const char* str);
int strcompare(char* str1, char* str2);
void* allocate_memory(size_t size);
void free_memory(void* var);
int stoint(char* str);