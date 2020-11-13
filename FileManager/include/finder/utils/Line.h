#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

namespace finder
{
	class Line
	{
	public:
		std::string line;

	public:
		Line() = default;
		Line(std::string line);
		Line(Line& copy);
		~Line() = default;

		Line& operator=(Line& copy);
		Line& operator=(std::string string);

		Line& operator+=(std::string string);

		bool operator==(Line line2);
		bool operator==(std::string line2);

		friend std::ostream& operator<<(std::ostream& os, const Line& copy);

		bool contains(std::string string);

		bool startsWith(std::string start);
		bool endsWith(std::string end);

		Line toLower();
		Line toUpper();

		Line popFront();
		Line popBack();

		std::vector<std::string> splitStr(char delimeter);
	};


	inline Line::Line(std::string line)
		:
		line(line)
	{}

	inline Line::Line(Line& copy)
	{
		*this = copy;
	}

	inline Line& Line::operator=(Line& copy)
	{
		line = copy.line;

		return *this;
	}

	inline Line& Line::operator=(std::string string)
	{
		line = string;

		return *this;
	}

	inline Line& Line::operator+=(std::string string)
	{
		line += string;

		return *this;
	}

	inline std::ostream& operator<<(std::ostream& os, const Line& copy)
	{
		os << copy.line;
		return os;
	}

	inline bool Line::operator==(Line line2)
	{
		return line == line2.line;
	}

	inline bool Line::operator==(std::string line2)
	{
		return line == line2;
	}

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
		int count = 0;
		for (int i = line.size()-1,max=end.size()-1; count < end.size() ; --i, ++count, --max)
		{
			if (line[i] != end[max])
			{
				return false;
			}
		}

		return true;
	}

	inline Line Line::toLower()
	{
		std::transform(line.begin(), line.end(), line.begin(), 
		[](unsigned char c){ return std::tolower(c); });

		return *this;
	}

	inline Line Line::toUpper()
	{
		return *this;
	}

	inline Line Line::popFront()
	{
		Line newline;
		for(int i=1;i<line.size();++i)
		{
			newline.line.push_back(line[i]);
		}
		line = newline.line;

		return *this;
	}

	inline Line Line::popBack()
	{
		line.pop_back();

		return *this;
	}

	inline std::vector<std::string> Line::splitStr(char delimeter)
	{
		std::vector<std::string> out;
		int startIndex = 0;
		size_t end = 0;
		while ((end = line.find(delimeter, end+1)))
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
}