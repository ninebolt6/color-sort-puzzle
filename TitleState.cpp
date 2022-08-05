#include <stdio.h>
#include "TitleState.h"

TitleState::TitleState() : key(0) {}

StateCode TitleState::print() {
	printf("============== COLOR SORT PUZZLE ==============\n");
	printf("Press 'Enter' to start\n");
	printf("Press 'Q' to exit\n\n");
	printf("[���[��]\n");
	printf("�F�̑w��1�����o���A�ʂ̃X�y�[�X�ɓ���邱�Ƃ��ł���B\n");
	printf("��̃X�y�[�X�ɓ���邱�Ƃ̂ł���w��4���܂łł���B\n");
	printf("�F�̑w������ɂ́A�X�y�[�X���󂩁A���o���Ă���F��\n");
	printf("�����F�̑w���X�y�[�X�̍ŏ�ʂɂ���K�v������B");

	key = _getch();
	if (0x0D == key) {
		return StateCode::GO_NEXT;
	}
	else if ('q' == key) {
		return StateCode::EXIT;
	}

	return StateCode::PROCESSING;
}