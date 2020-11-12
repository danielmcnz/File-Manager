#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

#include <finder/emlreader/EMLReader.h>
#include <finder/utils/Line.h>

namespace finder
{
	namespace fs = std::filesystem;

	class Search
	{
	public:
		Search() = default;
		Search(std::string pathToSearch);
		~Search() = default;

		std::vector<std::string> FindFilesBySubject(std::string path, std::string fileSubject, std::vector<std::string> &files);
		
		std::vector<std::string> FindFilesByDate(std::string path, std::string date);

		std::vector<std::string> FindFilesBySender(std::string path, std::string sender);

	private:
		EMLReader reader;

		std::string path;
	};
}