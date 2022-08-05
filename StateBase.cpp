#include "StateBase.h"

StateBase::StateBase() : next_state(nullptr) {}

void StateBase::set_next_state(std::shared_ptr<StateBase>& state) {
	next_state = state;
}

std::shared_ptr<StateBase>& StateBase::get_next_state() {
	return next_state;
};