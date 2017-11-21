#include "Utils.h"

//global definition for random()
unsigned int seed = 0;
bool initialized = false;

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

	char* newStr = new char[size + 1];

	if (newStr == nullptr)
		return nullptr;

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

unsigned int random()
{
	if (initialized == false)
	{
		char t = '1';
		seed = (unsigned int)&t;
		initialized = true;
	}

	seed = (seed * 1103515245U + 12345U) & 0x7fffffffU;
	return seed;
}
