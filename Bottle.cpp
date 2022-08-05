#include "Bottle.h"

bool Bottle::push(Color * slot) {
	if (stack.size() == 4 || (stack.size() >= 1 && *(stack.front()) != *slot)) {
		return false;
	}
	stack.push_front(slot);
	return true;
}

bool Bottle::force_push(Color* slot) {
	if (stack.size() >= 4) {
		return false;
	}
	stack.push_front(slot);
	return true;
}

Color* Bottle::pop() {
	if (stack.size() == 0) {
		return nullptr;
	}
	Color* target = stack.front();
	stack.pop_front();
	return target;
}

const std::deque<Color*> Bottle::get_colors() const {
	return stack;
}

bool Bottle::is_finished() const {
	if (is_empty()) {
		return true;
	}
	if (is_full()) {
		for (int i = 1; i < 4; i++) {
			if (*stack[0] != *stack[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Bottle::is_full() const {
	return stack.size() == 4;
}

bool Bottle::is_empty() const {
	return stack.empty();
}