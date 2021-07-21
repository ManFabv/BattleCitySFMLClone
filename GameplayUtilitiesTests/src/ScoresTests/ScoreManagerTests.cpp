#pragma once

#include <gtest/gtest.h>
#include "GameplayUtilities/ScoreManager.h"

using namespace GameplayUtilities::Scores;

TEST(ScoreManagerTests, ConstructorInitializesScoreListWithZeroElements)
{
	ScoreManager score_manager;
	EXPECT_EQ(0, score_manager.ScoresCount());
}

TEST(ScoreManagerTests, ScoreCountUpCorrectlyTheNumberOfAddedScoresAfterAddScore)
{
	Score score("MyUserName", 100);
	ScoreManager score_manager;
	score_manager.AddNewScore(score);
	EXPECT_EQ(1, score_manager.ScoresCount());
}

TEST(ScoreManagerTests, ScoreCountDoesntChangeIfRemoveUnexistentUser)
{
	Score score("MyUserName", 100);
	ScoreManager score_manager;
	score_manager.AddNewScore(score);
	score_manager.RemoveScore("MyUserName2");
	EXPECT_EQ(1, score_manager.ScoresCount());
}

TEST(ScoreManagerTests, ScoreCountDoesntChangeIfRemoveEmptyUser)
{
	Score score("MyUserName", 100);
	ScoreManager score_manager;
	score_manager.AddNewScore(score);
	score_manager.RemoveScore("");
	EXPECT_EQ(1, score_manager.ScoresCount());
}

TEST(ScoreManagerTests, ScoreCountUpCorrectlyTheNumberOfAddedScoresAfterRemoveScore)
{
	Score score1("MyUserName", 100);
	Score score2("MyUserName2", 200);
	ScoreManager score_manager;
	score_manager.AddNewScore(score1);
	score_manager.AddNewScore(score2);
	score_manager.RemoveScore("MyUserName");
	EXPECT_EQ(1, score_manager.ScoresCount());
}

TEST(ScoreManagerTests, ScoreValueIsShownCorrectlyAfterAddScore)
{
	Score score("MyUserName", 100);
	ScoreManager score_manager;
	score_manager.AddNewScore(score);
	EXPECT_EQ(100, score_manager.GetScoreOfUser("MyUserName"));
}

TEST(ScoreManagerTests, ScoreValueIsShownCorrectlyAfterAddMoreThanOneScores)
{
	Score score1("MyUserName", 100);
	Score score2("MyUserName2", 200);
	ScoreManager score_manager;
	score_manager.AddNewScore(score1);
	score_manager.AddNewScore(score2);
	score_manager.RemoveScore("MyUserName");
	EXPECT_EQ(200, score_manager.GetScoreOfUser("MyUserName2"));
}

TEST(ScoreManagerTests, ScoreValueIsMinusOneIfUserDoesntExists)
{
	Score score1("MyUserName", 100);
	ScoreManager score_manager;
	score_manager.AddNewScore(score1);
	EXPECT_EQ(-1, score_manager.GetScoreOfUser("MyUserName2"));
}

TEST(ScoreManagerTests, ScoreValueIsMinusOneIfScoresIsEmpty)
{
	ScoreManager score_manager;
	EXPECT_EQ(-1, score_manager.GetScoreOfUser("MyUserName"));
}
