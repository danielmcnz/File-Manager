#include <finder/utils/envreader.h>

namespace finder
{

	ENVReader::ENVReader()
	{}

	ENVReader::~ENVReader()
	{}

	int ENVReader::OpenFile(std::string filepath)
	{
		std::ifstream env(".env");	
	
		if(!env.is_open())
		{
			std::cout << "Failed to open .env file" << std::endl;
			return 1;
		}

		Line line;
		while(getline(env, line.line))
		{
			if(line.contains("FILEPATH"))
			{
				m_Email_Path = line.splitStr('=')[1];
			}
			else if(line.contains("SUBJECT"))
			{
				auto args = line.splitStr('=');
				m_Subject = args[1];
				for(int i=2;i<args.size();++i)
				{
					m_Subject += " " + args[i];
				}
				if(m_Subject.startsWith("[") && m_Subject.endsWith("]"))
				{
					if(m_Subject == "[(no subject)]")
					{
						m_Subject = "[]";
					}
				}
			}
		}
	}
}
