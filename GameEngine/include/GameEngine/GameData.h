#pragma once

#include "GameEngineExportDefine.h"
#include <iostream>

namespace GameEngine
{
	namespace GameDataConfig
	{
		struct GAMEENGINE_API GameData
		{
		public:
			int resX;
			int resY;
			std::string window_title;
			std::string config_root_folder;
			std::string animations_folder;
			std::string player_config;
		};
	}
}
