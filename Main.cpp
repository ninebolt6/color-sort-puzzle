#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <memory>
#include "StateBase.h"
#include "GameState.h"
#include "TitleState.h"
#include "ResultState.h"

int main()
{
	// �G�X�P�[�v�V�[�P���X��L����
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdOut, &mode);
	SetConsoleMode(hStdOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	// �J�[�\��������
	printf("\x1b[?25l");

	{
		// FIXME: �X�e�[�g�Ǘ����X�e�[�g�}�V���ɈϏ�������
		std::shared_ptr<StateBase> titleState(new TitleState());
		std::shared_ptr<StateBase> gameState(new GameState());
		std::shared_ptr<StateBase> resultState(new ResultState());

		// State���z������
		titleState->set_next_state(gameState);
		gameState->set_next_state(resultState);
		resultState->set_next_state(titleState);

		std::shared_ptr<StateBase> current_state = titleState;

		// init
		current_state->on_start();

		StateCode state_code;
		bool isEnded = false;
		while(!isEnded) {
			printf("\x1b[2J"); // ��ʃN���A
			printf("\x1b[0;0H"); // �J�[�\�����g�b�v�Ɉړ�

			state_code = current_state->print();
			switch (state_code) {
			case StateCode::EXIT:
				// �v���O�����I��
				isEnded = true;
				current_state->on_end();
				break;
			case StateCode::GO_NEXT:
				current_state->on_end();
				// ���̃X�e�[�g�ֈړ�
				current_state = current_state->get_next_state();
				// init
				current_state->on_start();
				break;
			case StateCode::PROCESSING:
				// noop
				break;
			}
		}
	}

	// �J�[�\����\��
	printf("\x1b[?25h");
	printf("\x1b[37m"); // reset color
	printf("\x1b[2J"); // ��ʃN���A
	printf("\x1b[0;0H"); // �J�[�\�����g�b�v�Ɉړ�
	return EXIT_SUCCESS;
}
