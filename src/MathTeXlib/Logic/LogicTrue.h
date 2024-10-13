#pragma once
#include<functional>
#include "Predicate.h"

namespace MathTeXlib::Logic
{
	class LogicTrue : public MathTeXlib::Logic::Predicate
	{
		public:
			LogicTrue() : MathTeXlib::Logic::Predicate { std::function<bool()>{[](){return true;}} } {}
	};
}
