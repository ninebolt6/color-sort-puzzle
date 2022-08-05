#pragma once
#include <conio.h>
#include "StateBase.h"
#include "StateCode.h"

class TitleState : public StateBase
{
public:
	TitleState();
	~TitleState() = default;

	StateCode print() override;

private:
	int key;
};