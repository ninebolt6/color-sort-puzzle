#include <conio.h>
#include <stdio.h>
#include <algorithm>
#include "GameState.h"
#include "ScoreManager.h"

void GameState::print_border(const int& topLeftX, const int& topLeftY) {
	printf("\x1b[%d;%dH------", topLeftY + 2, topLeftX);
	for (int i = 3; i < 7; i++) {
		printf("\x1b[%d;%dH|", topLeftY + i, topLeftX);
		printf("\x1b[%d;%dH|", topLeftY + i, topLeftX + 5);
	}
}

void GameState::print_color(const Color& color, const int& topLeftX, const int& topLeftY) {
	printf("\x1b[%dm", color);
	printf("\x1b[%d;%dH■■", topLeftY, topLeftX);
	printf("\x1b[37m"); // reset
}

void GameState::print_indicator(const int& topLeftX, const int& topLeftY) {
	printf("\x1b[%d;%dH------", topLeftY, topLeftX);
}

void GameState::print_bottles() {
	int idx = 1;
	for (Bottle* bottle : bottles) {
		const auto colors = bottle->get_colors();
		int p_x = 9 * idx;
		int p_y = 6 + 4 - (int)colors.size();
		for (const Color* color : colors) {
			print_color(*color, p_x, p_y);
			p_y++;
		}
		print_indicator(9 * idx - 1, p_y);
		idx++;
	}
}

void GameState::on_start() {
	std::vector<Color*> colors;
	colors.reserve(20);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			Color* color = color_allocator.Alloc();
			if (color != nullptr) {
				// redから始める
				*color = static_cast<Color>(31 + i);
				colors.push_back(color);
			}
		}
	}

	std::shuffle(colors.begin(), colors.end(), eng);

	for (int i = 0; i < 7; i++) {
		Bottle* bottle = bottle_allocator.Alloc();
		if (bottle != nullptr) {
			for (int j = 0; j < 4; j++) {
				if (!colors.size()) {
					break;
				}
				Color* slot = colors.back();
				colors.pop_back();
				bottle->force_push(slot);
			}
			bottles.push_back(bottle);
		}
	}
	time_start = std::chrono::system_clock::now();
}

void GameState::on_end() {
	for (Bottle* bottle : bottles) {
		for (Color* color : bottle->get_colors()) {
			color_allocator.Free(color);
		}
		bottle_allocator.Free(bottle);
	}
	bottles.clear();

	// スコア保存
	int elapsed_sec = (int)std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - time_start).count();
	ScoreManager::get_instance()->set_score(move_count, elapsed_sec);
	move_count = 0;
	time_start = {};
}

StateCode GameState::print() {
	if (slot_selected == nullptr) {
		printf("Select a space you want to pick up a color");
	}
	else {
		printf("Select a space you want to place the color");
		print_color(*slot_selected, x * 9, 3);
	}
	print_border(x * 9 - 1, 3);
	printf("\x1b[14;0HPress 'A', 'D' to move\nPress 'Enter' to pick up/place\nPress 'BackSpace' to cancel\nPress 'Q' to exit");
	print_bottles();

	key = _getch();
	// キー入力で座標更新
	switch (key) {
	case 'a':
		if (x > 1) {
			x--;
		}
		else {
			x = 7;
		}
		break;
	case 'd':
		if (x < 7) {
			x++;
		}
		else {
			x = 1;
		}
		break;
	case 0x0D: // Enter
		if (slot_selected == nullptr) {
			// なにも選択していない
			slot_selected = bottles[x - 1]->pop();
			selected_from = x - 1;
		}
		else {
			// 色を選択済み
			if (bottles[x - 1]->push(slot_selected)) {
				// 色を置くことができた
				slot_selected = nullptr;
				selected_from = -1;
				move_count++;

				bool is_finished = true;
				for (Bottle* bottle : bottles) {
					if (!bottle->is_finished()) {
						// 一つでもfinishしてなかったら判定やめる
						is_finished = false;
						break;
					}
				}
				if (is_finished) {
					return StateCode::GO_NEXT;
				}
			}
		}
		break;
	case '\b': // Backspace
		// cancel
		if (slot_selected != nullptr && selected_from != -1) {
			bottles[selected_from]->force_push(slot_selected);
			slot_selected = nullptr;
		}
		break;
	case 'q':
		return StateCode::EXIT;
	}
	return StateCode::PROCESSING;
}