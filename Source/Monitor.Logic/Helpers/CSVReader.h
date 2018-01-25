#pragma once

#include "../Externals.h"

/* Class: CSVReader
   CSVReader is a helper class which returns requested data from a .csv file.
*/
class CSVReader
{
private:
	/*Variable: m_file*/
	ifstream* m_file;
public:
	/* Function: CSVReader
	Initializes a new instance of the CSVReader class

	Parameters:

	p_file - file path
	*/
	CSVReader(string p_file);

	/* Function: ~CSVReader
	Finalizes an instance of the CSVReader*/
	~CSVReader();

	/* Function: readLine
	   Read the next line in the file.

	  Returns:
	  strings vector, each cell reflects to the actual column.
	*/
	vector<string> readLine() const;
};
