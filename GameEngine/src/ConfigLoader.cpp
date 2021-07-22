#include "GameEngine/ConfigLoader.h"
#include "GameplayUtilities/File.h"
#include "GameEngine/FilePathHelper.h"

using namespace GameEngine::DataUtils;
using namespace GameplayUtilities::IO;

const std::string ConfigLoader::LoadDataFrom(const std::string& root_folder, const std::string& config_folder, const std::string& file_name)
{
	std::string player_anim_file = FilePathHelper::GeneratePath(root_folder, config_folder, file_name);
	File file_reader;
	file_reader.OpenForRead(player_anim_file);
	return file_reader.Read();
}
