#include "GameplayUtilities/ScoreManager.h"
#include <algorithm>

using namespace GameplayUtilities::Scores;

ScoreManager::ScoreManager()
{
}

ScoreManager::~ScoreManager()
{
	scores.clear();
}

const size_t ScoreManager::ScoresCount()
{
	return scores.size();
}

void ScoreManager::AddNewScore(Score score)
{
	scores.push_back(score);
	//TODO: improve this sorted vector
	std::sort(scores.begin(), scores.end(), [](Score a, Score b) {
		return (a.GetScore() > b.GetScore());
	});
}

void ScoreManager::AddNewScore(const std::string& user_name_score_owner, const long int new_score)
{
	Score score(user_name_score_owner, new_score);
	AddNewScore(score);
}

void ScoreManager::RemoveScore(const std::string& user_name_score_owner)
{
	int array_offset = 0;
	for (Score score : scores)
	{
		if (score.GetUserName() == user_name_score_owner)
		{
			scores.erase(scores.begin() + array_offset);
			break;
		}
		array_offset++;
	}
}

const long int ScoreManager::GetScoreOfUser(const std::string& user_name_score_owner)
{
	for (Score score : scores)
	{
		if (score.GetUserName() == user_name_score_owner)
		{
			return score.GetScore();
		}
	}
	return -1;
}

const long int ScoreManager::GetHighScore()
{
	return scores[0].GetScore();
}
