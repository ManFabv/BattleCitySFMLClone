#include "GameEngine/SceneMainMenu.h"

using namespace GameEngine::DataUtils;
using namespace GameEngine::GameDataConfig;
using namespace GameEngine::Scenes;

void SceneMainMenu::InitializeSystems(const GameData& game_data, ConfigLoader& config_loader, AssetLoader& asset_loader)
{
	AbstractSceneBase::InitializeSystems(game_data, config_loader, asset_loader);
}

void SceneMainMenu::CleanUpSystems()
{
	AbstractSceneBase::CleanUpSystems();
}

void SceneMainMenu::CustomPlayerInput()
{
}

void SceneMainMenu::UpdateUI(float dt)
{
}

void SceneMainMenu::CheckWinLoseConditions()
{
}
