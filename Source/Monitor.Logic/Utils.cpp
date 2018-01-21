#include "Utils.h"

int Utils::strlength(const char* str)
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

char* Utils::strcopy(const char* str)
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

bool Utils::strcompare(char* str1, char* str2)
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

int Utils::stoint(char* str)
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

unsigned int Utils::random()
{
	if (m_initialized == false)
	{
		char t = '1';
		m_seed = (unsigned int)&t;
		m_initialized = true;
	}

	m_seed = (m_seed * 1103515245U + 12345U) & 0x7fffffffU;
	return m_seed;
}
