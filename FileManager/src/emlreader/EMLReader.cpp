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
		if (line.startsWith("Subject:"))
		{
			auto args = line.splitStr(' ');

			if(args.size() == 1)
			{
				return "(no subject)";
			}

			std::string subject = args[1];
			for(int i=2;i<args.size();++i)
			{
				subject += " " + args[i];
			}
			return subject;
		}
	}

	return "";
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
			if(words.size() == 1)
			{
				return "Cant find sender";
			}

			std::string date = words[1];
			for (int i=2;i<words.size();++i)
			{
				date += " " + words[i];
			}
			return date;
		}
	}

	return "";
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

			if(lineArr.size() == 1)
			{
				return { "Can't find sender name", "Can't find sender email" };
			}
			else if(lineArr.size() == 2)
			{
				return { "Can't find sender name", lineArr[1] };
			}

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

	return {"",""};
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

			if(lineArr.size() == 1)
			{
				return { "Can't find recipient name", "Can't find recipient email" };
			}
			else if(lineArr.size() == 2)
			{
				return { "Can't find recipient name", lineArr[1] };
			}

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

	return {"",""};
}

int EMLReader::SaveImages(Image imageType, std::string filename)
{
	std::ofstream savefile;
	std::vector<std::pair<Image, std::string>> images;
	std::ifstream check;
	int index = 0;
	switch(imageType)
	{
		case Image::jpeg:
			images = ReadImages(imageType);

			for(int i=0;i<images.size();++i,++index)
			{
				filename = filename+std::to_string(index)+".jpeg";
				// check.open(filename);
				// check.close();

				savefile.open(filename);

				savefile.write(images[i].second.c_str(), images[i].second.size());
				savefile.close();
			}
			break;
		case Image::png:
			break;
	}

	return 0;
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
	int afterTag = 0;
	while (std::getline(file, line.line))
	{
		if (isImage == true)
		{
			if (!line.startsWith("--"))
			{
				if(afterTag == 4)
				{
					cur_image += line.line;
				}
				else
				{
					afterTag++;
				}
				
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
				break;
			case Image::png:
				if (line.contains("Content-Type: image/png"))
				{
					isImage = true;
					cur_imageType = Image::png;
					cur_image.clear();
				}
				break;
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