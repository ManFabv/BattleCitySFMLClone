#pragma once

#include "GameEngineExportDefine.h"

#include "GameEngine/AbstractSceneBase.h"
#include "GameplayUtilities/ScoreManager.h"

namespace GameEngine
{
	namespace Scenes
	{
		class GAMEENGINE_API SceneMainMenu : public GameEngine::Scenes::AbstractSceneBase
		{
		public:
			virtual void InitializeSystems(const GameEngine::GameDataConfig::GameData& game_data, GameEngine::DataUtils::ConfigLoader& config_loader, GameEngine::DataUtils::AssetLoader& asset_loader) override;
			virtual void CleanUpSystems() override;
		private:
			virtual void CustomPlayerInput() override;
			virtual void UpdateUI(float dt) override;
			virtual void CheckWinLoseConditions() override;
		};
	}
}
