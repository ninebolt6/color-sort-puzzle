#include <stdio.h>
#include "TitleState.h"

TitleState::TitleState() : key(0) {}

StateCode TitleState::print() {
	printf("============== COLOR SORT PUZZLE ==============\n");
	printf("Press 'Enter' to start\n");
	printf("Press 'Q' to exit\n\n");
	printf("[ルール]\n");
	printf("色の層を1枚取り出し、別のスペースに入れることができる。\n");
	printf("一つのスペースに入れることのできる層は4枚までである。\n");
	printf("色の層を入れるには、スペースが空か、取り出している色と\n");
	printf("同じ色の層がスペースの最上位にある必要がある。");

	key = _getch();
	if (0x0D == key) {
		return StateCode::GO_NEXT;
	}
	else if ('q' == key) {
		return StateCode::EXIT;
	}

	return StateCode::PROCESSING;
}