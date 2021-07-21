#pragma once

#include "GameplayUtilitiesExportDefine.h"

#include <iostream>

namespace GameplayUtilities
{
	namespace Scores
	{
		struct GAMEPLAYUTILITIES_API Score
		{
		private:
			std::string user_name;
			unsigned long int score;

		public:
			Score(const std::string& user_name, const long int score);
			void AddPointToScore(const long int points);
			void ChangeUserName(const std::string& new_user_name);
			const long int GetScore();
			const std::string& GetUserName();
		};
	}
}
