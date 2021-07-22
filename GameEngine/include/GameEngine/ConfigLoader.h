#pragma once

#include "GameEngineExportDefine.h"
#include <iostream>

namespace GameEngine
{
	namespace DataUtils
	{
		class GAMEENGINE_API ConfigLoader
		{
		public:
			const std::string LoadDataFrom(const std::string& root_folder, const std::string& config_folder, const std::string& file_name);
			const std::string GeneratePath(const std::string& root_folder, const std::string& config_folder, const std::string& file_name);
		};
	}
}
