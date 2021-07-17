#include "GameplayUtilities\Score.h"

using namespace GameplayUtilities::ScoreManager;

Score::Score(const std::string user_name, const long int score)
{
	this->score = 0;
	this->user_name = "guest";
	AddPointToScore(score);
	ChangeUserName(user_name);
}

void Score::AddPointToScore(const long int points)
{
	if(points > 0)
		this->score += points;
}

void Score::ChangeUserName(const std::string new_user_name)
{
	if(!new_user_name.empty())
		this->user_name = new_user_name;
}

const long int Score::GetScore()
{
	return score;
}

const std::string Score::GetUserName()
{
	return user_name;
}
