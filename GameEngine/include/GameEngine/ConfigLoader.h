#pragma once

#include "GameEngineExportDefine.h"
#include "GameEngine/GameData.h"

namespace GameEngine
{
	namespace DataUtils
	{
		class GAMEENGINE_API ConfigLoader
		{
		public:
			const std::string LoadDataFrom(const GameEngine::GameDataConfig::GameData& game_data);
		};
	}
}
