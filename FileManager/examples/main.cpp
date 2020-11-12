#include <finder/Finder.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

int main()
{
	std::fstream env(".env", std::ios::in);
	
	std::string path;
	std::string subject;
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
		}
	}

	Search search(path);

	EMLReader reader;

	std::vector<std::string> files;
	files = search.FindFilesBySubject(path, subject, files);

	for (std::string file : files)
	{
		std::cout << file << std::endl;
		reader.OpenFile(file);
		std::cout << reader.ReadPlainBody() << std::endl;
		reader.CloseFile();
	}

	return 0;
}