#pragma once
#include<functional>
#include "Predicate.h"

namespace MathTeXlib::Logic
{
	class LogicFalse : public MathTeXlib::Logic::Predicate
	{
		public:
			LogicFalse() : MathTeXlib::Logic::Predicate { std::function<bool()>{[](){return false;}} } {} 
	};
}
