#include <stdio.h>
#include <conio.h>
#include "ResultState.h"
#include "ScoreManager.h"

ResultState::ResultState() : score{ 0, 0 }, key(0) {}

StateCode ResultState::print() {
	printf("============== RESULT ==============\n\n");
	printf("%d times moved, %d seconds elapsed\n\n", score.move_count, score.play_sec);
	printf("====================================\n\n");
	printf("Press 'Enter' to return to title\n");
	printf("Press 'Q' to exit");

	key = _getch();
	if (0x0D == key) {
		return StateCode::GO_NEXT;
	}
	else if ('q' == key) {
		return StateCode::EXIT;
	}

	return StateCode::PROCESSING;
}

void ResultState::on_start() {
	score = ScoreManager::get_instance()->get_score();
}

void ResultState::on_end() {
	ScoreManager::get_instance()->set_score(0, 0);
}