#pragma once

#include "Externals.h"

class CSVReader
{
private:
	ifstream* m_file;
public:
	CSVReader(string p_file);
	~CSVReader();
	vector<string> readLine() const;
};
