#pragma once
#include<functional>
#include "Predicate.h"
#include "State.h"

namespace MathTeXlib::Logic
{
	class LogicTrue : public MathTeXlib::Logic::Predicate
	{
		public:
			LogicTrue() : MathTeXlib::Logic::Predicate { std::function<State()>{[](){return State::TRUE;}} } {}
	};
}
