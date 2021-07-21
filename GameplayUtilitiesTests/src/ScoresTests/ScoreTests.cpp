#pragma once

#include <gtest/gtest.h>
#include "GameplayUtilities/Score.h"

using namespace GameplayUtilities::Scores;

TEST(ScoreTests, ConstructorSetCorrectValuesForScoreAndUserName) 
{
	Score score("MyUserName", 100);
	EXPECT_EQ(100, score.GetScore());
	EXPECT_EQ("MyUserName", score.GetUserName());
}

TEST(ScoreTests, ConstructorDontSetUserNameIfEmpty)
{
	Score score("", 0);
	EXPECT_EQ("guest", score.GetUserName());
}

TEST(ScoreTests, ConstructorDontSetScoreIfNegative)
{
	Score score("", -100);
	EXPECT_EQ(0, score.GetScore());
}

TEST(ScoreTests, ChangeUserNameDontChangeUserNameIfEmpty)
{
	Score score("MyUserName", 0);
	score.ChangeUserName("");
	EXPECT_EQ("MyUserName", score.GetUserName());
}

TEST(ScoreTests, AddPointsDontSetScoreIfNegative)
{
	Score score("", 100);
	score.AddPointToScore(-100);
	EXPECT_EQ(100, score.GetScore());
}
