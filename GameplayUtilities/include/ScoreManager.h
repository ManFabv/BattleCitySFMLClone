#pragma once

#include "GameplayUtilitiesDefines.h"
#include "Score.h"
#include <vector>

class GAMEPLAYUTILITIES_API ScoreManager
{
private:
	std::vector<Score> scores;

public:
	ScoreManager();
	~ScoreManager();
	const size_t ScoresCount();
	void AddNewScore(Score score);
	void RemoveScore(const std::string user_name_score_owner);
	const long int GetScoreOfUser(const std::string user_name_score_owner);
};
