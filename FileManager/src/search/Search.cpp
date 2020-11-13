#include <finder/search/Search.h>

using namespace finder;

Search::Search(std::string pathToSearch)
	:
	path(pathToSearch)
{}

std::vector<std::string> Search::FindFilesBySubject(std::string path, Line fileSubject, std::vector<std::string> &files)
{
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (fs::is_directory(entry.path()))
		{
			FindFilesBySubject(entry.path().string(), fileSubject, files);
		}
		else if (fs::is_regular_file(entry.path()))
		{
			reader.OpenFile(entry.path().string());
			Line subject;
			subject.line = reader.GetSubject();
			if(fileSubject.startsWith("[") && fileSubject.endsWith("]"))
			{
				if (subject.toLower().line == fileSubject.toLower().popBack().popFront().line)
				{
					files.push_back(entry.path().string());
				}
			}
			else
			{
				if (subject.toLower().contains(fileSubject.toLower().line))
				{
					files.push_back(entry.path().string());
				}
			}
			
			reader.CloseFile();
		}
	}

	return files;
}

std::vector<std::string> Search::FindFilesByDate(std::string path, std::string date)
{
	/* No, I am in fact, not written */

	return std::vector<std::string>();
}

std::vector<std::string> Search::FindFilesBySender(std::string path, std::string sender)
{
	/* No, I am in fact, not written */

	return std::vector<std::string>();
}