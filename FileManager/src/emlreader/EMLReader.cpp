#include <finder/emlreader/EMLReader.h>

using namespace finder;

EMLReader::EMLReader(std::string filename)
	:
	filename(filename)
{}

int EMLReader::OpenFile(std::string filename)
{
	this->filename = filename;

	file.open(filename, std::ios::in);
	if (file.is_open())
	{
		return 0;
	}
	return 1;
}

int EMLReader::CloseFile()
{
	file.close();

	if (file.is_open())
	{
		return 1;
	}

	return 0;
}

std::string EMLReader::GetSubject()
{
	file.clear();
	file.seekg(0);

	Line line;
	while (std::getline(file, line.line))
	{
		if (line.contains("Subject:"))
		{
			return line.splitStr(' ')[1];
		}
	}
}

std::string EMLReader::GetDate()
{
	file.clear();
	file.seekg(0);
	
	Line line;
	while (std::getline(file, line.line))
	{
		if (line.contains("Date:"))
		{
			auto words = line.splitStr(' ');
			std::string date = words[1];
			for (int i=2;i<words.size();++i)
			{
				date += " " + words[i];
			}
			return date;
		}
	}
}

EMLReader::Email EMLReader::GetSender()
{
	file.clear();
	file.seekg(0);

	Line line;
	while (std::getline(file, line.line))
	{
		if (line.contains("From:"))
		{
			std::vector<std::string> lineArr = line.splitStr(' ');
			std::string name = lineArr[1];
			int emailIndex = 0;
			for (int i = 2; i < lineArr.size(); ++i)
			{
				Line line;
				line.line = lineArr[i];
				if (line.contains("<") && line.contains(">"))
				{
					emailIndex = i;
					break;
				}
				else
				{
					name += " " + lineArr[i];
				}
			}
			Email sender;
			sender.name = name;
			sender.email = lineArr[emailIndex].substr(1, lineArr[emailIndex].size()-2);
			return sender;
		}
	}
}

EMLReader::Email EMLReader::GetRecipient()
{
	file.clear();
	file.seekg(0);

	Line line;
	while (std::getline(file, line.line))
	{
		if (line.contains("To:"))
		{
			std::vector<std::string> lineArr = line.splitStr(' ');
			std::string name = lineArr[1];
			int emailIndex = 0;
			for (int i = 2; i < lineArr.size(); ++i)
			{
				Line line;
				line.line = lineArr[i];
				if (line.contains("<") && line.contains(">"))
				{
					emailIndex = i;
					break;
				}
				else
				{
					name += " " + lineArr[i];
				}
			}
			Email sender;
			sender.name = name;
			sender.email = lineArr[emailIndex].substr(1, lineArr[emailIndex].size() - 2);
			return sender;
		}
	}
}

std::vector<std::pair<EMLReader::Image, std::string>> EMLReader::ReadImages(Image imageType)
{
	file.clear();
	file.seekg(0);

	std::vector<std::pair<Image, std::string>> images;
	std::string cur_image;
	Image cur_imageType;

	Line line;
	bool isImage = false;
	while (std::getline(file, line.line))
	{
		if (isImage == true)
		{
			if (!line.startsWith("--00000000"))
			{
				cur_image += line.line;
			}
			else
			{
				isImage = false;
				images.push_back({ cur_imageType, cur_image });
				if (file.eof())
				{
					break;
				}
			}
		}
		else
		{
			switch (imageType)
			{
			case Image::jpeg:
				if (line.contains("Content-Type: image/jpeg"))
				{
					isImage = true;
					cur_imageType = Image::jpeg;
					cur_image.clear();
				}
			case Image::png:
				if (line.contains("Content-Type: image/png"))
				{
					isImage = true;
					cur_imageType = Image::png;
					cur_image.clear();
				}
			}
		}
	}

	return images;
}

std::string EMLReader::ReadPlainBody()
{
	file.clear();
	file.seekg(0);

	Line line;
	bool body = false;
	std::string bodyText;
	while (std::getline(file, line.line))
	{
		if (body == true)
		{
			if (!line.startsWith("--00000000"))
			{
				bodyText += line.line;
			}
			else
			{
				body = false;
				break;
			}
		}
		else
		{
			if (line.contains("Content-Type: text/plain"))
			{
				body = true;
			}
		}
	}

	return bodyText;
}

std::string EMLReader::ReadHTMLBody()
{
	file.clear();
	file.seekg(0);

	Line line;
	bool body = false;
	std::string bodyText;
	while (std::getline(file, line.line))
	{
		if (body == true)
		{
			if (!line.startsWith("--00000000"))
			{
				bodyText += line.line;
			}
			else
			{
				body = false;
				break;
			}
		}
		else
		{
			if (line.contains("Content-Type: text/html"))
			{
				body = true;
			}
		}
	}

	return bodyText;
}