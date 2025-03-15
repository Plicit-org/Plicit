#pragma once
#include<functional>
#include "Predicate.h"
#include "State.h"

namespace MathTeXlib::Logic
{
	class LogicFalse : public MathTeXlib::Logic::Predicate
	{
		public:
			LogicFalse() : MathTeXlib::Logic::Predicate { std::function<State()>{[](){return State::FALSE;}} } {} 
	};
}
