#include "GameEngine/SceneGamePlay.h"
#include <rapidjson/document.h>
#include <string>

using namespace GameEngine::DataUtils;
using namespace GameEngine::GameDataConfig;
using namespace GameEngine::Scenes;
using namespace GameEngine::Systems;
using namespace GameEngine::Components;

void SceneGamePlay::InitializeSystems(const GameData& game_data, ConfigLoader& config_loader, AssetLoader& asset_loader, sf::RenderWindow* main_window)
{
	AbstractSceneBase::InitializeSystems(game_data, config_loader, asset_loader, main_window);

	world_scale.x = game_data.world_scale;
	world_scale.y = game_data.world_scale;
	entities_scale.x = game_data.entities_scale;
	entities_scale.y = game_data.entities_scale;

	m_user_name = "guest";
	m_score_manager.AddNewScore("dev", 1000);
	m_score_manager.AddNewScore(m_user_name, 0);

	std::string player_json = config_loader.LoadDataFrom(game_data.config_root_folder, game_data.animations_folder, game_data.player_config);

	rapidjson::Document player_json_document;
	player_json_document.Parse(player_json.c_str());

	std::string entities_atlas_name = player_json_document["atlas_name"].GetString();
	entt::entity player_entity = m_registry.create();

	AnimationData player_anim_data;
	player_anim_data.row_index = player_json_document["anim_row"].GetInt();
	player_anim_data.horizontal_sprites = player_json_document["horizontal_sprites"].GetInt();
	player_anim_data.vertical_sprites = player_json_document["vertical_sprites"].GetInt();
	player_anim_data.sprites_width = player_json_document["sprites_width"].GetInt();
	player_anim_data.sprites_height = player_json_document["sprites_height"].GetInt();
	player_anim_data.frame_time = player_json_document["frame_time"].GetFloat();
	player_anim_data.initial_animation = player_json_document["initial_animation"].GetString();
	player_anim_data.animations_loop = player_json_document["animations_loop"].GetBool();
	//TODO: player_json_document["animations"] should be loaded from config
	LoadPlayerEntity(player_entity, asset_loader, entities_atlas_name);
	LoadAnimationInformationForEntity(player_entity, player_anim_data);
	LoadMovementForEntity(player_entity);
	AddPlayerInputComponent(player_entity);

	entt::entity gamefont_entity = m_registry.create();
	LoadGameFont(gamefont_entity, asset_loader, game_data.font_name);

	std::string level_json = config_loader.LoadDataFrom(game_data.config_root_folder, game_data.gameplay_levels_folder_name, m_json_level_name);
	LoadLevel(asset_loader, level_json);

	entt::entity enemy_entity = m_registry.create();
	LoadEnemyEntity(enemy_entity, asset_loader, entities_atlas_name, 8, 8);
}

void SceneGamePlay::CleanUpSystems()
{
	AbstractSceneBase::CleanUpSystems();

	if (m_player_score_font != nullptr)
	{
		delete m_player_score_font;
		m_player_score_font = nullptr;
	}
}

void SceneGamePlay::CustomPlayerInput()
{
	m_input_system->Execute(m_registry);
}

void SceneGamePlay::UpdateUI(float dt)
{
	UpdateScoreUI();
}

void SceneGamePlay::CheckWinLoseConditions()
{
	//TODO: implement this
}

void SceneGamePlay::LoadPlayerEntity(entt::entity entity, AssetLoader& asset_loader, const std::string& file_name)
{
	sf::Sprite* m_player_sprite = new sf::Sprite();
	m_player_sprite->setTexture(asset_loader.GetTexture(file_name));
	m_player_sprite->setScale(sf::Vector2f(m_player_sprite->getScale().x * entities_scale.x, m_player_sprite->getScale().y * entities_scale.y));
	m_player_sprite->setPosition(72, 814); //TODO: player should be at the spawn point position
	m_registry.emplace<DrawableComponent>(entity, *m_player_sprite);

	TransformComponent* transform = new TransformComponent(*m_player_sprite);
	m_registry.emplace<TransformComponent>(entity, *transform);

	DynamicColliderComponent* dynamic_collider_component = new DynamicColliderComponent(*m_player_sprite);
	m_registry.emplace<DynamicColliderComponent>(entity, *dynamic_collider_component);
}

void SceneGamePlay::LoadEnemyEntity(entt::entity entity, GameEngine::DataUtils::AssetLoader& asset_loader, const std::string& file_name, int posx, int posy)
{
	sf::Sprite* m_enemy_sprite = new sf::Sprite();
	m_enemy_sprite->setTexture(asset_loader.GetTexture(file_name));
	m_enemy_sprite->setScale(sf::Vector2f(m_enemy_sprite->getScale().x * entities_scale.x, m_enemy_sprite->getScale().y * entities_scale.y));
	m_enemy_sprite->setTextureRect(sf::IntRect(64, 64, 16, 16));
	m_enemy_sprite->setPosition(posx, posy); //TODO: player should be at the spawn point position
	m_registry.emplace<DrawableComponent>(entity, *m_enemy_sprite);

	TransformComponent* transform = new TransformComponent(*m_enemy_sprite);
	m_registry.emplace<TransformComponent>(entity, *transform);

	StaticColliderComponent* static_collider_component = new StaticColliderComponent();
	static_collider_component->m_fixture = m_enemy_sprite->getGlobalBounds();
	m_registry.emplace<StaticColliderComponent>(entity, *static_collider_component);
}

void SceneGamePlay::LoadAnimationInformationForEntity(entt::entity entity, const AnimationData& anim_data)
{
	AnimationComponent* anim_component_idle_up = new AnimationComponent();
	anim_component_idle_up->m_frames.push_back(sf::IntRect(0, 0, 16, 16));
	anim_component_idle_up->m_loop = true;
	anim_component_idle_up->m_duration = 0.075f;
	anim_component_idle_up->animation_type = PLAYER_ANIMATION_TYPE::IDLE_UP;
	AnimationComponent* anim_component_idle_down = new AnimationComponent();
	anim_component_idle_down->m_frames.push_back(sf::IntRect(64, 0, 16, 16));
	anim_component_idle_down->m_loop = true;
	anim_component_idle_down->m_duration = 0.075f;
	anim_component_idle_down->animation_type = PLAYER_ANIMATION_TYPE::IDLE_DOWN;
	AnimationComponent* anim_component_idle_left = new AnimationComponent();
	anim_component_idle_left->m_frames.push_back(sf::IntRect(32, 0, 16, 16));
	anim_component_idle_left->m_loop = true;
	anim_component_idle_left->m_duration = 0.075f;
	anim_component_idle_left->animation_type = PLAYER_ANIMATION_TYPE::IDLE_LEFT;
	AnimationComponent* anim_component_idle_right = new AnimationComponent();
	anim_component_idle_right->m_frames.push_back(sf::IntRect(96, 0, 16, 16));
	anim_component_idle_right->m_loop = true;
	anim_component_idle_right->m_duration = 0.075f;
	anim_component_idle_right->animation_type = PLAYER_ANIMATION_TYPE::IDLE_RIGHT;
	AnimationComponent* anim_component_move_up = new AnimationComponent();
	anim_component_move_up->m_frames.push_back(sf::IntRect(0, 0, 16, 16));
	anim_component_move_up->m_frames.push_back(sf::IntRect(16, 0, 16, 16));
	anim_component_move_up->m_loop = true;
	anim_component_move_up->m_duration = 0.075f;
	anim_component_move_up->animation_type = PLAYER_ANIMATION_TYPE::MOVE_UP;
	AnimationComponent* anim_component_move_down = new AnimationComponent();
	anim_component_move_down->m_frames.push_back(sf::IntRect(64, 0, 16, 16));
	anim_component_move_down->m_frames.push_back(sf::IntRect(80, 0, 16, 16));
	anim_component_move_down->m_loop = true;
	anim_component_move_down->m_duration = 0.075f;
	anim_component_move_down->animation_type = PLAYER_ANIMATION_TYPE::MOVE_DOWN;
	AnimationComponent* anim_component_move_left = new AnimationComponent();
	anim_component_move_left->m_frames.push_back(sf::IntRect(32, 0, 16, 16));
	anim_component_move_left->m_frames.push_back(sf::IntRect(48, 0, 16, 16));
	anim_component_move_left->m_loop = true;
	anim_component_move_left->m_duration = 0.075f;
	anim_component_move_left->animation_type = PLAYER_ANIMATION_TYPE::MOVE_LEFT;
	AnimationComponent* anim_component_move_right = new AnimationComponent();
	anim_component_move_right->m_frames.push_back(sf::IntRect(96, 0, 16, 16));
	anim_component_move_right->m_frames.push_back(sf::IntRect(112, 0, 16, 16));
	anim_component_move_right->m_loop = true;
	anim_component_move_right->m_duration = 0.075f;
	anim_component_move_right->animation_type = PLAYER_ANIMATION_TYPE::MOVE_RIGHT;
	PlayerAnimationControllerComponent* animation_controller_component = new PlayerAnimationControllerComponent();
	animation_controller_component->animations.insert(std::make_pair(anim_component_idle_up->animation_type, *anim_component_idle_up));
	animation_controller_component->animations.insert(std::make_pair(anim_component_idle_down->animation_type, *anim_component_idle_down));
	animation_controller_component->animations.insert(std::make_pair(anim_component_idle_left->animation_type, *anim_component_idle_left));
	animation_controller_component->animations.insert(std::make_pair(anim_component_idle_right->animation_type, *anim_component_idle_right));
	animation_controller_component->animations.insert(std::make_pair(anim_component_move_up->animation_type, *anim_component_move_up));
	animation_controller_component->animations.insert(std::make_pair(anim_component_move_down->animation_type, *anim_component_move_down));
	animation_controller_component->animations.insert(std::make_pair(anim_component_move_left->animation_type, *anim_component_move_left));
	animation_controller_component->animations.insert(std::make_pair(anim_component_move_right->animation_type, *anim_component_move_right));
	animation_controller_component->current_animation = anim_component_idle_up;
	m_registry.emplace<PlayerAnimationControllerComponent>(entity, *animation_controller_component);
}

void SceneGamePlay::LoadMovementForEntity(entt::entity entity)
{
	MovementComponent* movement_component = new MovementComponent();
	movement_component->max_velocity = 1.5f; //TODO: this should be taken from config
	movement_component->m_velocity = sf::Vector2f(0, 0);
	m_registry.emplace<MovementComponent>(entity, *movement_component);
}

void SceneGamePlay::LoadGameFont(entt::entity entity, AssetLoader& asset_loader, const std::string& file_name)
{
	m_player_score_font = new sf::Text();
	m_player_score_font->setFont(asset_loader.GetFont(file_name));
	UpdateScoreUI();
	m_player_score_font->setFillColor(sf::Color::White); //TODO: style should be loaded from config file
	m_player_score_font->setCharacterSize(24); //TODO: style should be loaded from config file
	m_player_score_font->setPosition(272, 8); //TODO: score should be at the top center
	m_registry.emplace<DrawableFontComponent>(entity, *m_player_score_font);
}

void SceneGamePlay::AddPlayerInputComponent(entt::entity entity)
{
	CustomPlayerInputComponent* custom_player_input_component = new CustomPlayerInputComponent();
	custom_player_input_component->move_left = sf::Keyboard::Left;
	custom_player_input_component->move_right = sf::Keyboard::Right;
	custom_player_input_component->move_up = sf::Keyboard::Up;
	custom_player_input_component->move_down = sf::Keyboard::Down;
	m_registry.emplace<CustomPlayerInputComponent>(entity, *custom_player_input_component);
}

void SceneGamePlay::LoadLevel(GameEngine::DataUtils::AssetLoader& asset_loader, const std::string& level_json)
{
	rapidjson::Document level_json_document;
	level_json_document.Parse(level_json.c_str());

	int tilewidth = level_json_document["tilewidth"].GetInt();
	int tileheight = level_json_document["tileheight"].GetInt();
	int mapwidth = level_json_document["mapwidth"].GetInt();
	int mapheight = level_json_document["mapheight"].GetInt();
	int atlassize = level_json_document["atlassize"].GetInt();
	int mapsize = level_json_document["mapsize"].GetInt();
	const std::string atlas_name = level_json_document["atlasname"].GetString();
	auto data = level_json_document["data"].GetArray();
	auto data_iterator = data.Begin();

	for (int position_in_array = 0; data_iterator != data.End(); data_iterator++, position_in_array++)
	{
		CreateTileAndAddComponents(asset_loader, atlassize, mapsize, tilewidth, tileheight, data_iterator->GetInt(), position_in_array, atlas_name);
	}
}

void SceneGamePlay::CreateTileAndAddComponents(GameEngine::DataUtils::AssetLoader& asset_loader, int atlas_size, int map_size, int tilewidth, int tileheight, int tiletype, int position_in_array, const std::string& atlas_name)
{
	if (tiletype == 0)
		return;

	sf::Sprite* sprite = new sf::Sprite();
	entt::entity entity = m_registry.create();
	sprite->setTexture(asset_loader.GetTexture(atlas_name));
	sprite->setScale(sf::Vector2f(sprite->getScale().x * world_scale.x, sprite->getScale().y * world_scale.y));

	int pos_in_array_x = (position_in_array % map_size);
	int pos_in_array_y = (position_in_array / map_size);
	sf::Vector2f position;
	position.x = pos_in_array_x * tilewidth * world_scale.x;
	position.y = pos_in_array_y * tileheight * world_scale.y;
	int pos_in_atlas_x = ((tiletype - 1) % atlas_size);
	int pos_in_atlas_y = ((tiletype - 1) / atlas_size);
	int subrectx = pos_in_atlas_x * tilewidth;
	int subrecty = pos_in_atlas_y * tileheight;
	sf::IntRect texture_rect(subrectx, subrecty, tilewidth, tileheight);

	sprite->setPosition(position);
	sprite->setTextureRect(texture_rect);

	m_registry.emplace<DrawableComponent>(entity, *sprite);

	StaticColliderComponent* static_collider_component = new StaticColliderComponent();
	static_collider_component->m_fixture = sprite->getGlobalBounds();
	m_registry.emplace<StaticColliderComponent>(entity, *static_collider_component);
}

void SceneGamePlay::UpdateScoreUI()
{
	std::string score_text = "HIGHSCORE: ";
	score_text += std::to_string(m_score_manager.GetHighScore());
	score_text += " - SCORE ";
	score_text += std::to_string(m_score_manager.GetScoreOfUser(m_user_name));
	m_player_score_font->setString(score_text);
}
