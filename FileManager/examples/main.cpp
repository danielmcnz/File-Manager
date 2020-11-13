#include <finder/Finder.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace finder;

int main()
{
	std::fstream env(".env", std::ios::in);
	
	if(!env.is_open())
	{
		std::cout << "Failed to open .env file" << std::endl;
		return 1;
	}

	std::string path;
	Line subject;
	Line line;
	while(std::getline(env, line.line))
	{
		if(line.contains("FILEPATH"))
		{
			path = line.splitStr('=')[1];
		}
		else if(line.contains("SUBJECT"))
		{
			auto args = line.splitStr('=');
			subject = args[1];
			for(int i=2;i<args.size();++i)
			{
				subject += " " + args[i];
			}
			if(subject.startsWith("[") && subject.endsWith("]"))
			{
				if(subject == "[(no subject)]")
				{
					subject = "[]";
				}
			}
		}
	}

	Search search(path);

	EMLReader reader;

	std::vector<std::string> files;
	files = search.FindFilesBySubject(path, subject, files);

	if(files.size() == 0)
	{
		std::cout << "Couldn't find any files with that subject" << std::endl;
	}

	for (std::string file : files)
	{
		reader.OpenFile(file);

		auto sender = reader.GetSender();

		Line temp(sender.name);
		if(temp.contains("bob"))
		{
			std::cout << sender.name << std::endl;
			std::cout << sender.email << std::endl;
		}

		std::cout << file << std::endl;
		std::cout << reader.GetSubject() << std::endl;

		reader.SaveImages(EMLReader::Image::jpeg, "/home/skyline/Desktop/file");

		reader.CloseFile();
	}

	return 0;
}