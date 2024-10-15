#pragma once
#include<functional>
#include "Predicate.h"
#include "State.h"

namespace MathTeXlib::Logic
{
	class LogicUnknown : public MathTeXlib::Logic::Predicate
	{
		public:
			LogicUnknown() : MathTeXlib::Logic::Predicate { std::function<State()>{[](){return State::UNKNOWN;}} } {}
	};
}
