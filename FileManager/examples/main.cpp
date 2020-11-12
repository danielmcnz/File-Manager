#include <finder/Finder.h>

#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::string path = "/home/skyline/Desktop/Emails";
	Search search(path);

	EMLReader reader;

	std::vector<std::string> files;
	std::string subject = "Family Photos at the Mission";
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