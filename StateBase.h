#pragma once
#include <memory>
#include "StateCode.h"

class StateBase
{
public:
	StateBase();
	virtual ~StateBase() = default;

	virtual StateCode print() = 0;
	virtual void on_start() {}
	virtual void on_end() {}

	void set_next_state(std::shared_ptr<StateBase>& state);
	std::shared_ptr<StateBase>& get_next_state();

private:
	std::shared_ptr<StateBase> next_state;
};