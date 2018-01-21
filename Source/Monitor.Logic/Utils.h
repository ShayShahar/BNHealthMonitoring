#pragma once

static unsigned int m_seed = 0;
static bool m_initialized = false;

class Utils
{
public:
	Utils()
	{
	}

	~Utils()
	{
	}

	static int strlength(const char* str);
	static char* strcopy(const char* str);
	static bool strcompare(char* str1, char* str2);
	static int stoint(char* str);
	static unsigned int random();
};