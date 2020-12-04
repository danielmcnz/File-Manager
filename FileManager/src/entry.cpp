#include <finder/Finder.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace finder;

int main(int argc, char* argv[])
{
	std::string path = "/home/skyline/Desktop/Emails/";
	Line subject;

	if(argc < 2)
	{
		std::cout << "pee pee poo poo fuck you too" << std::endl;
		return 1;
	}
	else if(argc == 2)
	{
		subject.line = argv[1];
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

		std::cout << file << std::endl;
		std::cout << reader.GetSubject() << std::endl;

		reader.SaveImages(EMLReader::Image::jpeg, "/home/skyline/Desktop/SavedImages");

		reader.CloseFile();
	}

	return 0;
}
