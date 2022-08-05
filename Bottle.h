#pragma once
#include <deque>
#include "Color.h"

class Bottle
{
public:
	Bottle() = default;

	bool push(Color* slot);
	bool force_push(Color* slot);
	Color* pop();
	const std::deque<Color*> get_colors() const;

	bool is_finished() const;
	bool is_full() const;
	bool is_empty() const;

private:
	std::deque<Color*> stack;
};