#include "Utils.h"

int strlength(const char* str)
{
	const char* p = str;
	int count = 0;

	while (*p != '\0')
	{
		count++;
		p++;
	}

	return count;
}

char* strcopy(const char* str)
{
	int i;
	int size = strlength(str);

	char* newStr = (char*)allocate_memory(sizeof(char)*size + 1);

	if (newStr == NULL)
		exit(1);

	for (i = 0; i < size + 1; i++)
	{
		newStr[i] = str[i];
	}

	return newStr;
}

int strcompare(char* str1, char* str2)
{
	char* p = str1;
	char* q = str2;

	for (; *q != '\0' && *p != '\0'; q++, p++)
	{
		if (*p != *q)
			return 0;
	}

	return 1;
}

void* allocate_memory(size_t size)
{
	return malloc(size);
}

void free_memory(void* var)
{
	free(var);
}

int stoint(char* str)
{
	char* p = str;
	int result = 0;

	while (*p != '\0')
	{
		if (*p < '0' || *p > '9')
			return -1;

		if (result == 0)
			result = (*p - '0');
		else
			result = result * 10 + (*p - '0');
		p++;
	}

	return result;
}