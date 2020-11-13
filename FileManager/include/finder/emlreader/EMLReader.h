#pragma once

#include <string>
#include <fstream>

#include <finder/utils/Line.h>

namespace finder
{
	class EMLReader
	{
	public:
		/* Stores name and email */
		struct Email
		{
			std::string name;
			std::string email;
		};

		/* Email structure with all
			relevant information */
		struct EMLFile
		{
			Email sender;
			Email recipient;
			std::string subject;
			std::string plainBody;
			std::string HTMLBody;
		};

		/* Supported image types*/
		enum class Image
		{
			jpeg,
			png
		};
	public:
		EMLReader() = default;
		EMLReader(std::string filename);
		~EMLReader() = default;

		/* Returns value depending upon success
			0 for success, 1 for faliure */
		int OpenFile(std::string filename);
		int CloseFile();

		/* Gets email subject */
		std::string GetSubject();

		/* Gets email sent date */
		std::string GetDate();

		/* Gets email sender */
		Email GetSender();

		/* Gets email recipient */
		Email GetRecipient();

		/* Returns plain message body */
		std::string ReadPlainBody();

		/* Returns html formatted body*/
		std::string ReadHTMLBody();

		/* Saves images in base64 format */
		int SaveImages(Image imageType, std::string filename);

	private:
		/* Returns array of Base64 encoded images
			of selected image type */
		std::vector<std::pair<Image, std::string>> ReadImages(Image imageType);

	private:
		std::string filename;
		std::fstream file;
		EMLFile email;
	};
}
