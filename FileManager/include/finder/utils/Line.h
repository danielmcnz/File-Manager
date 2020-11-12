#pragma once

#include <string>
#include <vector>

namespace finder
{
	class Line
	{
	public:
		std::string line;

		bool contains(std::string string);

		bool startsWith(std::string start);
		bool endsWith(std::string end);

		std::vector<std::string> splitStr(char delimeter);
	};
}

using namespace finder;

inline bool Line::contains(std::string string)
{
	int stringIndex = 0;
	for (int i = 0; i < line.size(); ++i)
	{
		if (line[i] == string[stringIndex])
		{
			++stringIndex;
			if (stringIndex == string.size())
			{
				return true;
			}
		}
		else
		{
			if (stringIndex > 1)
			{
				stringIndex = 0;
			}
		}
	}

	return false;
}

inline bool Line::startsWith(std::string start)
{
	for (int i = 0; i < start.size(); ++i)
	{
		if (line[i] != start[i])
		{
			return false;
		}
	}
	
	return true;
}

inline bool Line::endsWith(std::string end)
{
	for (int i = end.size(); i > 0; --i)
	{
		if (line[i] != end[i])
		{
			return false;
		}
	}

	return true;
}

inline std::vector<std::string> Line::splitStr(char delimeter)
{
	std::vector<std::string> out;
	int startIndex = 0;
	size_t end = 0;
	while (end = line.find(delimeter, end+1))
	{
		if (end == std::string::npos)
		{
			out.push_back(line.substr(startIndex, line.size()));
			break;
		}

		out.push_back(line.substr(startIndex, end-startIndex));

		if (startIndex == end+1)
		{
			break;
		}

		startIndex = end+1;
	}

	return out;
}