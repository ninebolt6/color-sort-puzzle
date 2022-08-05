#pragma once
#include "StateBase.h"
#include "StateCode.h"
#include "Score.h"

class ResultState : public StateBase
{
public:
	ResultState();

	StateCode print() override;

	void on_start() override;
	void on_end() override;

private:
	Score score;
	int key;
};