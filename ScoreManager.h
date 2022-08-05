#pragma once
#include "Score.h"

class ScoreManager
{
public:
	~ScoreManager();

	static ScoreManager* get_instance();

	void set_score(const int& move_count, const int& play_sec);
	Score get_score();

private:
	ScoreManager();
	static ScoreManager* instance;

	Score score;
};