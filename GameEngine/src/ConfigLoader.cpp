#include "GameEngine/ConfigLoader.h"
#include "GameplayUtilities/File.h"

using namespace GameEngine::DataUtils;
using namespace GameplayUtilities::IO;

const std::string ConfigLoader::LoadDataFrom(const std::string& root_folder, const std::string& config_folder, const std::string& file_name)
{
	std::string player_anim_file = root_folder;
	player_anim_file += "\\";
	player_anim_file += config_folder;
	player_anim_file += "\\";
	player_anim_file += file_name;
	File file_reader;
	file_reader.OpenForRead(player_anim_file);
	return file_reader.Read();
}
