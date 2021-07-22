#include "GameEngine/ConfigLoader.h"
#include "GameplayUtilities/File.h"

using namespace GameEngine::DataUtils;
using namespace GameplayUtilities::IO;
using namespace GameEngine::GameDataConfig;

const std::string ConfigLoader::LoadDataFrom(const GameData& game_data)
{
	std::string player_anim_file = game_data.config_root_folder;
	player_anim_file += "\\";
	player_anim_file += game_data.animations_folder;
	player_anim_file += "\\";
	player_anim_file += game_data.player_config;
	File file_reader;
	file_reader.OpenForRead(player_anim_file);
	return file_reader.Read();
}
