#include  "CSVReader.h"

CSVReader::CSVReader(string p_file)
{
	m_file = new ifstream(p_file);
	
	string value;
	getline(*m_file, value); //read header
}

CSVReader::~CSVReader()
{
	m_file->close();
	delete m_file;
}

vector<string> CSVReader::readLine() const
{
	vector<string> value;
	string data;
		 
	if (m_file->good())
	{
		getline(*m_file, data, '\n');
		{
			stringstream ss(data);
			string segment;

			while(getline(ss, segment, ','))
			{
				value.push_back(segment);
			}
		}
	}

	return value;
}
