#include "GameplayUtilities/File.h"

using namespace GameplayUtilities::IO;

File::File(const std::string& filepath, std::ios::openmode openMode)
{
	Open(filepath, openMode);
}

File::~File()
{
	Close();
}

void File::Open(const std::string& filepath, std::ios::openmode openMode)
{
	Close();

	if (!filepath.empty())
		file.open(filepath, openMode);
}

void File::OpenForRead(const std::string& filepath)
{
	Open(filepath, std::ios::in);
}

void File::OpenForWrite(const std::string& filepath)
{
	Open(filepath, std::ios::out);
}

void File::Write(const std::string& inputValue)
{
	if (!inputValue.empty() && IsOpen())
	{
		file << inputValue << std::endl;
	}
}

const std::string File::Read()
{
	std::string valueRead = "";
	std::string valueToReturn = "";
	if (IsOpen())
	{
		while (std::getline(file, valueRead))
		{
			valueToReturn = valueToReturn.append(valueRead) + "\n";
		}
	}
	return valueToReturn;
}

const bool File::IsOpen()
{
	return file.is_open();
}

void File::Close()
{
	if (IsOpen())
		file.close();
}
