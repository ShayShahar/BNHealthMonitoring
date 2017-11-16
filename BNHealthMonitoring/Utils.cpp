#include "Utils.h"

//global definitions for random()
unsigned int t1 = 0;
unsigned int t2 = 0;

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
	unsigned b;

	b = t1 ^ (t1 >> 2) ^ (t1 >> 6) ^ (t1 >> 7);
	t1 = (t1 >> 1) | (~b << 31);

	b = (t2 << 1) ^ (t2 << 2) ^ (t1 << 3) ^ (t2 << 4);
	t2 = (t2 << 1) | (~b >> 31);

	return t1 ^ t2;
}
