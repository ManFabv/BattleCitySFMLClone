#include "GameEngine/FilePathHelper.h"

using namespace GameEngine::DataUtils;

const std::string FilePathHelper::GeneratePath(const std::string& root_folder, const std::string& config_folder, const std::string& file_name)
{
	std::string path = root_folder;
	path += "\\";
	path += config_folder;
	path += "\\";
	path += file_name;
	return path;
}