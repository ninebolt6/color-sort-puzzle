#pragma once
#include <vector>
#include <random>
#include <chrono>
#include "Bottle.h"
#include "StateBase.h"
#include "StateCode.h"
#include "PoolAllocator.h"

class GameState : public StateBase
{
public:
	GameState() : slot_selected(nullptr), selected_from(-1), x(1), index(0), key(0), move_count(0), time_start{}, eng(rnd()) {
		bottles.reserve(7);
	}

	~GameState() override {
		for (Bottle* bottle : bottles) {
			bottle_allocator.Free(bottle);
		}
	};
	StateCode print() override;
	void print_border(const int& topLeftX, const int& topLeftY);
	void print_color(const Color& color, const int& topLeftX, const int& topLeftY);
	void print_bottles();
	void print_indicator(const int& topLeftX, const int& topLeftY);

	void on_start() override;
	void on_end() override;

private:
	PoolAllocator<Bottle, 7> bottle_allocator;
	PoolAllocator<Color, 20> color_allocator;
	std::vector<Bottle*> bottles;
	Color* slot_selected;
	int selected_from;
	int x;
	//int y;
	int index;
	int key;
	int move_count;
	std::chrono::system_clock::time_point time_start;

	std::random_device rnd;
	std::mt19937 eng;
};