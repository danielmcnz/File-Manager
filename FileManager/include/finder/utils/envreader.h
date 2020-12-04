#include <finder/utils/Line.h>

#include <iostream>
#include <string>
#include <fstream>

namespace finder
{
	class ENVReader
	{
	public:
		ENVReader();
		~ENVReader();

		int OpenFile(std::string filepath);

		inline std::string GetEmailPath() { return m_Email_Path; };

		inline std::string GetSubject() { return m_Subject.line; };

	private:
		std::string m_Email_Path;
		Line m_Subject;
	};
}
