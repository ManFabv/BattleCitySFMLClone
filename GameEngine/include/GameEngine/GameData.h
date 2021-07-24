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
			int resX = 0;
			int resY = 0;
			float world_scale = 1;
			std::string window_title = "";
			std::string config_root_folder = "";
			std::string animations_folder = "";
			std::string textures_folder = "";
			std::string fonts_folder = "";
			std::string sounds_folder = "";
			std::string player_config = "";
		};

		struct GAMEENGINE_API Animation
		{
		public:
			float time_between_frames = 0;
			std::string name = "";
			std::vector<int> frames;
			bool loop = false;
			~Animation()
			{
				frames.clear();
			}
		};

		struct GAMEENGINE_API AnimationData
		{
		public:
			int row_index = 0;
			int horizontal_sprites = 0;
			int vertical_sprites = 0;
			int sprites_width = 0;
			int sprites_height = 0;
			float frame_time = 0;
			std::string initial_animation = "";
			bool animations_loop = false;
			std::vector<Animation*> animations;
			~AnimationData()
			{
				animations.clear();
			}
		};
	}
}
